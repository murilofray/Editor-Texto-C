#ifndef MuriloLopesEstrutura_H
#define MuriloLopesEstrutura_H
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<locale.h>
#include<string.h>
#include<conio.h>
#define TAM 74

///CRIANDO STRUCTS

typedef struct sControlador{
    int linha_atual;
    int posicao_atual;
    int insert;
}CONTROLADOR;

typedef struct sColuna {
    char caracter[TAM];
    int tam_logico;
} COLUNA;

typedef struct sLinha {
    COLUNA coluna;
    struct sLinha *next;
    struct sLinha *back;
    int num_linhas;
} LINHA;

///FUNÇÕES CONTROLADOR
void inicializar_controlador(CONTROLADOR *controlador){
    controlador->linha_atual = 0;
    controlador->posicao_atual = 0;
    controlador->insert = -1;
}
///FUNÇÕES COLUNA
void inicializar_coluna(COLUNA *coluna) {
    coluna->tam_logico = -1;
}

int cheia_coluna(COLUNA *coluna) {
    return (coluna->tam_logico == TAM - 1);
}

int vazia_coluna(COLUNA *coluna) {
    return (coluna->tam_logico == -1);
}

// A variável tipo é 1 para funções de inserir ou 0 para outras coisas
int posicao_valida_coluna(COLUNA *coluna, int tipo, int posicao) {
    return (posicao >= 0 && posicao <= coluna->tam_logico + tipo && posicao < TAM);
}

void inserir_posicao_coluna(COLUNA *coluna, char caracter, int posicao) {
    int i;
    if (!(posicao_valida_coluna(coluna, 1, posicao)))
        return;

    for (i = coluna->tam_logico + 1; i >= posicao; i--)
        coluna->caracter[i] = coluna->caracter[i - 1];
    coluna->caracter[posicao] = caracter;
    coluna->tam_logico++;
}

void remover_posicao_coluna(COLUNA *coluna, int posicao) {
    int i;
    if (vazia_coluna(coluna) || !(posicao_valida_coluna(coluna, 0, posicao)))
        return;
    for (i = posicao; i < coluna->tam_logico; i++)
        coluna->caracter[i] = coluna->caracter[i + 1];
    coluna->tam_logico--;
}

void exibir_coluna(COLUNA *coluna) {
    int i;
    if (vazia_coluna(coluna))
        return;
    for (i = 0; i <= coluna->tam_logico; i++)
        printf("%c", coluna->caracter[i]);
}

///FUNÇÕES LINHAS
LINHA *getnode() {
    LINHA *linha = (LINHA *)malloc(sizeof(LINHA));
    if (linha != NULL) {
        inicializar_coluna(&(linha->coluna));
        linha->next = NULL;
        linha->back = NULL;
    }
    return linha;
}

void freenode(LINHA *q) {
    free(q);
}

void inicializar_linha(LINHA **linha) {
    LINHA *q = getnode();
    if (q == NULL)
        return;
    q->coluna.tam_logico = -2;
    q->next = q;
    q->back = q;
    q->num_linhas = -1;
    *linha = q;
}

int vazia_linha(LINHA *linha) {
    return (linha->coluna.tam_logico == -2 && linha->next->coluna.tam_logico == -2);
}

// A variável tipo é 1 para funções de inserir ou 0 para outras coisas
int posicao_valida_linha(LINHA *linha, int tipo, int posicao) {
    return (posicao >= 0 && posicao <= linha->num_linhas + tipo);
}

void criar_nova_linha_na_posicao(LINHA *linha, int posicao) {
    LINHA *q, *aux;
    int i;
    q = getnode();
    if (q == NULL || !(posicao_valida_linha(linha,1,posicao)))
        return;
    linha->num_linhas++;
    aux = linha->next;
    for (i = 0; i < posicao; i++)
        aux = aux->next;
    q->next = aux;
    q->back = aux->back;
    aux->back->next = q;
    aux->back = q;
}

void remove_linha_posicao(LINHA *linha, int posicao) {
    LINHA *q, *anterior;
    int i;
    if (vazia_linha(linha) || !(posicao_valida_linha(linha,0,posicao)))
        return;
    linha->num_linhas--;
    q = linha->next;
    for (i = 0; i < posicao; i++) {
        q = q->next;
    }
    if (q->next == linha && q->back == linha) {
        linha->next = linha;
        linha->back = linha;
        return;
    }
    anterior = q->back;
    anterior->next = q->next;
    q->next->back = anterior;
    freenode(q);
}

void exibir_todas_linhas(LINHA *linha) {
    LINHA *aux;
    int numeroLinha = 0;
    if (vazia_linha(linha))
        return;
    aux = linha->next;
    while (aux->coluna.tam_logico != -2) {
        exibir_coluna(&(aux->coluna));
        aux = aux->next;
        printf("\n");
        numeroLinha++;
    }

}

void limpar_estrutura(LINHA *linha) {
    while (!vazia_linha(linha)) {
        remove_linha_posicao(linha,linha->num_linhas);
    }
}

#endif
