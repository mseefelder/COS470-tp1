#include <iostream> 
#include <string>
#include <sstream>
#include <csignal>
#include "../../utility/cexception.h"

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		cout<<"Pass target pid and desired signal code as parameters: [pid] [code]"<<endl;
	}
	else
	{
		int pid;
		int sig;
		stringstream(argv[1]) >> pid;
		stringstream(argv[2]) >> sig;
		cout << "Sending signal "<<sig<<" to process "<<pid<<endl; 
		try
		{
			int status = kill(pid, sig);
			if (status < 0)
			{
				throw CException("ERROR while sending signal.");
			}
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			return 0;
		}
		cout << "Signal sent!" << endl;

	}
	return 0;
}