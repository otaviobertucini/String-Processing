#ifndef TRABALHO_3_H
#define TRABALHO_3_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

class Trabalho_3 {
public:
    Trabalho_3();
    void readText(char* name);
    void addWord(string word, int index);
    void printMap();
    void searchWord(string word);
    void printPart(int index);
    virtual ~Trabalho_3();
private:
    string text;
    vector<std::string> strings;
    map<string, vector<int>* > inverted;
    int last_character;
    char* name;
};

#endif /* TRABALHO_3_H */

