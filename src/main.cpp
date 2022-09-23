#include "tree.hpp"
#include<iostream>
#include<string>

using namespace std;

int main(){

    Tree *HT;
    vector<Tree*> florest;
    char *caracter[] = {"a","b","c","d", "e", "f"};
    float vector[] = {0.08, 0.1, 0.12, 0.15, 0.20, 0.35};
    Tree *aux;
    Record r;
    
    for(int i = 0; i < 7; i++){
        
        aux = CreateTree();
        r.key = (char*)malloc(sizeof(char)*5);
        strcpy(r.key,caracter[i]);
        r.freq = vector[i];
        

        insertTree(&aux,r);

        florest.push_back(aux);

    }


    TreeRecursiveInsert(florest, &HT);

    Print(HT);
    return 0;
}