#include "tree.hpp"

using namespace std;

int main(){
    
    Tree *HT;
    vector<Tree*> florest;
    //char *caracter[] = {"a","b","c","d", "e", "f"};
    //float vector[] = {0.08, 0.1, 0.12, 0.15, 0.20, 0.35};
    Tree *aux;
    Record r;
    float qtd_words;
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
    MapFreq(&Umap, &qtd_words);

    cout << endl;
    
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
    cout << qtd_words << endl;
    NormalizateFrequencies(&florest, &qtd_words);
    
    /*vector<Tree*>::iterator itv;

    for(itv = florest.begin(); itv != florest.end(); ++itv){

        cout << (*itv)->reg.key << " -> " << (*itv)->reg.freq << endl; 
    }
    */

    TreeRecursiveInsert(florest, &HT);

    cout << "frq raiz: " << HT->reg.freq << endl;
    Print(HT);
    cout << endl;

    map<string, string> CodTable;
    MakesCodificationTable(HT, &CodTable,"","");

    map<string, string>::iterator itr;
    for(itr = CodTable.begin(); itr != CodTable.end(); ++itr){

        cout << itr->first << " -> " << itr->second << endl; 
    }
    

    return 0;
}