#include <stdio.h>

#define livrosTAD_h
#define QTD 150

typedef struct Livro {
    int id;
    char titulo[QTD];
    char autor[QTD];
    int ano;
    int status;
    char  emprestadoPara[QTD];
    struct Livro *next;
} Livro;

typedef struct {
    Livro *head;
    int size;
} ListaLivro;

ListaLivro createListLivro();
int registerBook(ListaLivro *lista, char *titulo, char *autor, int ano, int newId);
Livro* findBookById(ListaLivro *lista, int id);
void findBookByAuthor(ListaLivro *lista, char *autor);
void listLoansByUser(ListaLivro *lista, char *email);
int updateBook(ListaLivro *lista, int id, char *novoTitulo, char *novoAutor, int novoAno);
int deleteBook(ListaLivro *lista, int id);
int loanBook(ListaLivro *lista, int id, char *emprestadoPara);
void devolveBook(ListaLivro *lista, int id);
void freeListLivro(ListaLivro *lista);

    /*
        Criação das struct de livros - Dados (id, titulo, autor, ano, status, emprestadoPara) um ponteiro para o prox.
        E criação da struct de lista de livros - Ponteiro para o head e tamanho da lista.

        Criacao das funcoes necessarias para a implementacao:
        - createListLivro: Cria uma lista de livros vazia.
        - registerBook: Registra um livro na lista.
        - findBookById: Busca um livro na lista pelo ID.
        - findBookByAuthor: Busca livros na lista pelo autor
        - listLoansByUser: Lista os emprestimos de um usuario
        - updateBook: Atualiza as informações de um livro na lista
        - deleteBook: Deleta um livro da lista
        - loanBook: Realiza o emprestimo de um livro
        - devolveBook: Devolve um livro emprestado
        - freeListLivro: Libera a memoria alocada para a lista de livros
    */