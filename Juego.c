#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <pthread.h>
#include "Procedimiento.c"
int main()
{
    srand(time(0));
    Inicio();
    Base(mapa);
    o = 0;

    if (salir)
    {
        printf("Gracias por jugar. Presiona enter para salir");
        Sleep(9);
        getchar();
        return 0;
    }
    // Funciones y procedimientos
    do
    {
        if (gano == 1 || murio)
        {
            break;
        }
        algo_Mapa(o);
        o++;
    } while (1);
    if (murio)
    {
        system("cls");
        gotoxy(40, 10);
        printf("Perdiste en el nivel %i.\n", o);
        Sleep(9);
        gotoxy(40, 11);
        printf("Gracias por jugar. Presiona enter para salir");
        getchar();
    }
    if (gano == 1)
    {
        system("cls");
        gotoxy(36, 10);
        printf("ENCONTRASTE LA SALIDA Y SALISTE DEL LABERINTO. \n");
        gotoxy(36, 11);
        printf("Tardaste %i habitaciones en salir\n", o);
        Sleep(9);
        gotoxy(36, 12);
        printf("Gracias por jugar. Presiona enter para salir");
        getchar();
    }
    return 0;
}
