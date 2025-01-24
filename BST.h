

#include <iostream>
#include <string>
#include "person.h"

using namespace std;

class BST
{
private:
    struct Node
    {
        person *data;
        Node *left;
        Node *right;
    };
    Node *root = nullptr;

public:
    /// BST();
    //~BST();

    void insert(person *p);
    void insert(person *p, Node *node);
    // void display(Node *node);
    // void check();
    void searchbyname(person *p);
    void searchbyname(person *p, Node *node, int &i);
    //   void edit(string name);
};
