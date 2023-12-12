#ifndef MuriloLopesTeclas_H
#define MuriloLopesTeclas_H
#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include "MuriloLopesFuncoes.h"
#include "MuriloLopesTela.h"
#include "MuriloLopesEstrutura.h"

void teclas_especiais(LINHA *linha, LINHA **aux, wchar_t caracter, CONTROLADOR *controlador)
{
    setlocale(LC_ALL, "Portuguese");

    int i;
    switch (caracter)
    {
    case 59: // F1
        system("cls");
        arquivo_ajuda();
        do
        {
            caracter = _getwch();
        }
        while(caracter != 27);
        system("cls");
        exibir_todas_linhas(linha);
        meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        break;

    case 60: // F2
        salvar_texto(linha);
        break;

    case 68: // F10
        limpar_estrutura(linha);
        system("cls");
        abrir_arquivo(linha);
        controlador->linha_atual = linha->num_linhas;
        (*aux) = linha->back;
        controlador->posicao_atual = (*aux)->coluna.tam_logico+1;
        exibir_todas_linhas(linha);
        meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        break;
    case 71: //HOME
        meu_gotoxy(controlador->linha_atual, 0);
        controlador->posicao_atual = 0;
        break;
    case 72: // CIMA
        if(controlador->linha_atual > 0)
        {
            (*aux) = (*aux)->back;
            controlador->linha_atual--;
            if(controlador->posicao_atual < (*aux)->coluna.tam_logico)
            {
                meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
            }
            else
            {
                controlador->posicao_atual = (*aux)->coluna.tam_logico+1;
                meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
            }
        }
        break;

    case 73: //PAGE UP
        if(controlador->linha_atual > 25)
        {
            controlador->linha_atual -= 25;

            for(i=0; i<25; i++)
            {
                (*aux) = (*aux)->back;
            }

        }
        else
        {
            controlador->linha_atual = 0;
            (*aux) = linha->next;
        }

        if(controlador->posicao_atual <= (*aux)->coluna.tam_logico)
        {
            meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        }
        else
        {
            controlador->posicao_atual = (*aux)->coluna.tam_logico+1;
            meu_gotoxy(controlador->linha_atual,(*aux)->coluna.tam_logico);
        }
        break;

    case 75: // ESQUERDA
        if(controlador->posicao_atual > 0)
        {
            controlador->posicao_atual--;
            meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
            return;
        }
        if(controlador->linha_atual > 0)
        {
            (*aux) = (*aux)->back;
            controlador->posicao_atual = (*aux)->coluna.tam_logico+1;
            controlador->linha_atual--;
            meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        }
        break;

    case 77: // DIREITA
        if(controlador->posicao_atual <= (*aux)->coluna.tam_logico)
        {
            controlador->posicao_atual++;
            meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
            return;
        }
        if(controlador->linha_atual < linha->num_linhas){
            (*aux) = (*aux)->next;
            controlador->posicao_atual = 0;
            controlador->linha_atual++;
            meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        }
        break;

    case 79: //END
        controlador->posicao_atual = (*aux)->coluna.tam_logico+1;
        meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        break;

    case 80: // BAIXO
        if(linha->num_linhas > controlador->linha_atual)
        {
            (*aux) = (*aux)->next;
            controlador->linha_atual++;
            if(controlador->posicao_atual > (*aux)->coluna.tam_logico)
            {
                controlador->posicao_atual = (*aux)->coluna.tam_logico+1;
            }
            meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        }
        break;

    case 81: //PAGE DOWN
        if(controlador->linha_atual+25 < linha->num_linhas)
        {
            controlador->linha_atual += 25;

            for(i=0; i<25; i++)
            {
                (*aux) = (*aux)->next;
            }
        }
        else
        {
            controlador->linha_atual = linha->num_linhas;
            (*aux) = linha->back;
        }
        if(controlador->posicao_atual > (*aux)->coluna.tam_logico)
        {
            controlador->posicao_atual = (*aux)->coluna.tam_logico+1;
        }
        meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        break;

    case 82: // INSERT
        controlador->insert *= -1;
        break;

    case 83: // DELETE
        ///sei que ta errado mais funciona faltou validar
        remover_posicao_coluna(&((*aux)->coluna), controlador->posicao_atual);
        system("cls");
        exibir_todas_linhas(linha);
        meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        break;


    case 134: // F12
        system("cls");
        info_aluno();
        do
        {
            caracter = _getwch();
        }
        while(caracter != 27);
        system("cls");
        exibir_todas_linhas(linha);
        meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        break;

    }

}

void teclas_ascii(LINHA *linha, LINHA **aux, wchar_t caracter, CONTROLADOR *controlador)
{
    setlocale(LC_ALL, "Portuguese");

    int escolha;
    int i;
    switch(caracter)
    {
    case 27:
        system("cls");
        printf("Digite (1) para salvar ou (2) para descartar o texto: ");
        scanf("%d", &escolha);
        if(escolha == 1)
        {
            salvar_texto(linha);
        }
        system("cls");
        break;
    case 13: //ENTER
        controlador->linha_atual++;
        criar_nova_linha_na_posicao(linha,controlador->linha_atual);

        while(controlador->posicao_atual <= (*aux)->coluna.tam_logico)
        {
            inserir_posicao_coluna(&(((*aux)->next)->coluna),(*aux)->coluna.caracter[controlador->posicao_atual],((*aux)->next)->coluna.tam_logico+1);
            remover_posicao_coluna(&((*aux)->coluna),controlador->posicao_atual);
        }

        (*aux) = (*aux)->next;
        controlador->posicao_atual=0;
        system("cls");
        exibir_todas_linhas(linha);
        meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        break;
    case 8: //BACKSPACE
        if(controlador->linha_atual > 0 || controlador->posicao_atual > 0)
        {
            if(controlador->linha_atual > 0 && controlador->linha_atual == 0)
            {
                (*aux) = (*aux)->back;
                remove_linha_posicao(linha, controlador->linha_atual);
                controlador->posicao_atual = (*aux)->coluna.tam_logico-1;
                controlador->linha_atual--;
                system("cls");
                exibir_todas_linhas(linha);
                meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
            }
            else
            {
                controlador->posicao_atual--;
                remover_posicao_coluna(&((*aux)->coluna), controlador->posicao_atual);
                system("cls");
                exibir_todas_linhas(linha);
                meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
            }
        }
        break;
    default:
        if(controlador->insert == -1)
        {
            system("cls");
            if(controlador->posicao_atual >= 74 || (*aux)->coluna.tam_logico >= TAM - 1)
            {
                controlador->linha_atual++;
                criar_nova_linha_na_posicao(linha,controlador->linha_atual);
                controlador->posicao_atual = 0;
                (*aux) = (*aux)->next;
            }

            inserir_posicao_coluna(&((*aux)->coluna), caracter, controlador->posicao_atual);
            controlador->posicao_atual++;
            exibir_todas_linhas(linha);
            meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
        }
        else
        {
            if(controlador->posicao_atual <= (*aux)->coluna.tam_logico)
            {
                (*aux)->coluna.caracter[controlador->posicao_atual] = caracter;
                exibir_todas_linhas(linha);
            }
            else
            {
                system("cls");
                if(controlador->posicao_atual >= 74 || (*aux)->coluna.tam_logico >= TAM - 1)
                {
                    controlador->linha_atual++;
                    criar_nova_linha_na_posicao(linha,controlador->linha_atual);
                    controlador->posicao_atual = 0;
                    (*aux) = (*aux)->next;
                }

                inserir_posicao_coluna(&((*aux)->coluna), caracter, controlador->posicao_atual);
                controlador->posicao_atual++;

                exibir_todas_linhas(linha);
                meu_gotoxy(controlador->posicao_atual,controlador->linha_atual);
            }

        }
    }
}



#endif
