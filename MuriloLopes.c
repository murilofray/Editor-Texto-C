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
    controlador.linha_atual = 0;
    controlador.posicao_atual = 0;
    controlador.insert = -1;
    inicializar_linha(&linha);
    //crio a primeira linha
    criar_nova_linha_na_posicao(linha,0);
    aux = linha->next;
    meu_gotoxy(0,0);

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

    limpar_estrutura(linha);
    freenode(linha);
}
