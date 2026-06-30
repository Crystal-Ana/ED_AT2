#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarioTAD.h"
#include "livrosTAD.h"
#include "BSTAD.h"

void menuCadastro(ListaLivro *listaLivros, Node **root, ListaUsuario *listaUsuarios, int *idContador);
void menuConsulta(ListaLivro *listaLivros, Node *root, ListaUsuario *listaUsuarios);
void menuAtualizacao(ListaLivro *listaLivros, ListaUsuario *listaUsuarios);
void menuExclusao(ListaLivro *listaLivros, Node **root, ListaUsuario *listaUsuarios);

int main() {
    ListaUsuario *listaUsuarios = createListUser();
    ListaLivro *listaLivros = createListLivro();
    Node *root = createBST();
    
    int idContador = 1;
    int opcao;

    loadUser(listaUsuarios);
    root = loadBooks(listaLivros, root, &idContador);

    do {
        printf("\n====================================\n");
        printf("    SISTEMA DE BIBLIOTECA   \n");
        printf("====================================\n");
        printf("1. Cadastro\n");
        printf("2. Consulta\n");
        printf("3. Atualizacao\n");
        printf("4. Exclusao\n");
        printf("5. Emprestimo\n");
        printf("6. Devolucao\n");
        printf("0. Sair\n");
        printf("====================================\n");
        printf("Escolha uma opcao: ");
        if(scanf("%d", &opcao) != 1){
            while(getchar() != '\n');
            opcao = -1; 
        }else{
            getchar();
        }

        switch (opcao) {
            case 1:
                menuCadastro(listaLivros, &root, listaUsuarios, &idContador);
                break;
            case 2:
                menuConsulta(listaLivros, root, listaUsuarios);
                break;
            case 3:
                menuAtualizacao(listaLivros, listaUsuarios);
                break;
            case 4:
                menuExclusao(listaLivros, &root, listaUsuarios);
                break;
            case 5: {
                int id;
                char email[QTD];
                printf("\n--- Emprestimo de Livro ---\n");

                printf("Digite o email de usuario:");
                scanf(" %[^\n]", email);
                getchar();

                if(findUserByEmail(listaUsuarios, email) == NULL) {
                    printf("Usuario nao cadastrado.\n");
                    break;
                }

                printf("Digite o ID do livro: ");
                if(scanf("%d", &id) != 1) { while(getchar() != '\n'); printf("Entrada invalida.\n"); break;}
                getchar();

                if (searchID(root, id) != 1) {
                    printf("Livro nao encontrado.\n");
                    break;
                }

                if (loanBook(listaLivros, id, email)) {
                    printf("Emprestimo realizado com sucesso!\n");
                } else {
                    printf("Nao foi possivel realizar o emprestimo (Livro ja emprestado).\n");
                }
                break;

                /*
                    Solicita o email do usuario e verifica se ele esta cadastrado
                    Solicita o ID do livro e verifica se ele existe na arvore
                    Chama a funcao loanBook para realizar o emprestimo
                */
            }
            case 6: {
                char email[QTD];
                int id;
                printf("\n--- Devolucao de Livro ---\n");
                printf("Digite o email do usuario: ");
                scanf(" %[^\n]", email);
                getchar();
                if(findUserByEmail(listaUsuarios, email) == NULL) {
                    printf("Usuario nao cadastrado.\n");
                    break;
                }

                printf("\n --- Livros Emprestados ---\n");
                listLoansByUser(listaLivros, email);
                printf("\n---------------------------\n");

                printf("Digite o ID do livro a ser devolvido: ");
                if(scanf("%d", &id) != 1){ while(getchar() != '\n'); break;}
                getchar();

                Livro *livro = findBookById(listaLivros, id);
                if(livro == NULL || livro->status == 0 || strcmp(livro->emprestadoPara, email) != 0) {
                    printf("Devolucao nao permitida. Verifique o ID do livro e se ele esta emprestado para o usuario correto.\n");
                } else {
                    devolveBook(listaLivros, id);
                    printf("Devolucao realizada com sucesso!\n");
                }
                break;

                /*
                    Solicita o email do usuario e verifica se ele esta cadastrado
                    Lista os livros emprestados para o usuario
                    Solicita o ID do livro a ser devolvido
                    Verifica se o livro existe, se esta emprestado e se foi emprestado para o usuario correto
                    Chama a funcao devolveBook para realizar a devolucao  
                */
            }
            case 0:
                printf("Finalizando o sistema...\n");
                saveUser(listaUsuarios);
                saveBooks(listaLivros);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    freeListUser(listaUsuarios);
    freeListLivro(listaLivros);
    freeBST(root);

    return 0;
}

void menuCadastro(ListaLivro *listaLivros, Node **root, ListaUsuario *listaUsuarios, int *idContador) {
    int opcao;
    printf("\n--- Menu Cadastro ---\n");
    printf("1. Livros\n");
    printf("2. Usuarios\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &opcao) != 1) { while (getchar() != '\n'); return; }
    getchar();

    if (opcao == 1) {
        char titulo[QTD], autor[QTD];
        int ano;
        printf("Titulo (sem espacos): ");
        scanf(" %[^\n]", titulo);
        printf("Autor (sem espacos): ");
        scanf(" %[^\n]", autor);
        printf("Ano de publicacao: ");
        scanf("%d", &ano);

        if (registerBook(listaLivros, *root, titulo, autor, ano, *idContador)) {
            *root = insertID(*root, *idContador);
            printf("Livro cadastrado com sucesso! ID gerado: %d\n", *idContador);
            (*idContador)++;
        } else {
            printf("Erro: ID ja existente na arvore.\n");
        }
    } else if (opcao == 2) {
        char nome[QTD], email[QTD];
        printf("Nome (sem espacos): ");
        scanf(" %[^\n]", nome);
        printf("Email: ");
        scanf(" %[^\n]", email);

        if (registerUser(listaUsuarios, nome, email)) {
            printf("Usuario cadastrado com sucesso!\n");
        } else {
            printf("Erro: Email ja cadastrado no sistema.\n");
        }
    }
}

void menuConsulta(ListaLivro *listaLivros, Node *root, ListaUsuario *listaUsuarios) {
    int opcao;
    printf("\n--- Menu Consulta ---\n");
    printf("1. Livros por Codigo\n");
    printf("2. Livros por Autor\n");
    printf("3. Usuarios por Email\n");
    printf("4. Usuarios por Nome\n");
    printf("5. Emprestimos por Usuario\n");
    printf("6. Listar Livros\n");
    printf("7. Listar usuarios\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &opcao) != 1) { while (getchar() != '\n'); return; }
    getchar(); //ia salvando vidas

    switch (opcao) {
        case 1: {
            int id;
            printf("Digite o ID do livro: ");
            scanf("%d", &id);
            while (getchar() != '\n');
            Livro *l = findBookById(listaLivros, id);
            if (l != NULL && searchID(root, id) == 1) {
                printf("\nLivro Encontrado:\nID: %d\nTitulo: %s\nAutor: %s\nAno: %d\nStatus: %s\n", 
                       l->id, l->titulo, l->autor, l->ano, (l->status == 0) ? "Disponivel" : "Emprestado");
            } else {
                printf("Livro nao encontrado.\n");
            }
            break;
        }
        case 2: {
            char autor[QTD];
            printf("Digite o autor: ");
            scanf(" %[^\n]", autor); 
            findBookByAuthor(listaLivros, autor);
            break;
        }
        case 3: {
            char email[QTD];
            printf("Digite o email: ");
            scanf(" %[^\n]", email); 
            Usuario *u = findUserByEmail(listaUsuarios, email);
            if (u != NULL) {
                printf("Usuario encontrado: Nome: %s | Email: %s\n", u->nome, u->email);
            } else {
                printf("Usuario nao cadastrado.\n");
            }
            break;
        }
        case 4: {
            char nome[QTD];
            printf("Digite o nome: ");
            scanf(" %[^\n]", nome); 
            findUserByName(listaUsuarios, nome);
            break;
}
        case 5: {
            char email[QTD];
            printf("Digite o email do usuario: ");
            scanf(" %[^\n]", email);
            listLoansByUser(listaLivros, email);
            break;
        }
        case 6: {
            char titulo[QTD];
            int id;
            
            
        }
    }
}

void menuAtualizacao(ListaLivro *listaLivros, ListaUsuario *listaUsuarios) {
    int opcao;
    printf("\n--- Menu Atualizacao ---\n");
    printf("1. Livros\n");
    printf("2. Usuarios\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &opcao) != 1) { while (getchar() != '\n'); return; }
    getchar();

    if (opcao == 1) {
        int id, ano;
        char titulo[QTD], autor[QTD];
        printf("Digite o ID do livro que deseja alterar: ");
        if (scanf("%d", &id) != 1) { while (getchar() != '\n'); return; }
        getchar();
        
        Livro *l = findBookById(listaLivros, id);
        if (l != NULL) {
            printf("Novo Titulo (sem espacos): ");
            scanf(" %[^\n]", titulo);
            printf("Novo Autor (sem espacos): ");
            scanf(" %[^\n]", autor);
            printf("Novo Ano: ");
            if (scanf("%d", &ano) != 1) { while (getchar() != '\n'); return; }
            getchar();
            updateBook(listaLivros, id, titulo, autor, ano);
            printf("Dados do livro atualizados!\n");
        } else {
            printf("Livro nao encontrado.\n");
        }
    } else if (opcao == 2) {
        char email[QTD], nome[QTD];
        printf("Digite o email do usuario que deseja alterar: ");
        scanf(" %[^\n]", email);
        getchar();

        if (findUserByEmail(listaUsuarios, email) != NULL) {
            printf("Novo nome (sem espacos): ");
            scanf(" %[^\n]", nome);
            updateUser(listaUsuarios, email, nome);
            printf("Dados do usuario atualizados!\n");
        } else {
            printf("Usuario nao cadastrado.\n");
        }
    }
}

void menuExclusao(ListaLivro *listaLivros, Node **root, ListaUsuario *listaUsuarios) {
    int opcao;
    printf("\n--- Menu Exclusao ---\n");
    printf("1. Livros\n");
    printf("2. Usuarios\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &opcao) != 1) { while (getchar() != '\n'); return; }
    getchar();

    
    if (opcao == 1) {
        int id, sucesso = 0, status;
        printf("Digite o ID do livro a ser excluido: ");
        scanf("%d", &id);
        
        if (findBookById(listaLivros, id)){
            printf("Nao e possivel excluir o livro, pois ele esta emprestado.\n");
            return;
        }
        
        *root = deleteBook(listaLivros, *root, id, &sucesso);
        if (sucesso) {
            printf("Livro excluido com sucesso!\n");
        } else {
            printf("Nao foi possivel realizar a exclusao (Livro nao encontrado).\n");
        }
    } else if (opcao == 2) {
        char email[QTD];
        printf("Digite o email do usuario a ser excluido: ");
        scanf(" %[^\n]", email);

        if(findBookById(listaLivros, email)) {
            printf("Nao e possivel excluir o usuario, pois ele possui livros emprestados.\n");
            return;
        }

        if (deleteUser(listaUsuarios, email)) {
            printf("Usuario excluido com sucesso!\n");
        } else {
            printf("Nao foi possivel realizar a exclusao (Usuario nao encontrado).\n");
        }
    }

}