#include <iostream>
#include <string>
#include "person.h"
#include "ABLL.h"

using namespace std;

void ABLL::insert(int age, person *p)
{
    person::validateAge(age);
    for (Node *curr = ageArray[age].get(); curr != nullptr; curr = curr->next.get())
    {
        if (*(curr->p) == *p)
        {
            return;
        }
    }
    unique_ptr<Node> newNode(new Node);
    newNode->p = p;
    newNode->next = std::move(ageArray[age]);
    ageArray[age] = std::move(newNode);
}

void ABLL::remove(int age, person *p)
{
    person::validateAge(age);
    unique_ptr<Node> *link = &ageArray[age];
    while (*link)
    {
        if ((*link)->p == p)
        {
            *link = std::move((*link)->next);
            return;
        }
        link = &((*link)->next);
    }
}

void ABLL::makeEmpty()
{
    for (auto &head : ageArray)
    {
        head.reset();
    }
}

void ABLL::dispbyage()
{
    for (const auto &head : ageArray)
    {
        for (Node *curr = head.get(); curr != nullptr; curr = curr->next.get())
        {
            cout << endl
                 << *(curr->p);
            curr->p->popularity();
        }
    }
    cout << endl;
}
