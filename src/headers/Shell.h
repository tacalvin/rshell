#ifndef Shell_hh
#define Shell_hh
#include <vector>
#include <string>
#include <stack>
#include "./Base.h"
#include "./SemiOperator.h"
#include "./AndOperator.h"
#include "./OrOperator.h"
using namespace std;
class Shell
{
public:
  Shell();
  void run();
  stack<string> parse(string line);
  Base* buildCommand(stack<string>& commandStack);
//  void (*signal(int signo, void (*func )(int)))(int);
//  ~Shell();
private:
  void cleanPush(stack<string>&, string);
  vector<char*> convertCharVector(string command);
};
#endif
