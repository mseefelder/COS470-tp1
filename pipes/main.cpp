#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include "../utility/isPrime.h"
#include "../utility/cexception.h"

using namespace std;


/* Write some random text to the pipe. */

void producer(int interations, int file){
  cout << "Producing " << endl;
  //setup c++11 random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 10);

  int number = 1;
  FILE *stream;
  stream = fdopen(file,"w");
  if (stream == NULL)
  {
    throw CException("ERROR opening pipe.");
  }
  for (int i = 0; i < interations; i ++) {
    number += dis(gen);
    //printf("p: %i \n", number);
    fprintf(stream, "%i \n", number);
  }
  fprintf(stream, "%i \n", 0);
  fclose(stream);
}

void consumer(int file) {
  cout << "consuming" << endl;
  int number, recived;
  FILE *stream;
  stream = fdopen(file, "r");
  if(stream == NULL)
  if (stream == NULL)
  {
    throw CException("ERROR opening pipe.");
  }
  while(1) {
    recived = fscanf(stream, "%i \n", &number);
    if (recived < 0) 
    {
      throw CException("ERROR reading from pipe.");
    }
    if( number == 0){
      break;
    }
    if(isPrime(number)) {
      printf("%i is prime\n", number);
    } else {
      printf("%i is NOT prime\n", number);
    }
  }
  fclose(stream);
}


int main (int argc, char const *argv[]) {

  if (argc < 2)
  {
    cout<<"Usage is:\n"<<argv[0]<<
      " <amount of numbers to generate>"<<
      endl;
    return 0;
  }

  if (!isdigit(argv[1][0]))
  {
    cerr<<"Amount of numbers to generate should be a number!"<<endl;
    return 0;
  }
  int amount = atoi(argv[1]);

  pid_t pid;
  int mypipe[2];

  try
  {

    /* Create the pipe. */
    if (pipe (mypipe) < 0)
    {
      throw CException("Pipe failed.");
    }

    /* Create the child process. */
    pid = fork ();
    if (pid < (pid_t) 0)
    {
      throw CException("Fork failed.");
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
  if (pid == (pid_t) 0)
  {
     /* This is the child process.
        Close other end first. */
    close (mypipe[1]);
    try
    {
      consumer(mypipe[0]);
    }
    catch (std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
  }
  else
  {
    /* This is the parent process.
      Close other end first. */
    close (mypipe[0]);
    try
    {
      producer(amount, mypipe[1]);
    }
    catch (exception &e)
    {
      cerr << e.what() << endl;
    }

    return EXIT_SUCCESS;
  }
}
