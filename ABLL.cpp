#include <iostream>
#include <string>
#include "person.h"
#include "ABLL.h"

using namespace std;

ABLL::ABLL()
{
    for (int i = 0; i < 101; i++)
    {
        ageArray[i] = nullptr;
    }
}

ABLL::~ABLL()
{
    makeEmpty();
}

void ABLL::insert(int age, person *p)
{
    int t = 0;
    Node *curr = ageArray[age];
    while (curr != nullptr)
    {
        if ((*curr->p) == *p)
        {
            t = 1;
        }
        curr = curr->next;
    }
    if (t == 1)
    {
        return;
    }
    else
    {
        Node *newNode = new Node;
        newNode->p = p;
        newNode->next = nullptr;
        int i = age;
        if (ageArray[i] == nullptr)
        {
            ageArray[i] = newNode;
        }
        else
        {
            newNode->next = ageArray[i];
            ageArray[i] = newNode;
        }
    }
}

void ABLL::makeEmpty()
{
    for (int i = 0; i < 101; i++)
    {
        Node *curr = ageArray[i];
        while (curr != nullptr)
        {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
        ageArray[i] = nullptr;
    }
}

void ABLL::dispbyage()
{
    for (int i = 0; i < 101; i++)
    {
        Node *curr = ageArray[i];
        while (curr != nullptr)
        {
            Node *temp = curr;
            cout << endl;
            temp->p->disp();
            temp->p->popularity();
            curr = curr->next;
        }
    }
    cout << endl;
}
