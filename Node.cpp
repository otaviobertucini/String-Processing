#include "Node.h"

Node::Node() {}

Node::Node(int n, string word, Node* left, Node* right){
    this->n = n;
    this->word = word;
    this->left = left;
    this->right = right;
}

bool Node::isEnd(){
    if(left == NULL)
        return true;
    return false;
}

Node::~Node() {}

