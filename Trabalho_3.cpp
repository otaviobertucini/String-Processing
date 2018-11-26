#include "Trabalho_3.h"

Trabalho_3::Trabalho_3() {
}

void Trabalho_3::readText(char* name) {
    ifstream myfile(name);
    if (myfile.is_open()) {
        std::string line;
        int index = -1;
        while (getline(myfile, line)) {
            int first = 0;
            int last = 0;
            for (int i = 0; i < line.size() + 1; i++) { 
                index++;
                if (line[i] != 32 && line[i] != 0) {
                    last++;
                } else {
                    std::string copy = line.substr(first, last);
                    if(copy[0] != 32 && copy[0] != 0)
                        addWord(copy, index-last);
                    copy.clear();
                    first = i + 1;
                    last = 0;
                }
            }
        }
    }
    for (int i = 0; i < strings.size(); i++) {
        cout << strings[i] << endl;
    }
}

void Trabalho_3::addWord(string word, int index){
    try{
        inverted.at(word);
    }
    catch(out_of_range){
        vector<int>* aux = new vector<int>;
        aux->push_back(index);
        inverted.insert(make_pair(word, aux));
        return;
    }
    inverted.at(word)->push_back(index);
}   

void Trabalho_3::printMap(){
    map<string, vector<int>*>::iterator itr;
    for(itr = inverted.begin(); itr != inverted.end(); itr++){
        cout << itr->first << ": ";
        for(int i = 0; i < itr->second->size(); i++){
            cout << itr->second->at(i) << ", ";
        }
        cout << "\n";
    }
}

Trabalho_3::~Trabalho_3() {
}

