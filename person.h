#ifndef PERSON_H
#define PERSON_H

#include <array>
#include <ostream>
#include <string>

using namespace std;

inline const array<string, 5> CATEGORIES = {"Tech", "Cinema", "Sports", "Music", "Entrepreneur"};

class person
{
private:
    string name;
    int age;
    string desc;
    int pop;
    string category;

public:
    static constexpr int MIN_AGE = 0;
    static constexpr int MAX_AGE = 100;

    person(string name1, int age1, string desc1, string cat, int pop1 = 1);

    static void validateName(const string &name1);
    static void validateAge(int age1);
    static void validateCategory(const string &cat);

    bool operator==(const person &other) const;
    bool operator!=(const person &other) const;
    bool operator<(const person &other) const;

    void shallowdisp() const;
    void popularity();

    const string &getName() const;
    int getAge() const;
    const string &getDesc() const;
    const string &getCategory() const;
    int getPop() const;

    void setAge(int age1);
    void setDesc(string desc1);
    void setCategory(string cat);
};

ostream &operator<<(ostream &out, const person &p);

#endif
