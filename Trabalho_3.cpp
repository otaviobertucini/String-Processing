#include "Trabalho_3.h"

Trabalho_3::Trabalho_3() {
}

void Trabalho_3::readText(char* name) {
    this->name = name;
    ifstream file(name);
    if (file.is_open()) {
        std::string line;
        int index = -1;
        int i;
        while (getline(file, line)) {
            int first = 0;
            int last = 0;
            for (i = 0; i < line.size() + 1; i++) { 
                index++;
                if (    (line[i] >= 48 && line[i] <= 57) || 
                        (line[i] >= 65 && line[i] <= 90) || 
                        (line[i] >= 97 && line[i] <= 172)) {
                    last++;
                } 
                else {
                    std::string copy = line.substr(first, last);
                    if(copy[0] != 32 && copy[0] != 0)
                        addWord(copy, index-last);
                    copy.clear();
                    first = i + 1;
                    last = 0;
                    if(line[i] != 0 && line[i] != 32){
                        string aux;
                        aux = line[i];
                        addWord(aux, i);
                    }
                }
            }
        }
        last_character = index-1;
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

void Trabalho_3::searchWord(string word){
    vector<int>* indexes;
    try{
        indexes = inverted.at(word);
    }
    catch(out_of_range){
        cout << "Palavra não encontrada!" << endl;
        return;
    }
    cout << "Número de ocorrências: " << indexes->size() << endl;
    cout << "Posição: " << (*indexes)[0] << endl;
    printPart((*indexes)[0]);
//    for(int i = 0; i < indexes->size(); i++){
//        cout << (*indexes)[i] << endl;
//    }
}

void Trabalho_3::printPart(int index){
    int bottom = index - 20;
    if(bottom < 0)
        bottom = 0;
    int top = index + 20;
    if(top > last_character)
        top = last_character;    
    
    ifstream file(name);
    if(!file.is_open()){
        cout << "Nenhum arquivo encontrado!" << endl;
        return;
    }
    
    string text = "";
    string line;
    int index_file = 0;
    
    while (getline(file, line)) {
        for(int i = 0; i < line.size(); i++){
            if(index_file >= bottom && index_file <= top){
                text += line[i];
            }
            index_file++;
        }
        text += " ";
    }
    cout << "Parte do texto:\n" << text << endl;    
}

Trabalho_3::~Trabalho_3() {
}

