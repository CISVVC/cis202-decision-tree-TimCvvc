/*
 File: binary_tree.cpp
 Description: implementation for the Binary_tree class
 Created: 5/15/20
 Author: Tim Chester
 email: chestert@student.vvc.edu
*/

#include <algorithm>
#include "binary_tree.h"

using namespace std;
#include <iostream>

Binary_tree::Binary_tree()
{
    root = nullptr;
}

Binary_tree::Binary_tree(string root_data)
{
    root = new Node;
    root->data = root_data;
    root->left = nullptr;
    root->right = nullptr;
}

Binary_tree::Binary_tree(string root_data, Binary_tree left, Binary_tree right)
{
    root = new Node;
    root->data = root_data;
    root->left = left.root;
    root->right = right.root;
}

int Binary_tree::height(const Node* n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + max(height(n->left), height(n->right));
    }
}

int Binary_tree::height() const
{
    return height(root);
}

bool Binary_tree::empty() const
{
    return root == nullptr;
}

string Binary_tree::data() const
{
    return root->data;
}

Binary_tree Binary_tree::left() const
{
    Binary_tree result;
    result.root = root->left;
    return result;
}

Binary_tree Binary_tree::right() const
{
    Binary_tree result;
    result.root = root->right;
    return result;
}



void Binary_tree::insert(string question, string new_answer, string original_answer)
{
    Binary_tree left, right;
    
    root->left = new Node;
    root->right = new Node;

    left.root = root->left;
    right.root = root->right;

    right.root->data = root->data;
    root->data = question;
    left.root->data = new_answer;
}