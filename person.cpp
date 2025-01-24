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

bool person::operator=(const person &other) const
{
    return (name == other.name);
}

bool person::operator==(const person &other) const
{
    return (name == other.name && age == other.age && category == other.category);
}

bool person::checkname(const person &other) const
{
    return (name == other.name);
}
bool person::operator>(const person &other) const
{
    return (name > other.name);
}

void person::disp()
{
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Description: " << desc << endl;
    cout << "Category: " << category << endl;
    cout << "Overall Popularity: " << pop << endl;
}

void person::shallowdisp()
{
    cout << name << ", " << age << endl;
}
void person::popularity()
{
    pop++;
}

/*int person::check(person *a, person *b)
{
    if (a->name == b->name)
    {
        if (a->age == b->age)
        {
            cout << "Person with same name and age already exists." << endl;
            cout << "Do you still want to add this person?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                return 1;
            }
            else if (choice == 2)
            {
                return 2;
            }
            else
            {
                cout << "Invalid choice." << endl;
                return 3;
            }
        }
    }
    else
    {
        return 0;
    }
}*/