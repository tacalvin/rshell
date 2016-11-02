#include "./headers/Shell.h"
#include "./headers/Base.h"
#include "./headers/Command.h"
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <csignal>
#include <stdexcept>

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
	if(uname == NULL)
		perror("error getting login");
	char hname[BUFFSIZE];
	gethostname(hname,BUFFSIZE);

	if(hname == NULL)
		perror("error getting hostname");
	
	int status = 1;
	//register signal handler
	// signal(SIGINT,signalHandler);

	while(status)
	{

		cout << uname << "@" << hname  << "$" << endl;
		
		stack<string> cmds = parse();
		Base* cmd = buildCommand(cmds);
		cmd->evaluate();
		// cout <<"Status: "<< res << endl;
		uname = getlogin();
		gethostname(hname,BUFFSIZE);
	}
}

Base* Shell::buildCommand(stack<string>& commandStack)
{
	stack<Base*> treeStack;
	while (!commandStack.empty())
	{
		string currString = commandStack.top();
		commandStack.pop();
		
		if (currString == ";")
		{
			// Base* left = new Command(convertCharVector(commandStack.top()));
			// commandStack.pop();
			// Base* right = treeStack.top();
			// treeStack.pop();
			// treeStack.push(new SemiOperator(left, right));
			Base* right = treeStack.top();
			treeStack.pop();
			Base* left = buildCommand(commandStack);
			treeStack.push(new SemiOperator(left, right));
		}
		else if (currString == "&&")
		{
			Base* left = new Command(convertCharVector(commandStack.top()));
			commandStack.pop();
			Base* right = treeStack.top();
			treeStack.pop();
			treeStack.push(new AndOperator(left, right));
		}
		else if (currString == "||")
		{
			Base* left = new Command(convertCharVector(commandStack.top()));
			commandStack.pop();
			Base* right = treeStack.top();
			treeStack.pop();
			treeStack.push(new OrOperator(left, right));
		}
		else
		{
			treeStack.push(new Command(convertCharVector(currString)));
		}
	}
	
	if (treeStack.size() != 1) throw runtime_error("tempstack building didn't work.");
	return treeStack.top();
}
stack<string> Shell::parse()
{
	//c-string ver
	//char* line[BUFFSIZE];
	//getline(line,BUFFSIZE);
	//vector<char*> s;

	//get all input as a single line
	string line;
	getline(cin,line);
	char currChar;
	string delimiters = ";|&";
	stack<string> commandStack;

	istringstream ss(line);
	
	string command = "";
	
	// the purpose of this loop is the create a vector of strings of individual
	// commands to parse seperately, operators are their own entries
	while(ss.get(currChar)) 
	{
		size_t delimStatus = delimiters.find(currChar);
		// if the current character is not a delimiter
		if (currChar =='#')
			break;
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
				cleanPush(commandStack, command);
				command = ";";
				cleanPush(commandStack, command);
				command = "";
			}
			else if (currChar == '&' && ss.peek() == '&')
			{
				cleanPush(commandStack, command);
				command = "&&";
				cleanPush(commandStack, command);
				command = "";
				// remove extra &
				currChar = ss.get();
			}
			else if (currChar == '|' && ss.peek() == '|')
			{
				cleanPush(commandStack, command);
				command = "||";
				cleanPush(commandStack, command);
				command = "";
				currChar = ss.get();
			}
			else 
			{
				command.push_back(currChar);
			}
		}
	}
	cleanPush(commandStack, command);
	//TODO: test case of what happens if there is a leading space

	//debug
	cout << "LINE: " << line <<endl;

	return commandStack;
}

void Shell::cleanPush(stack<string>& targetStack, string target)
{
    target.erase(0, target.find_first_not_of(' '));
    target.erase(target.find_last_not_of(' ') + 1);
	targetStack.push(target);
}

vector<char*> Shell::convertCharVector(string command) 
{
	vector<char*> s;
	istringstream ss(command);
	
	//since char** is needed converting const char* to char* via copying
	while(getline(ss,command,' '))
	{
		//create new char* of size line
		char* lineC = new char(sizeof(command.c_str()));
		strcpy(lineC,command.c_str());
		s.push_back(lineC);
	}
	return s;
}
