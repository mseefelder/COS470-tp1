#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include "isPrime.h"

using namespace std;


/* Write some random text to the pipe. */

void producer(int interations, int file){
  cout << "producing " << endl;
  int number = 0;
  FILE *stream;
  stream = fdopen(file,"w");
  for (int i = 0; i < interations; i ++) {
    int new_random = rand() % 10 + 1 ;
    number += new_random;
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
  if(stream == NULL) perror("ERROR OPENING PIPE");
  while(1) {
    recived = fscanf(stream, "%i \n", &number);
    if (recived < 0) perror("Erro na leitura");
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

void read_from_pipe (int file) {
  FILE *stream;
  int c;
  stream = fdopen (file, "r");
  while ((c = fgetc (stream)) != EOF)
    putchar (c);
  fclose (stream);
}




int main (void) {
  pid_t pid;
  int mypipe[2];

  /* Create the pipe. */
  if (pipe (mypipe))
  {
    fprintf (stderr, "Pipe failed.\n");
    return EXIT_FAILURE;
  }

  /* Create the child process. */
  pid = fork ();
  if (pid == (pid_t) 0)
  {
     /* This is the child process.
        Close other end first. */
    close (mypipe[1]);
    //read_from_pipe (mypipe[0]);
    consumer(mypipe[0]);
    return EXIT_SUCCESS;
  }
  else if (pid < (pid_t) 0)
  {
     /* The fork failed. */
    fprintf (stderr, "Fork failed.\n");
    return EXIT_FAILURE;
  }
  else
  {
    /* This is the parent process.
      Close other end first. */
    close (mypipe[0]);
    //    write_to_pipe (mypipe[1]);
    producer(5000000, mypipe[1]);
    return EXIT_SUCCESS;
  }
}
