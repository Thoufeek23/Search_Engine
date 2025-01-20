#include <iostream>
#include <string>
#include "person.h"

using namespace std;

class ABLL
{
private:
    struct Node
    {
        person *p;
        Node *next;
    };
    Node *ageArray[101];

public:
    ABLL();
    ~ABLL();
    void insert(int age, person *p);
    void makeEmpty();
    void dispbyage();
};