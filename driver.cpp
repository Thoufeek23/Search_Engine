#include <iostream>
#include <string>

#include "person.h"
#include "ABLL.h"

using namespace std;

int main()
{
    ABLL abll;
    cout << "Welcome to Thoufeek's search engine" << endl;
    int option = 1;
    while (option > 0 && option < 6)
    {
        cout << "--------------------------------------------" << endl;
        cout << "Enter option number to select" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "1. Search by name" << endl;
        cout << "2. Search by category" << endl;
        cout << "3. List by age" << endl;
        cout << "4. List by popularity" << endl;
        cout << "5. Add new person" << endl;
        cout << "6. Exit" << endl;
        cin >> option;

        if (option == 1)
        {
            cout << "Search by name selected." << endl;
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

            cout << "Enter age: ";
            cin >> age;

            cout << "Enter description: ";
            cin.ignore();
            getline(cin, description);

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
            abll.insert(age, p);
            cout << "New person added successfully!" << endl;
            // delete p;
        }
    }

    cout << "Thank you for using our search engine!" << endl;
    return 0;
}
