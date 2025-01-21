

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
    // void searchbyname(string name);
    // void searchbyname(string name, Node* node);
    //  void edit(string name);
};
