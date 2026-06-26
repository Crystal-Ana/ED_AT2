#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livrosTAD.h"


ListaLivro* createListLivro() {
    ListaLivro *lista = malloc(sizeof(ListaLivro));
    if (lista != NULL) {
        lista->head = NULL;
        lista->size = 0;
    }
    return lista;
}

int registerBook(ListaLivro *lista, char *titulo, char *autor, int ano, int newId){

    /*1*/
    if (findBookById(lista, newId) != NULL) {
        return 0;
    }
    /*2*/
    Livro *new = (Livro*) malloc(sizeof(Livro));
    if (new == NULL) {
        return 0;
    }
    new->id = newId;
    strcpy(new->titulo, titulo);
    strcpy(new->autor, autor);
    new->ano = ano;
    /*3*/
    new->status = 0;
    strcpy(new->emprestadoPara, "");
    /*4*/
    new->next = lista->head;
    lista->head = new;
    lista->size++;
    return 1;

    /*
        1- verifica se o livro ja existe;
        2- aloca a memoria e faz os apontamentos;
        3- inicializa o status em 0 como disponivel e o emprestadoPara '' vazio;
        4- insere no inicio da lista e incrementa o size
    */
}

Livro *findBookbyId(ListaLivro *lista, int id){
    Livro *atual = lista->head;
    while (atual != NULL) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;

    /*
        Percorre e compara o id, se achar retorna o livro, se naoretorna null
    */
}

void findBookByAuthor(ListaLivro *lista, char *autor){
    Livro *atual = lista->head;
    int achei = 0;
    while(atual != NULL){
        if(strcmp(atual->autor, autor) ==0){
            printf("ID: %d\n", atual->id);
            printf("Titulo: %s\n", atual->titulo);
            printf("Ano: %d\n", atual->ano);
            printf("Emprestado para: %s\n", atual->emprestadoPara);
            achei = 1;
        }
        atual = atual->next;
    }
    if (!achei) {
        printf("Nenhum livro encontrado para o autor: %s\n", autor);
    }

    /*
        Percorre a lista e compara o autor, se achar printa as informacoes do livro
        se nao printa que nao existe
    */
}

void listLoansByUser(ListaLivro *lista, char *email){
    Livro *atual = lista->head;
    int emprestimos = 0;
    while(atual != NULL){
        if(atual->status == 1 && strcmp(atual->emprestadoPara, email) == 0){
            printf("ID: %d\n", atual->id);
            printf("Titulo: %s\n", atual->titulo);
            printf("Autor: %s\n", atual->autor);
            printf("Ano: %d\n", atual->ano);
            emprestimos++;
        }
        atual = atual->next;
    }
    if (!emprestimos) {
        printf("Nenhum livro emprestado para o usuario: %s\n", email);
    }

    /**
        Percorre a lista e compara o email, se achar printa as informacoes do livro
        se nao printa que nao existe
    */
}

int updateBook(ListaLivro *lista, int id, char *newTitulo, char *newAutor, int newAno){
    Livro *livro= findBookbyId(lista, id);
    if (livro != NULL) {
        strcpy(livro->titulo, newTitulo);
        strcpy(livro->autor, newAutor);
        livro->ano = newAno;
        return 1;
    }
    return 0;

    /*
        Procura o livro pelo id usando a funcao 
        se achar atualiza as informacoes e retorna
    
    */
}

int deleteBook(ListaLivro *lista, int id) {
    Livro *atual = lista->head;
    Livro *anterior = NULL;

    while (atual != NULL) {
        if (atual->id == id) {
            if (anterior == NULL) {
                lista->head = atual->next;
            } else {
                anterior->next = atual->next;
            }
            free(atual);
            lista->size--;
            return;
        }
        anterior = atual;
        atual = atual->next;
    }

    /*
        percorre a lista, compara id, se achar deleta e decrementa o size
    */
}

int loanBook(ListaLivro *lista, int id, char *emprestadoPara) {
    Livro *livro = findBookbyId(lista, id);
    if (livro != NULL && livro->status == 0) {
        livro->status = 1;
        strcpy(livro->emprestadoPara, emprestadoPara);
        return 1;
    }
    return 0;

    /*
        Procura o livro pelo id usando a funcao 
        se achar e estiver disponivel atualiza o status e o emprestadoPara
    */
}

void devolveBook(ListaLivro *lista, int id) {
    Livro *livro = findBookbyId(lista, id);
    if (livro != NULL && livro->status == 1) {
        livro->status = 0;
        strcpy(livro->emprestadoPara, "");
    }

    /*
        Procura o livro pelo id usando a funcao 
        se achar e estiver emprestado atualiza o status e o emprestadoPara
    */
}

void freeListLivro(ListaLivro *lista) {
    Livro *atual = lista->head;
    while (atual != NULL) {
        Livro *temp = atual;
        atual = atual->next;
        free(temp);
    }
    free(lista);

    /*
        Percorre a lista e libera a memoria alocada para cada livro
        e depois libera a memoria alocada para a lista
    */
}
