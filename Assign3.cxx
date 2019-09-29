/***********************************************************
 CSCI 480 - Assignment 3 - Fall 2019
 
 Progammer: Sam Piecz
 Z-ID: Z1732715
 Section: 2 
 TA: Jingwan Li  
 Date Due: Sep 28, 2019 
 Purpose: Microshell Simulation. 
 ************************************************************/

#include <iostream>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

using namespace std;

void doPipe(char *buf)
{
  char * ar1[32], * ar2[32];
  char * p, * p2;
  int counter = 0;
  int pipe1[2], pipe2[2];
  bool firstPipe = true;

  p = strtok(buf, "||");
  while (p != NULL)
  {
    if( firstPipe == true)
    {
      p2 = strtok(p, " ");
      while (p2 != NULL)
      {
        ar1[counter] = p2;     
        p2 = strtok(NULL, " ");
        counter++;
      }
      firstPipe = false;
      counter = 0;
    }
    else
    {
      p2 = strtok(p, " ");
      while (p2 != NULL)
      {
        ar2[counter] = p2;     
        p2 = strtok(NULL, " ");
        counter++;
      }
      counter = 0;
    }
  }
  cout << "ar1" << endl;
  for ( auto x : ar1 )
    cout << x << endl;

}

int main(void)
{
  bool cool = true;

  while (cool)
  {
    char buf[1024];
    printf("480shell> ");
    string command; 
    cin.getline(buf, sizeof(buf));
    int status;
    char * args[32];
    char *p;
    pid_t pid;
    int count = 0;
    p = strtok(buf, " ");
    while (p != NULL)
    {
      if (strcmp(p, "quit") == 0 || strcmp(p, "q") == 0)
      {
        cool = false;
      }
      else if (strcmp(p, "||") == 0)
      {
        doPipe(buf);
      }
      else if ( count == 0 )
      {
        command = p;
        args[count] = p;
        count++;
      }
      else
      {
        args[count] = p;
        count++;
      }
      p = strtok(NULL, " ");
    }
    args[count] = (char *) NULL;

    if ( (pid = fork()) < 0 )
    {
			printf("fork error");
    }
    else if ( pid == 0 )
    {
      execvp(command.c_str(), args);
    }
    if ( (pid = waitpid(pid, &status, 0)) < 0)
    {
			printf("waitpid error");  
      cool = false;
    }
  }

  return 0;

} 
