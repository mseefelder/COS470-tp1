#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>

using namespace std;


void signal_callback(int signum){

  cout << "caught signal" << signum << endl;
  if(signum == 2){
    exit(signum);
  }
  return ;

}

  int main () {

    signal(SIGHUP, signal_callback);
    signal(SIGINT, signal_callback);
    signal(SIGQUIT,signal_callback);
    signal(SIGILL, signal_callback);
    signal(SIGTRAP, signal_callback);
    signal(SIGABRT, signal_callback);
    signal(SIGBUS, signal_callback);
    signal(SIGFPE, signal_callback);
    signal(SIGKILL, signal_callback);
    signal(SIGUSR1, signal_callback);
    signal(SIGSEGV, signal_callback);
    signal(SIGUSR2, signal_callback);
    signal(SIGPIPE, signal_callback);
    signal(SIGALRM, signal_callback);
    signal(SIGTERM, signal_callback);
    signal(SIGSTKFLT, signal_callback);
    signal(SIGCHLD, signal_callback);
    signal(SIGCONT, signal_callback);
    signal(SIGSTOP, signal_callback);
    signal(SIGTSTP, signal_callback);
    signal(SIGTTIN, signal_callback);
    signal(SIGTTOU, signal_callback);
    signal(SIGURG, signal_callback);
    signal(SIGXCPU, signal_callback);
    signal(SIGXFSZ, signal_callback);
    signal(SIGVTALRM, signal_callback);
    signal(SIGPROF, signal_callback);
    signal(SIGWINCH, signal_callback);
    signal(SIGIO, signal_callback);
    signal(SIGPWR, signal_callback);
    signal(SIGSYS, signal_callback);
    signal(SIGRTMIN, signal_callback);
    signal(SIGRTMIN+1, signal_callback);
    signal(SIGRTMIN+2, signal_callback);
    signal(SIGRTMIN+3, signal_callback);
    signal(SIGRTMIN+4, signal_callback);
    signal(SIGRTMIN+5, signal_callback);
    signal(SIGRTMIN+6, signal_callback);
    signal(SIGRTMIN+7, signal_callback);
    signal(SIGRTMIN+8, signal_callback);
    signal(SIGRTMIN+9, signal_callback);
    signal(SIGRTMIN+10, signal_callback);
    signal(SIGRTMIN+11, signal_callback);
    signal(SIGRTMIN+12, signal_callback);
    signal(SIGRTMIN+13, signal_callback);
    signal(SIGRTMIN+14, signal_callback);
    signal(SIGRTMIN+15, signal_callback);
    signal(SIGRTMAX-14, signal_callback);
    signal(SIGRTMAX-13, signal_callback);
    signal(SIGRTMAX-12, signal_callback);
    signal(SIGRTMAX-11, signal_callback);
    signal(SIGRTMAX-10, signal_callback);
    signal(SIGRTMAX-9, signal_callback);
    signal(SIGRTMAX-8, signal_callback);
    signal(SIGRTMAX-7, signal_callback);
    signal(SIGRTMAX-6, signal_callback);
    signal(SIGRTMAX-5, signal_callback);
    signal(SIGRTMAX-4, signal_callback);
    signal(SIGRTMAX-3, signal_callback);
    signal(SIGRTMAX-2, signal_callback);
    signal(SIGRTMAX-1, signal_callback);
    signal(SIGRTMAX, signal_callback);

    while(1) {
      printf("Program processing stuff here. \n");
      sleep(1);

    }

    return EXIT_SUCCESS;

  }
