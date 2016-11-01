#include "./include/Shell.h"
#include "./include/Base.h"
#include "./include/Command.h"
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <csignal>

const int BUFFSIZE = 1024;
const char* AND = "&&";
const char* OR = "||";
const char* SEMI = ";";
const char* REDIRL = "<";
const char* REDIRR = ">";


Shell::Shell()
{
	//do configuration stuff here
}

// void Shell::signalHandler( int signum )
// {
//    cout << "Interrupt signal (" << signum << ") received.\n";
//
//    // cleanup and close up stuff here
//    // terminate program
//
//    exit(signum);
//
// }
void Shell::run()
{
	//getlogin does not work on windows bash atm
	char* uname = getlogin();
	char hname[BUFFSIZE];
	gethostname(hname,BUFFSIZE);
	int status = 1;
	//register signal handler
	// signal(SIGINT,signalHandler);

	while(status)
	{

		cout << uname << "@" << hname  << "$" << endl;
		// cout << "windows$" << endl;
		vector<char*> cmds = parse();
		Base* cmd = buildCommand(cmds);
		cmd->evaluate();
		// cout <<"Status: "<< res << endl;
		uname = getlogin();
		gethostname(hname,BUFFSIZE);
	}
}

Base* Shell::buildCommand(vector<char*> args)
{
	//build base tree
	return new Command(args);
	// for(unsigned i = 0; i < cmd.size();i++)
	// {
	//
	// }
}
vector<char*> Shell::parse()
{
	//c-string ver
	//char* line[BUFFSIZE];
	//getline(line,BUFFSIZE);
	vector<char*> s;

	//get all input as a single line
	string line;
	getline(cin,line);
	char currChar = '';
	string delimiters = ";|&";
	vector<string> commandVector;

	istringstream ss(line);
	string command = "";
	
	// the purpose of this loop is the create a vector of strings of individual
	// commands to parse seperately, operators are their own entries
	while(ss.get(currChar)) 
	{
		size_t delimStatus = delimiter.find(currChar);
		// if the current character is not a delimiter
		if (delimStatus == string::npos)
		{
			// add the character as part of the command
			command.push_back(currChar);
		}
		else
		{
			//if the current character is a delimiter candidate
			if (currChar == ';') 
			{
				commandVector.push_back(command);
				command = ";";
				commandVector.push_back(command);
				command = "";
			}
			else if (currChar == '&' && ss.peek() == '&')
			{
				commandVector.push_back(command);
				command = "&&";
				commandVector.push_back(command);
				command = "";
				// remove extra &
				currChar = ss.get();
			}
			else if (currChar == '|' && ss.peek() == '|')
			{
				commandVector.push_back(command);
				command = "||";
				commandVector.push_back(command);
				command = "";
				currChar = ss.get();
			}
			else 
			{
				command.push_back(currChar);
			}
		}
	}
	
	//TODO: test case of what happens if there is a leading space

	//split using string sstream
	ss.str("");
	ss.clear();
	ss.str(line);
	
	//since char** is needed converting const char* to char* via copying
	while(getline(ss,line,' '))
	{
		//create new char* of size line
		char* lineC= new char(sizeof(line.c_str()));
		strcpy(lineC,line.c_str());
		s.push_back(lineC);
	}

	cout << s.size() << endl;


	return s;
}
