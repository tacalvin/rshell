#ifndef OrOperator_hh
#define OrOperator_hh
#include "./Operator.h"

class OrOperator : public Operator
{
public:
  OrOperator(Base* left, Base* right);
  ~OrOperator();
  bool evaluate();
};
#endif
