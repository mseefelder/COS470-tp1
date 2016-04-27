#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include "../utility/isPrime.h"
#include "pipeexception.h"

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
    throw PipeException("ERROR opening pipe.");
  }
  for (int i = 0; i < interations; i ++) {
    number += dis(gen);
    printf("p: %i \n", number);
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
    throw PipeException("ERROR opening pipe.");
  }
  while(1) {
    recived = fscanf(stream, "%i \n", &number);
    if (recived < 0) 
    {
      throw PipeException("ERROR reading from pipe.");
    }
    if( number == 0){
      break;
    }
    if(isPrime(number)) {
      printf("c true :%i \n", number);
    } else {
      printf("c false :%i \n", number);
    }
  }
  fclose(stream);
}




int main (void) {
  pid_t pid;
  int mypipe[2];

  try
  {
    /* Create the pipe. */
    if (pipe (mypipe) < 0)
    {
      throw PipeException("Pipe failed.");
    }

    /* Create the child process. */
    pid = fork ();
    if (pid < (pid_t) 0)
    {
      throw PipeException("Fork failed.");
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
      producer(1000, mypipe[1]);
    }
    catch (std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
  }
}
