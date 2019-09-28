/***********************************************************
 CSCI 480 - Assignment 3 - Fall 2019
 
 Progammer: Sam Piecz
 Z-ID: Z1732715
 Section: 2 
 TA: Jingwan Li  
 Date Due: Sep 28, 2019 
 Purpose: Microshell Simulation. 
 ************************************************************/

#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

void doPipe()
{
  cout << "It's a pipe." << endl;
}

string getInput(string command)
{
  cout << "480shell>";
  getline(cin, command);
  return command;
}

void executeCommand(string command)
{
  string realCommand; 

  for ( auto x : command )
  {
    realCommand += x;
  }

  execlp(realCommand.c_str(), realCommand.c_str(), NULL);
}

int main()
{

  // Cool bool
  bool cool = true;

  // We cool?
  while(cool)
  {
    string command;
    command = getInput(command);

    // Should we stop?
    if(command.find("quit") != string::npos || command.find("q") != string::npos)
    {
      cool = false;
    }
    // If not stopping, see if pipe
    else if (command.find("||") != string::npos)
    {
      doPipe();
    }
    // If no pipe and no stop just do the command
    else
    {
      executeCommand(command);
    }
  } 

  return 0;
}
