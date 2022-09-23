#include "tree.hpp"

Tree* CreateTree(){
	return NULL;
}

bool TVazia(Tree **t){
  return *t == NULL;
}

void insertTree(Tree **t, Record r){

  if(TVazia(t)){
    *t = (Tree*)malloc(sizeof(Tree));
    (*t)->esq = NULL; 
    (*t)->dir = NULL; 
    (*t)->reg.key = (char*)malloc(sizeof(char)*30); 
    strcpy((*t)->reg.key,r.key);
    (*t)->reg.freq = r.freq;
  }
}

/**
 * @brief Atribui as posições das árvores para montar a Huffman Tree.
 * 
 * @param t1 Primeiro elemento da floresta.
 * @param t2 Segundo elemento da florest.
 * @param florest Vetor de Nós.
 */
void TreePosition(Tree **t1, Tree **t2,vector<Tree*> florest){

  vector<Tree*> :: iterator it;

  bool cont = true;

  for(it = florest.begin(); it != florest.end(); ++it){
    if(cont){
      *t1 = *it;
      cont = false;
    }else{
      *t2 = *it;
      return;
    }
  }
}

/**
 * @brief Monta a árvore de Huffman.
 * 
 * @param florest vetor com todos os nós.
 * @param raiz recebe o endereço da raiz da árvore após montada.
 */
void TreeRecursiveInsert(vector<Tree*> florest, Tree **raiz){
  
  if(florest.size() <= 1){

    for(auto n: florest){
      *raiz = n;
    }
    return;
  }

  Tree *t = CreateTree();
  Tree *p1 = CreateTree();
  Tree *p2 = CreateTree();

  TreePosition(&p1,&p2,florest);

  t = (Tree*)malloc(sizeof(Tree));
  t->esq = p2;
  t->dir = p1; 
  t->reg.key = (char*)malloc(sizeof(char)*30);
  strcpy(t->reg.key,"/");
  t->reg.freq = p1->reg.freq + p2->reg.freq;

  vector<Tree*> reduce;
  ReduceFlorest(florest, &reduce, t);
  
  /*
  for(auto n: florest){cout << n->reg.key << "-" << n->reg.freq << " ";}
  cout << endl;

  for(auto n: reduce){cout << n->reg.key << "-" << n->reg.freq << " ";}
  cout << endl << endl;
  */

  TreeRecursiveInsert(reduce,raiz); //Faz a chamada recursiva.

}

/**
 * @brief Tabela Hash com as frequências de cada palavra.
 * 
 * @param map_freq Endereço da Tabela Hash de Frequência.
 * @param qtd_words Contador de quantidade de palavras no texto.
 */
void MapFreq(map<string, float> *map_freq, float *qtd_words){
  
  ifstream file("./src/input/text.txt");
  
  string str_line;
  string token;
  (*map_freq)["\n"] = 0;
  *qtd_words = 0.0; 
  if(file.is_open()){
      
      while(getline(file, str_line)){

        stringstream sstream(str_line);

        while(getline(sstream, token, ' ')){

          if(map_freq->find(token) != map_freq->end()){

            (*map_freq)[token]++;
          
          }else{

            (*map_freq)[token] = 1;

          }

          (*qtd_words)++;
        }

        (*map_freq)["\n"]++;
      }

  }else{

    cout << "erro ao abrir arquivo!" << endl;
  }

  file.close();
}

/**
 * @brief Faz a remoção dos nós que formarão uma sub-árvore e o insere novamente no vetor de nós.
 * 
 * @param florest Vetor de nós.
 * @param reduce Vetor de nós auxiliar.
 * @param node_new Novo nó criado a partir dos nós iniciais.
 */
void ReduceFlorest(vector<Tree*> florest, vector<Tree*> *reduce, Tree *node_new){
  
  florest.erase(florest.begin());
  florest.erase(florest.begin());
  bool verify = true;

  for(auto n: florest){

    if(node_new->reg.freq <= n->reg.freq && verify){
  
      verify=false;
      reduce->push_back(node_new);

    }
    reduce->push_back(n);
  
  }

  if(verify){

    reduce->push_back(node_new);
  }

}

/**
 * @brief Ordena de de forma crescente o vetor de nós.
 * 
 * @param florest Endereço do Vetor de nós(&florest).
 */
void OrdenaFlorest(vector<Tree*> *florest){

  Tree *aux;
  int i, j;
  for(i = 0; i < florest->size(); i++){

    aux = (*florest)[i];

    for(j = i; (j > 0) && (aux->reg.freq < (*florest)[j-1]->reg.freq); j--){

      (*florest)[j] = (*florest)[j-1];
    }

    (*florest)[j] = aux;
  }
}

/**
 * @brief Faz a normalização das frequancias de cada nó do vetor de nós.
 * 
 * @param florest Endereço do Vetor de nós(&florest).
 * @param qtd_words Contador de palavras.
 */
void NormalizateFrequencies(vector<Tree*> *florest, float *qtd_words){

  float max = (float)florest->back()->reg.freq;
  //cout << max << endl;

  float min = (float)florest->front()->reg.freq;
  //cout << min << endl;
  
  for(int i = 0; i < florest->size(); i++){

    (*florest)[i]->reg.freq = (*florest)[i]->reg.freq/(*qtd_words);

  }
}

/**
 * @brief Cria a Tabela Hash de Codificação.
 * 
 * @param raiz Raiz da Árvore de Huffman.
 * @param CodTable Endereço da Tabela Hash de Codificação(&CodTable).
 * @param binary String de 0's e 1's.
 * @param aux string auxiliar.
 */
void MakesCodificationTable(Tree *raiz, map<string, string> *CodTable, string binary, string aux){
  
  if(!(raiz == NULL)){
    
    binary.append(aux);
    MakesCodificationTable(raiz->esq,CodTable,binary,"0");
    MakesCodificationTable(raiz->dir,CodTable,binary,"1");
    string convert = raiz->reg.key;
    (*CodTable)[convert] = binary;
  }
}

/**
 * @brief Cria o arquivo de Codificação.
 * 
 * @param CodTable Endereço da Tabela Hash de Codificação(&CodTable).
 */
void EncodingFile(map<string, string> *CodTable){

  ifstream file("./src/input/text.txt");
  ofstream exit_file("./src/input/output.txt");

  string str_line;
  string token;

  if(file.is_open()){
      
    while(getline(file, str_line)){

      stringstream sstream(str_line);

      while(getline(sstream, token, ' ')){
        
        if(CodTable->find(token) != CodTable->end()){

          exit_file << (*CodTable)[token];
          cout << token << endl;
        }
      }

      exit_file << (*CodTable)["\n"];
    }

  }else{

    cout << "erro ao abrir arquivo!" << endl;
  }

  file.close();
  exit_file.close();
}

/**
 * @brief Decodifica o arquivo codificado.
 * 
 * @param raiz Raiz da Árvore de Huffman.
 */
void DecodingFile(Tree *raiz){

  ifstream exit_file("./src/input/output.txt");
  ofstream decodification_file("./src/output/exit_file.txt");
  char caracter;
  Tree *aux;
  aux = raiz;

  if(exit_file.is_open()){

    while(exit_file.get(caracter)){

      if(!(aux == NULL)){
        
        if(caracter == '0'){

          aux = aux->esq;

        }else{

          aux = aux->dir;
        }

        if(!(strcmp(aux->reg.key,"/") == 0)){
          
          if(!(strcmp(aux->reg.key,"\n") == 0 )){
            decodification_file << aux->reg.key << " ";
          }else{
            decodification_file << aux->reg.key;
          }
          aux = raiz;
        
        }
      }
    }
  }

  exit_file.close();
  decodification_file.close();
}

int isInTree(Tree *t, Record r) {
  
  if(t == NULL){ 
    return 0;
  }
  
  return t->reg.key == r.key || isInTree(t->esq, r) || isInTree(t->dir, r);
}

void Print(Tree *t)
{
  if(!(t == NULL)){
    
    Print(t->esq);
    if(strcmp(t->reg.key, "/") != 0){
      printf("%s ", t->reg.key);
    } 
    Print(t->dir); 
  }
}


