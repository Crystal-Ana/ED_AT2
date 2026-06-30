#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int id;
    struct Node *left;
    struct Node *right;
} Node;

Node *createBST();
Node *insertID(Node *root, int id);
int searchID(Node *root, int id);
Node *deleteID(Node *root, int id);
void freeBST(Node *root);

    /*
        Criacao da struct de arvore binaria de busca - Dados (id) e ponteiros para esquerda e direita
        Criacao das funcoes necessarias para a implementacao
        - createBST: Cria uma arvore binaria de busca vazia
        - insertID: Insere um id na arvore
        - searchID: Busca um id na arvore
        - deleteID: Deleta um id da arvore
        - freeBST: Libera a memoria alocada para a arvore
    */