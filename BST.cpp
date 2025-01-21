#include <iostream>
#include <string>
#include "person.h"
#include "BST.h"

using namespace std;

void BST::insert(person *p)
{
    if (root == nullptr)
    {
        root = new Node;
        root->data = p;
        root->left = nullptr;
        root->right = nullptr;
        cout << "New person added successfully!" << endl;
    }
    else
    {
        insert(p, root);
    }
}

void BST::insert(person *p, Node *node)
{
    if (*p == *(node->data))
    {
        cout << "Person with same name and age exist in the category!" << endl;
    }
    else
    {
        if (*p > *(node->data))
        {
            if (node->right == nullptr)
            {
                node->right = new Node;
                node->right->data = p;
                node->right->left = nullptr;
                node->right->right = nullptr;
                cout << "New person added successfully!" << endl;
                return;
            }
            insert(p, node->right);
        }
        else
        {
            if (node->left == nullptr)
            {
                node->left = new Node;
                node->left->data = p;
                node->left->right = nullptr;
                node->left->right = nullptr;
                cout << "New person added successfully!" << endl;
                return;
            }
            insert(p, node->left);
        }
    }
}
/*
void BST::searchbyname(string name)
{
    if (root == nullptr)
    {
        cout << "No person found." << endl;
    }
    else
    {
        searchbyname(name, root);
    }
}

void BST::searchbyname(string name, Node* root)
{
    string s = root -> data -> getname;
}
*/
