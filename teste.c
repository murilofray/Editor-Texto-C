#include <windows.h>
#include <locale.h>
#include <stdio.h>
#include <conio.h>
void main() {
    wchar_t caract;
    while(1){
        caract = _getwch();
        printf("%d\n", caract);
        caract = _getwch();
        printf("%d\n", caract);
    }
}
