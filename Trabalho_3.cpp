#include "Trabalho_3.h"

Trabalho_3::Trabalho_3() {
    tree_root = NULL;
}

void Trabalho_3::readText(const char* name) {
    inverted.clear();
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
                    if(copy[0] != 32 && copy[0] != 0){
                        addWord(copy, index-last);
                    }
                    copy.clear();
                    first = i + 1;
                    last = 0;
                    if(line[i] != 0 && line[i] != 32){
                        string aux;
                        aux = line[i];
                        addWord(aux, index+last);
                    }
                }
            }
        }
        last_character = index-1;
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
    int ocur_size = indexes->size();
    cout << "Número de ocorrências: " << ocur_size << endl;
    int cmd = 1, k=0;
    while(cmd > 0){
        cout << "---------------------------------" << endl;
        cout << "Palavra: " << word << endl;
        cout << "Posição: " << (*indexes)[k] << endl;
        printPart((*indexes)[k]);
        cout << "Digite 1 para a próxima ocorrência e 0 para sair." << endl;
        cin >> cmd;
        if(cmd == 1){            
            k++;
            if(k == ocur_size){
                cmd = 0;
                cout << "Não há mais ocorrências!" << endl;
            }
        }
    }
}

void Trabalho_3::printWords(string txt){
    ;
    for(int i = 0; i < txt.size(); i++){
        int value = txt[i];
        cout << txt[i] << ": " << value << endl;
    }
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
    int wrote = 0;
    while (getline(file, line)) {   
        for(int i = 0; i < line.size()+1; i++){            
            if(index_file >= bottom && index_file <= top){
                text += line[i];
                wrote = 1;
            }
            index_file++;
        }
        if(wrote){
            text += " ";
        }
        wrote = 0;
    }
    cout << "Parte do texto:\n" << text << endl; 
    cout << "---------------------------------" << endl;
    file.clear();
    file.seekg(0, std::ios::beg);
}

void Trabalho_3::menu(){
    string name;
    cout << "Digite o nome do arquivo que deseja abrir: " << endl;
    cin >> name;
    readText(name.c_str());
    int loop = 1; 
    int cmd;
    while(loop){
        cout << "1 - Procurar palavra \n2 - Arquivo invertido "
                "\n3 - Novo arquivo \n4 - Codificar \n0 - Sair "
                << endl;
        cin >> cmd;
        if(cmd == 1){
            string word;
            cout << "Digite a palavra que deseja procurar: " << endl;
            cin >> word;
            searchWord(word);    
        }
        if(cmd == 2)
            printMap();
        if(cmd == 3){
            string name;
            cout << "Digite o nome do arquivo que deseja abrir: " << endl;
            cin >> name;
            readText(name.c_str());
        }            
        if(cmd == 4){
            makeNodes();
            makeTree();
            createTable(tree_root, "");
            makeEncoding();
            printEncoding();
        }
        if(cmd == 0)
            loop = 0;
    }
}

struct compareNodes{
    bool operator()(Node* a, Node* b){return (a->n < b->n);}
};

void Trabalho_3::makeNodes(){
    map<string, vector<int>*>::iterator itr;
    for(itr = inverted.begin(); itr != inverted.end(); itr++){
        nodes.push_back(new Node(itr->second->size(), itr->first));
    }
    sort(nodes.begin(), nodes.end(), compareNodes());    
}

void Trabalho_3::makeTree(){
    while(nodes.size() > 1){
        Node* aux1 = nodes[0];
        Node* aux2 = nodes[1];
        nodes.push_back(new Node(aux1->n + aux2->n, "**", aux1, aux2));
        sort(nodes.begin(), nodes.end(), compareNodes());
        nodes.erase(nodes.begin(), nodes.begin()+2);
    }
    tree_root = nodes[0];    
}

void Trabalho_3::createTable(Node* node, string bin){
    if(node->isEnd())
        table.insert(make_pair(node->word, bin));
    else{
        createTable(node->left, bin + "0");
        createTable(node->right, bin + "1");
    }    
}

void Trabalho_3::printTree(Node* a){
    if(a->isEnd())
        cout << a->word << ", " << a->n << endl;
    else{
        cout << a->word << ", " << a->n << endl;
        printTree(a->left);
        printTree(a->right);
    }    
}

void Trabalho_3::printNodes(){
    cout << "---------------------------------" << endl;
    for(int i = 0; i < nodes.size(); i++){
        cout << nodes[i]->n << ", " << nodes[i]->word << endl;
    }
    cout << "---------------------------------" << endl;
}

void Trabalho_3::makeEncoding() {
    ifstream file(name);
    ofstream dest("encoding.txt");
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
                    if(copy[0] != 32 && copy[0] != 0){
                        string bin = getBinary(copy);
                        dest << bin;
                    }
                    copy.clear();
                    first = i + 1;
                    last = 0;
                    if(line[i] != 0 && line[i] != 32){
                        string aux;
                        aux = line[i];
                        string bin = getBinary(aux);
                        dest << bin;
                    }
                }
            }
        }
        last_character = index-1;
    }
}

string Trabalho_3::getBinary(string word){
    try{
        table.at(word);
    }
    catch(out_of_range){
        return "";
    }    
    return table.at(word);
}

void Trabalho_3::printEncoding(){
    ifstream file("encoding.txt");
    string encoding;
    getline(file, encoding);
    cout << encoding << endl;
}

Trabalho_3::~Trabalho_3() {
}

