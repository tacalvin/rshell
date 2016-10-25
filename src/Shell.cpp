#include "./include/Shell.h"
#include <vector>
#include <iostream>
#include <unistd.h>

const int BUFFSIZE = 1024;


Shell::Shell()
{

}

void Shell::run()
{
	char* uname = getlogin();
	int status = 1;

	while(status)
	{
		cout << uname << ">" << endl;
		parse();
	}
}

vector<string> Shell::parse()
{
	//c-string ver
	//char* line[BUFFSIZE];
	//getline(line,BUFFSIZE);

	
	string line;
	getline(cin,line);
	cout << line << endl;
}
