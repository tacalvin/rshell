#include "./include/Shell.h"
#include "./include/Base.h"
#include "./include/Command.h"
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string.h>

const int BUFFSIZE = 1024;


Shell::Shell()
{

}

void Shell::run()
{
	//getlogin does not work on windows bash atm
	// char* uname = getlogin();
	int status = 1;

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


	// for(unsigned i =0; i < s.size(); i++)
	// {
	// 		cout << s.at(i) << endl;
	// }

	return s;
}
