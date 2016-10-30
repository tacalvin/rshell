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
  vector<string> parse();
  Base* buildCommand();
//  ~Shell();
private:
};
#endif
