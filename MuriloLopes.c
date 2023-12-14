#include <stdio.h>
#include <stdlib.h>
#include "MuriloLopesEstrutura.h"
#include "MuriloLopesTeclas.h"
#include "MuriloLopesTela.h"
#include <locale.h>
#define TAM 74

void main()
{
    setlocale(LC_ALL, "Portuguese");
    LINHA *linha;
    LINHA *aux;
    CONTROLADOR controlador;
    wchar_t caracter;
    fixar_tamanho_console();
    inicializar_controlador(&controlador);
    inicializar_linha(&linha);
    //crio a primeira linha
    criar_nova_linha_na_posicao(linha,0);
    aux = linha->next;
    meu_gotoxy(&controlador);
    do
    {
        caracter = _getwch();
        if (caracter == 0 || caracter == 224)
        {
            caracter = _getwch();  // Captura o segundo byte da tecla especial
            teclas_especiais(linha, &aux, caracter, &controlador);
        }
        else
        {
            teclas_ascii(linha, &aux, caracter, &controlador);
        }

    }
    while(caracter != 27);
    /// Dou freenode em todos meu nó
    limpar_estrutura(linha);
    /// Dou freenode no meu nó cabeçalho
    freenode(linha);
}
