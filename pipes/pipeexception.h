/**
 * 
 * Socket exception handling based on:
 * http://www.linuxhowtos.org/C_C++/socket.htm
 * http://cs.baylor.edu/~donahoo/practical/CSockets/practical/
 * 
 */

#include <cerrno>
#include <cstring>
#include <string>
#include <exception>

class PipeException: public std::exception {
public:
	PipeException(const std::string &m) throw()
	{
		message = std::string(m);
		message.append("\n");
		message.append(std::strerror(errno));
	}
	
	~PipeException() throw()
	{

	}

	const char *what() const throw()
	{
		return message.c_str();
	}

private:
	/* data */
	std::string message;
};