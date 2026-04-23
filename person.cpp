#include "person.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
using namespace std;

person::person(string name1, int age1, string desc1, string cat, int pop1)
    : name(std::move(name1)), age(age1), desc(std::move(desc1)), pop(pop1), category(std::move(cat))
{
    validateName(name);
    validateAge(age);
    validateCategory(category);
    if (pop < 0)
    {
        throw invalid_argument("Popularity cannot be negative.");
    }
}

void person::validateName(const string &name1)
{
    if (name1.empty())
    {
        throw invalid_argument("Name cannot be empty.");
    }
}

void person::validateAge(int age1)
{
    if (age1 < MIN_AGE || age1 > MAX_AGE)
    {
        throw out_of_range("Invalid age. [Range " + to_string(MIN_AGE) + " - " + to_string(MAX_AGE) + "]");
    }
}

void person::validateCategory(const string &cat)
{
    if (find(CATEGORIES.begin(), CATEGORIES.end(), cat) == CATEGORIES.end())
    {
        throw invalid_argument("Invalid category: " + cat);
    }
}

bool person::operator==(const person &other) const
{
    return (name == other.name && age == other.age && category == other.category);
}

bool person::operator!=(const person &other) const
{
    return !(*this == other);
}

bool person::operator<(const person &other) const
{
    return (name < other.name);
}

void person::shallowdisp() const
{
    cout << name << ", " << age << endl;
}

void person::popularity()
{
    pop++;
}

const string &person::getName() const
{
    return name;
}

int person::getAge() const
{
    return age;
}

const string &person::getDesc() const
{
    return desc;
}

const string &person::getCategory() const
{
    return category;
}

int person::getPop() const
{
    return pop;
}

void person::setAge(int age1)
{
    validateAge(age1);
    age = age1;
}

void person::setDesc(string desc1)
{
    desc = std::move(desc1);
}

void person::setCategory(string cat)
{
    validateCategory(cat);
    category = std::move(cat);
}

ostream &operator<<(ostream &out, const person &p)
{
    out << "Name: " << p.getName() << '\n'
        << "Age: " << p.getAge() << '\n'
        << "Description: " << p.getDesc() << '\n'
        << "Category: " << p.getCategory() << '\n'
        << "Overall Popularity: " << p.getPop() << '\n';
    return out;
}
