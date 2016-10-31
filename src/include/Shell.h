#ifndef Shell_hh
#define Shell_hh
#include <vector>
#include <string>
#include "./Base.h"
using namespace std;
class Shell
{
public:
  Shell();
  void run();
  vector<char*> parse();
  Base* buildCommand(vector<char*> cmds);
  void (*signal(int signo, void (*func )(int)))(int);
//  ~Shell();
private:
};
#endif
