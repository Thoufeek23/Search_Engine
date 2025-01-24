#include <iostream>
#include <string>

#include "person.h"
#include "ABLL.h"
#include "BST.h"

using namespace std;

int main()
{
    ABLL abll;
    BST bst;
    cout << "Welcome to Thoufeek's search engine" << endl;
    int option = 1;

    while (option > 0 && option < 7)
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
        cin >> option;

        if (option == 1)
        {
            cout << "Search by name selected." << endl;
            string s;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, s);
            person *p = new person(s, 0, "", "");
            bst.searchbyname(p);
            // bst.check();
        }
        else if (option == 2)
        {
            cout << "Search by category selected." << endl;
        }
        else if (option == 3)
        {
            cout << "List by age selected." << endl;
            abll.dispbyage();
        }
        else if (option == 4)
        {
            cout << "List by popularity selected." << endl;
        }
        else if (option == 5)
        {
            string name;
            int age;
            string description;
            int categoryOption;

            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            if (name == "")
            {
                cout << "Name cannot be empty. Please start over." << endl;
                continue;
            }

            cout << "Enter age: ";
            cin >> age;
            if (age < 0 || age > 100)
            {
                cout << "Invalid age. Please start over. [Range 1 - 100]" << endl;
                continue;
            }
            cout << "Enter description: ";
            cin.ignore();
            getline(cin, description);
            if (description == "")
            {
                cout << "Alert! Description is empty." << endl;
            }

            cout << "Choose category: " << endl;
            cout << "1. Tech" << endl;
            cout << "2. Cinema" << endl;
            cout << "3. Sports" << endl;
            cout << "4. Music" << endl;
            cout << "5. Entrepreneur" << endl;
            cin >> categoryOption;

            string category;
            switch (categoryOption)
            {
            case 1:
                category = "Tech";
                break;
            case 2:
                category = "Cinema";
                break;
            case 3:
                category = "Sports";
                break;
            case 4:
                category = "Music";
                break;
            case 5:
                category = "Entrepreneur";
                break;
            default:
                cout << "Invalid category. Please start over." << endl;
                continue;
            }

            person *p = new person(name, age, description, category);
            bst.insert(p);
            abll.insert(age, p);
        }
        else if (option == 6)
        {
            string ch;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, ch);
            // bst.edit(ch);
        }
    }
    cout << "Thank you for using our search engine!" << endl;
    return 0;
}
