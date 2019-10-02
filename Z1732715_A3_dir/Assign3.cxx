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
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

using namespace std;

void doPipe(char *buf)
{
  // process buff and get vars
  int i = 0, status,status2, pipefd[2], pid, grandChild;
  string realCommand1, realCommand2;
  char *command1, *command2;
  char *args1[32], *args2[32];

  command1 = strtok(buf, "||");
  command2 = strtok(NULL, "||");

  command1 = strtok(command1, " ");
  while (command1 != NULL)
  {
    if ( i == 0 )
    {
      realCommand1 = command1;
      args1[i] = command1;
    }
    else
    {
      args1[i] = command1;
    }

    command1 = strtok(NULL, " ");

    i++;
  }

	args1[i] = (char *) NULL;

  i = 0;
  
  command2 = strtok(command2, " ");
  while (command2 != NULL)
  {
    if ( i == 0 )
    {
      realCommand2 = command2;
      args2[i] = command2;
    }
    else
    {
      args2[i] = command2;
    }

    command2 = strtok(NULL, " ");

    i++;
  }
	args2[i] = (char *) NULL;
 
  // execute exec with forks and dup2 and pipes
	pipe(pipefd);

	if ((pid = fork()) <0)
	{
		printf("fork error");
	}
	/* child */
	else if (pid == 0)
	{
	 dup2(pipefd[1], 1);
	 close(pipefd[0]);
	 execlp(realCommand1.c_str(), realCommand1.c_str(), args1[1], (char *) NULL);
	 printf("couldn't execute: %s", buf);
	 exit(127);
	}
	/* parent */
	if ((grandChild = fork()) < 0)
	{
		printf("fork#2 error");
	}
	else if (grandChild == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		execlp(realCommand2.c_str(), realCommand2.c_str(), args2[1], (char *) NULL);
		printf("couldn't execute: %s", buf);
		exit(127);
	}

	close(pipefd[1]);

	if((grandChild = waitpid(grandChild, &status2, 0)) < 0)
	{
		printf("waitpid error in child");
	}

	if ( (pid = waitpid(pid, &status, 0)) < 0)
	{
		printf("waitpid error");
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
      exit(0);
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
        exit(-1);
      }

    }

  }

  return 0;

} 
