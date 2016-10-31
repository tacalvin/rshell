#ifndef Operator_hh
#define Operator_hh
#include "./Base.h"

class Operator : public Base
{
public:
  Operator(Base* left, Base* right);
  ~Operator();
  virtual bool evaluate() = 0;
protected:
  Base* right;
  Base* left;
};
#endif
