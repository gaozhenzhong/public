#ifndef BASECLASS_H
#define BASECLASS_H
#include<iostream>

#include "muduo/base/copyable.h"

namespace nBaseClass
{
bool isCurrectIP(const char *ip);

class BaseTestClass : public muduo::copyable
{
public:
    BaseTestClass(std::string _name) : name(_name){std::cout<<__FUNCTION__<<__LINE__<<" : class name is "<<name<<std::endl;}
    ~BaseTestClass(void){std::cout<<__FUNCTION__<<__LINE__<<" : class name is "<<name<<std::endl;}
private:
    std::string name;
};

}

#endif // BASECLASS_H
