#ifndef TRABALHO_3_H
#define TRABALHO_3_H
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include "Node.h"
using namespace std;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

class Trabalho_3 {
public:
    Trabalho_3();
    void readText(const char* name);
    void addWord(string word, int index);
    void printMap();
    void searchWord(string word);
    void printPart(int index);
    void printWords(string txt);
    void menu();
    void makeNodes();
    void makeTree();
    void printNodes();
    void printTree(Node* a);
    void createTable(Node* node, string bin);
    void makeEncoding();
    string getBinary(string word);
    void printEncoding();
    virtual ~Trabalho_3();
private:
    string text;
    vector<std::string> strings;
    map<string, vector<int>* > inverted;
    map<string, string> table;
    int last_character;
    const char* name;
    vector<Node*> nodes;
    Node* tree_root;
};

#endif /* TRABALHO_3_H */

