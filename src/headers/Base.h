#ifndef __BASE_H__
#define __BASE_H__

class Base
{
protected:
    Base(){};
public:
    virtual bool evaluate() = 0;
    virtual ~Base() = 0;
};
inline Base::~Base(){}
#endif
