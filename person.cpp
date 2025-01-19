#include "person.h"
#include <iostream>
#include <string>
using namespace std;

person::person(string name1, int age1, string desc1, string cat)
{
    name = name1;
    age = age1;
    desc = desc1;
    pop = 1;
    category = cat;
}

void person::disp()
{
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Description: " << desc << endl;
    cout << "Category: " << category << endl;
    cout << "Overall Popularity: " << pop << endl;
}