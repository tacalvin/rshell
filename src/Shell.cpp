#include "./include/Shell.h"
#include "./include/Base.h"
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sstream>

const int BUFFSIZE = 1024;


Shell::Shell()
{

}

void Shell::run()
{
	// char* uname = getlogin();
	int status = 1;

	while(status)
	{
		// cout << uname << ">" << endl;
		cout << "windows$" << endl;
		vector<string> cmd = parse();
		// Base* cmd = buildCommand(cmd);
		// status = cmd.evaluate();
	}
}

// Base* Shell::buildCommand(vector<string> cmd)
// {
//
// }
vector<string> Shell::parse()
{
	//c-string ver
	//char* line[BUFFSIZE];
	//getline(line,BUFFSIZE);
	vector<string> s;

	//get all input as a single line
	string line;
	getline(cin,line);

	//split using string sstream
	istringstream ss(line);
	while(getline(ss,line,' '))
		s.push_back(line);

	for(unsigned i =0; i < s.size(); i++)
	{
			cout << s.at(i) << endl;
	}

	return s;
}
