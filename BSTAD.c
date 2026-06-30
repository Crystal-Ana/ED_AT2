#include <stdlib.h>
#include <stdio.h>
#include "BSTAD.h"

Node *createBST() {
    return NULL;
}

Node *insertID(Node *root, int id) {
    if (root == NULL){
        Node *new = (Node*) malloc(sizeof(Node));
        if (new != NULL) {
            new->id = id;
            new->left = NULL;
            new->right = NULL;
        }
        return new;
    }
    if (id < root->id) {
        root->left = insertID(root->left, id);
    } else if (id > root->id) {
        root->right = insertID(root->right, id);
    }
    return root;

    /*
        Se a raiz for nula, aloca memoria para um novo no e inicializa os ponteiros
        Se o id for menor que o id da raiz, chama recursivamente a funcao para a subarvore esquerda
        Se o id for maior que o id da raiz, chama recursivamente a funcao para a subarvore direita
        Retorna a raiz
    */
}

int searchID(Node *root, int id) {
    if (root == NULL) {
        return 0;
    }
    if (id == root->id) {
        return 1;
    } else if (id < root->id) {
        return searchID(root->left, id);
    } else {
        return searchID(root->right, id);
    }

    /*
        Se a raiz for nula, retorna 0
        Se o id for igual ao id da raiz, retorna 1
        Se o id for menor que o id da raiz, chama recursivamente a funcao para a subarvore esquerda
        Se o id for maior que o id da raiz, chama recursivamente a funcao para a subarvore direita
    */
}

static Node *Min(Node *root){
    Node *atual = root;
    while (atual && atual->left != NULL) {
        atual = atual->left;
    }
    return atual;

    /*
        Percorre a subarvore esquerda ate encontrar o menor elemento
        Retorna o menor elemento
    */
}

Node *deleteID(Node *root, int id) {
    if (root == NULL) {
        return root;
    }
    if (id < root->id) {
        root->left = deleteID(root->left, id);
    } else if (id > root->id) {
        root->right = deleteID(root->right, id);
    } else {
        if (root->left == NULL) {
            Node *aux = root->right;
            free(root);
            return aux;
        } else if (root->right == NULL) {
            Node *aux = root->left;
            free(root);
            return aux;
        }
        Node *aux = Min(root->right);
        root->id = aux->id;
        root->right = deleteID(root->right, aux->id);
    }
    return root;

    /*
        Se a raiz for nula, retorna a raiz
        Se o id for menor que o id da raiz chama recursivamente a funcao para a subarvore esquerda
        Se o id for maior que o id da raiz chama recursivamente a funcao para a subarvore direita
        Se o id for igual ao id da raiz verifica se o no tem filhos
            Se nao tiver filhos libera a memoria e retorna NULL
            Se tiver um filho libera a memoria e retorna o filho
            Se tiver dois filhos encontra o menor elemento da subarvore direita copia o valor para a raiz e chama recursivamente a funcao para deletar o menor elemento da subarvore direita
        Retorna a raiz
    */
}

void freeBST(Node *root) {
    if (root == NULL) {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
    free(root);

    /*
        Percorre a arvore em pos-ordem e libera a memoria alocada para cada no
    */
}