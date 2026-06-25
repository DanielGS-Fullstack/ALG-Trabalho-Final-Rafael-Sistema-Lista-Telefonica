/*
Sistema de Gerenciamento de Contatos
Trabalho em C - Structs, vetores e arquivos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 100
#define ARQUIVO "contatos.dat"

/* Estrutura do contato */
typedef struct {
    char nome[50];
    char email[50];
    char telefone[20];
    char tipo[20];
} Contato;

Contato contatos[MAX_CONTATOS];
int totalContatos = 0;

/* Funções principais */
void menu();
void carregar();
void salvar();

void cadastrar();
void alterar();
void apagar();
void procurar();
void listar();

int buscar(char nome[]);

/* ================= MAIN ================= */
int main() {

    int opcao;

    carregar();

    do {

        menu();

        scanf("%d", &opcao);
        while(getchar() != '\n');

        switch(opcao) {

            case 1: cadastrar(); break;
            case 2: alterar(); break;
            case 3: apagar(); break;
            case 4: procurar(); break;
            case 5: listar(); break;

            case 6:
                salvar();
                printf("\n[INFO] Programa encerrado.\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida.\n");
        }

    } while(opcao != 6);

    return 0;
}

/* ================= MENU ================= */
void menu() {

    printf("\n");
    printf("+---------------------------------------------------+\n");
    printf("|        SISTEMA DE GERENCIAMENTO DE CONTATOS       |\n");
    printf("+---------------------------------------------------+\n");
    printf("| [1] Cadastrar contato                             |\n");
    printf("| [2] Alterar contato                               |\n");
    printf("| [3] Apagar contato                                |\n");
    printf("| [4] Procurar contato                              |\n");
    printf("| [5] Lista de contatos                             |\n");
    printf("| [6] Salvar e sair                                 |\n");
    printf("+---------------------------------------------------+\n");

    printf("Escolha uma opcao: ");
}

/* ================= ARQUIVO ================= */
void carregar() {

    FILE *arq = fopen(ARQUIVO, "rb");

    if(arq == NULL) return;

    fread(&totalContatos, sizeof(int), 1, arq);
    fread(contatos, sizeof(Contato), totalContatos, arq);

    fclose(arq);
}

void salvar() {

    FILE *arq = fopen(ARQUIVO, "wb");

    if(arq == NULL) {
        printf("\n[ERRO] Falha ao salvar.\n");
        return;
    }

    fwrite(&totalContatos, sizeof(int), 1, arq);
    fwrite(contatos, sizeof(Contato), totalContatos, arq);

    fclose(arq);
}

/* ================= BUSCA (ignora maiusculas) ================= */
char minusculo(char c) {
    if(c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

int comparar(char a[], char b[]) {

    int i = 0;

    while(a[i] != '\0' && b[i] != '\0') {

        if(minusculo(a[i]) != minusculo(b[i]))
            return 0;

        i++;
    }

    return (a[i] == '\0' && b[i] == '\0');
}

int buscar(char nome[]) {

    int i;

    for(i = 0; i < totalContatos; i++) {

        if(comparar(contatos[i].nome, nome))
            return i;
    }

    return -1;
}

/* ================= CADASTRO ================= */
void cadastrar() {

    if(totalContatos >= MAX_CONTATOS) {
        printf("\n[ERRO] Agenda cheia.\n");
        return;
    }

    printf("\nNome: ");
    fgets(contatos[totalContatos].nome, 50, stdin);
    contatos[totalContatos].nome[strcspn(contatos[totalContatos].nome, "\n")] = '\0';

    printf("Email: ");
    fgets(contatos[totalContatos].email, 50, stdin);
    contatos[totalContatos].email[strcspn(contatos[totalContatos].email, "\n")] = '\0';

    printf("Telefone: ");
    fgets(contatos[totalContatos].telefone, 20, stdin);
    contatos[totalContatos].telefone[strcspn(contatos[totalContatos].telefone, "\n")] = '\0';

    printf("Tipo: ");
    fgets(contatos[totalContatos].tipo, 20, stdin);
    contatos[totalContatos].tipo[strcspn(contatos[totalContatos].tipo, "\n")] = '\0';

    totalContatos++;
    salvar();

    printf("\n[SUCESSO] Contato cadastrado.\n");
}

/* ================= ALTERAR ================= */
void alterar() {

    char nome[50];
    int pos;

    printf("\nNome do contato: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    pos = buscar(nome);

    if(pos == -1) {
        printf("\n[ERRO] Nao encontrado.\n");
        return;
    }

    printf("\nNovo nome: ");
    fgets(contatos[pos].nome, 50, stdin);
    contatos[pos].nome[strcspn(contatos[pos].nome, "\n")] = '\0';

    printf("Novo email: ");
    fgets(contatos[pos].email, 50, stdin);
    contatos[pos].email[strcspn(contatos[pos].email, "\n")] = '\0';

    printf("Novo telefone: ");
    fgets(contatos[pos].telefone, 20, stdin);
    contatos[pos].telefone[strcspn(contatos[pos].telefone, "\n")] = '\0';

    printf("Novo tipo: ");
    fgets(contatos[pos].tipo, 20, stdin);
    contatos[pos].tipo[strcspn(contatos[pos].tipo, "\n")] = '\0';

    salvar();

    printf("\n[SUCESSO] Alterado.\n");
}

/* ================= APAGAR ================= */
void apagar() {

    char nome[50];
    int pos, i;

    printf("\nNome para apagar: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    pos = buscar(nome);

    if(pos == -1) {
        printf("\n[ERRO] Nao encontrado.\n");
        return;
    }

    for(i = pos; i < totalContatos - 1; i++) {
        contatos[i] = contatos[i + 1];
    }

    totalContatos--;
    salvar();

    printf("\n[SUCESSO] Removido.\n");
}

/* ================= PROCURAR ================= */
void procurar() {

    char nome[50];
    int pos;

    printf("\nNome: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    pos = buscar(nome);

    if(pos == -1) {
        printf("\n[ERRO] Nao encontrado.\n");
        return;
    }

    printf("\n+-----------------------------------------------+\n");
    printf("|              DADOS DO CONTATO                |\n");
    printf("+-----------------------------------------------+\n");
    printf("Nome     : %s\n", contatos[pos].nome);
    printf("Email    : %s\n", contatos[pos].email);
    printf("Telefone : %s\n", contatos[pos].telefone);
    printf("Tipo     : %s\n", contatos[pos].tipo);
}

/* ================= LISTA ================= */
void listar() {

    int i;

    printf("\n+-----------------------------------------------+\n");
    printf("|              LISTA DE CONTATOS               |\n");
    printf("+-----------------------------------------------+\n");

    if(totalContatos == 0) {
        printf("| Nenhum contato cadastrado                   |\n");
        return;
    }

    printf("| Nº   | Nome                                 |\n");
    printf("+-----------------------------------------------+\n");

    for(i = 0; i < totalContatos; i++) {
        printf("| %03d  | %-35s |\n", i + 1, contatos[i].nome);
    }

    printf("+-----------------------------------------------+\n");
    printf("| Total: %d | Vagas restantes: %d             |\n",
           totalContatos, MAX_CONTATOS - totalContatos);
    printf("+-----------------------------------------------+\n");
}
