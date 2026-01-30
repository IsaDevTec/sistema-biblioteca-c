#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LIVROS 100
#define MAX_USUARIOS 50
#define MAX_TITULO 50
#define MAX_AUTOR 30
#define MAX_NOME 50

typedef struct {
    int codigo;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
    int emprestado; // 0 = disponivel, 1 = emprestado
} Livro;

typedef struct {
    int matricula;
    char nome[MAX_NOME];
} Usuario;

// Variaveis globais
Livro livros[MAX_LIVROS];
Usuario usuarios[MAX_USUARIOS];
int totalLivros = 0;
int totalUsuarios = 0;

// Funcoes
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void cadastrarLivro() {
    if (totalLivros >= MAX_LIVROS) {
        printf("Limite de livros atingido.\n");
        return;
    }

    Livro l;
    printf("Codigo do livro: ");
    scanf("%d", &l.codigo);
    while(getchar() != '\n'); // Limpeza robusta do buffer

    printf("Titulo do livro: ");
    fgets(l.titulo, MAX_TITULO, stdin);
    l.titulo[strcspn(l.titulo, "\n")] = '\0';

    printf("Autor do livro: ");
    fgets(l.autor, MAX_AUTOR, stdin);
    l.autor[strcspn(l.autor, "\n")] = '\0';

    printf("Ano de publicacao: ");
    scanf("%d", &l.ano);
    l.emprestado = 0;

    livros[totalLivros++] = l;
    printf("Livro cadastrado com sucesso!\n");
}

void cadastrarUsuario() {
    if (totalUsuarios >= MAX_USUARIOS) {
        printf("Limite de usuarios atingido.\n");
        return;
    }

    Usuario u;
    printf("Matricula do usuario: ");
    scanf("%d", &u.matricula);
    while(getchar() != '\n'); // Limpeza do buffer

    printf("Nome do usuario: ");
    fgets(u.nome, MAX_NOME, stdin);
    u.nome[strcspn(u.nome, "\n")] = '\0';

    usuarios[totalUsuarios++] = u;
    printf("Usuario cadastrado com sucesso!\n");
}

void listarLivros() {
    printf("\n=== LISTA DE LIVROS ===\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("Codigo: %d | Titulo: %s | Autor: %s | Ano: %d | %s\n",
               livros[i].codigo, livros[i].titulo, livros[i].autor,
               livros[i].ano, livros[i].emprestado ? "Emprestado" : "Disponivel");
    }
}

void listarUsuarios() {
    printf("\n=== LISTA DE USUARIOS ===\n");
    for (int i = 0; i < totalUsuarios; i++) {
        printf("Matricula: %d | Nome: %s\n", usuarios[i].matricula, usuarios[i].nome);
    }
}

Livro* buscarLivro(int codigo) {
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].codigo == codigo) return &livros[i];
    }
    return NULL;
}

Usuario* buscarUsuario(int matricula) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].matricula == matricula) return &usuarios[i];
    }
    return NULL;
}

void emprestarLivro() {
    int cod, mat;
    printf("Codigo do livro: ");
    scanf("%d", &cod);
    printf("Matricula do usuario: ");
    scanf("%d", &mat);

    Livro* l = buscarLivro(cod);
    Usuario* u = buscarUsuario(mat);

    if (l == NULL) {
        printf("Livro nao encontrado.\n");
        return;
    }
    if (u == NULL) {
        printf("Usuario nao encontrado.\n");
        return;
    }
    if (l->emprestado) {
        printf("Livro ja esta emprestado.\n");
        return;
    }

    l->emprestado = 1;
    printf("Emprestimo realizado com sucesso para %s!\n", u->nome);
}

void devolverLivro() {
    int cod;
    printf("Codigo do livro para devolucao: ");
    scanf("%d", &cod);

    Livro* l = buscarLivro(cod);

    if (l == NULL) {
        printf("Livro nao encontrado.\n");
        return;
    }
    if (!l->emprestado) {
        printf("Livro nao esta emprestado.\n");
        return;
    }

    l->emprestado = 0;
    printf("Livro devolvido com sucesso!\n");
}

int main() {
    int opcao;

    do {
        printf("\n=== SISTEMA DE BIBLIOTECA ===\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Cadastrar Usuario\n");
        printf("3 - Listar Livros\n");
        printf("4 - Listar Usuarios\n");
        printf("5 - Emprestar Livro\n");
        printf("6 - Devolver Livro\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); // Limpa entrada invalida
            continue;
        }
        limparTela();

        switch(opcao) {
            case 1: cadastrarLivro(); break;
            case 2: cadastrarUsuario(); break;
            case 3: listarLivros(); break;
            case 4: listarUsuarios(); break;
            case 5: emprestarLivro(); break;
            case 6: devolverLivro(); break;
            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}
