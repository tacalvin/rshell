#include "./include/OrOperator.h"

OrOperator::OrOperator(Base* left, Base* right) : Operator(left, right)
{}

OrOperator::~OrOperator()
{}

bool OrOperator::evaluate() {
    if (!left->evaluate()) return false;
    else return right->evaluate();
}