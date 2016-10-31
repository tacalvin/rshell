#include "./include/AndOperator.h"

AndOperator::AndOperator(Base* left, Base* right) : Operator(left, right)
{}

AndOperator::~AndOperator()
{}

bool AndOperator::evaluate() {
    if (left->evaluate()) return true;
    else return right->evaluate();
}