#ifndef BST_H
#define BST_H

#include <memory>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class BST
{
private:
    struct Node
    {
        unique_ptr<T> data;
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        Node(unique_ptr<T> item) : data(std::move(item)) {}
    };
    unique_ptr<Node> root;

    bool insert(unique_ptr<T> &item, unique_ptr<Node> &node)
    {
        if (!node)
        {
            node = make_unique<Node>(std::move(item));
            return true;
        }
        if (*item == *(node->data))
        {
            return false;
        }
        if (*item < *(node->data))
        {
            return insert(item, node->left);
        }
        return insert(item, node->right);
    }

    template <typename Pred>
    void findAll(Node *node, Pred &pred, vector<T *> &results) const
    {
        if (node == nullptr)
        {
            return;
        }
        findAll(node->left.get(), pred, results);
        if (pred(*(node->data)))
        {
            results.push_back(node->data.get());
        }
        findAll(node->right.get(), pred, results);
    }

public:
    bool insert(unique_ptr<T> item)
    {
        return insert(item, root);
    }

    template <typename Pred>
    vector<T *> findAll(Pred pred) const
    {
        vector<T *> results;
        findAll(root.get(), pred, results);
        return results;
    }

    vector<T *> getAll() const
    {
        return findAll([](const T &)
                       { return true; });
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }
};

#endif
