#ifndef tela_H
#define tela_H
#include "MuriloLopesEstrutura.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void meu_gotoxy(CONTROLADOR *controlador)
{
    COORD coord;
    coord.X = controlador->posicao_atual;
    coord.Y = controlador->linha_atual;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void configura_terminal() {
    int colunas = 80;
    int linhas = 10000;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Desativar o redimensionamento manual
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_SIZEBOX);

    // Definir o tamanho do buffer de tela
    COORD bufferSize = { colunas, linhas };
    SetConsoleScreenBufferSize(consoleHandle, bufferSize);

//    // Definir o tamanho da janela para coincidir com o tamanho do buffer
//    SMALL_RECT windowSize = { 0, 0, colunas - 1, linhas - 1 };
//    SetConsoleWindowInfo(consoleHandle, TRUE, &windowSize);
}


#endif



