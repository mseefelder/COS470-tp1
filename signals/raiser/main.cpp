#include <iostream> 
#include <string>
#include <sstream>
#include <csignal>

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
			kill(pid, sig);
		}
		catch (int e)
		{
			cout<<"Unable to send signal!"<<endl;
		}
		cout << "Signal sent!" << endl;

	}
	return 0;
}