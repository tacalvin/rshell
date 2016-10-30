#ifndef COMMAND_H
#define COMMAND_H
#include "./Base.h"
#include <vector>
#include <string>
using namespace std;
class Command : public Base
{
public:
  Command(string s);
  bool evaluate();
private:
  vector<string> cmd;
};

#endif
