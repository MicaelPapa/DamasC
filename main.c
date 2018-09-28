///Librerias:
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>
#include "gotoxy.h"
#include "damas.h"


///Prototipos:
void tituloDamas();
void llenarMatrix(int tablero[DIM][DIM]);
void desplazar_seleccionador ();
int desplazamiento(int *x, int *y, int tecla, int flag, int tablero[DIM][DIM]);
void cuadroEstructura();
void cuadroInfo();
void posiblesMovimientos(int tablero[DIM][DIM]);
int HabilitadoMover(int tablero[DIM][DIM]);
void casilleroToMatrix(int x, int y, int *i, int *j);
void posicion_gotoXY(int i, int j, int tipo, int tablero[DIM][DIM]);
void posicion_matrix_cuadrado(int *i, int *j);
void matrixToGotoxy(int i, int j, int *x, int *y);
void moverFicha(int x, int y, int movimiento, int tablero[DIM][DIM],int fichaC);
void EscapeCase(int x, int y, int contador, int movimiento);
void EnterCase(int x, int y, int tablero[DIM][DIM],int fichaC);
void casilleroToMatrix(int x, int y, int *i, int *j);
void FichaToMatrix(int x, int y, int *i, int *j);
void reloj();
void * ejecutar(void *flag);

pthread_mutex_t llave;


int main()
{
    SetConsoleTitle("\"Damas in C\"");
    system("MODE 93,45");
    hidecursor(0);

    ///Llamadas
    ///introDamas();

    pthread_mutex_init(&llave,NULL);

    pthread_t hilo1;
    pthread_t hilo2;

    pthread_attr_t atributos;
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    pthread_create(&hilo1,&atributos,(void *)(*ejecutar),(void *)0);
    pthread_create(&hilo2,&atributos,(void *)(*ejecutar),(void *)1);

    pthread_join(hilo1,(void **)0);
    pthread_join(hilo2,(void **)0);

    pthread_attr_destroy(&atributos);

    return 0;
}

void * ejecutar(void *flag)
{
    pthread_mutex_lock(&llave);
    int *bandera = (int *)flag;
    pthread_mutex_unlock(&llave);
    pthread_mutex_destroy(&llave);
    int tablero[DIM][DIM] = {0};
    int turno = 2;

    if(bandera==0)
    {
        reloj();
    }
    indices();
    tablero_damas();
    llenarMatrix(tablero);
    imprimirFichas(tablero);
    cuadroEstructura();
    cuadroInfo(turno);
    desplazar_seleccionador(tablero);

    return NULL;
}

void llenarMatrix(int tablero[DIM][DIM])
{
    int i,j;

    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
        {
            if(i<3)
            {
                if((i%2==0 && j%2==0) || (i%2!=0 && j%2!=0))
                {
                    tablero[i][j] = 2;
                }
            }
            else if(i > 4)
            {
                if((i%2 == 0 && j%2 == 0) || (i%2 != 0 && j%2 != 0))
                {
                    tablero[i][j] = 1;
                }
            }
        }
    }
}

int desplazamiento(int *x, int *y, int tecla, int flag, int tablero[DIM][DIM])
{
    int i=0,j=0;

    switch(tecla)
    {
    case ABA:
        Sleep(100);
        (*y) += 3;
        if((*y)> 22)
        {
            (*y) = 1;
        }
        break;
    case ARR:
        Sleep(100);
        (*y) -= 3;
        if((*y) < 1)
        {
            (*y) = 22;
        }
        break;
    case DER:
        Sleep(100);
        (*x) += 9;
        if((*x) > 73)
        {
            (*x) = 10;
        }
        break;
    case IZQ:
        Sleep(100);
        (*x) -= 9;
        if((*x) < 10)
        {
            (*x) = 73;
        }
        break;
    case ENTER:
        gotoxy(*x,*y);
        if(HabilitadoMover(tablero) == 0)
        {
            casilleroToMatrix(*x,*y,&i,&j);
            casillero(*x,*y,VIOLET);
            posiblesMovimientos(tablero);
        }
        break;
    case ESCAPE:
        exit(0);
        break;
    }
    return flag;
}

void posiblesMovimientos(int tablero[DIM][DIM])
{
    int i,j, tipo;

    posicion_matrix_cuadrado(&i,&j);
    gotoxy(20,40);

    i-=1;
    j-=1;

    tipo = tablero[i][j];
    posicion_gotoXY(i,j,tipo, tablero);

}

void posicion_gotoXY(int i, int j, int tipo, int tablero[DIM][DIM])
{
    int x,y,movimiento = 0;

    matrixToGotoxy(i,j,&x,&y);

    if(tipo == 2)
    {
        if(j == 0)   ///Limite izquierda
        {
            y += 3;
            x += 9;
            gotoxy(x,y);
            ficha(x,y,GREEN);
            moverFicha(x,y,movimiento, tablero, tipo);
        }
        else if(j == 7)     ///Limite derecha
        {
            y += 3;
            x -= 9;
            gotoxy(x,y);
            ficha(x,y,GREEN);
            moverFicha(x,y, movimiento, tablero, tipo);
        }
        else if(j<7 && j>0)     ///no esta al limite
        {
            y += 3;
            x += 9;
            gotoxy(x,y);
            ficha(x,y,BLACK);
            x -= 18;
            gotoxy(x,y);
            ficha(x,y,GREEN);
            movimiento = 18;
            moverFicha(x,y,movimiento, tablero, tipo);
        }
    }
    else if(tipo == 1)
    {
        if(j == 0)   ///Limite izquierda
        {
            y -= 3;
            x += 9;
            gotoxy(x,y);
            ficha(x,y,GREEN);
            moverFicha(x,y,movimiento,tablero, tipo);
        }

        else if(j == 7)   ///Limite derecha
        {
            y -= 3;
            x -= 9;
            gotoxy(x,y);
            ficha(x,y,GREEN);
            moverFicha(x,y,movimiento,tablero,tipo);
        }


        else if(j<7 && j>0)   ///No esta al limite
        {
            y -= 3;
            x -= 9;
            gotoxy(x,y);
            ficha(x,y,BLACK);
            x += 18;
            gotoxy(x,y);
            ficha(x,y,GREEN);
            movimiento = -18;
            moverFicha(x,y,movimiento,tablero,tipo);
        }
    }
}

void moverFicha(int x, int y, int movimiento, int tablero[DIM][DIM], int fichaC)
{
    int tecla;
    int flag = 0;
    int contador = 0;

    do
    {
        do
        {
            tecla = getch();
            fflush(stdin);
        }
        while(tecla!=DER && tecla!= IZQ && tecla!=ENTER && tecla!=ESCAPE);

        if(tecla == DER || tecla == IZQ)
        {
            tecla = MOV;
        }

        switch (tecla)
        {
        case ENTER:
            EscapeCase(x,y,contador,movimiento);
            EnterCase(x,y,tablero,fichaC);
            flag = -1;
            break;
        case ESCAPE:
            EscapeCase(x,y,contador,movimiento);
            flag = -1;
            break;
        case MOV:
            if(contador%2 == 0)
            {
                system("color");
                Sleep(100);
                gotoxy(x,y);
                ficha(x,y,BLACK);
                x += movimiento;
                gotoxy(x,y);
                ficha(x,y,GREEN);
            }
            else
            {
                system("color");
                Sleep(100);
                gotoxy(x,y);
                ficha(x,y,BLACK);
                x -= movimiento;
                gotoxy(x,y);
                ficha(x,y,GREEN);
            }
            contador ++;
            break;
        }
    }
    while(flag == 0);
}

void EnterCase(int x, int y, int tablero[DIM][DIM],int fichaC)
{
    int i=0,j=0;

    FichaToMatrix(x,y,&i,&j);

    tablero[i][j] = fichaC;
    imprimirFichas(tablero);
}

void EscapeCase(int x, int y, int contador, int movimiento)
{
    gotoxy(x,y);
    ficha(x,y,BLACK);
    if(contador%2 == 0)
    {
        x += movimiento;
        gotoxy(x,y);
        ficha(x,y,BLACK);
    }
    else
    {
        x -= movimiento;
        gotoxy(x,y);
        ficha(x,y,BLACK);
    }
}

int posicionActual(int tablero[DIM][DIM],int i, int j)
{
    int posActual;

    posActual = tablero[i][j];

    return posActual;
}

void borrarFichaMovida()
{


}

void desplazar_seleccionador(int tablero[DIM][DIM])
{
    int x = 10;
    int y = 1;
    int tecla;
    int flag = 0;

    do
    {
        do
        {
            fflush(stdin);
            tecla = getch();
            gotoxy(x,y);
            casillero_auxiliar(x,y,YELLOW);
        }
        while(tecla!=ARR && tecla!=ABA && tecla!=DER && tecla!=IZQ && tecla!=ENTER && tecla!= ESCAPE);

        gotoxy(x,y);
        flag = desplazamiento(&x,&y,tecla,flag,tablero);
        gotoxy(x,y);
        casillero(x,y,LIGHTBLUE_DIFFERENT);
    }
    while(flag==0);
}

int HabilitadoMover(int tablero[DIM][DIM])
{
    int i=0,j=0;
    int flag = 1;

    posicion_matrix_cuadrado(&i,&j);
    gotoxy(40,38);
    printf("i: %d j: %d",i,j);

    if(tablero[i][j] == 1)
    {
        if(tablero[i-1][j-1] != 1 && tablero[i-1][j+1] != 1)
        {
            flag = 0;
        }
    }
    else if(tablero[i][j] == 2)
    {
        if(tablero[i+1][j-1] != 2 && tablero[i+1][j+1] != 2)
        {
            flag = 0;
        }
    }

    return flag;
}

void posicion_matrix_cuadrado(int *i, int *j)
{
    (*i) = whereY();
    (*j) = whereX();

    (*j) -= 10;
    (*i) -= 1;

    if((*j)!=0)
    {
        (*j) /= 9;
    }
    if((*i)!=0)
    {
        (*i) /= 3;
    }
}

void cuadroInfo(int turno)
{
///Texto puntuacion:
    if(turno == 1)
    {
        color(WHITE);
        gotoxy(30,31);
        printf("Tiempo: ");
        gotoxy(8,31);
        printf("Turno Jugador: 1 %c%c",FICHA,FICHA);
        gotoxy(72,31);
        printf("PUNTUACION:"RESET);
    }
    else
    {
        color(RED);
        gotoxy(30,31);
        printf("Tiempo: ");
        gotoxy(8,31);
        printf("Turno Jugador: 2 %c%c",FICHA,FICHA);
        gotoxy(72,31);
        printf("PUNTUACION:"RESET);

    }
///Texto turno:
    color(WHITE);
    gotoxy(72,35);
    printf("JUGADOR %c%c: 7"RESET,FICHA,FICHA);


    color(RED);
    gotoxy(72,39);
    printf("JUGADOR %c%c: 9"RESET,FICHA,FICHA);

///Texto info:

}

void matrixToGotoxy(int i, int j, int *x, int *y)
{
    (*x) = 13 + (9 * j);
    (*y) = 2 + (3 * i);
}

void FichaToMatrix(int x, int y, int *i, int *j)
{
    (*j) = x - 13;
    if((*j) > 0)
    {
        (*j) /= 9;
    }

    (*i) = (y - 2);
    if((*i) > 0)
    {
        (*i) /= 3;
    }
}

void casilleroToMatrix(int x, int y, int *i, int *j)
{
    (*j) = x - 10;
    if((*j) > 0)
    {
        (*j) /= 9;
    }

    (*i) = (y - 1);
    if((*i) > 0)
    {
        (*i) /= 3;
    }
}

void introDamas()
{
    int i;
    int vel = 30;
    int bandera = 1;

    for(i=0; i<40; i++)
    {
        Sleep(vel);
        if(i % 2 == 0)
        {
            color(RED);
            gotoxy(46+i,12);
            printf("%c",HORIZ);

            gotoxy(46-i,20);
            printf("%c"RESET,HORIZ);
        }
        else
        {
            gotoxy(46+i,12);
            printf("%c",HORIZ);

            gotoxy(46-i,20);
            printf("%c",HORIZ);
        }
    }

    gotoxy(86,12);
    printf("%c",SUP_D);

    gotoxy(6,20);
    printf("%c",INF_I);

    for(i=0; i<7; i++)
    {
        Sleep(vel);

        if(i % 2 == 0)
        {
            color(RED);
            gotoxy(86,13+i);
            printf("%c",VERTIC);

            gotoxy(6,19-i);
            printf("%c"RESET,VERTIC);
        }
        else
        {
            gotoxy(86,13+i);
            printf("%c",VERTIC);

            gotoxy(6,19-i);
            printf("%c",VERTIC);

        }
    }

    gotoxy(6,12);
    printf("%c",SUP_I);

    gotoxy(86,20);
    printf("%c",INF_D);

    for(i=0; i<40; i++)
    {
        Sleep(vel);

        if(i % 2 == 0)
        {
            color(RED);
            gotoxy(85-i,20);
            printf("%c",HORIZ);

            gotoxy(7+i,12);
            printf("%c"RESET,HORIZ);
        }
        else
        {
            gotoxy(85-i,20);
            printf("%c",HORIZ);

            gotoxy(7+i,12);
            printf("%c",HORIZ);
        }

    }

    tituloDamas();

    while(bandera == 1)
    {
        Sleep(600);
        gotoxy(31,30);
        printf("PRESIONE ENTER PARA CONTINUAR...");
        Sleep(600);
        gotoxy(31,30);
        printf("                                       ");

        if(GetAsyncKeyState(0x0D))
        {
            bandera = 0;
            system("cls");
        }

    }
}

void tituloDamas()
{
    int vel = 100;

    Sleep(vel);
    gotoxy(12,13);
    printf("  _____          __  __           _____     _____ _   _       _____ ");
    Sleep(vel);
    gotoxy(12,14);
    printf(" |  __ \\   /\\   |  \\/  |   /\\    / ____|   |_   _| \\ | |     / ____|");
    Sleep(vel);
    gotoxy(12,15);
    printf(" | |  | | /  \\  | \\  / |  /  \\  | (___       | | |  \\| |    | |     ");
    Sleep(vel);
    gotoxy(12,16);
    printf(" | |  | |/ /\\ \\ | |\\/| | / /\\ \\  \\___ \\      | | | . ` |    | |     ");
    Sleep(vel);
    gotoxy(12,17);
    printf(" | |__| / ____ \\| |  | |/ ____ \\ ____) |    _| |_| |\\  |    | |____ ");
    Sleep(vel);
    gotoxy(12,18);
    printf(" |_____/_/    \\_\\_|  |_/_/    \\_\\_____/    |_____|_| \\_|     \\_____|");

}

void reloj()
{
    int hora, minuto, segundo;

    for (hora=0; hora<=24; hora++ )
    {
        for (minuto=0; minuto<60; minuto++ )
        {
            for (segundo=0; segundo<60; segundo++ )
            {
                // AGREGAMOS UN INTERVALO DE 1000 MS = 1 SEGUNDO
                Sleep(1000);
                // IMPRIMIR NUESTRO CRONOMETRO
                fflush(stdin);
                color(WHITE);
                gotoxy(37,31);
                printf(" %.2i : %.2i : %i "RESET, hora, minuto, segundo);
            }
        }
    }
}

