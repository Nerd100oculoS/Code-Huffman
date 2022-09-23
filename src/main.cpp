#include "tree.hpp"


using namespace std;

int main(){
    
    Tree *HT;
    vector<Tree*> florest;
    char *caracter[] = {"a","b","c","d", "e", "f"};
    float vector[] = {0.08, 0.1, 0.12, 0.15, 0.20, 0.35};
    Tree *aux;
    Record r;

    map<string, float> Umap;
    
    /*for(int i = 0; i < 6; i++){
        
        aux = CreateTree();
        r.key = (char*)malloc(sizeof(char)*5);
        strcpy(r.key,caracter[i]);
        r.freq = vector[i];
        

        insertTree(&aux,r);

        florest.push_back(aux);

    }
    */
    MapFreq(&Umap);

    map<string, float>::iterator it;

    for(it = Umap.begin(); it != Umap.end(); ++it){
        
        aux = CreateTree();
        r.key = (char*)malloc(sizeof(char)*5);
        strcpy(r.key,it->first.c_str());
        r.freq = it->second;
        
        insertTree(&aux,r);

        florest.push_back(aux);
        
    }
    
    OrdenaFlorest(&florest);

    TreeRecursiveInsert(florest, &HT);

    Print(HT);

    return 0;
}