#ifndef MuriloLopesFuncoes_H
#define MuriloLopesFuncoes_H
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>
#include <locale.h>
#include "MuriloLopesTela.h"
void ler_nome_arquivo(char nomeArquivo[]){
    printf("Digite o nome do arquivo texto (sem a extensao .txt): ");
    fflush(stdin);
    scanf("%[^\n]s",nomeArquivo);
    strcat(nomeArquivo,".txt");
}

int pegar_tamanho_arquivo(FILE *arquivo) {
    int tamanho;
    if (arquivo == NULL)
        return -1;

    fseek(arquivo, 0, SEEK_END);
    tamanho = ftell(arquivo);
    rewind(arquivo);

    return tamanho;
}

char *alocar_espaco_string(int tamanho) {
    return (char *)malloc(sizeof(char) * tamanho);
}


void salvar_linha(COLUNA *coluna, FILE* arquivo, int ultima_linha)
{
    char caracter;
    int i;
    for (i = 0; i <= coluna->tam_logico; i++)
    {
        caracter = coluna->caracter[i];
        fputc(caracter, arquivo);
    }
    ///Verifica se é a ultima linha entao nao adiciona o \n
    ///ultima_linha é igual a 0 quando não é a ultima linha e 1 quando é
    if(ultima_linha == 0)
        fputc('\n', arquivo);
}

void salvar_texto(LINHA *linha)
{
    LINHA *aux;
    FILE *arquivo;
    int ultima_linha = 0;
    arquivo = fopen("MuriloLopes.txt", "w");

    if (vazia_linha(linha))
        return;

    aux = linha->next;
    while (aux->coluna.tam_logico != -2)
    {
        ///se é a ultima linha
        if(aux->next->coluna.tam_logico == -2)
            ultima_linha = 1;
        salvar_linha(&(aux->coluna), arquivo,ultima_linha);
        aux = aux->next;
    }

    fclose(arquivo);
}

void arquivo_ajuda()
{
    setlocale(LC_ALL, "Portuguese");
    FILE *arquivo = fopen("MuriloLopes_ajuda.txt", "r, ccs=UTF-8");

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo MuriloLopes_ajuda.txt\n");
        return;
    }

    wint_t caractere;
    while ((caractere = fgetwc(arquivo)) != WEOF) {
        printf("%c", caractere);
    }

    fclose(arquivo);
}

void armazenar_na_estrutura(char *texto, LINHA *linha){
    int i,tam;
    LINHA *aux;
    tam = strlen(texto);
    criar_nova_linha_na_posicao(linha,0);
    aux = linha->next;
    for(i=0;i<tam;i++)
    {
        if(texto[i] == '\n' || aux->coluna.tam_logico >= 73){
            criar_nova_linha_na_posicao(linha,linha->num_linhas+1);
            aux = aux->next;
        }
        else if(texto[i] != '\n'){
            inserir_posicao_coluna(&(aux->coluna),texto[i],aux->coluna.tam_logico+1);
        }
    }
}

int abrir_arquivo(LINHA *linha) {
    setlocale(LC_ALL, "Portuguese");
    char *texto, nomeArquivo[100];
    wint_t caractere;
    int i=0, tamanho;
    FILE *arquivo;
    ler_nome_arquivo(nomeArquivo);
    arquivo = fopen(nomeArquivo, "r, ccs=UTF-8");

    if (arquivo == NULL) {
        fprintf(stderr, "O Arquivo %s não existe\n", nomeArquivo);
        return 0;
    }
    tamanho = pegar_tamanho_arquivo(arquivo);
    texto = alocar_espaco_string(tamanho);
    while ((caractere = fgetwc(arquivo)) != WEOF) {
        texto[i] = caractere;
        i++;
    }

    fclose(arquivo);
    armazenar_na_estrutura(texto,linha);
    return 1;
}

void info_aluno()
{
    printf("Prontuario: PE300998X\n");
    printf("Nome: Murilo Lopes Fray de Oliveira\n");
    printf("Curso: Bacharelado em Ciência da Computação\n");
    printf("Ano de Ingresso: 2021\n");
    printf("Aperte ESC para sair\n");
}

void rearranjar_texto(LINHA **aux, LINHA *linha, CONTROLADOR controlador)
{
    LINHA *aux2;
    aux2 = *aux;
    while(cheia_coluna(&(aux2->coluna)) && aux2->coluna.tam_logico != -2)
    {
        aux2 = aux2->next;
    }
    if(aux2->coluna.tam_logico == -2)
    {
        criar_nova_linha_na_posicao(linha,linha->num_linhas+1);
        aux2 = linha->back;
    }
    if(controlador.posicao_atual >= 74)
    {
        while(aux2->back != *aux)
        {
            inserir_posicao_coluna(&(aux2->coluna), aux2->back->coluna.caracter[aux2->back->coluna.tam_logico],0);
            remover_posicao_coluna(&(aux2->back->coluna),aux2->back->coluna.tam_logico);
            aux2 = aux2->back;
        }
    }
    else
    {
        while(aux2 != *aux)
        {
            inserir_posicao_coluna(&(aux2->coluna), aux2->back->coluna.caracter[aux2->back->coluna.tam_logico],0);
            remover_posicao_coluna(&(aux2->back->coluna),aux2->back->coluna.tam_logico);
            aux2 = aux2->back;
        }
    }
}

int caracter_valido(int caracter)
{
    return caracter >= 32 && caracter <= 255 && caracter != 173 && (caracter > 160 ||  caracter < 127);
}

#endif


