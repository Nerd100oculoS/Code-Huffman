#include "tree.hpp"

using namespace std;

int main(){
    
// -------------------------------------> Variaveis Gerais.
    Tree *HT;
    vector<Tree*> florest;
    
    Tree *aux;
    Record r;
    float qtd_words;

// (1) ----------------------------------> Faz a cmputação das frequências.
    map<string, float> Umap;
    MapFreq(&Umap, &qtd_words);

// (2) ----------------------------------> Monta a Floresta de nós.
    map<string, float>::iterator it;
    for(it = Umap.begin(); it != Umap.end(); ++it){
        
        aux = CreateTree();
        r.key = (char*)malloc(sizeof(char)*5);
        strcpy(r.key,it->first.c_str());
        r.freq = it->second;
        
        insertTree(&aux,r);

        florest.push_back(aux);
        
    }

// (3) ----------------------------------> Ordena a floresta, faz a normalização de frequências e constroi a Árvore de Huffman.
    OrdenaFlorest(&florest);
    NormalizateFrequencies(&florest, &qtd_words);
    TreeRecursiveInsert(florest, &HT);
    
    //Print(HT);

// (4) ----------------------------------> Cria a Tabela de Codificação.
    map<string, string> CodTable;
    MakesCodificationTable(HT, &CodTable,"","");

// (5) ----------------------------------> Codifica o texto.
    EncodingFile(&CodTable);

// (6) ----------------------------------> Decodifica o arquivo de bits.
    DecodingFile(HT);

    return 0;
}