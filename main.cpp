#include <cstdlib>
#include "Trabalho_3.h"

int main() {
    Trabalho_3 trab;
    trab.readText("Historia.txt");
    
    string word;
    cin >> word;
    trab.searchWord(word);
    //trab.printWords("façanhas");
    return 0;
}

//àáâãçéõôêó