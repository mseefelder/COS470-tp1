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
 * CONSUMER
 *
*/

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "socketexception.h"

int main(int argc, char const *argv[])
{
	//check if port argument was provided
	if (argc < 2)
	{
		std::cout<<"Usage is: "<<argv[0]<<" <port>"<<std::endl;
		return 0;
	}

	try
	{
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
		 * Fill sockaddr_in with parameters
		 * sockaddr_in is defined on netinet/in.h
		 */
		struct sockaddr_in serv_addr = {};//initialize cleared struct
		//Replacing: int portno = atoi(argv[1]);
		int portno;
		std::stringstream tempss;
		tempss << argv[1];
		tempss >> portno;
          //replaced.
          /**
           *  htons: converts the unsigned short integer from host byte 
           * order to network byte order (netinet/in.h)
           */
          serv_addr.sin_port = htons(portno);
          serv_addr.sin_family = AF_INET;
          serv_addr.sin_addr.s_addr = INADDR_ANY;//(?)

     	/**
     	 *  Assigning a name to the socket:
     	 *  bind() assigns the address specified by a sockaddr struct to the 
     	 * socket referred to by the file descriptor sockfd. The size of the 
     	 * struct in bytes must be passed.
     	 * 
     	 *  It is normally necessary to assign a local address using bind() 
     	 *  before a SOCK_STREAM socket may receive connections.
     	 */
     	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
     	{
     		throw SocketException("ERROR while binding");
     	}

     	/**
     	 *  listen() marks the socket referred to by sockfd as a passive socket, 
     	 * that is, as a socket that will be used to accept incoming connection 
     	 * requests using accept().
     	 * 
     	 *  first argument is the listener socket's file descriptor
     	 *  second argument is the maximum length to which the queue of pending 
     	 *  connections for the socket may grow.
     	 *  
     	 *  On our case, we want only one connected client
     	 */
     	listen(sockfd, 1);

     	//Preparing client address for accept()
     	struct sockaddr_in cli_addr;
     	socklen_t clilen = sizeof(cli_addr);

     	/**
     	 *  The accept() system call extracts the first connection request on the 
     	 * queue of pending connections for the listening socket, creates a new 
     	 * connected socket, and returns a new file descriptor referring to that 
     	 * socket. The newly created socket is not in the listening state.
     	 * 
     	 *  If no pending connections are present on the queue, and the socket is 
     	 * not marked as nonblocking, accept() blocks the caller until a 
     	 * connection is present.
     	 * 
     	 * 	first argument is the a listening socket's file descriptor
     	 * 	second argument is a pointer to a sockaddr structure. This structure 
     	 * is filled in with the address of the peer socket, as known to the 
     	 * communications layer.
     	 *  third argument is a value-result argument: the caller must initialize 
     	 * it to contain the size (in bytes) of the structure pointed to by the 
     	 * second argument.
     	 * 
     	 * 	In our case, as we didn't set our socket as nonblocking, accept() is a
     	 * blocking call.
     	 */
     	int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     	if (newsockfd < 0) 
     	{
     		throw SocketException("ERROR on accept()");
     	}

     	//initialize a clear char buffer for receiving messages
     	char buffer[256] = {};

          /**/
          std::cout<<"Server up and connected..."<<std::endl;
          bool keepReading = true;
          int n = -1;
          int number = 0;
          while(keepReading)
          {
               std::cout<<"Server waiting for message..."<<std::endl;
               n = recv(newsockfd,buffer,255,0);//blocking receive call
               if (n < 0)
               {
                    throw SocketException("ERROR reading from socket");
               }
               else if (n == 0)
               {
                    throw SocketException("Peer has disconnected!");
               }

               tempss.clear();
               tempss.str(buffer);
               number = std::stoi(tempss.str());

               std::cout<<"Message received: "<<number<<std::endl;
               if (number == 0)
               {
                    keepReading = false;
               }
               std::memset(buffer, 0, 256);
               n = write(newsockfd,"1",1);
               if (n < 0)
               {
                    throw SocketException("ERROR writing on socket");
               }
          }
          /**/
     	close(newsockfd);
     	close(sockfd);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}