#ifndef TREE_H 
#define TREE_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include<vector>
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<sstream>


using namespace std;

typedef struct Record Record;
typedef struct Tree Tree;

struct Record{
	char *key;
	float freq;
};

struct Tree{
	Record reg;
	Tree *esq, *dir;
};

void TreeRecursiveInsert(vector<Tree*> florest, Tree **raiz);
void ReduceFlorest(vector<Tree*> florest, vector<Tree*> *reduce, Tree *node_new);

Tree* CreateTree();
bool TVazia(Tree **t);
void insertTree(Tree **t, Record r);
int isInTree(Tree *t, Record r);

void TreePosition(Tree **t1, Tree **t2,vector<Tree*> florest);
void Print(Tree *t);
void MapFreq(map<string, float> *map_freq, float *qtd_words);
void OrdenaFlorest(vector<Tree*> *florest);
void MakesCodificationTable(Tree *raiz, map<string, string> *CodTable, string binary, string aux);
void NormalizateFrequencies(vector<Tree*> *florest, float *qtd_words); // somente depois de ordenar o vetor.
void EncodingFile(map<string, string> *CodTable);
void DecodingFile(Tree *raiz);

#endif
