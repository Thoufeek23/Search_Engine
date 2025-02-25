#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class person
{
private:
    string name;
    int age;
    string desc;
    int pop;
    string category;

public:
    person(string name1, int age1, string desc1, string cat);
    bool operator=(const person &other) const;
    bool operator==(const person &other) const;
    bool operator>(const person &other) const;
    bool checkname(const person &other) const;
    void disp();
    void shallowdisp();
    void popularity();
};

#endif