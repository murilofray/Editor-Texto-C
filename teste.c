#include <windows.h>

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Obtenha informações sobre o buffer de tela do console
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    COORD cursorPos = csbi.dwCursorPosition;

    // Simule uma rolagem para baixo, exibindo algumas linhas adicionais
    for (int i = 0; i < 25; ++i) {
        printf("Linha %d\n", i);
    }

    // Obtenha novamente as informações sobre o buffer de tela do console
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    COORD newCursorPos = csbi.dwCursorPosition;

    // Verifique se a posição do cursor mudou
    if (cursorPos.Y != newCursorPos.Y) {
        printf("A tela rolou para baixo!\n");
    } else {
        printf("A tela não rolou para baixo.\n");
    }

    return 0;
}
