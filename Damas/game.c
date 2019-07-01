#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "gotoxy.h"
#include "damas.h"
#include "game.h"

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

void EscapeCase(int x, int y, int contador, int movimiento, int tablero[DIM][DIM])
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
    imprimirFichas(tablero);
}

void borrarFichaMovida(int i, int j, int tablero[DIM][DIM])
{
    int x, y;

    matrixToGotoxy(i,j,&x,&y);
    ficha(x,y,BLACK);
    tablero[i][j] = 0;
}

int existeFicha(int ficha,int color)
{
    int bandera = 4;

    if(color == 1)
    {

        if(ficha == 2)
        {
            bandera = 1;
        }
        else if(ficha == 0)
        {
            bandera = 1;
        }
        else if(ficha == 4)
        {
            bandera = 1;
        }
        else if (ficha == 3)
        {
            bandera = 0;
        }
        else if (ficha == 1)
        {
            bandera = 0;
        }
    }

    if(color == 2)
    {
        if(ficha == 1)
        {
            bandera = 1;
        }
        else if(ficha == 0)
        {
            bandera = 1;
        }
        else if(ficha == 3)
        {
            bandera = 1;
        }
        else if (ficha == 4)
        {
            bandera = 0;
        }
        else if (ficha == 2)
        {
            bandera = 0;
        }
    }
    return bandera;
}

void fichasEliminadas(int tablero[DIM][DIM],int * puntosW, int * puntosR)
{
    int i=0,j=0,a=0,b=0;

    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
        {
            if(tablero[i][j] == 1 || tablero[i][j] == 3)
            {
                a++;
            }
            else if(tablero[i][j] == 2 || tablero[i][j] == 4)
            {
                b++;
            }
        }
    }

    (*puntosW) = 12 - b;
    (*puntosR) = 12 - a;
}

void HabilitadoMoverJug1(int tablero[DIM][DIM],int i, int j, int *flag)
{

    if(j != 7 && j !=0)                                                                         ///Afuera de los limites
    {

        if(noExisteFicha(tablero[i-1][j-1]) == 1 && noExisteFicha(tablero[i-1][j+1]) == 1)   ///Puede mover en ambos lugares pero no comer.
        {
            (*flag) = 4;
        }
        else if(noExisteFicha(tablero[i-1][j-1]) == 1 && noExisteFicha(tablero[i-1][j+1]) == 0)
        {
            (*flag) = 5;
        }
        else if(noExisteFicha(tablero[i-1][j-1]) == 0 && noExisteFicha(tablero[i-1][j+1]) == 1)
        {
            (*flag) = 6;
        }
    }
    else                                                                                        ///Limites
    {
        if(noExisteFicha(tablero[i-1][j-1]) == 1 && noExisteFicha(tablero[i-1][j+1]) == 1)
        {
            if(j == 0)
            {
                (*flag) = 6;

            }
            else if(j == 7)
            {

                (*flag) = 5;
            }

        }
    }
}

void HabilitadoMoverJug2(int tablero[DIM][DIM],int i, int j, int * flag)
{

    if(j != 7 && j !=0)                                                                         ///Afuera de los limites
    {

        if(noExisteFicha(tablero[i+1][j-1]) == 1 && noExisteFicha(tablero[i+1][j+1]) == 1)    ///Puede mover en ambos lugares pero no comer.
        {
            (*flag) = 4;
        }
        else if(noExisteFicha(tablero[i+1][j-1]) == 1 && noExisteFicha(tablero[i+1][j+1]) == 0)
        {
            (*flag) = 5;
        }
        else if(noExisteFicha(tablero[i+1][j-1]) == 0 && noExisteFicha(tablero[i+1][j+1]) == 1)
        {
            (*flag) = 6;
        }
    }
    else                                                                                        ///Limites
    {
        if(noExisteFicha(tablero[i+1][j-1]) == 1 && noExisteFicha(tablero[i+1][j+1]) == 1)
        {
            if(j == 0)
            {

                (*flag) = 6;

            }
            else if(j == 7)
            {

                (*flag) = 5;
            }

        }
    }
}

void estadisticasGame()
{
    system("cls");
    ESTADISTICAS est;
    int y = 3;

    FILE * file = fopen("estadisticas.bin","rb");

    gotoxy(15,2);
    printf("Movimientos");
    gotoxy(30,2);
    printf("Puntos");
    gotoxy(45,2);
    printf("Damas");

    if(file != NULL)
    {
        fread(&est,sizeof(ESTADISTICAS),1,file);
        gotoxy(2,y);
        printf("Jugador 1");
        gotoxy(15,y);
        printf("%d",est.movsBlanco);
        gotoxy(30,y);
        printf("%d",est.puntosBlanco);
        gotoxy(45,y);
        printf("%d",est.queenBlanco);

        y++;

        gotoxy(2,y);
        printf("Jugador 2");
        gotoxy(15,y);
        printf("%d",est.movsRojo);
        gotoxy(30,y);
        printf("%d",est.puntosRojo);
        gotoxy(45,y);
        printf("%d",est.queenRojo);

        y+=2;
        fclose(file);
        getch();
    }
}

void cargarEstadisticas(int puntosW,int puntosR,int movRojo,int movBlanco,int reinasBlancas,int reinasRojas)
{
    ESTADISTICAS est;
    FILE * file = fopen("estadisticas.bin","wb");

    if(file!= NULL)
    {
        est.movsBlanco = movBlanco;
        est.movsRojo = movRojo;
        est.puntosBlanco = puntosW;
        est.puntosRojo = puntosR;
        est.queenBlanco = reinasBlancas;
        est.queenRojo = reinasRojas;
        fwrite(&est,sizeof(ESTADISTICAS),1,file);
        fclose(file);
    }
}

