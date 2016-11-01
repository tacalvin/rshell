#ifndef AndOperator_hh
#define AndOperator_hh
#include "./Operator.h"

class AndOperator : public Operator
{
public:
  AndOperator(Base* left, Base* right);
  ~AndOperator();
  bool evaluate();
};
#endif
