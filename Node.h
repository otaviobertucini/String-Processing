#ifndef NODE_H
#define NODE_H
#include <stdlib.h>
#include <string>
#include <bits/stdc++.h> 
#include <iostream>
using namespace std;
using std::cout;
using std::endl;

class Node {
public:
    Node();
    Node(int n, string word = "", Node* left = NULL, Node* right = NULL);
    bool isEnd();
    ~Node();
    int n;
    string word;
    Node* left;
    Node* right;
private:   

};

#endif /* NODE_H */

