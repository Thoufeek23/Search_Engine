#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "person.h"
#include "ABLL.h"
#include "BST.h"
#include "Heap.h"

using namespace std;

const string DATA_FILE = "people.txt";

class EndOfInput : public runtime_error
{
public:
    EndOfInput() : runtime_error("End of input") {}
};

struct LessPopular
{
    bool operator()(const person *a, const person *b) const
    {
        if (a->getPop() != b->getPop())
        {
            return a->getPop() < b->getPop();
        }
        return a->getName() > b->getName();
    }
};

string readLine(string_view prompt = "")
{
    cout << prompt;
    string line;
    if (!getline(cin, line))
    {
        throw EndOfInput();
    }
    if (!line.empty() && line.back() == '\r')
    {
        line.pop_back();
    }
    return line;
}

int readInt(string_view prompt = "")
{
    string line = readLine(prompt);
    size_t pos = 0;
    int value = 0;
    try
    {
        value = stoi(line, &pos);
    }
    catch (const logic_error &)
    {
        throw invalid_argument("Please enter a number.");
    }
    if (line.find_first_not_of(" \t", pos) != string::npos)
    {
        throw invalid_argument("Please enter a number.");
    }
    return value;
}

const string &chooseCategory()
{
    cout << "Choose category: " << endl;
    for (size_t i = 0; i < CATEGORIES.size(); i++)
    {
        cout << i + 1 << ". " << CATEGORIES[i] << endl;
    }
    int choice = readInt();
    if (choice < 1 || choice > static_cast<int>(CATEGORIES.size()))
    {
        throw invalid_argument("Invalid category.");
    }
    return CATEGORIES[choice - 1];
}

person *choosePerson(const vector<person *> &results)
{
    if (results.empty())
    {
        cout << "No person found." << endl;
        return nullptr;
    }
    for (size_t i = 0; i < results.size(); i++)
    {
        cout << i + 1 << ". ";
        results[i]->shallowdisp();
    }
    int choice = readInt("Enter number to select (0 to go back): ");
    if (choice == 0)
    {
        return nullptr;
    }
    if (choice < 0 || choice > static_cast<int>(results.size()))
    {
        throw out_of_range("Invalid selection.");
    }
    return results[choice - 1];
}

string toLower(string_view s)
{
    string out(s);
    transform(out.begin(), out.end(), out.begin(), [](unsigned char c)
              { return static_cast<char>(tolower(c)); });
    return out;
}

vector<person *> searchbyname(const BST<person> &bst, string_view name)
{
    const string key = toLower(name);
    return bst.findAll([&key](const person &p)
                       { return toLower(p.getName()) == key; });
}

void viewPerson(person &p)
{
    cout << endl
         << p << endl;
    p.popularity();
}

void save(const string &path, const BST<person> &bst)
{
    ofstream out(path);
    if (!out)
    {
        throw runtime_error("Could not open " + path + " for writing.");
    }
    for (const person *p : bst.getAll())
    {
        out << quoted(p->getName()) << ' ' << p->getAge() << ' '
            << quoted(p->getDesc()) << ' ' << quoted(p->getCategory()) << ' '
            << p->getPop() << '\n';
    }
}

int load(const string &path, BST<person> &bst, ABLL &abll)
{
    ifstream in(path);
    if (!in)
    {
        return 0;
    }

    int loaded = 0;
    int lineNo = 0;
    string line;
    while (getline(in, line))
    {
        lineNo++;
        if (line.empty())
        {
            continue;
        }
        istringstream fields(line);
        string name, desc, category;
        int age = 0, pop = 0;
        if (!(fields >> quoted(name) >> age >> quoted(desc) >> quoted(category) >> pop))
        {
            cerr << "Skipping malformed line " << lineNo << " in " << path << endl;
            continue;
        }
        try
        {
            auto p = make_unique<person>(name, age, desc, category, pop);
            person *raw = p.get();
            if (bst.insert(std::move(p)))
            {
                abll.insert(age, raw);
                loaded++;
            }
        }
        catch (const exception &e)
        {
            cerr << "Skipping line " << lineNo << " in " << path << ": " << e.what() << endl;
        }
    }
    return loaded;
}

void searchByNameOption(const BST<person> &bst)
{
    cout << "Search by name selected." << endl;
    string name = readLine("Enter name: ");
    if (person *p = choosePerson(searchbyname(bst, name)))
    {
        viewPerson(*p);
    }
}

void searchByCategoryOption(const BST<person> &bst)
{
    cout << "Search by category selected." << endl;
    const string &category = chooseCategory();
    if (person *p = choosePerson(bst.findAll([&](const person &x)
                                             { return x.getCategory() == category; })))
    {
        viewPerson(*p);
    }
}

void listByPopularityOption(const BST<person> &bst)
{
    cout << "List by popularity selected." << endl;
    vector<person *> all = bst.getAll();
    if (all.empty())
    {
        cout << "No person found." << endl;
        return;
    }
    Heap<person *, LessPopular> heap(static_cast<int>(all.size()));
    for (person *p : all)
    {
        heap.insert(p);
    }
    for (int rank = 1; !heap.isEmpty(); rank++)
    {
        const person *p = heap.extractMax();
        cout << rank << ". " << p->getName() << ", " << p->getAge()
             << " (" << p->getCategory() << ") - Popularity: " << p->getPop() << endl;
    }
}

void addPersonOption(BST<person> &bst, ABLL &abll)
{
    string name = readLine("Enter name: ");
    person::validateName(name);

    int age = readInt("Enter age: ");
    person::validateAge(age);

    string description = readLine("Enter description: ");
    if (description.empty())
    {
        cout << "Alert! Description is empty." << endl;
    }

    const string &category = chooseCategory();

    auto p = make_unique<person>(name, age, description, category);
    person *raw = p.get();
    if (bst.insert(std::move(p)))
    {
        abll.insert(age, raw);
        cout << "New person added successfully!" << endl;
    }
    else
    {
        cout << "Person with same name and age exist in the category!" << endl;
    }
}

void editPersonOption(const BST<person> &bst, ABLL &abll)
{
    string name = readLine("Enter name: ");
    vector<person *> matches = searchbyname(bst, name);
    person *p = choosePerson(matches);
    if (p == nullptr)
    {
        return;
    }

    int newAge = p->getAge();
    string newDesc = p->getDesc();
    string newCategory = p->getCategory();

    cout << "What do you want to edit?" << endl;
    cout << "1. Age" << endl;
    cout << "2. Description" << endl;
    cout << "3. Category" << endl;
    switch (readInt())
    {
    case 1:
        newAge = readInt("Enter new age: ");
        person::validateAge(newAge);
        break;
    case 2:
        newDesc = readLine("Enter new description: ");
        if (newDesc.empty())
        {
            cout << "Alert! Description is empty." << endl;
        }
        break;
    case 3:
        newCategory = chooseCategory();
        break;
    default:
        throw invalid_argument("Invalid option.");
    }

    const person updated(p->getName(), newAge, newDesc, newCategory);
    bool duplicate = any_of(matches.begin(), matches.end(), [&](const person *m)
                            { return m != p && *m == updated; });
    if (duplicate)
    {
        cout << "Person with same name and age exist in the category!" << endl;
        return;
    }

    if (newAge != p->getAge())
    {
        abll.remove(p->getAge(), p);
        p->setAge(newAge);
        abll.insert(newAge, p);
    }
    p->setDesc(newDesc);
    p->setCategory(newCategory);
    cout << "Person updated successfully!" << endl;
}

void printMenu()
{
    cout << "--------------------------------------------" << endl;
    cout << "Enter option number to select" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "1. Search by name" << endl;
    cout << "2. Search by category" << endl;
    cout << "3. List by age" << endl;
    cout << "4. List by popularity" << endl;
    cout << "5. Add new person" << endl;
    cout << "6. Edit exisiting person" << endl;
    cout << "7. Exit" << endl;
}

int main()
{
    ABLL abll;
    BST<person> bst;
    cout << "Welcome to Thoufeek's search engine" << endl;

    int loaded = load(DATA_FILE, bst, abll);
    if (loaded > 0)
    {
        cout << "Loaded " << loaded << " people from " << DATA_FILE << endl;
    }

    bool running = true;
    while (running)
    {
        printMenu();
        try
        {
            switch (readInt())
            {
            case 1:
                searchByNameOption(bst);
                break;
            case 2:
                searchByCategoryOption(bst);
                break;
            case 3:
                cout << "List by age selected." << endl;
                abll.dispbyage();
                break;
            case 4:
                listByPopularityOption(bst);
                break;
            case 5:
                addPersonOption(bst, abll);
                break;
            case 6:
                editPersonOption(bst, abll);
                break;
            case 7:
                running = false;
                break;
            default:
                cout << "Invalid option. Please choose 1 - 7." << endl;
            }
        }
        catch (const EndOfInput &)
        {
            running = false;
        }
        catch (const exception &e)
        {
            cout << e.what() << " Please start over." << endl;
        }
    }

    try
    {
        save(DATA_FILE, bst);
        cout << "Saved " << bst.getAll().size() << " people to " << DATA_FILE << endl;
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }

    cout << "Thank you for using our search engine!" << endl;
    return 0;
}
