#include "./include/Operator.h"

Operator::Operator(Base* left, Base* right)
{
    this->left = left;
    this->right = right;
}

Operator::~Operator()
{}