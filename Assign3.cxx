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
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

using namespace std;

void doPipe(char *buf)
{
  char * d;
  int counter = 0;
  int pipe1[2], pipe2[2];
  bool firstPipe = true;
  char * pipeCommands[32];

  d = strtok(buf, "||");

  while (d != NULL)
  {
    pipeCommands[counter] = d;
    d = strtok(NULL, "||");
    counter++;
  }

  for(int i = 0; i < counter; i++) 
  {
    char * e;
    e = strtok(pipeCommands[i], " ");
    while (e != NULL)
    {
      cout << e << endl;
      e = strtok(NULL, " "); 
    }
  }


}

int main(void)
{
  bool cool = true;

  while (cool)
  {
    char buf[1024];
    printf("480shell> ");
    string realCommand;
    cin.getline(buf, sizeof(buf));
    string command (buf); 
    int status;
    char * args[32];
    char *p;
    pid_t pid;
    int count = 0;

    if (command.find("quit") != string::npos || command.find("q") != string::npos)
    {
      break;
    }
    else if (command.find("||") != string::npos)
    {
      doPipe(buf);
    }
    else
    {
      p = strtok(buf, " ");
      while (p != NULL)
      {
        if ( count == 0 )
        {
          realCommand = p;
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
        execvp(realCommand.c_str(), args);
      }

      if ( (pid = waitpid(pid, &status, 0)) < 0)
      {
        printf("waitpid error\n");  
        break;
      }

    }

  }

  return 0;

} 
