#ifndef ABLL_H
#define ABLL_H

#include <array>
#include <memory>
#include "person.h"

using namespace std;

class ABLL
{
private:
    struct Node
    {
        person *p;
        unique_ptr<Node> next;
    };
    array<unique_ptr<Node>, person::MAX_AGE + 1> ageArray;

public:
    void insert(int age, person *p);
    void remove(int age, person *p);
    void makeEmpty();
    void dispbyage();
};

#endif
