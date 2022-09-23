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

  /*for(auto n: florest){cout << n->reg.key << "-" << n->reg.freq << " ";}
  cout << endl;

  for(auto n: reduce){cout << n->reg.key << "-" << n->reg.freq << " ";}
  cout << endl << endl;
  */
  TreeRecursiveInsert(reduce,raiz);

}

void MapFreq(map<string, float> *map_freq){
  
  ifstream file("./src/input/text.txt");
  
  string str_line;
  string token;
  if(file.is_open()){
      
      while(getline(file, str_line)){

        stringstream sstream(str_line);

        while(getline(sstream, token, ' ')){

          if(map_freq->find(token) != map_freq->end()){

            (*map_freq)[token]++;
          
          }else{

            (*map_freq)[token] = 1;

          }
        }
      }

  }else{

    cout << "erro ao abrir arquivo!" << endl;
  }
  
}


void ReduceFlorest(vector<Tree*> florest, vector<Tree*> *reduce, Tree *node_new){
  
  florest.erase(florest.begin());
  florest.erase(florest.begin());
  int cont = 1;
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


