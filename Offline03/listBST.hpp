#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * Binary Search Tree implementation using linked list structure
 *
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value>
{
private:
    /**
     * Node class for the binary search tree
     */
    class Node
    {
    public:
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node *root;
    size_t node_count;

    // TODO: Implement private helper functions as needed
    // Start your private helper functions here
    void freeBST(Node* rt)
    {
        if (rt == nullptr)
            return;

        freeBST(rt->left);
        freeBST(rt->right);
        delete rt;
    }
    void print_D(Node* rt){
        if(rt == nullptr){
            cout << "()";
            return;
        }
        cout << "(" << rt -> key << ":" << rt -> value;
        print_D(root -> left);
        print_D(root -> right);
        cout << ")";
    }
    void print_I(Node* rt){
        if(rt == nullptr){
            return;
        }

        print_I(rt -> left);
        cout << "(" << rt -> key << ":" << rt -> value << ")";
        print_I(rt -> right);
    }
    void print_P(Node* rt){
        if(rt == nullptr){
            return;
        }

        cout << "(" << rt -> key << ":" << rt -> value << ")";
        print_P(rt -> left);
        print_P(rt -> right);
    }
    void print_O(Node* rt){
        if(rt == nullptr){
            return;
        }

        print_O(rt -> left);
        print_O(rt -> right);
        cout << "(" << rt -> key << ":" << rt -> value << ")";
    }
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}

    /**
     * Destructor
     */
    ~ListBST()
    {
        // TODO: Implement destructor to free memory
        freeBST(root);
        root = nullptr;
        node_count = 0;
    }

    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override
    {
        // TODO: Implement insertion logic
        if (root == nullptr)
        {
            root = new Node(key, value);
            node_count++;
            return true;
        }

        Node *temp = root;
        Node *parent_temp = nullptr;

        while (temp != nullptr)
        {
            if (key == temp->key)
            {
                return false;
            }
            else if (key < temp->key)
            {
                parent_temp = temp;
                temp = temp->left;
            }
            else
            {
                parent_temp = temp;
                temp = temp->right;
            }
        }
        if (parent_temp->key > key)
        {
            parent_temp->left = new Node(key, value);
            node_count++;
            return true;
        }
        else
        {
            parent_temp->right = new Node(key, value);
            node_count++;
            return true;
        }
    }

    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override
    {
        // TODO: Implement removal logic
        if (root == nullptr)
        {
            return false;
        }

        Node *temp = root;
        Node *parent_temp = root;

        while (temp != nullptr)
        {
            if (temp->key == key)
            {
                if (temp->right == nullptr && temp->left == nullptr)
                {
                    if (temp == root)
                    {
                        root = nullptr;
                    }
                    else if (parent_temp->left == temp)
                    {
                        parent_temp->left = nullptr;
                    }
                    else if (parent_temp->right == temp)
                    {
                        parent_temp->right = nullptr;
                    }
                    delete temp;
                    node_count--;
                    return true;
                }
                if (temp->left != nullptr && temp->right == nullptr)
                {
                    if (temp == root)
                    {
                        root = temp->left;
                    }
                    else if (parent_temp->left == temp)
                    {
                        parent_temp->left = temp->left;
                    }
                    else if (parent_temp->right == temp)
                    {
                        parent_temp->right = temp->left;
                    }
                    delete temp;
                    node_count--;
                    return true;
                }

                Node *suc_rt = temp->right;
                Node *suc_parent = parent_temp;

                while (suc_rt->left != nullptr)
                {
                    suc_parent = suc_rt;
                    suc_rt = suc_rt->left;
                }

                temp->key = suc_rt->key;
                temp->value = suc_rt->value;

                if (suc_parent->left == suc_rt)
                    suc_parent->left = suc_rt->right;
                else
                    suc_parent->right = suc_rt->right;

                delete suc_rt;
                node_count--;
                return true;
            }
            else if (temp->key > key)
            {
                parent_temp = temp;
                temp = temp->left;
            }
            else
            {
                parent_temp = temp;
                temp = temp->right;
            }
        }
        return false;
    }

    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override
    {
        // TODO: Implement find logic
        Node *temp = root;

        while (temp != nullptr)
        {
            if (key == temp->key)
            {
                return true;
            }
            else if (key < temp->key)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }

        return false;
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override
    {
        // TODO: Implement get logic
        Node *temp = root;

        while (temp != nullptr)
        {
            if (key == temp->key)
            {
                return temp->value;
            }
            else if (key < temp->key)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        throw std ::runtime_error("Key not found in BST.");
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override
    {
        // TODO: Implement update logic
        Node *temp = root;

        while (temp != nullptr)
        {
            if (key == temp->key)
            {
                temp->value = value;
                return;
            }
            else if (key < temp->key)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        throw std ::runtime_error("Key not found in BST.");
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override
    {
        // TODO: Implement clear logic
        freeBST(root);
        root = nullptr;
        node_count = 0;
    }

    /**
     * Get the number of keys in the BST
     */
    size_t size() const override
    {
        // TODO: Implement size logic
        return node_count;
    }

    /**
     * Check if the BST is empty
     */
    bool empty() const override
    {
        // TODO: Implement empty check logic
        return node_count == 0;
    }

    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override
    {
        // TODO: Implement find_min logic
        if(empty()){
            throw std::runtime_error("BST is empty, cannot find minimum");
        }

        Node* temp = root;

        while(temp -> left != nullptr){
            temp = temp -> left;
        }

        return temp -> key;
    }

    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override
    {
        // TODO: Implement find_max logic
        if(empty()){
            throw std::runtime_error("BST is empty, cannot find maximum");
        }

        Node* temp = root;

        while(temp -> right != nullptr){
            temp = temp -> right;
        }

        return temp -> key;
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override
    {
        // TODO: Implement print logic
        switch (traversal_type)
        {
        case 'D':
            print_D(root);
            break;
        case 'I':
            print_I(root);
            break;
        case 'P':
            print_P(root);
            break;
        case 'O':
            print_O(root);
            break;
        }
        cout << endl;
    }
};

#endif // LISTBST_H