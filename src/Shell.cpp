#include "./headers/Shell.h"
#include "./headers/Base.h"
#include "./headers/Command.h"
#include <vector>
#include <pwd.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include <errno.h>
#include <csignal>
#include <deque>
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

 void signalHandler( int signum )
 {
    cout << "Interrupt signal (" << signum << ") received.\n";

    // cleanup and close up stuff here
    // terminate program

    exit(signum);

 }
void Shell::run()
{
	//getlogin does not work on windows bash atm
	char* uname = getpwuid(getuid())->pw_name;
	char hname[BUFFSIZE];
	gethostname(hname,BUFFSIZE);

	if(hname == NULL)
		perror("error getting hostname");
	cout << uname << "@" << hname  << "$ ";
	//register signal handler
	signal(SIGINT,signalHandler);
	string line;
	//cout << uname <<"@" << hname <<"$" ;
	while(getline(cin,line))
	{

		try 
		{
      if(line == "")
      {
        cout << uname << "@" << hname<<"$ ";
        continue;
      }
      
			stack<string> cmds = parse(line);
			//	cin.clear();
      //fseek(stdin,0,SEEK_END);	
      //eof = false;
				//continue;
			
			Base* cmd = buildCommand(cmds);
			cmd->evaluate();
    	}
    	catch (runtime_error& e)
    	{
    		cout << e.what() << endl;
    	}
    	
    	uname = getpwuid(getuid())->pw_name;
		//cout << endl;
    	cout << uname << "@" << hname  << "$ " ;
	}

}

Base* Shell::buildParenthesis(stack<string>& commandStack) {
	int counter = 1;
	deque<string> tempDeque;
	while (counter > 0) 
	{
		string tempString = commandStack.top();
		commandStack.pop();
		if (tempString == ")") 
		{
			counter++;
			tempDeque.push_front(tempString);
		}
		else if (tempString == "(")
		{
			counter--;
			if (counter > 0)
				tempDeque.push_front(tempString);
		}
		else
		{
			tempDeque.push_front(tempString);
		}
	}
	stack<string> dequeStack(tempDeque);

	return buildCommand(dequeStack);
}

Base* Shell::buildCommand(stack<string>& commandStack)
{
	stack<Base*> treeStack;
	while (!commandStack.empty())
	{
		string currString = commandStack.top();
		commandStack.pop();
		
		if (currString == ")") 
		{
			treeStack.push(buildParenthesis(commandStack));
		}
		else if (currString == ";")
		{
			Base* left = buildCommand(commandStack);
			Base* right = treeStack.top();
			treeStack.pop();
			treeStack.push(new SemiOperator(left, right));
		}
		else if (currString == "&&")
		{
			Base* left;
			if (commandStack.top() == ")")
			{
				commandStack.pop();
				left = buildParenthesis(commandStack);
			}
			else
			{
				left = new Command(convertCharVector(commandStack.top()));
				commandStack.pop();
			}
			Base* right = treeStack.top();
			treeStack.pop();
			treeStack.push(new AndOperator(left, right));
		}
		else if (currString == "||")
		{
			Base* left;
			if (commandStack.top() == ")")
			{
				commandStack.pop();
				left = buildParenthesis(commandStack);
			}
			else
			{
				left = new Command(convertCharVector(commandStack.top()));
				commandStack.pop();
			}
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
stack<string> Shell::parse(string line)
{

	char currChar;
	string delimiters = ";|&()";
	stack<string> commandStack;

	istringstream ss(line);
	int parenthesisStatus = 0;
	
	//shit solution, but simple, iterate through and increment for each (, decrement for each ), must be 0 and
	//should never go to negative if valid
	while(ss.get(currChar))
	{
		if (currChar == '(')
			parenthesisStatus++;
		else if (currChar == ')')
			parenthesisStatus--;
		
		if (parenthesisStatus < 0)
      {
      throw runtime_error("syntax error near unexpected token ')'");
      }
	}
	if (parenthesisStatus)
    {
      throw runtime_error("syntax error near unexpected token '('");
    }
  ss.clear();
	ss.str(line);
	
	// false = operator is not fine, true = operator fine
	bool operatorValid = false;
	string command = "";
	
	// the purpose of this loop is the create a vector of strings of individual
	// commands to parse seperately, operators are their own entries
	while(ss.get(currChar)) 
	{
		size_t delimStatus = delimiters.find(currChar);
		// if the current character is not a delimiter
		if (currChar =='#')
			break;
		if (delimStatus == string::npos && !ss.eof())
		{
			// add the character as part of the command
			command.push_back(currChar);
			if (currChar != ' ')
				operatorValid = true;
		}
		else
		{
			//if the current character is a delimiter candidate
			if (currChar == '(')
			{
				if (!operatorValid && !commandStack.empty()) throw runtime_error("syntax error near unexpected token '('");
				command = "(";
				cleanPush(commandStack, command);
				command = "";
			}
     
			else if (currChar == ')')
			{
				if (!operatorValid) throw runtime_error("syntax error near unexpected token ')'");
				if (commandStack.top() == "(") throw runtime_error("syntax error near unexpected token '('");
				cleanPush(commandStack, command);
				command = ")";
				cleanPush(commandStack, command);
				command = "";
			}
			else if (currChar == ';') 
			{
				if (!operatorValid) throw runtime_error("syntax error near unexpected token `;'");
				cleanPush(commandStack, command);
				command = ";";
				cleanPush(commandStack, command);
				command = "";
				operatorValid = false;
			}
			else if (currChar == '&' && ss.peek() == '&')
			{
				if (!operatorValid) throw runtime_error("syntax error near unexpected token `&&'");
				cleanPush(commandStack, command);
				command = "&&";
				cleanPush(commandStack, command);
				command = "";
				// remove extra &
				currChar = ss.get();
				operatorValid = false;
			}
			else if (currChar == '|' && ss.peek() == '|')
			{
				if (!operatorValid) throw runtime_error("syntax error near unexpected token `||'");
				cleanPush(commandStack, command);
				command = "||";
				cleanPush(commandStack, command);
				command = "";
				currChar = ss.get();
				operatorValid = false;
			}
			else 
			{
				command.push_back(currChar);
			}
		}
	}
	if (!operatorValid) throw runtime_error("syntax error near unexpected ending token");
	
	cleanPush(commandStack, command);
	//TODO: test case of what happens if there is a leading space

	//debug

	return commandStack;
}

void Shell::cleanPush(stack<string>& targetStack, string target)
{
	if (target == "" || target.find_first_not_of(' ') == string::npos) return;
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
		char* lineC = new char[command.size()];
		//char* lineC = new char(sizeof(command.c_str()));
		strcpy(lineC,command.c_str());
		s.push_back(lineC);
	}
	return s;
}
