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
	string realCommand, token, delimiter = " ";
	vector<string> buffer; 
	size_t pos = 0;
	int count = 0;

	while ((pos = command.find(delimiter)) != std::string::npos)
	{
		token = command.substr(0, pos);
		if ( count == 0 )
		{
			realCommand = token;
		}
		buffer.push_back(token);
		command.erase(0, pos + delimiter.length());
		cout << token << endl;
		count++;
	}

	char * args[buffer.size()];
	count = 0;
	for ( auto x : buffer )
	{
		char * writable = new char[x.size() + 1];
		copy(x.begin(), x.end(), writable);
		writable[x.size()] = '\0'; 
		args[count] = writable;
		delete[] writable;
		count++;
	}
	args[count] = (char *) NULL;
	
	execvp(realCommand.c_str(), args);

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
