#define usuarioTAD_h

#define QTD 150

typedef struct Usuario {
    char nome[QTD];
    char email[QTD];
    struct Usuario *next;
} Usuario;

typedef struct {
    Usuario *head;
    int size;
} ListaUsuario;

ListaUsuario createListUser();
int registerUser(ListaUsuario *head, char *nome, char *email);
Usuario* findUserByEmail(ListaUsuario *lista, char *email);
Usuario* findUserByName(ListaUsuario *lista, char *nome);
int updateUser(ListaUsuario *lista, char *email, char *novoNome);
int deleteUser(ListaUsuario *lista, char *email);
void freeListUser(ListaUsuario *lista);

    /*
        Criação das struct de usuario - Dados (email e nome) um ponteiro para o prox.
        E criação da struct de lista de usuario - Ponteiro para o head e tamanho da lista.

        Criacao das funcoes necessarias para a implementacao:
        - createListUser: Cria uma lista de usuario vazia.
        - registerUser: Registra um usuario na lista.
        - findUserByEmail: Busca um usuario na lista pelo email.
        - findUserByName: Busca um usuario na lista pelo nome.
        - updateUser: Atualiza o nome de um usuario na lista.
        - deleteUser: Deleta um usuario da lista pelo email.
        - freeListUser: Libera a memória alocada para a lista de usuarios.
    */
