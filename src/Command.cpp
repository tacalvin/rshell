#include <iostream>
#include "./include/Command.h"
#include "./include/Base.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
Command::Command(vector<char*> s)
{
  cmd = s;
}

// Will return false if no erros and true if there are errors
bool Command::evaluate()
{
  pid_t pid, wpid;
  int status;
  char** args = &cmd[0];
  pid = fork();
  if (pid == 0)
  {
    cout << "Here" << endl;
    // Child process
    if (execvp(args[0], args) == -1)
    {
      cout << "Error executing" << endl;

    }
    exit(EXIT_FAILURE);
    
  }
  else if (pid < 0)
  {
    // Error forking
    cout <<"Error Forking" << endl;
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
