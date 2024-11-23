#include <stdio.h>   // Prelibrerias de C
#include <stdlib.h>  // generacion de numeros aleatorios
#include <windows.h> // limpiar pantalla
#include <conio.h>   // funciones para el timer
#include <pthread.h> // hilos (No es nativo de C pero se utilizo para la creacion de HILOS)

#define H 100
#define Xx 20
#define Yy 60
int DX;
int DY;
int random;
int pozo;
int fin_tempo;
int o; // Variables contadores
int gano;
int perdio;
int resg_h;
int puertas;
int px = Xx / 2;
int py = Yy / 2;
int r_x = 0;
int r_y = 0;
int key = 0;
int cont = 0;
int salir = 0;
int murio = 0;
int segundos = 0;
int numero = 1;
int door = 2;
int verd = 1;
int minutos = 5;
int gan = 100;
int perd = 20;
char tecla;
pthread_t tempor, teclar;
char mapa[H][Xx][Yy];
int nivel[H] = {0};

// Procedimiento para cambiar la posición
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*Procedimiento para pantalla de inicio*/
void Inicio();
void Inicio()
{
    int flag = 1;
    gotoxy(35, 1);
    printf("Bienvenidos al laberinto 'C perdio'\n");
    do
    {

        int eleccion;
        gotoxy(35, 2);
        printf("[1] Jugar\n");
        gotoxy(35, 3);
        printf("[2] Reglas\n");
        gotoxy(35, 4);
        printf("[3] Salir\n");
        gotoxy(35, 5);
        scanf("%i", &eleccion);

        switch (eleccion)
        {
        case 1:
            flag = 0; // Sale del switch con falso
            break;
        case 2:
            printf("Reglas y funciones del juego\n");
            printf("Busca las llaves para abrir las puertas que hayan en la habitacion\n");
            printf("Evita caer en pozos 'O'\n");
            printf("Recoje las llaves exparcidas en el camino '*'\n");
            printf("Presiona 'I' para ver cuantas llaves tienes en el momento\n");
            printf("Si abres una puerta trampa vuelves al nivel 0 con las llaves respectivas para volver al nivel dónde caiste\n");
            printf("Si caes en un pozo automaticamente Mueres y pierdes el juego\n");
            printf("Presiona '1' para comenzar el juego\n");
            break;
        case 3:
            salir = 1; // pone la flag en 0 o sea falso
            flag = 0;  // Y pone la salida en verdadero para luego salir
            break;

        default:
            printf("eleccion no valida, por favor elija un numero valido\n");
            break;
        }

    } while (flag);
}

// Procedimiento Para iniciar el vector
void iniciar();
void iniciar()
{
    for (int i = 0; i < H; i++)
    {
        nivel[i] = 0;
    }
}

// Procedimiento rellenar array
void Base(char arr[H][Xx][Yy]);
void Base(char arr[H][Xx][Yy])
{
    for (int h = 0; h < H; h++)
    {
        for (int i = 0; i < Xx; i++)
        {
            for (int j = 0; j < Yy; j++)
            {
                if (i == 0 || i == Xx - 1)
                {
                    arr[h][i][j] = '-';
                }
                else
                {
                    if (j == 0 || j == Yy - 1)
                    {
                        arr[h][i][j] = '|';
                    }
                    else
                    {
                        arr[h][i][j] = ' ';
                    }
                }
            }
        }
    }
}

// Procedimiento mostrar por pantalla el array
void imprimir(char arr[H][Xx][Yy], int h);
void imprimir(char arr[H][Xx][Yy], int h)
{
    for (int i = 0; i < Xx; i++)
    {
        for (int j = 0; j < Yy; j++)
        {
            printf("%c", arr[h][i][j]);
        }
        printf("\n");
    }
}

// Procedimiento para ver una llave cerca
void cerca(int h);
void cerca(int h)
{
    if (mapa[h][(px + 1)][py] == '*')
    {
        printf("Hay una llave cerca, presiona E para agarrarla\n");
        tecla = getch();
        if (tecla == 69 || tecla == 101)
        {
            tecla = 1;
        }
        else
        {
            mapa[h][px][py] = ' ';
            px = px - 1;
            mapa[h][px][py] = 'p';
        }
        if (tecla == 1)
        {
            key = key + 1;
            mapa[h][(px + 1)][py] = ' ';
        }
    }
    else if (mapa[h][(px - 1)][py] == '*')
    {
        printf("Hay una llave cerca, presiona E para agarrarla\n");
        tecla = getch();
        if (tecla == 69 || tecla == 101)
        {
            tecla = 1;
        }
        else
        {
            mapa[h][px][py] = ' ';
            px = px + 1;
            mapa[h][px][py] = 'p';
        }
        if (tecla == 1)
        {
            key = key + 1;
            mapa[h][(px - 1)][py] = ' ';
        }
    }
    else if (mapa[h][px][(py + 1)] == '*')
    {
        printf("Hay una llave cerca, presiona E para agarrarla\n");
        tecla = getch();
        if (tecla == 69 || tecla == 101)
        {
            tecla = 1;
        }
        else
        {
            mapa[h][px][py] = ' ';
            py = py - 1;
            mapa[h][px][py] = 'p';
        }
        if (tecla == 1)
        {
            key = key + 1;
            mapa[h][px][(py + 1)] = ' ';
        }
    }
    else if (mapa[h][px][(py - 1)] == '*')
    {
        printf("Hay una llave cerca, presiona E para agarrarla\n");
        tecla = getch();
        if (tecla == 69 || tecla == 101)
        {
            tecla = 1;
        }
        else
        {
            mapa[h][px][py] = ' ';
            py = py + 1;
            mapa[h][px][py] = 'p';
        }
        if (tecla == 1)
        {
            key = key + 1;
            mapa[h][px][(py - 1)] = ' ';
        }
    }
}
// Procedimiento caida
void caida(int h);
void caida(int h)
{
    if (mapa[h][px][py] == 'O')
    {
        system("cls");
        gotoxy(10, 10);
        printf("Te caiste por un pozo.\n");
        gotoxy(10, 11);
        printf("MORISTE\n");
        Sleep(1000);
        gotoxy(10, 12);
        printf("Presiona enter para continuar.\n");
        murio = 1;
        verd = 0;
        getchar();
    }
}

// Procedimiento movimiento del pj
void tecleo(int h);
void tecleo(int h)
{
    verd = 1;
    gotoxy(0, 22);
    printf("presiona W/A/S/D para moverte");
    printf("\n");

    do
    {
        if (murio)
        {
            break;
        }
        mapa[h][px][py] = ' ';
        tecla = getch();
        if (tecla == 87 || tecla == 119) // es el código ASCII para W y w
        {
            tecla = 1;
        }
        else if (tecla == 83 || tecla == 115) // es el código ASCII para S y s
        {
            tecla = 3;
        }
        else if (tecla == 65 || tecla == 97) // es el código ASCII para A y a
        {
            tecla = 2;
        }
        else if (tecla == 68 || tecla == 100) // es el código ASCII para D y d
        {
            tecla = 4;
        }
        else if (tecla == 73 || tecla == 105) // es el código ASCII para I y i
        {
            tecla = 5;
        }

        switch (tecla)
        {
        case 1: // 87 es el código ASCII para W
            if (mapa[h][px - 1][py] != '-')
            {
                px = px - 1;
            }
            caida(h);
            mapa[h][px][py] = 'p';
            break;
        case 2: // 65 es el código ASCII para A
            if (mapa[h][px][py - 1] != '|')
            {
                py = py - 1;
            }
            caida(h);
            mapa[h][px][py] = 'p';
            break;
        case 3: // 83 es el código ASCII para S
            if (mapa[h][px + 1][py] != '-')
            {
                px = px + 1;
            }
            caida(h);
            mapa[h][px][py] = 'p';
            break;
        case 4: // 68 es el código ASCII para D
            if (mapa[h][px][py + 1] != '|')
            {
                py = py + 1;
            }
            caida(h);
            mapa[h][px][py] = 'p';
            break;
        case 5: // 73 es el código ASCII para I
            gotoxy(0, 23);
            printf("Tienes %i, llaves. Presiona cualquier tecla para continuar", key);
            mapa[h][px][py] = 'p';
            getch();
            break;
        default:
            mapa[h][px][py] = 'p';
            break;
        }
        system("cls");
        imprimir(mapa, h);
        printf("\n");
        printf("Nivel %i \n", h);
        cerca(h); // Verifica si hay una llave cerca
        if (key < 1)
        {
            if (mapa[h][px - 1][py] == '=')
            {
                printf("No puedes pasar, esta cerrado con llave.");
                mapa[h][px][py] = ' ';
                px = px + 1;
                mapa[h][px][py] = 'p';
            }
            else if (mapa[h][px + 1][py] == '=')
            {
                printf("No puedes pasar, esta cerrado con llave.");
                mapa[h][px][py] = ' ';
                px = px - 1;
                mapa[h][px][py] = 'p';
            }
            else if (mapa[h][px][py + 1] == '[')
            {
                printf("No puedes pasar, esta cerrado con llave.");
                mapa[h][px][py] = ' ';
                py = py - 1;
                mapa[h][px][py] = 'p';
            }
        }
        else
        {
            if (mapa[h][px - 1][py] == '=')
            {
                mapa[h][px][py] = ' ';
                verd = !verd;
                key = key - 1;
            }
            else if (mapa[h][px + 1][py] == '=')
            {
                mapa[h][px][py] = ' ';
                verd = !verd;
                key = key - 1;
            }
            else if (mapa[h][px][py + 1] == '[')
            {
                mapa[h][px][py] = ' ';
                verd = !verd;
                key = key - 1;
            }
        }

    } while (verd);
}
/* Procedimiento llaves randoms
 Decide la ubicacion de las llaves random*/
void r_r();
void r_r()
{

    r_y = rand() % (Yy - 3) + 1;

    r_x = rand() % (Xx - 2) + 1;
}
// Procedimiento more_key
// La x que entre seran las cantidad de llaves u objeto que habrá
void random_position(int x, int h, char cosa);
void random_position(int x, int h, char cosa)
{
    for (int i = 0; i < x; i++)
    {

        do
        {
            r_r();
        } while (mapa[h][r_x][r_y] == '*' || mapa[h][r_x][r_y] == 'o' || mapa[h][r_x][r_y] == 'p');

        mapa[h][r_x][r_y] = cosa;
    }
}
// Procedimiento subpuertas
void subpuertas(int h);
void subpuertas(int h)
{
    int x;

    x = rand() % 3 + 1;
    switch (x)
    {
    case 1:
        DX = Xx - 1;
        DY = Yy / 2;
        mapa[h][DX][DY] = '=';
        DX = 0;
        DY = Yy / 2;
        mapa[h][DX][DY] = '=';
        break;
    case 2:
        DX = Xx - 1;
        DY = Yy / 2;
        mapa[h][DX][DY] = '=';
        DX = Xx / 2;
        DY = Yy - 1;
        mapa[h][DX][DY] = '[';
        break;
    case 3:
        DX = 0;
        DY = Yy / 2;
        mapa[h][DX][DY] = '=';
        DX = Xx / 2;
        DY = Yy - 1;
        mapa[h][DX][DY] = '[';
        break;
    }
}
static void *teclado(void *data)
{
    int *h = (int *)data;
    tecleo(*h);
    fin_tempo = 0;
}
static void *tempo(void *parmetrosApasar)
{

    verd = 1;
    while (verd)
    {

        if (segundos == 00 && minutos == 00 || murio)
        {
            murio = 1;
            break;
        }

        if (segundos == 00)
        {
            segundos = 60; // reseteo los segundos
            minutos--;     // comienzo a contar los minutos
        }
        segundos--; // comienzo a descontar los segundos

        // Mueve el cursor a una posición específica en la consola
        gotoxy(61, 2); // Posiciona el cronómetro debajo del mapa (ajusta Y si es necesario)
        printf("temporizador: [%.2d:%.2d] \n", minutos, segundos);
        fflush(stdout); // Asegura que se muestre de inmediato
        Sleep(1000);    // Pausa de 1 segundo
    }
    return NULL;
}

// Procedimiento de algoritmo random de mapa
void algo_Mapa(int h);
void algo_Mapa(int h)
{

    if (murio != 1)
    {
        // Animación de entrada
        for (int i = 1; i < Yy / 2; i++)
        {
            mapa[h][px][i] = 'p';
            imprimir(mapa, h);
            mapa[h][px][i] = ' ';
            system("cls");
        }
        mapa[h][px][py] = 'p';
        if (cont == 0)
        {
            if (h == 0)
            {
                // Obtiene puerta y llave random

                door = rand() % 3 + 1;
                r_r();
                switch (door)
                {
                case 1:
                    DX = Xx - 1;
                    DY = Yy / 2;
                    mapa[h][DX][DY] = '=';
                    break;
                case 2:
                    DX = 0;
                    DY = Yy / 2;
                    mapa[h][DX][DY] = '=';
                    break;
                case 3:
                    DX = Xx / 2;
                    DY = Yy - 1;
                    mapa[h][DX][DY] = '[';
                    break;
                }
                while (r_x == Xx / 2 && r_y == Yy / 2)
                {
                    r_r();
                }
                mapa[h][r_x][r_y] = '*';
                system("cls");
            }
            else
            {
                // Obtiene cuantas puertas habrá

                door = rand() % 2 + 1;
                switch (door)
                {
                case 1: // Significa que hay 2 puertas
                    subpuertas(h);
                    random_position(2, h, '*');
                    break;
                case 2: // Significa que hay 3 puertas
                    DX = Xx - 1;
                    DY = Yy / 2;
                    mapa[h][DX][DY] = '=';
                    DX = 0;
                    DY = Yy / 2;
                    mapa[h][DX][DY] = '=';
                    DX = Xx / 2;
                    DY = Yy - 1;
                    mapa[h][DX][DY] = '[';
                    random_position(3, h, '*');
                    break;
                }

                // bloque para generar pozos despues del nivel 5
                if (h > 3)
                {
                    if (h < Xx * Yy)
                    {
                        r_r();
                        random_position(numero, h, 'O'); // Genera en una posicion random en el mapa el caracter O (Pozo)
                        numero = numero + 2;
                    }
                }

                // Bloque para decidir si va a ganar o volver al inicio
                if (h > 5)
                {
                    gano = rand() % gan + 1;
                    perdio = rand() % perd + 1;
                    gan--;
                    if (((gano == perdio) && (perdio = 1)) || perdio == 1)
                    {
                        gano = gan;
                        key = h;
                        resg_h = h; // Si perdio, que tenga la cantidad de llaves que nivel paso
                        h = 0;      // Si son iguales, que sobresalga el perder
                        o = 0;      // Si son iguales, que sobresalga el perder
                        perdio = 0; // Resetea el valor de perdio
                        cont = 1;
                    }
                }
            }
        }
        // Muestra en pantalla el mapa
        if (h == 0)
        {
            printf("Entras en una habitacion con 1 Puerta. \n ");
        }
        else
        {
            for (int j = 0; j < Xx; j++)
            {
                for (int i = 0; i < Yy; i++)
                {
                    if (mapa[h][j][i] == '=' || mapa[h][j][i] == '[')
                    {
                        puertas++;
                    }
                }
            }
            printf("Entras en una habitacion con %i Puertas. \n ", puertas);
        }
        puertas = 0;
        imprimir(mapa, h);
        pthread_create(&tempor, NULL, &tempo, NULL);
        pthread_create(&teclar, NULL, teclado, &h);
        pthread_join(tempor, NULL); // funcion dentro de un hilo Del temporizador
        pthread_join(teclar, NULL); // funcion dentro de un hilo que detecte las teclas
        px = Xx / 2;
        py = Yy / 2;
        if (resg_h == h)
        {
            cont = 0;
        }
    }
}
