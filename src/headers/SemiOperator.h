#ifndef SemiOperator_hh
#define SemiOperator_hh
#include "./Operator.h"

class SemiOperator : public Operator
{
public:
  SemiOperator(Base* left, Base* right);
  ~SemiOperator();
  bool evaluate();
};
#endif
