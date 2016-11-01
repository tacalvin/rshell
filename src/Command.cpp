#include <iostream>
#include "./include/Command.h"
#include "./include/Base.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
using namespace std;
Command::Command(vector<char*> s)
{
  cmd = s;
}

int cd(char* args)
{
	int condition = chdir(args);
	return condition++;
}

void exitf()
{
	exit(0);
}


// Will return false if no erros and true if there are errors
bool Command::evaluate()
{
  if(!strcmp(cmd.at(0),"exit")) 
  {
	  exitf();
	  //return true;
  }
  if(!strcmp(cmd.at(0),"cd")) 
  {
	  int condition = chdir(cmd.at(1));
	  return !condition;
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
    exit(EXIT_FAILURE);

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
    }
    while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return status;
  }

  return true;
}
