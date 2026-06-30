#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livrosTAD.h"
#include "BSTAD.h"


ListaLivro* createListLivro() {
    ListaLivro *lista = malloc(sizeof(ListaLivro));
    if (lista != NULL) {
        lista->head = NULL;
        lista->size = 0;
    }
    return lista;
}

int registerBook(ListaLivro *lista, Node *root, char *titulo, char *autor, int ano, int newId){

    /*1*/
    if (searchID(root, newId)== 1) {
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

Livro *findBookById(ListaLivro *lista, int id){
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
    Livro *encontrados[QTD];
    int emprestimos = 0;

    while(atual != NULL){
        if(atual->status == 1 && strcmp(atual->emprestadoPara, email) == 0){
            if (emprestimos < QTD) {
                encontrados[emprestimos] = atual;
                emprestimos++;
            }
        }
        atual = atual->next;
    }
    if (!emprestimos) {
        printf("Nenhum livro emprestado para o usuario: %s\n", email);
    }

    for(int i = 0; i < emprestimos; i++){
        for(int j = 0; j < emprestimos - i - 1; j++){
            if(encontrados[j]->id > encontrados[j + 1]->id){
                Livro *temp = encontrados[j];
                encontrados[j] = encontrados[j + 1];
                encontrados[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < emprestimos; i++){
        printf("-------------------------\n");
        printf("ID: %d\n", encontrados[i]->id);
        printf("Titulo: %s\n", encontrados[i]->titulo);
        printf("Autor: %s\n", encontrados[i]->autor);
        printf("Ano: %d\n", encontrados[i]->ano);
        printf("-------------------------\n");
    }

    /*
        percorre a lista e compara os status e o emprestimo, 
        se achar vai armazenar em um vetor pra ordenar os ids e 
        printar as info dos livros emprestados em ordem de id
    */
}

int updateBook(ListaLivro *lista, int id, char *newTitulo, char *newAutor, int newAno){
    Livro *livro= findBookById(lista, id);
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

Node *deleteBook(ListaLivro *lista, Node *root, int id, int *success) {
    Livro *atual = lista->head;
    Livro *anterior = NULL;
    *success = 0;

    while (atual != NULL) {
        if (atual->id == id) {
            if (anterior == NULL) {
                lista->head = atual->next;
            } else {
                anterior->next = atual->next;
            }
            free(atual);
            lista->size--;
            *success = 1;
            return root;
        }
        anterior = atual;
        atual = atual->next;
    }
    return root;

    /*
        percorre a lista, compara id, se achar deleta e decrementa o size
        remove o idda bst e indica sucesso, se nao achar retorna a raiz
    */
}

int loanBook(ListaLivro *lista, int id, char *emprestadoPara) {
    Livro *livro = findBookById(lista, id);
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
    Livro *livro = findBookById(lista, id);
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

void saveBooks(ListaLivro *lista) {
    FILE *arq = fopen("livros.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para salvar os livros.\n");
        return;
    }

    Livro *atual = lista->head;
    while (atual != NULL) {
        char pEmprestimo[QTD];
        if(atual->status == 1 && strlen(atual->emprestadoPara) > 0){
            strcpy(pEmprestimo, atual->emprestadoPara);
        } else {
            strcpy(pEmprestimo, "Sem emprestimo");
        }

        fprintf(arq, "%d;%s;%s;%d;%d;%s\n", atual->id, atual->titulo, atual->autor, atual->ano, atual->status, pEmprestimo);
        atual = atual->next;
    }

    fclose(arq);

    /*
        Abre o arquivo para escrita e percorre a lista de livros
        salvando os dados do livro no arquivo
        pra nao dar bugs que nem estava dando sem colocar nenhum campo no pemprestimo, 
        foi colocado uma descricao de 'sem emprestimo'
    */
}

Node *loadBooks(ListaLivro *lista, Node *root, int *idCount) {
    FILE *arq = fopen("livros.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para carregar os livros.\n");
        return root;
    }

    int id, ano, status;
    char titulo[QTD], autor[QTD], emprestadoPara[QTD];
    int maiorID = 0;

    while (fscanf(arq, "%d;%[^;];%[^;];%d;%d;%[^\n]\n", &id, titulo, autor, &ano, &status, emprestadoPara) == 6) {
        registerBook(lista, root, titulo, autor, ano, id);
        root = insertID(root, id);

        Livro *livro = findBookById(lista, id);
        if (livro != NULL) {
            livro->status = status;
            if(status == 1 && strcmp(emprestadoPara, "Sem emprestimo") != 0) {
                strcpy(livro->emprestadoPara, emprestadoPara);
            } else {
                livro->status = 0;
                strcpy(livro->emprestadoPara, "");
            }
        }
        if(id > maiorID) {
            maiorID = id;
        }
    }

    *idCount = maiorID + 1;
    fclose(arq);
    return root;

    /*
        Abre o arquivo para leitura e percorre o arquivo de livros
        carregando os dados do livro na lista e na arvore binaria de busca
        atualizando o idCount para o maior id + 1
    */
}

void listAllBooks(ListaLivro *lista) {
    if (lista == NULL || lista->head == NULL) {
        printf("Nenhum livro cadastrado no sistema.\n");
        return;
    }
    
    Livro *atual = lista->head;
    printf("\nlista\n");
    while (atual != NULL) {
        printf("ID: %d | Titulo: %s | Status: %s\n", 
               atual->id, atual->titulo, 
               (atual->status == 0) ? "Disponivel" : "Emprestado");
        atual = atual->next;
    }
    printf("=================================\n");
}