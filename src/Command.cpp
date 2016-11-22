#include <iostream>
#include "./headers/Command.h"
#include "./headers/Base.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

using namespace std;
Command::Command(vector<char*> s)
{
  cmd = s;
}

Command::~Command()
{
	for(vector<char*>::iterator it = cmd.begin(); it != cmd.end(); it++)
		delete *it;
	cmd.clear();
}

int cd(char* args)
{
	int condition = chdir(args);
  cout << "CD condition: " << condition << endl;
	return condition++;
}

void exitf()
{
	_exit(0);
}

bool testf(vector<char *> cmds)
{
  //remove either test or [] from vector
  if(!strcmp(cmds.at(0),"test"))
    {
      cmds.erase(cmds.begin());
    }
  else
    {
      cmds.erase(cmds.begin());
      cmds.erase(cmds.end()-1);
    }

  //struct stat is needed for stat()
  struct stat fileStat; //= malloc(sizeof(struct stat));
  int fstatus = stat(cmds.back(),&fileStat);


  //cout << "File exisits: " << fstatus << endl;
  //cout << "STMODE:" << fileStat.st_mode << endl;
  //cout <<"DIRFILE TEST:" << (fileStat.st_mode & S_IFDIR)   << endl;
  //cout <<"REGFILE TEST:" << (fileStat.st_mode & S_IFREG)   << endl;
  //-e checks if the file/directory exists
  //-f checks if the file/directory exists and is a regular file
  //-d checks if the file/directory exists and is a directory
  //cout <<"S_IFREG:"<< S_IFREG << endl;
  //cout <<"S_IFDIR:"<< S_IFDIR << endl;
  
  //check file
  if(fstatus == -1)
    {
      cout <<"(False)" << endl;
      return false;
    }
  if(!strcmp(cmds.at(0),"-f"))
    {
      int res = S_ISREG(fileStat.st_mode);
      //  cout <<"Result:"<< (bool)res << endl;
      if(res)
        cout << "(True)" <<endl;
      else
        cout << "(False)" << endl;
      //return res;
      return S_ISREG(fileStat.st_mode);
    }
  //check if dir
  else if(!strcmp(cmds.at(0),"-d"))
    {
      int res = S_ISDIR(fileStat.st_mode);
      //cout <<"Result:" << (bool)res << endl;
      if(res)
        cout << "(True)" <<endl;
      else
        cout << "(False)" << endl;
      return S_ISDIR(fileStat.st_mode);
    }
  //check existance test "-e"
  //fstatus+1 because stat returns 0 if it does exist
    cout << "(True)" <<endl;
  return true;

  //S_IFREG
  //S_IFDIR
  

}

// Will return false if no erros and true if there are errors
bool Command::evaluate()
{
  cout << "Command " << endl;
  if(cmd.size() == 0)
  	return false;

  if(!strcmp(cmd.at(0),"exit")) 
  {
	  exitf();
	  //return true;
  }

  if(!strcmp(cmd.at(0),"cd")) 
  {
    //size 1 so cd
    if(cmd.size())
      {
        
        char* home;
        int condition = chdir(home);
        return condition++;
      }
    //if cd -
    if(!strcmp(cmd.at(1),"-"))
      {
        int condition = chdir("..");
        return condition++;
      }
	  int condition = chdir(cmd.at(1));
	  return condition++;
  }
  //check test
  if(!strcmp(cmd.at(0),"[")||!strcmp(cmd.at(0),"test"))
    {
      //inverted since false if no errors but testf returns true if true
      return !testf(cmd);
    }



  pid_t pid, wpid;
  int status;
  //execvp needs a null terminated char **
  cmd.push_back(NULL);
  //using internal vector sturcture
  char** args = &cmd[0];
  pid = fork();
	

  if (pid == 0)
  {
    // Child process
    int res = execvp(args[0], args);
    if (res == -1)
    {
      perror("Exec failed");
    }
    _exit(-1);

  }
  else if (pid < 0)
  {
    // Error forking
    perror("Forking Failed");
    
    return true;
  }
  else
  {
    // Parent process
    do
    {
      wpid = waitpid(pid, &status, WUNTRACED);
      if(wpid == -1)
      	perror("error waiting");
    }
    while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return status;
  }

  return true;
}
