#include "./include/SemiOperator.h"

SemiOperator::SemiOperator(Base* left, Base* right) : Operator(left, right)
{}

SemiOperator::~SemiOperator()
{}

bool SemiOperator::evaluate() {
    return left->evaluate() && right->evaluate();
}