#include "usuarioTAD.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
    
ListaUsuario* createListUser() {
    ListaUsuario *lista = malloc(sizeof(ListaUsuario));
    if (lista != NULL) {
        lista->head = NULL;
        lista->size = 0;
    }
    return lista;
}

int registerUser(ListaUsuario *head, char *nome, char *email){
    if (findUserByEmail(head, email) != NULL) {
        return 0;}

    Usuario *new = (Usuario*) malloc(sizeof(Usuario));
    if (new == NULL) {
        return 0;
    }
    strcpy(new->nome, nome);
    strcpy(new->email, email);

    new->next = head->head;
    head->head = new;
    head->size++;
    return 1;

    /*
        Verifica se o email ta na lista - retorna 0 se sim;
        Aloca a memoria e se nao der retorna 0;
        copia o nome e o email para o novo cadastrado;
        insere no inicio da lista e incrementa o size
        retorna 1 para dizer q funcionou
    */
}

Usuario* findUserByEmail(ListaUsuario *lista, char *email) {
    Usuario *noAtual = lista->head;
    while (noAtual != NULL) {
        if (strcmp(noAtual->email, email) == 0) {
            return noAtual;
        }
        noAtual = noAtual->next;
    }
    return NULL;

    /*
        Percorre a lista e compara o email;
        se encontrar retorna o usuario, se nao retorna NULL
    */
}
Usuario* findUserByName(ListaUsuario *lista, char *nome) {
    Usuario *noAtual = lista->head;
    int i = 0;
    while (noAtual != NULL) {
        if (strcmp(noAtual->nome, nome) == 0) {
            printf("Usuario encontrado: %s, %s\n", noAtual->nome, noAtual->email);
            i = 1;
        }
        noAtual = noAtual->next;
    }
    if (i == 0) {
        printf("Usuario nao encontrado\n");
    }
    return NULL;

    /*
        Percorre a lista e compara o nome;
        se encontrar o usuario printa que achou, se nao printa que nao existe
    */
}

int updateUser(ListaUsuario *lista, char *email, char *novoNome){
    Usuario *usuario = findUserByEmail(lista, email);
    if (usuario != NULL) {
        strcpy(usuario->nome, novoNome);
        return 1;
    }
    return 0;

    /*
        Busca o usuario pelo email, se encontrar atualiza o nome e retorna 1, se nao retorna 0
    */
}

int deleteUser(ListaUsuario *lista, char *email) {
   /*usei ia para me ajudar*/
   Usuario *atual = lista->head;
    Usuario *anterior = NULL;
    
     while (atual != NULL) {
          if (strcmp(atual->email, email) == 0) {
                if (anterior == NULL) {
                 lista->head = atual->next;
                } else {
                 anterior->next = atual->next;
                }
                free(atual);
                lista->size--;
                return 1; 
          }
          anterior = atual;
          atual = atual->next;
     }
     return 0; 
}

void freeListUser(ListaUsuario *lista){
    /* usei ia para me ajudar*/
    if (lista == NULL) {
        return;
    }
    Usuario *atual = lista->head;
    Usuario *proximo;
    while (atual != NULL) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    
    free(lista);
}

void saveUser(ListaUsuario *lista) {
    FILE *arq = fopen("usuarios.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para salvar usuarios.\n");
        return;
    }

    Usuario *atual = lista->head;
    while (atual != NULL) {
        fprintf(arq, "%s,%s\n", atual->nome, atual->email);
        atual = atual->next;
    }

    fclose(arq);

    /* 
         Abre o arquivo para escrita e percorre a lista de usuarios
          salvando os dados do usuario no arquivo
    */
}

void loadUser(ListaUsuario *lista) {
    FILE *arq = fopen("usuarios.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para carregar usuarios.\n");
        return;
    }

    char nome[QTD], email[QTD];
    while (fscanf(arq, "%[^,],%s\n", nome, email) == 2) {
        registerUser(lista, nome, email);
    }

    fclose(arq);

    /*
        Abre o arquivo para leitura e percorre o arquivo de usuarios
        carregando os dados do usuario na lista
    */
}

void listAllUsers(ListaUsuario *lista) {
    if (lista == NULL || lista->head == NULL) {
        printf("Nenhum usuario cadastrado no sistema.\n");
        return;
    }
    
    Usuario *atual = lista->head;
    printf("\nlista\n");
    while (atual != NULL) {
        printf("Nome: %s | Email: %s\n", atual->nome, atual->email);
        atual = atual->next;
    }
    printf("===================================\n");
}