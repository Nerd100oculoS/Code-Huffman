#include "tree.hpp"

using namespace std;

int main(){
    
// (1) ----------------------------------> Variaveis Gerais.
    Tree *HT;
    vector<Tree*> florest;
    
    Tree *aux;
    Record r;
    float qtd_words;

// (2) ----------------------------------> Faz a cmputação das frequências.
    map<string, float> Umap;
    MapFreq(&Umap, &qtd_words);

// (3) ----------------------------------> Monta a Floresta de nós.
    map<string, float>::iterator it;
    for(it = Umap.begin(); it != Umap.end(); ++it){
        
        aux = CreateTree();
        r.key = (char*)malloc(sizeof(char)*5);
        strcpy(r.key,it->first.c_str());
        r.freq = it->second;
        
        insertTree(&aux,r);

        florest.push_back(aux);
        
    }

// (4) ----------------------------------> Ordena a floresta, faz a normalização de frequências e constroi a Árvore de Huffman.
    OrdenaFlorest(&florest);
    NormalizateFrequencies(&florest, &qtd_words);
    TreeRecursiveInsert(florest, &HT);
    
    //Print(HT);

// (5) ----------------------------------> Cria a Tabela de Codificação.
    map<string, string> CodTable;
    MakesCodificationTable(HT, &CodTable,"","");

// (6) ----------------------------------> Codifica o texto.
    EncodingFile(&CodTable);

// (1) ----------------------------------> Decodifica o arquivo de bits.
    DecodingFile(HT);

    return 0;
}