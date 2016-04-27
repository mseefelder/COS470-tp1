/*
 * 
 * Socket code based on tutorial found on:
 * http://tldp.org/LDP/LG/issue74/tougher.html
 * http://www.linuxhowtos.org/C_C++/socket.htm
 * 
 * http://linux.die.net/man/2/socket
 * http://linux.die.net/man/2/bind
 * http://linux.die.net/man/2/accept
 * http://linux.die.net/man/2/listen
 *
 * compile with -std=c++11
*/

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <random>
#include "socketexception.h"

int main(int argc, char const *argv[])
{
	//check if port argument was provided
	if (argc < 4)
	{
		std::cout<<"Usage is: "<<argv[0]<<"<hostname> <port> <# of messages>"<<std::endl;
		return 0;
	}

	try
	{
		//Number of messages that will be sent by producer:
		int messageNum;
		std::stringstream tempss;
		tempss << argv[3];
		tempss >> messageNum;

		/**
		*  Creates socket that: 
		*  Uses IPv4 internet protocols (AF_INET defined on sys/socket.h)
		*  Provides sequenced, reliable, two-way, connection-based byte streams. 
		* (SOCK_STREAM defined on sys/socket.h)
		*  Uses TCP protocol (IPPROTO_TCP defined on netinet/in.h)
		* 
		*  sockfd stands for socket file descriptor, which is the return value of
		* socket().
		*/
		int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockfd < 0)
		{
			throw SocketException("ERROR while opening socket");
		}

		/**
		 * 
		 */
		struct hostent *server;
		server = gethostbyname(argv[1]);
		if (server == NULL) 
		{
	        throw SocketException("ERROR, no such host\n");
	    }

		/**
		 * Fill sockaddr_in with parameters
		 * sockaddr_in is defined on netinet/in.h
		 */
		struct sockaddr_in serv_addr = {};//initialize cleared struct
		//Replacing: int portno = atoi(argv[2]);
		int portno;
		tempss.str("");
		tempss.clear();
		tempss << argv[2];
		tempss >> portno;
		//replaced.
     	serv_addr.sin_family = AF_INET;
     	/**
     	 *  Replacing: bcopy((char *)server->h_addr, 
     	 * (char *)&serv_addr.sin_addr.s_addr, server->h_length);
     	 */
     	//serv_addr.sin_addr.s_addr = (char *)server->h_addr;
     	std::memcpy((char *)&serv_addr.sin_addr.s_addr, 
     		(char *)server->h_addr, server->h_length);
     	//replaced(?)
     	/**
     	 *  htons: converts the unsigned short integer from host byte 
     	 * order to network byte order (netinet/in.h)
     	 */
     	serv_addr.sin_port = htons(portno);

     	/**
     	 *  connect()
     	 */
     	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
     	{
     		throw SocketException("ERROR while connecting");
     	}


     	/**/
     	//initialize a clear char buffer for receiving messages
     	std::cout<<"Client ready and running!"<<std::endl;
     	char buffer[256] = {};

     	//setup c++11 random number generator
     	std::random_device rd;
    	std::mt19937 gen(rd());
    	std::uniform_int_distribution<> dis(1, 6);

     	int n = -1;
     	int randNo = 1;

     	for (int i = 1; i < messageNum; ++i)
     	{
     		//add pseudo-random integer to randNo
     		randNo += dis(gen);
     		std::string number = std::to_string(randNo);
     		n = write(sockfd, number.c_str(), number.length());
     		if (n < 0)
     		{
			throw SocketException("ERROR writing on socket");
     		}
     		std::cout<<"Message sent!"<<std::endl;
     		n = recv(sockfd,buffer,255,0);
     		if (n < 0)
     		{
				throw SocketException("ERROR reading from socket");
     		}
     		else if (n == 0)
     		{
     			throw SocketException("Peer has disconnected!");
     		}
     		std::cout<<"Response: "<<buffer<<std::endl;
     		std::memset(buffer, 0, 256);
     	}
     	n = write(sockfd,"0",1);
     	if (n < 0)
     	{
			throw SocketException("ERROR writing on socket");
     	}
     	/**/

     	close(sockfd);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}