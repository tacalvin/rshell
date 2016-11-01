#include "./include/SemiOperator.h"

SemiOperator::SemiOperator(Base* left, Base* right) : Operator(left, right)
{}

SemiOperator::~SemiOperator()
{}

bool SemiOperator::evaluate() 
{
    bool leftResult = left->evaluate();
    bool rightResult = right->evaluate();
    return leftResult && rightResult;
    //return left->evaluate() && right->evaluate()
    //doesn't work this way, idk
}