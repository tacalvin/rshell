#ifndef COMMAND_H
#define COMMAND_H
#include "./Base.h"
#include <vector>
#include <string>
using namespace std;
class Command : public Base
{
public:
  Command(vector<char*> s);
  ~Command();
  bool evaluate();
private:
  vector<char*> cmd;
};

#endif
