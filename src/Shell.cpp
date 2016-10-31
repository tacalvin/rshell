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
	// char* uname = getlogin();
	int status = 1;
	//register signal handler
	// signal(SIGINT,signalHandler);

	while(status)
	{
		// cout << uname << ">" << endl;
		cout << "windows$" << endl;
		vector<char*> cmds = parse();
		Base* cmd = buildCommand(cmds);
		cmd->evaluate();
		// cout <<"Status: "<< res << endl;
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

	//split using string sstream
	istringstream ss(line);
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
