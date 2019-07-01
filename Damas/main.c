///Librerias
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <conio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include "gotoxy.h"
#include "damas.h"
#include "game.h"
#include "reloj.h"
#include "listas.h"

///Constante nombre archivo
const char ARCHIVO_MOVIMIENTOS[17] = "movimientos.bin";
const char ARCHIVO_ESTADISTICAS[17] = "estadisticas.bin";
const char ARCHIVO[15] = "usuarios.bin";

///Variables globales
int turno = 1;
int detector = NULL;
int vertical = 32;

BOOL X1 = TRUE;
BOOL X2 = TRUE;
BOOL X3 = TRUE;
BOOL X4 = TRUE;

BOOL pause = FALSE;
BOOL finDelJuego = FALSE;
sem_t semaforo;

///Prototipos:
void * reloj(int minuto);
void * ejecutar(int tiempo);
void unlimitedTime(int tiempo);
int desplazar_seleccionador(int tablero[DIM][DIM], int flag, int tiempo);
void checkFinPartida(int tablero[DIM][DIM], int * flag);
void finPartida(int flag, int tablero[DIM][DIM]);
int cantidadFichas(int tablero[DIM][DIM]);
void crearReina(int tablero[DIM][DIM], int * reinasBlancas, int * reinasRojas);
void desplazamiento(int *x, int *y, int tecla, int tablero[DIM][DIM], int * movBlanco,int * movRojo);
void posicionIndices(int i, int j, int opcion);
void pauseMenu(int tablero[DIM][DIM]);
void seleccionMenuEscape(int y, int *flag, int tablero[DIM][DIM]);
void calcularMovimientosPosibles(int tablero[DIM][DIM], int *escape,int flag, int x1, int x2, int x3, int x4);
void imprimirMovimientosPosibles(int i, int j, int tipo, int tablero[DIM][DIM], int **escape,int flag);
void moverFicha(int x, int y, int movimiento, int tablero[DIM][DIM], int fichaC, int ***escape);
void EnterCase(int x, int y, int tablero[DIM][DIM],int fichaC,int accion,int diagonal);
int HabilitadoMover(int tablero[DIM][DIM]);
void cuadroInfo(int puntosW, int puntosR);
void infoMovimiento();
int noExisteFicha(int ficha);
int buscarPosicionNombre(char nombre[30]);
void puedeComer(int tablero[DIM][DIM],int i, int j, int *flag);
void comerFicha(int x, int y, int movimiento, int tablero[DIM][DIM], int fichaC, int ***escape,int diagonal,int bandera);
void comer(int x, int y, int tablero[DIM][DIM],int fichaC, int diagonal);
void comerYmoverFicha(int x, int y, int movimiento,int ymovimiento, int tablero[DIM][DIM], int fichaC, int ***escape,int diagonal,int bandera);
void comerEnRebote(int tablero[DIM][DIM], int tipo,int flag,int i,int j);
int HabilitadoMoverDamas(int tablero[DIM][DIM], int *x1, int *x2, int *x3, int *x4);
void HabilitadoMoverJug1Damas(int tablero[DIM][DIM],int i, int j, int *flag, int **x1, int **x2, int **x3, int **x4);
void HabilitadoMoverJug2Damas(int tablero[DIM][DIM],int i, int j, int *flag, int **x1, int **x2, int **x3, int **x4);
void puedeComerDamas(int tablero[DIM][DIM],int i, int j, int *flag, int **x1, int **x2, int **x3, int **x4);
void imprimirMovimientosPosiblesDamas(int i,int j,int tipo,int tablero[DIM][DIM],int **escape,int x1, int x2, int x3, int x4);
int imprimePrimeraOpcion(int x1, int x2, int x3, int x4,int *x, int *y, int *diagonal);
void moverDama(int x, int y,int tablero[DIM][DIM], int fichaC, int ***escape,int diagonal,int opc, int x1, int x2, int x3, int x4);
void seleccionarMovimiento(int tablero[DIM][DIM],int tecla,int *x, int *y, int *posActual, int *diagonal, int *accion, int x1, int x2, int x3, int x4);
void EnterCaseDamas(int x, int y, int tablero[DIM][DIM],int fichaC,int accion,int diagonal,int opc);
void comerDamas(int x, int y, int tablero[DIM][DIM],int fichaC, int diagonal,int opc);
void imprimirPosicionesVioletas(int x1, int x2, int x3, int x4,int x, int y);
void inicioJuego(int tiempo);
void menuDetalles(NODO *lista,ARBOL *aux,int *min,JUGADOR *J1,JUGADOR *J2);
void menuDetalles(NODO *lista,ARBOL *aux,int *min,JUGADOR *J1,JUGADOR *J2);
JUGADOR menuElegirUsuario(NODO * lista,ARBOL *aux,int Jug);
void cargarArchivo(int Jug);
void verificarNombre(char nombre[30]);
JUGADOR buscarUltimaEstructura();
JUGADOR usuarioExistente(ARBOL *aux,int Jug);
JUGADOR retornarJugador(char nombre[30]);
void menuJugadores(NODO * lista, ARBOL *aux);
NODO * ordenarGanadas(NODO *lista);
void bajaJugadores(NODO * lista,ARBOL *aux);
int existeNombre(ARBOL *aux,char nombre[30]);
int buscarPosicionNombre(char nombre[30]);
void bajaJugador(int pos);
JUGADOR eliminarJugador(JUGADOR J);
void controles(NODO * lista,ARBOL *aux);
void reglas(NODO * lista,ARBOL *aux);

int main()
{

    SetConsoleTitle("\"Damas in C\"");

    HWND consoleWindow =  GetConsoleHwnd();
    SetWindowPos(consoleWindow, 0,500, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER );

    system("MODE 93,40");
    hidecursor(0);

    ///Llamadas
    introDamas();
    getch();

    NODO *lista;
    lista = inicLista();
    ARBOL * aux = inicArbol();
    aux = archivoToArbol(aux);
    menuPrincipal(lista,aux);


    return EXIT_SUCCESS;
}


void * reloj(int minuto)
{
    int segundo = 59;
    int color = YELLOW;

    for ( ; minuto>=0 && finDelJuego == FALSE; minuto--)
    {
        for (segundo=59; segundo>=0 && finDelJuego == FALSE; segundo--)
        {
            sem_wait(&semaforo);
            if(pause == FALSE)
            {
                Sleep(1000);
                fflush(stdin);
                tono(color);
                cartesiano(37,31);
                if(pause==FALSE)
                    printf(" %.2d : %.2d", minuto, segundo);
                if(finDelJuego == TRUE)
                {
                    cartesiano(37,31);
                    printf("                          ");
                }
            }
            else
            {
                segundo+=1;
                Sleep(1000);
            }

            if(minuto == 4 && segundo == 55)
            {
                color = BLACK;
                finDelJuego = TRUE;
            }
            sem_post(&semaforo);
        }
    }
    pthread_exit(NULL);

    return NULL;
}

void * ejecutar(int tiempo)
{
    int tablero[DIM][DIM] = {{0},{0}};
    int flagFin=0;

    indices();
    tablero_damas();
    llenarMatrix(tablero);
    imprimirFichas(tablero);
    cuadroEstructura();
    flagFin = desplazar_seleccionador(tablero,flagFin,tiempo);

    system("cls");
    finPartida(flagFin,tablero);
    estadisticasGame();
    ///Aca deberia volver para el menu principal que esta haciendo enzo

    return NULL;
}

void unlimitedTime(int tiempo)
{
    sem_wait(&semaforo);
    if(tiempo == NULL)
    {
        gotoxy(38,31);
        color(YELLOW);
        printf("Ilimitado"RESET);
    }
    sem_post(&semaforo);
}

int desplazar_seleccionador(int tablero[DIM][DIM], int flag, int tiempo)
{
    int x = 10, y = 22, x2 = 73, y2 = 1, t;
    int puntosW=0,puntosR=0, movsRojo =0, movsBlanco=0,reinasBlancas=0,reinasRojas=0;

    do
    {
        checkFinPartida(tablero,&flag);
        Sleep(50);
        fichasEliminadas(tablero,&puntosW,&puntosR);
        crearReina(tablero,&reinasBlancas,&reinasRojas);
        cuadroInfo(puntosW,puntosR);
        unlimitedTime(tiempo);
        if(turno == 1)
        {
            gotoxy(x2,y2);
            casillero_auxiliar(x2,y2,YELLOW);
            gotoxy(x,y);
            casillero(x,y,LIGHTBLUE_DIFFERENT);
            do
            {
                fflush(stdin);
                t = getch();
                if(t!=ARR && t!=ABA && t!=DER && t!=IZQ && t!=ENTER && t!= ESCAPE && t!=ASTERISCO)
                {
                    gotoxy(x,y);
                    casillero(x,y,LIGHTBLUE_DIFFERENT);
                }
                else
                {
                    gotoxy(x,y);
                    casillero_auxiliar(x,y,YELLOW);
                }

            }
            while(t!=ARR && t!=ABA && t!=DER && t!=IZQ && t!=ENTER && t!= ESCAPE && t!=ASTERISCO);

            gotoxy(x,y);
            desplazamiento(&x,&y,t,tablero,&movsBlanco,&movsRojo);
            gotoxy(x,y);
            casillero(x,y,LIGHTBLUE_DIFFERENT);
        }
        else
        {
            gotoxy(x,y);
            casillero_auxiliar(x,y,YELLOW);
            gotoxy(x2,y2);
            casillero(x2,y2,LIGHTBLUE);
            do
            {
                fflush(stdin);
                t = toupper(getch());
                if(t!=A && t!=S && t!=D && t!=W && t!= SPACE && t!= ESCAPE && t!= ASTERISCO)
                {
                    gotoxy(x2,y2);
                    casillero(x2,y2,LIGHTBLUE);
                }
                else
                {
                    gotoxy(x2,y2);
                    casillero_auxiliar(x2,y2,YELLOW);
                }
            }
            while(t!=A && t!=S && t!=D && t!=W && t!= SPACE && t!= ESCAPE && t!= ASTERISCO);

            gotoxy(x2,y2);
            desplazamiento(&x2,&y2,t,tablero,&movsBlanco,&movsRojo);
            gotoxy(x2,y2);
            casillero(x2,y2,LIGHTBLUE);
        }
    }
    while(finDelJuego == FALSE);

    cargarEstadisticas(puntosW,puntosR,movsRojo,movsBlanco,reinasBlancas,reinasRojas);

    return flag;
}

void checkFinPartida(int tablero[DIM][DIM], int * flag)
{
    int rojas = 0, blancas = 0;
    int i,j;

    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
        {
            if(tablero[i][j] == 1 || tablero[i][j] == 3)
                blancas += 1;
            else if(tablero[i][j] == 2 || tablero[i][j] == 4)
                rojas += 1;
        }
    }


    if(rojas == 0 && blancas != 0)
    {
        finDelJuego = TRUE;
        (*flag) = 1;
    }
    else if(rojas != 0 && blancas == 0)
    {
        finDelJuego = TRUE;
        (*flag) = 2;
    }
}

void finPartida(int flag, int tablero[DIM][DIM])
{
    int i;
    int bandera=0;
    int tecla;

    if(flag == 0)
    {
        timeIsOver();
        Sleep(1000);
        system("cls");
        if(cantidadFichas(tablero) == 0)
            tiedPlayers();
        else if(cantidadFichas(tablero) == 1)
            playerOneWin();
        else if(cantidadFichas(tablero) == 2)
            playerTwoWin();
    }
    else if(flag == 3)
        tiedPlayers();
    else if(flag == 1)
        playerOneWin();
    else if(flag == 2)
        playerTwoWin();

    gotoxy(35,30);
    printf("PRESS ENTER TO CONTINUE");

    do
    {
        fflush(stdin);
        tecla = getch();
    }
    while(tecla != ENTER);
}

int cantidadFichas(int tablero[DIM][DIM])
{
    int rojas = 0, blancas = 0;
    int i,j;
    int ganador;

    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
        {
            if(tablero[i][j] == 1 || tablero[i][j] == 3)
                blancas += 1;
            else if(tablero[i][j] == 2 || tablero[i][j] == 4)
                rojas += 1;
        }
    }

    if(blancas == rojas)
        ganador = 0;
    else if(blancas > rojas)
        ganador = 1;
    else if(blancas < rojas)
        ganador = 2;

    return ganador;
}

void crearReina(int tablero[DIM][DIM], int * reinasBlancas, int * reinasRojas)
{
    int i;

    for(i=0; i<DIM; i++)
    {
        if(tablero[0][i] == 1)
        {
            detector = 4;
            tablero[0][i] = 3;
            (*reinasBlancas)++;
            imprimirFichas(tablero);
        }
        else if(tablero[7][i] == 2)
        {
            detector = 4;
            tablero[7][i] = 4;
            (*reinasRojas)++;
            imprimirFichas(tablero);
        }
    }
}

void desplazamiento(int *x, int *y, int tecla, int tablero[DIM][DIM], int * movBlanco,int * movRojo)
{
    int i=0,j=0,escape,b,r;
    int flag;
    int x1=0,x2=0,x3=0,x4=0;

    ESTADISTICAS E;

    FILE * file = fopen(ARCHIVO_ESTADISTICAS,"wb");

    if(tecla == S)
        tecla = ABA;
    else if(tecla == W)
        tecla = ARR;
    else if(tecla == D)
        tecla = DER;
    else if(tecla == A)
        tecla = IZQ;
    else if(tecla == SPACE)
        tecla = ENTER;

    switch(tecla)
    {
    case ABA:
        (*y) += 3;
        if((*y)> 22)
        {
            (*y) = 1;
        }
        break;
    case ARR:
        (*y) -= 3;
        if((*y) < 1)
        {
            (*y) = 22;
        }
        break;
    case DER:
        (*x) += 9;
        if((*x) > 73)
        {
            (*x) = 10;
        }
        break;
    case IZQ:
        (*x) -= 9;
        if((*x) < 10)
        {
            (*x) = 73;
        }
        break;
    case ENTER:
        casilleroToMatrix(*x,*y,&i,&j);
        if(tablero[i][j] == 1 || tablero[i][j] == 2)
        {
            flag = HabilitadoMover(tablero);
        }
        else if(tablero[i][j] == 3 || tablero[i][j] == 4)
        {
            flag = HabilitadoMoverDamas(tablero,&x1,&x2,&x3,&x4);
        }

        if(flag == 0)
        {
            vertical++;
            detector = 1;
        }

        if(flag != 0 && flag <= 8)
        {
            escape = 0;
            casilleroToMatrix(*x,*y,&i,&j);
            posicionIndices(i,j,1);
            casillero(*x,*y,VIOLET);
            calcularMovimientosPosibles(tablero,&escape,flag,x1,x2,x3,x4);
            if(escape == 0)
            {
                if(turno == 1)
                {
                    (*movBlanco)++;
                }
                else
                {
                    (*movRojo)++;
                }
                borrarFichaMovida(i,j,tablero);
            }
        }
        else if(flag == 9)
        {
            escape = 0;
            casilleroToMatrix(*x,*y,&i,&j);
            posicionIndices(i,j,1);
            casillero(*x,*y,VIOLET);
            calcularMovimientosPosibles(tablero,&escape,flag,x1,x2,x3,x4);
            if(escape == 0)
            {
                if(turno == 1)
                {
                    (*movBlanco)++;
                }
                else
                {
                    (*movRojo)++;
                }
                borrarFichaMovida(i,j,tablero);
            }

        }
        break;
    case ASTERISCO:
        vertical = 32;
        detector = -1;
        system("cls");
        hidecursor(0);
        tablero_damas();
        indices();
        imprimirFichas(tablero);
        cuadroEstructura();
        fichasEliminadas(tablero,&b,&r);
        cuadroInfo(b,r);
        break;
    case ESCAPE:
        detector = 5;
        system("cls");
        pauseMenu(tablero);
        break;
    }
}

void posicionIndices(int i, int j, int opcion)
{
    MOVIMIENTOS mov;
    char letra = 'A';
    char numero = '8';
    FILE * file;

    if(opcion == 1)
    {
        file = fopen(ARCHIVO_MOVIMIENTOS,"wb");
    }
    else
    {
        file = fopen(ARCHIVO_MOVIMIENTOS,"ab");
    }

    if(file != NULL)
    {
        letra += j;
        numero -= i;

        if(opcion == 1 )
        {
            mov.letraPartida = letra;
            mov.numeroPartida = numero;
            fwrite(&mov,sizeof(MOVIMIENTOS),1,file);
        }
        else
        {
            mov.letraLlegada = letra;
            mov.numeroLlegada = numero;
            fwrite(&mov,sizeof(MOVIMIENTOS),1,file);
        }
        fclose(file);
    }
}

void pauseMenu(int tablero[DIM][DIM])
{
    int tecla;
    int y = 30;
    int flag = 0;
    sem_wait(&semaforo);
    pause = TRUE;
    sem_post(&semaforo);

    logoPause();
    color(RED);
    gotoxy(42,OPCION_SUP);
    printf("RESUME"RESET);
    color(WHITE);
    gotoxy(42,OPCION_INF);
    printf("EXIT"RESET);

    do
    {
        fflush(stdin);
        tecla = getch();

        switch (tecla)
        {
        case ARR:
            if(y == OPCION_SUP)      ///Limite superior
            {
                y = OPCION_INF;      ///Limite inferior
            }
            else
            {
                y -= 2;
            }
            menuColoresPausa(y);
            break;

        case ABA:
            if(y == OPCION_INF)        ///Limite inferior
            {
                y = OPCION_SUP;    ///Limite superior
            }
            else
            {
                y += 2;
            }
            menuColoresPausa(y);
            break;
        case ENTER:
            seleccionMenuEscape(y,&flag,tablero);
            break;
        }
    }
    while(flag == 0);
}

void seleccionMenuEscape(int y, int *flag, int tablero[DIM][DIM])
{
    int b,r;
    switch (y)
    {
    case OPCION_SUP:
        system("cls");
        indices();
        tablero_damas();
        imprimirFichas(tablero);
        cuadroEstructura();
        fichasEliminadas(tablero,&b,&r);
        cuadroInfo(b,r);
        sem_wait(&semaforo);
        pause = FALSE;
        sem_post(&semaforo);
        (*flag) = 1;
        break;
    case OPCION_INF:
        system("cls");
        color(BLACK);
        exit(0);
        break;
    }
}

void calcularMovimientosPosibles(int tablero[DIM][DIM], int *escape,int flag, int x1, int x2, int x3, int x4)
{
    int i,j, tipo;

    posicion_matrix_cuadrado(&i,&j);
    gotoxy(20,40);

    i-=1;
    j-=1;

    tipo = tablero[i][j];
    if(tipo == 1 || tipo == 2)
    {
        imprimirMovimientosPosibles(i,j,tipo, tablero,&escape,flag);
    }
    else if(tipo == 3 || tipo == 4)
    {
        imprimirMovimientosPosiblesDamas(i,j,tipo, tablero,&escape,x1, x2, x3, x4);
    }
}

void imprimirMovimientosPosibles(int i, int j, int tipo, int tablero[DIM][DIM], int **escape,int flag)
{
    int x,y,movimiento=0,ymovimiento = 0;

    int a,b;

    int diagonal = 0;

    matrixToGotoxy(i,j,&x,&y);

    if(tipo == 2)
    {
        if(flag == 1)                   ///Come a los 2 lados
        {
            y += 6;
            x -= 18;
            ficha(x,y,LILAC);
            x += 36;
            ficha(x,y,GREEN);
            movimiento = 36;
            comerFicha(x,y,movimiento,tablero, tipo,&escape,diagonal,flag);
        }
        else if(flag == 2)             ///Come a la izquierda
        {
            y += 6;
            x -= 18;
            ficha(x,y,GREEN);
            movimiento = 0;
            diagonal = -1;
            comerFicha(x,y,movimiento,tablero, tipo,&escape,diagonal,flag);

        }
        else if(flag == 3)           ///Come a la derecha
        {
            y += 6;
            x += 18;
            ficha(x,y,GREEN);
            movimiento = 0;
            diagonal = 1;
            comerFicha(x,y,movimiento,tablero, tipo,&escape,diagonal,flag);
        }
        else if(flag == 4)        ///mueve a la derecha y a la izquierda
        {
            y += 3;
            x -= 9;
            ficha(x,y,LILAC);
            x += 18;
            ficha(x,y,GREEN);
            movimiento = -18;
            moverFicha(x,y,movimiento,tablero,tipo,&escape);
        }
        else if(flag == 5)        ///mueve a la izquierda
        {
            y += 3;
            x -= 9;
            ficha(x,y,GREEN);
            moverFicha(x,y,movimiento,tablero,tipo,&escape);
        }
        else if(flag == 6)       ///mueve a la derecha
        {
            y += 3;
            x += 9;
            ficha(x,y,GREEN);
            moverFicha(x,y,movimiento,tablero, tipo,&escape);
        }
        else if(flag == 7)       ///Come a la izquierda y mueve a la derecha
        {
            y += 3;
            x -= 9;
            ficha(x-9,y+3,LILAC);
            x += 18;
            ficha(x,y,GREEN);
            movimiento = 27;
            ymovimiento =  -3;
            diagonal = 2;
            comerYmoverFicha(x,y,movimiento,ymovimiento,tablero,tipo,&escape,diagonal,flag);

        }
        else if(flag == 8)       ///Come a la derecha y mueve a la izquierda
        {
            y += 3;
            x += 9;
            ficha(x+9,y+3,LILAC);
            x -= 18;
            ficha(x,y,GREEN);
            movimiento = 27;
            ymovimiento =  -3;
            diagonal = 2;
            comerYmoverFicha(x,y,movimiento,ymovimiento,tablero,tipo,&escape,diagonal,flag);
        }

    }
    else if(tipo == 1)
    {
        if(flag == 1)                   ///Come a los 2 lados
        {
            y -= 6;
            x += 18;
            ficha(x,y,GREEN);
            ficha(x-36,y,LILAC);
            movimiento = 36;
            comerFicha(x,y,movimiento,tablero, tipo,&escape,diagonal,flag);
        }
        else if(flag == 2)             ///Come a la izquierda
        {
            y -= 6;
            x -= 18;
            ficha(x,y,GREEN);
            movimiento = 0;
            diagonal = -1;
            comerFicha(x,y,movimiento,tablero, tipo,&escape,diagonal,flag);

        }
        else if(flag == 3)           ///Come a la derecha
        {
            y -= 6;
            x += 18;
            ficha(x,y,GREEN);
            movimiento = 0;
            diagonal = 1;
            comerFicha(x,y,movimiento,tablero, tipo,&escape,diagonal,flag);
        }
        else if(flag == 4)        ///mueve a la derecha y a la izquierda
        {
            y -= 3;
            x -= 9;
            ficha(x,y,LILAC);
            x += 18;
            ficha(x,y,GREEN);
            movimiento = -18;
            moverFicha(x,y,movimiento,tablero,tipo,&escape);
        }
        else if(flag == 5)        ///mueve a la izquierda
        {
            y -= 3;
            x -= 9;
            ficha(x,y,GREEN);
            moverFicha(x,y,movimiento,tablero,tipo,&escape);
        }
        else if(flag == 6)       ///mueve a la derecha
        {
            y -= 3;
            x += 9;
            ficha(x,y,GREEN);
            moverFicha(x,y,movimiento,tablero, tipo,&escape);
        }
        else if(flag == 7)       ///Come a la izquierda y mueve a la derecha
        {
            y -= 3;
            x -= 9;
            ficha(x-9,y-3,LILAC);
            x += 18;
            ficha(x,y,GREEN);
            movimiento = 27;
            ymovimiento =  3;
            diagonal = 2;
            comerYmoverFicha(x,y,movimiento,ymovimiento,tablero,tipo,&escape,diagonal,flag);

        }
        else if(flag == 8)        ///Come a la derecha y mueve a la izquierda
        {
            y -= 3;
            x += 9;
            ficha(x+9,y-3,LILAC);
            x -= 18;
            ficha(x,y,GREEN);
            movimiento = 27;
            ymovimiento =  3;
            diagonal = 2;
            comerYmoverFicha(x,y,movimiento,ymovimiento,tablero,tipo,&escape,diagonal,flag);
        }
    }
}

void moverFicha(int x, int y, int movimiento, int tablero[DIM][DIM], int fichaC, int ***escape)
{
    int t;
    int mover = 0;
    int diagonal = 2;
    int flag = 0;
    int contador = 0;
    int a,b;

    do
    {
        do
        {
            if(turno == 1)
            {
                fflush(stdin);
                t = getch();
            }
            else
            {
                fflush(stdin);
                t = toupper(getch());
            }
        }
        while(t!=DER && t!= IZQ && t!= D && t!= A && t!= SPACE && t!=ENTER && t!=ESCAPE);

        if(turno == 1 && (t==DER || t==IZQ))
            t = MOV;
        else if(turno == 2 && (t==D || t==A))
            t = MOV;
        else if(turno == 2 && t==SPACE)
            t = ENTER;
        else if(turno == 2 && t==ENTER)
            t = 0;

        switch(t)
        {
        case ENTER:
            vertical++;
            detector = 2;
            EnterCase(x,y,tablero,fichaC,mover,diagonal);
            flag = -1;
            break;

        case ESCAPE:
            EscapeCase(x,y,contador,movimiento,tablero);
            flag = -1;
            (***escape) = 1;
            break;

        case MOV:
            if(contador%2 == 0)
            {
                FichaToMatrix(x,y,&a,&b);
                if(tablero[a][b] == 0)
                {
                    gotoxy(x,y);
                    ficha(x,y,LILAC);
                }
                x += movimiento;
                gotoxy(x,y);
                ficha(x,y,GREEN);
            }
            else
            {
                FichaToMatrix(x,y,&a,&b);
                if(tablero[a][b] == 0)
                {
                    gotoxy(x,y);
                    ficha(x,y,LILAC);
                }
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

void EnterCase(int x, int y, int tablero[DIM][DIM],int fichaC,int accion,int diagonal)
{
    int i=0,j=0;

    FichaToMatrix(x,y,&i,&j);
    if(accion == 1)
    {
        comer(x,y, tablero, fichaC, diagonal);
    }
    else
    {
        tablero[i][j] = fichaC;
        posicionIndices(i,j,2);
    }

    if(turno == 1)
    {
        turno = 2;
    }
    else
    {
        turno = 1;
    }

    imprimirFichas(tablero);

}

int HabilitadoMover(int tablero[DIM][DIM])
{
    int i=0,j=0;
    int flag = 0;

    posicion_matrix_cuadrado(&i,&j);

    if(tablero[i][j] == 1 && turno == 1)
    {
        puedeComer(tablero,i,j,&flag);
        if(flag == 0)
        {
            HabilitadoMoverJug1(tablero,i,j,&flag);
        }
        else if(flag == 2)
        {
            if(j != 7 && j !=0)
            {
                if(noExisteFicha(tablero[i-1][j-1]) == 0 && noExisteFicha(tablero[i-1][j+1]) == 1)
                {
                    flag = 7;
                }
                else
                {
                    flag = 2;
                }
            }
            else
            {
                flag = 2;
            }
        }
        else if(flag == 3)
        {
            if(j != 7 && j !=0)
            {
                if(noExisteFicha(tablero[i-1][j-1]) == 1 && noExisteFicha(tablero[i-1][j+1]) == 0)
                {
                    flag = 8;
                }
                else
                {
                    flag = 3;
                }
            }
            else
            {
                flag = 3;
            }
        }

    }
    else if(tablero[i][j] == 2 && turno == 2)
    {
        puedeComer(tablero,i,j,&flag);
        if(flag == 0)
        {
            HabilitadoMoverJug2(tablero,i,j,&flag);
        }
        else if(flag == 2)
        {
            if(j != 7 && j !=0)
            {
                if(noExisteFicha(tablero[i+1][j-1]) == 0 && noExisteFicha(tablero[i+1][j+1]) == 1)
                {
                    flag = 7;
                }
                else
                {
                    flag = 2;
                }
            }
            else
            {
                flag = 2;
            }
        }
        else if(flag == 3)
        {
            if(j != 7 && j !=0)
            {
                if(noExisteFicha(tablero[i+1][j-1]) == 1 && noExisteFicha(tablero[i+1][j+1]) == 0)
                {
                    flag = 8;
                }
                else
                {
                    flag = 3;
                }
            }
            else
            {
                flag = 3;
            }
        }
    }

    return flag;
}

void cuadroInfo(int puntosW, int puntosR)
{
///Texto puntuacion:
    if(turno == 1)
    {
        color(WHITE);
        gotoxy(8,31);
        printf("Turno Jugador: 1 %c%c"RESET,FICHA,FICHA);
    }
    else
    {
        color(RED);
        gotoxy(8,31);
        printf("Turno Jugador: 2 %c%c"RESET,FICHA,FICHA);
    }

    color(YELLOW);
    gotoxy(30,31);
    printf("Tiempo: ");

    gotoxy(72,31);
    printf("PUNTUACION:"RESET);

///Texto turno:
    color(WHITE);
    gotoxy(72,35);
    printf("JUGADOR %c%c: %i",FICHA,FICHA,puntosW);

    color(RED);
    gotoxy(72,39);
    printf("JUGADOR %c%c: %i",FICHA,FICHA,puntosR);

///Texto info:
    infoMovimiento();
}

void infoMovimiento()
{
    MOVIMIENTOS mov;
    FILE * file = fopen(ARCHIVO_MOVIMIENTOS,"rb");
    int des=0;

    if(vertical == 43)
    {
        for(vertical=33; vertical<43; vertical++)
        {
            gotoxy(8,vertical);
            printf("                                                             ");
        }
        vertical = 33;
    }


    if(file != NULL && detector != NULL)
    {
        if(detector == 2)
        {
            if(turno == 1)
            {
                fread(&mov,sizeof(MOVIMIENTOS),1,file);
                gotoxy(8,vertical);
                printf("                                                             ");
                color(RED);
                gotoxy(8,vertical);
                printf("Jugador 2 se desplaz%c de %c%c a ",O_ACENTO,mov.letraPartida,mov.numeroPartida);
                fseek(file,0,SEEK_END);
                des = ftell(file) - sizeof(MOVIMIENTOS);
                fseek(file,des,SEEK_SET);
                fread(&mov,sizeof(MOVIMIENTOS),1,file);
                printf("%c%c..."RESET,mov.letraLlegada,mov.numeroLlegada);
            }
            else
            {
                fread(&mov,sizeof(MOVIMIENTOS),1,file);
                gotoxy(8,vertical);
                printf("                                                             ");
                color(WHITE);
                gotoxy(8,vertical);
                printf("Jugador 1 se desplaz%c de %c%c a ",O_ACENTO,mov.letraPartida,mov.numeroPartida);
                fseek(file,0,SEEK_END);
                des = ftell(file) - sizeof(MOVIMIENTOS);
                fseek(file,des,SEEK_SET);
                fread(&mov,sizeof(MOVIMIENTOS),1,file);
                printf("%c%c..."RESET,mov.letraLlegada,mov.numeroLlegada);
            }
        }
        else if(detector == 3)
        {
            if(turno == 1)
            {
                fread(&mov,sizeof(MOVIMIENTOS),1,file);
                color(LIGHTBLUE_DIFFERENT);
                gotoxy(8,vertical);
                printf("Jugador 2 se desplaz%c de %c%c a ",O_ACENTO,mov.letraPartida,mov.numeroPartida);
                fseek(file,0,SEEK_END);
                des = ftell(file) - sizeof(MOVIMIENTOS);
                fseek(file,des,SEEK_SET);
                fread(&mov,sizeof(MOVIMIENTOS),1,file);
                printf("%c%c eliminando a Jugador 1..."RESET,mov.letraLlegada,mov.numeroLlegada);
            }
            else
            {
                fread(&mov,sizeof(MOVIMIENTOS),1,file);
                color(LIGHTBLUE_DIFFERENT);
                gotoxy(8,vertical);
                printf("Jugador 1 se desplaz%c de %c%c a ",O_ACENTO,mov.letraPartida,mov.numeroPartida);
                fseek(file,0,SEEK_END);
                des = ftell(file) - sizeof(MOVIMIENTOS);
                fseek(file,des,SEEK_SET);
                fread(&mov,sizeof(MOVIMIENTOS),1,file);
                printf("%c%c eliminando a Jugador 2..."RESET,mov.letraLlegada,mov.numeroLlegada);
            }
        }
        else if(detector == 1)
        {
            color(GREEN);
            gotoxy(8,vertical);
            printf("                                                             ");
            gotoxy(8,vertical);
            printf("Ficha invalida"RESET);
        }
        else if(detector == 4)
        {
            color(VIOLET);
            gotoxy(8,vertical);
            printf("                                                             ");
            gotoxy(8,vertical);
            if(turno == 2)
                printf("El jugador 1 se convirti%c en Reina...",O_ACENTO,RESET);
            else
                printf("El jugador 2 se convirti%c en Reina...",O_ACENTO,RESET);
        }
        else if(detector == 5)
        {
            for(vertical=33; vertical<43; vertical++)
            {
                gotoxy(8,vertical);
                printf("                                                             ");
            }
            vertical = 32;
        }
        fclose(file);
    }
}

int noExisteFicha(int ficha)
{
    int flag = 0;

    if(ficha == 0)
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }
    return flag;
}

void puedeComer(int tablero[DIM][DIM],int i, int j, int *flag)
{

    if((tablero[i][j] == 1 || tablero[i][j] == 3) && turno == 1)
    {
        if(i > 1)
        {
            if(j < 7 && j > 0)
            {
                if((tablero[i-1][j-1] == 2 || tablero[i-1][j-1] == 4) && (tablero[i-1][j+1] == 2 || tablero[i-1][j+1] == 4))   ///Come de los
                {
                    ///dos lados
                    if(j < 6 && j > 1 && tablero[i-2][j-2] == 0 && tablero[i-2][j+2] == 0)   ///verifica los dos lados
                    {
                        (*flag) = 1;

                    }
                    else if(tablero[i-2][j-2] == 0 && (j-2) >= 0)     /// verifica el lado izquierdo
                    {
                        (*flag) = 2;
                    }
                    else if(tablero[i-2][j+2] == 0 && (j+2) <= 7)     ///verifica el lado derecho
                    {
                        (*flag) = 3;
                    }
                    else     ///En cualquier otro caso no se puede comer
                    {
                        (*flag) = 0;
                    }
                }
                else if(tablero[i-1][j-1] == 2 || tablero[i-1][j-1] == 4)     ///Come del lado izquierdo
                {
                    if(tablero[i-2][j-2] == 0 && (j-2) >= 0)   ///Verifica el lado izquierdo
                    {
                        (*flag) = 2;
                    }
                    else
                    {
                        (*flag) = 0;
                    }
                }
                else if(tablero[i-1][j+1] == 2 || tablero[i-1][j+1] == 4)     ///Come del lado derecho
                {
                    if(tablero[i-2][j+2] == 0 && (j+2) <= 7)   ///Verifica el lado derecho
                    {
                        (*flag) = 3;
                    }
                    else
                    {
                        (*flag) = 0;
                    }
                }

            }
            else     ///Caso de los bordes
            {
                if(j == 7)                                  ///verifica el lado derecho
                {
                    if(tablero[i-1][j-1] == 2 || tablero[i-1][j-1] == 4)
                    {
                        if(tablero[i-2][j-2] == 0)
                        {

                            (*flag) = 2;

                        }
                        else
                        {

                            (*flag) = 0;
                        }
                    }
                }
                else if(j == 0)                          /// verifica el lado izquierdo
                {
                    if(tablero[i-1][j+1] == 2 || tablero[i-1][j+1] == 4)
                    {
                        if(tablero[i-2][j+2] == 0)
                        {
                            (*flag) = 3;
                        }
                        else
                        {

                            (*flag) = 0;

                        }
                    }


                }
            }
        }
    }
    else if((tablero[i][j] == 2 || tablero[i][j] == 4) && turno == 2)
    {
        if(i < 6)
        {
            if(j < 7 && j > 0)
            {
                if((tablero[i+1][j-1] == 1 || tablero[i+1][j-1] == 3) && (tablero[i+1][j+1] == 1 || tablero[i+1][j+1] == 3))   ///Come de los
                {
                    ///dos lados
                    if(j < 6 && j > 1 && tablero[i+2][j-2] == 0 && tablero[i+2][j+2] == 0)   ///verifica los dos lados
                    {
                        (*flag) = 1;
                    }
                    else if(tablero[i+2][j-2] == 0 && (j-2) >= 0)     /// verifica el lado izquierdo
                    {
                        (*flag) = 2;
                    }
                    else if(tablero[i+2][j+2] == 0 && (j+2) <= 7)     ///verifica el lado derecho
                    {
                        (*flag) = 3;
                    }
                    else     ///En cualquier otro caso no se puede comer
                    {
                        (*flag) = 0;
                    }
                }
                else if(tablero[i+1][j-1] == 1 || tablero[i+1][j-1] == 3)     ///Come del lado izquierdo
                {
                    if(tablero[i+2][j-2] == 0 && (j-2) >= 0)   ///Verifica el lado izquierdo
                    {
                        (*flag) = 2;
                    }
                    else
                    {
                        (*flag) = 0;
                    }
                }
                else if(tablero[i+1][j+1] == 1 || tablero[i+1][j+1] == 3)     ///Come del lado derecho
                {
                    if(tablero[i+2][j+2] == 0 && (j+2) <= 7)   ///Verifica el lado derecho
                    {
                        (*flag) = 3;
                    }
                    else
                    {
                        (*flag) = 0;
                    }
                }

            }
            else     ///Caso de los bordes
            {
                if(j == 7)                                  ///verifica el lado derecho
                {
                    if(tablero[i+1][j-1] == 1 || tablero[i+1][j-1] == 3)
                    {
                        if(tablero[i+2][j-2] == 0)
                        {

                            (*flag) = 2;

                        }
                        else
                        {

                            (*flag) = 0;
                        }
                    }
                }
                else if(j == 0)                          /// verifica el lado izquierdo
                {
                    if(tablero[i+1][j+1] == 1 || tablero[i+1][j+1] == 3)
                    {
                        if(tablero[i+2][j+2] == 0)
                        {
                            (*flag) = 3;
                        }
                        else
                        {

                            (*flag) = 0;

                        }
                    }


                }
            }
        }
    }

}

void comerFicha(int x, int y, int movimiento, int tablero[DIM][DIM], int fichaC, int ***escape,int diagonal,int bandera)
{
    int t;
    int comer = 1;
    int flag = 0;
    int contador = 0;
    int a,b;
    int diagonalDireccion = diagonal; ///-1 es derecha, 1 es izquierda

    do
    {
        do
        {
            if(turno == 1)
                t = getch();
            else
                t = toupper(getch());
            fflush(stdin);
        }
        while(t!=DER && t!= IZQ && t!= D && t!= A && t!= SPACE && t!=ENTER && t!=ESCAPE);

        if(bandera == 1 || bandera == 7 || bandera == 8)
        {

            if(turno == 1 && (t==DER || t==IZQ))
                t = MOV;
            else if(turno == 2 && (t==D || t==A))
                t = MOV;
            else if(turno == 2 && t==SPACE)
                t = ENTER;
        }

        if(t==SPACE)
        {
            t = ENTER;
        }
        switch(t)
        {
        case ENTER:
            vertical++;
            detector = 3;
            EnterCase(x,y,tablero,fichaC,comer,diagonalDireccion);
            flag = -1;
            break;

        case ESCAPE:
            EscapeCase(x,y,contador,movimiento,tablero);
            flag = -1;
            (***escape) = 1;
            break;

        case MOV:
            if(contador%2 == 0)
            {
                FichaToMatrix(x,y,&a,&b);
                if(tablero[a][b] == 0)
                {
                    gotoxy(x,y);
                    ficha(x,y,LILAC);
                }
                x -= movimiento;
                gotoxy(x,y);
                ficha(x,y,GREEN);
                diagonalDireccion = -1;
            }
            else
            {
                FichaToMatrix(x,y,&a,&b);
                if(tablero[a][b] == 0)
                {
                    gotoxy(x,y);
                    ficha(x,y,LILAC);
                }
                x += movimiento; ///Movimiento
                gotoxy(x,y);
                ficha(x,y,GREEN);
                diagonalDireccion = 1;
            }
            contador ++;
            break;
        }
    }
    while(flag == 0);
}

void comer(int x, int y, int tablero[DIM][DIM],int fichaC, int diagonal)
{
    int i=0,j=0;
    int flag = 0;

    FichaToMatrix(x,y,&i,&j);
    tablero[i][j] = fichaC;
    posicionIndices(i,j,2);

    if(turno == 1)                  ///Comen las Fichas
    {
        if(diagonal == -1)
        {
            tablero[i+1][j+1] = 0;
        }
        else if(diagonal == 1)
        {
            tablero[i+1][j-1] = 0;
        }
    }
    else if(turno == 2)
    {
        if(diagonal == 1)
        {
            tablero[i-1][j-1] = 0;
        }
        else if(diagonal == -1)
        {
            tablero[i-1][j+1] = 0;
        }
    }


    ///Crear el rebote.

    puedeComer(tablero,i,j,&flag);

    comerEnRebote(tablero,fichaC,flag,i,j);

    imprimirFichas(tablero);
}

void comerYmoverFicha(int x, int y, int movimiento,int ymovimiento, int tablero[DIM][DIM], int fichaC, int ***escape,int diagonal,int bandera)
{

    int t;
    int comer = 1;
    int flag = 0;
    int contador = 0;
    int a,b;
    int diagonalDireccion = diagonal; ///-1 es izquierda, 1 es derecha

    do
    {
        do
        {
            if(turno == 1)
                t = getch();
            else
                t = toupper(getch());
            fflush(stdin);
        }
        while(t!=DER && t!= IZQ && t!= D && t!= A && t!= SPACE && t!=ENTER && t!=ESCAPE);

        if(turno == 1 && (t==DER || t==IZQ))
            t = MOV;
        else if(turno == 2 && (t==D || t==A))
            t = MOV;
        else if(turno == 2 && t==SPACE)
            t = ENTER;

        switch(t)
        {
        case ENTER:
            vertical++;
            detector = 3;
            EnterCase(x,y,tablero,fichaC,comer,diagonalDireccion);
            flag = -1;
            break;

        case ESCAPE:
            EscapeCase(x,y,contador,movimiento,tablero);
            flag = -1;
            (***escape) = 1;
            break;

        case MOV:

            if(bandera == 7)           ///Se produce si se come del lado izquierdo y se mueve al lado derecho
            {
                if(contador%2 == 0)
                {
                    FichaToMatrix(x,y,&a,&b);
                    if(tablero[a][b] == 0)
                    {
                        gotoxy(x,y);
                        ficha(x,y,LILAC);
                    }
                    x -= movimiento;
                    y -= ymovimiento;
                    gotoxy(x,y);
                    ficha(x,y,GREEN);
                    diagonalDireccion = -1;
                }
                else
                {
                    FichaToMatrix(x,y,&a,&b);
                    if(tablero[a][b] == 0)
                    {
                        gotoxy(x,y);
                        ficha(x,y,LILAC);
                    }
                    x += movimiento;
                    y += ymovimiento;
                    gotoxy(x,y);
                    ficha(x,y,GREEN);
                    diagonalDireccion = 2;
                }
                contador ++;
            }
            else if(bandera == 8)                   ///Se produce si se come del lado derecha y se mueve al lado izquierda
            {
                if(contador%2 == 0)
                {
                    FichaToMatrix(x,y,&a,&b);
                    if(tablero[a][b] == 0)
                    {
                        gotoxy(x,y);
                        ficha(x,y,LILAC);
                    }
                    x += movimiento;
                    y -= ymovimiento;
                    gotoxy(x,y);
                    ficha(x,y,GREEN);
                    diagonalDireccion = 1;
                }
                else
                {
                    FichaToMatrix(x,y,&a,&b);
                    if(tablero[a][b] == 0)
                    {
                        gotoxy(x,y);
                        ficha(x,y,LILAC);
                    }
                    x -= movimiento;
                    y += ymovimiento;
                    gotoxy(x,y);
                    ficha(x,y,GREEN);
                    diagonalDireccion = 2;
                }
                contador ++;
            }
            break;
        }
    }
    while(flag == 0);

}

void comerEnRebote(int tablero[DIM][DIM], int tipo,int flag,int i,int j)
{

    int x,y,movimiento=0,ymovimiento = 0;

    int a,b;

    int diagonal = 0;

    matrixToGotoxy(i,j,&x,&y);

    if(tipo == 1 || tipo == 3 || tipo == 4)
    {
        if(flag == 2)   ///Come a la izquierda
        {
            y -= 6;
            x -= 18;
            ficha(x,y,GREEN);
            movimiento = 0;
            diagonal = -1;
            Sleep(200);
            comer(x,y,tablero,tipo,diagonal);
            borrarFichaMovida(i,j,tablero);
        }
        else if(flag == 3)              ///Come a la derecha
        {
            y -= 6;
            x += 18;
            ficha(x,y,GREEN);
            movimiento = 0;
            diagonal = 1;
            Sleep(200);
            comer(x,y,tablero,tipo,diagonal);
            borrarFichaMovida(i,j,tablero);
        }
    }
    else if(tipo == 2 || tipo == 3 || tipo == 4)
    {
        if(flag == 2)   ///Come a la izquierda
        {
            y += 6;
            x -= 18;
            ficha(x,y,GREEN);
            movimiento = 0;
            diagonal = -1;
            Sleep(200);
            comer(x,y,tablero,tipo,diagonal);
            borrarFichaMovida(i,j,tablero);
        }
        else if(flag == 3)              ///Come a la derecha
        {
            y += 6;
            x += 18;
            ficha(x,y,GREEN);
            movimiento = 0;
            diagonal = 1;
            Sleep(200);
            comer(x,y,tablero,tipo,diagonal);
            borrarFichaMovida(i,j,tablero);
        }
    }
}

int HabilitadoMoverDamas(int tablero[DIM][DIM], int *x1, int *x2, int *x3, int *x4)
{
    int i=0,j=0;
    int flag = 0;


    posicion_matrix_cuadrado(&i,&j);

    if(tablero[i][j] == 3 && turno == 1)
    {
        puedeComerDamas(tablero,i,j,&flag, &x1, &x2, &x3, &x4);

        HabilitadoMoverJug1Damas(tablero,i,j,&flag, &x1, &x2, &x3, &x4);

        if((*x1) != 0 || (*x2) != 0 || (*x3) != 0 || (*x4) != 0)
        {
            flag = 9;  ///Significa que es valido para mover o comer
        }


    }
    else if(tablero[i][j] == 4 && turno == 2)
    {
        puedeComerDamas(tablero,i,j,&flag, &x1, &x2, &x3, &x4);
        HabilitadoMoverJug2Damas(tablero,i,j,&flag, &x1, &x2, &x3, &x4);

        if((*x1) != 0 || (*x2) != 0 || (*x3) != 0 || (*x4) != 0)
        {
            flag = 9; ///Significa que es valido para mover o comer
        }

    }

    return flag;
}

void HabilitadoMoverJug1Damas(int tablero[DIM][DIM],int i, int j, int *flag, int **x1, int **x2, int **x3, int **x4)
{

    if(i > 0 && i < 7)                                  ///No esta en los limites superiores e inferiores
    {
        if(j < 7 && j > 0)                      ///No esta en los limites laterales
        {
            if(tablero[i-1][j-1] == 0)          ///Verifica esquina superior izquierda
            {
                (**x1) = 2;
            }
            if(tablero[i-1][j+1] == 0)        ///Verifica esquina superior derecha
            {
                (**x2) = 2;
            }
            if(tablero[i+1][j-1] == 0)        ///Verifica esquina inferior izquierda
            {
                (**x3) = 2;
            }
            if(tablero[i+1][j+1] == 0)        ///Verifica esquina inferior derecha
            {
                (**x4) = 2;
            }
        }
    }
    else     ///Caso de los bordes
    {
        if(j == 7)                                  ///verifica el lado derecho
        {


            if(tablero[i-1][j-1] == 0)                  ///Verifica esquina superior izquierda
            {
                (**x1) = 2;
            }
            if(tablero[i+1][j-1] == 0)            ///Verifica esquina inferior izquierda
            {
                (**x3) = 2;
            }
        }
        else if(j == 0)                          /// verifica el lado izquierdo
        {



            if(tablero[i-1][j+1] == 0)                  ///Verifica esquina superior derecha
            {
                (**x2) = 2;
            }
            if(tablero[i+1][j+1] == 0)               ///Verifica esquina inferior derecha
            {
                (**x4) = 2;
            }

        }
        else if(i == 0)
        {


            if(tablero[i+1][j-1] == 0)                                  ///Verifica esquina inferior izquierda
            {
                (**x3) = 2;
            }
            if(tablero[i+1][j+1] == 0)                                  ///Verifica esquina inferior derecha
            {
                (**x4) = 2;
            }

        }
        else if(i == 7)
        {


            if(tablero[i-1][j-1] == 0)                                  ///Verifica esquina superior izquierda
            {
                (**x1) = 2;
            }
            if(tablero[i-1][j+1] == 0)                                   ///Verifica esquina superior derecha
            {
                (**x2) = 2;
            }
        }
    }
}

void HabilitadoMoverJug2Damas(int tablero[DIM][DIM],int i, int j, int *flag, int **x1, int **x2, int **x3, int **x4)
{

    if(i > 0 && i < 7)                                  ///No esta en los limites superiores e inferiores
    {
        if(j < 7 && j > 0)                      ///No esta en los limites laterales
        {
            if(tablero[i-1][j-1] == 0)          ///Verifica esquina superior izquierda
            {
                (**x1) = 2;
            }
            if(tablero[i-1][j+1] == 0)                            ///Verifica esquina superior derecha
            {
                (**x2) = 2;
            }
            if(tablero[i+1][j-1] == 0)                            ///Verifica esquina inferior izquierda
            {
                (**x3) = 2;
            }
            if(tablero[i+1][j+1] == 0)                             ///Verifica esquina inferior derecha
            {
                (**x4) = 2;
            }
        }

    }
    else     ///Caso de los bordes
    {
        if(j == 7)                                  ///verifica el lado derecho
        {

            (**x2) = 0;                              ///Asigna 0 a las posiciones que no se pueden mover
            (**x4) = 0;

            if(tablero[i-1][j-1] == 0)              ///Verifica esquina superior izquierda
            {
                (**x1) = 2;
            }

            if(tablero[i+1][j-1] == 0)              ///Verifica esquina inferior izquierda
            {
                (**x3) = 2;
            }

        }
        else if(j == 0)                          /// verifica el lado izquierdo
        {

            (**x1) = 0;
            (**x3) = 0;

            if(tablero[i-1][j+1] == 0)              ///Verifica esquina superior derecha
            {
                (**x2) = 2;
            }

            if(tablero[i+1][j+1] == 0)              ///Verifica esquina inferior derecha
            {
                (**x4) = 2;
            }
        }
        else if(i == 0)
        {
            (**x1) = 0;
            (**x2) = 0;

            if(tablero[i+1][j-1] == 0)                                  ///Verifica esquina inferior izquierda
            {
                (**x3) = 2;
            }
            if(tablero[i+1][j+1] == 0)                                  ///Verifica esquina inferior derecha
            {
                (**x4) = 2;
            }

        }
        else if(i == 7)
        {
            (**x3) = 0;
            (**x4) = 0;

            if(tablero[i-1][j-1] == 0)                                  ///Verifica esquina superior izquierda
            {
                (**x1) = 2;
            }
            if(tablero[i-1][j+1] == 0)                                   ///Verifica esquina superior derecha
            {
                (**x2) = 2;
            }
        }
    }
}

void puedeComerDamas(int tablero[DIM][DIM],int i, int j, int *flag, int **x1, int **x2, int **x3, int **x4)
{

    if(tablero[i][j] == 3 && turno == 1)                        ///Mueve dama blanca
    {
        if(i > 1 && i < 6)                                 ///No esta en los limites superiores e inferiores
        {
            if(j < 7 && j > 0)                             ///No esta en los limites laterales
            {
                if(tablero[i-1][j-1] == 2 || tablero[i-1][j-1] == 4)
                {
                    if(tablero[i-2][j-2] == 0)                          ///Verifica esquina superior izquierda
                    {
                        (**x1) = 1;
                    }
                }
                if(tablero[i-1][j+1] == 2 || tablero[i-1][j+1] == 4)
                {
                    if(tablero[i-2][j+2] == 0)                          ///Verifica esquina superior derecha
                    {
                        (**x2) = 1;
                    }
                }
                if(tablero[i+1][j-1] == 2 || tablero[i+1][j-1] == 4)
                {
                    if(tablero[i+2][j-2] == 0)                          ///Verifica esquina inferior izquierda
                    {
                        (**x3) = 1;
                    }
                }
                if(tablero[i+1][j+1] == 2 || tablero[i+1][j+1] == 4)
                {
                    if(tablero[i+2][j+2] == 0)                          ///Verifica esquina inferior derecha
                    {
                        (**x4) = 1;
                    }
                }
            }
        }
        else     ///Caso de los bordes
        {
            if(j >=6)                                  ///verifica el lado derecho
            {

                (**x2) = 0;                              ///Asigna 0 a las posiciones que no se pueden mover
                (**x4) = 0;

                if(tablero[i-1][j-1] == 2 || tablero[i-1][j-1] == 4)
                {
                    if(tablero[i-2][j-2] == 0)                          ///Verifica esquina superior izquierda
                    {
                        (**x1) = 1;
                    }
                }
                if(tablero[i+1][j-1] == 2 || tablero[i+1][j-1] == 4)
                {
                    if(tablero[i+2][j-2] == 0)                          ///Verifica esquina inferior izquierda
                    {
                        (**x3) = 1;
                    }
                }
            }
            else if(j <= 1)                          /// verifica el lado izquierdo
            {

                (**x1) = 0;
                (**x3) = 0;

                if(tablero[i-1][j+1] == 2 || tablero[i-1][j+1] == 4)
                {
                    if(tablero[i-2][j+2] == 0)                          ///Verifica esquina superior derecha
                    {
                        (**x2) = 1;
                    }
                }
                if(tablero[i+1][j+1] == 2 || tablero[i+1][j+1] == 4)
                {
                    if(tablero[i+2][j+2] == 0)                          ///Verifica esquina inferior derecha
                    {
                        (**x4) = 1;
                    }
                }
            }
            else if(i <= 1)
            {
                (**x1) = 0;
                (**x2) = 0;


                if(tablero[i+1][j-1] == 2 || tablero[i+1][j-1] == 4)        ///Verifica esquina inferior izquierda
                {
                    if(tablero[i+2][j-2] == 0)
                    {
                        (**x3) = 1;
                    }
                }
                if(tablero[i+1][j+1] == 2 || tablero[i+1][j+1] == 4)                                  ///Verifica esquina inferior derecha
                {
                    if(tablero[i+2][j+2] == 0)
                    {
                        (**x4) = 1;
                    }
                }
            }
            else if(i >= 6)
            {

                (**x3) = 0;
                (**x4) = 0;

                if(tablero[i-1][j-1] == 2 || tablero[i-1][j-1] == 4)                                  ///Verifica esquina superior izquierda
                {
                    if(tablero[i-2][j-2] == 0)
                    {
                        (**x1) = 1;
                    }
                }
                if(tablero[i-1][j+1] == 2 || tablero[i-1][j+1] == 4)                                   ///Verifica esquina superior derecha
                {
                    if(tablero[i-2][j+2] == 0)
                    {
                        (**x2) = 1;
                    }
                }
            }
        }
    }
    else if(tablero[i][j] == 4 && turno == 2)
    {
        if(i > 1 && i < 6)                                 ///No esta en los limites superiores e inferiores
        {
            if(j < 7 && j > 0)                             ///No esta en los limites laterales
            {
                if(tablero[i-1][j-1] == 1 || tablero[i-1][j-1] == 3)
                {
                    if(tablero[i-2][j-2] == 0)                          ///Verifica esquina superior izquierda
                    {
                        (**x1) = 1;
                    }
                }
                if(tablero[i-1][j+1] == 1 || tablero[i-1][j+1] == 3)
                {
                    if(tablero[i-2][j+2] == 0)                          ///Verifica esquina superior derecha
                    {
                        (**x2) = 1;
                    }
                }
                if(tablero[i+1][j-1] == 1 || tablero[i+1][j-1] == 3)
                {
                    if(tablero[i+2][j-2] == 0)                          ///Verifica esquina inferior izquierda
                    {
                        (**x3) = 1;
                    }
                }
                if(tablero[i+1][j+1] == 1 || tablero[i+1][j+1] == 3)
                {
                    if(tablero[i+2][j+2] == 0)                          ///Verifica esquina inferior derecha
                    {
                        (**x4) = 1;
                    }
                }
            }
        }
        else     ///Caso de los bordes
        {
            if(j >= 6)                                  ///verifica el lado derecho
            {

                (**x2) = 0;                              ///Asigna 0 a las posiciones que no se pueden mover
                (**x4) = 0;

                if(tablero[i-1][j-1] == 1 || tablero[i-1][j-1] == 3)
                {
                    if(tablero[i-2][j-2] == 0)                          ///Verifica esquina superior izquierda
                    {
                        (**x1) = 1;
                    }
                }
                if(tablero[i+1][j-1] == 1 || tablero[i+1][j-1] == 3)
                {
                    if(tablero[i+2][j-2] == 0)                          ///Verifica esquina inferior izquierda
                    {
                        (**x3) = 1;
                    }
                }
            }
            else if(j <= 1)                          /// verifica el lado izquierdo
            {

                (**x1) = 0;
                (**x3) = 0;

                if(tablero[i-1][j+1] == 1 || tablero[i-1][j+1] == 3)
                {
                    if(tablero[i-2][j+2] == 0)                          ///Verifica esquina superior derecha
                    {
                        (**x2) = 1;
                    }
                }
                if(tablero[i+1][j+1] == 1 || tablero[i+1][j+1] == 3)
                {
                    if(tablero[i+2][j+2] == 0)                          ///Verifica esquina inferior derecha
                    {
                        (**x4) = 1;
                    }
                }
            }
            else if(i <= 1)
            {
                (**x1) = 0;
                (**x2) = 0;

                if(tablero[i+1][j-1] == 1 || tablero[i+1][j-1] == 3)        ///Verifica esquina inferior izquierda
                {
                    if(tablero[i+2][j-2] == 0)
                    {
                        (**x3) = 2;
                    }
                }
                if(tablero[i+1][j+1] == 1 || tablero[i+1][j+1] == 3)                                  ///Verifica esquina inferior derecha
                {
                    if(tablero[i+2][j+2] == 0)
                    {
                        (**x4) = 2;
                    }
                }
            }
            else if(i >= 6)
            {
                (**x3) = 0;
                (**x4) = 0;

                if(tablero[i-1][j-1] == 2 || tablero[i-1][j-1] == 4)                                  ///Verifica esquina superior izquierda
                {
                    if(tablero[i-2][j-2] == 0)
                    {
                        (**x1) = 2;
                    }
                }
                if(tablero[i-1][j+1] == 2 || tablero[i-1][j+1] == 4)                                   ///Verifica esquina superior derecha
                {
                    if(tablero[i-2][j+2] == 0)
                    {
                        (**x2) = 2;
                    }
                }
            }
        }

    }
}

void imprimirMovimientosPosiblesDamas(int i,int j,int tipo,int tablero[DIM][DIM],int **escape,int x1, int x2, int x3, int x4)
{

    int opc = 0;
    int diagonal;
    int x=0,y=0;

    matrixToGotoxy(i,j,&x,&y);

    if(tipo == 3)
    {

        imprimirPosicionesVioletas(x1,x2,x3,x4,x,y);

        opc = imprimePrimeraOpcion(x1,x2,x3,x4,&x,&y,&diagonal);

        moverDama(x,y,tablero,tipo,&escape,diagonal,opc,x1,x2,x3,x4);

    }
    else if(tipo == 4)
    {

        imprimirPosicionesVioletas(x1,x2,x3,x4,x,y);

        opc = imprimePrimeraOpcion(x1,x2,x3,x4,&x,&y,&diagonal);

        moverDama(x,y,tablero,tipo,&escape,diagonal,opc,x1,x2,x3,x4);

    }



}

int imprimePrimeraOpcion(int x1, int x2, int x3, int x4,int *x, int *y, int *diagonal)
{
    int opc = 0;
    int tecla;


    if(x1 == 0)
        X1 = FALSE;
    if(x2 == 0)
        X2 = FALSE;
    if(x3 == 0)
        X3 = FALSE;
    if(x4 == 0)
        X4 = FALSE;


    if(x1 != 0 && X1 == TRUE)
    {
        if(x1 == 1)
        {
            (*y) -= 6;
            (*x) -= 18;
            fichaMaster((*x),(*y),GREEN);
            opc = 1;
            (*diagonal) = 1;
        }
        else
        {
            (*y) -= 3;
            (*x) -= 9;
            fichaMaster((*x),(*y),GREEN);
            opc = 5;
        }
        X1 = FALSE;
    }
    else if(x2 != 0 && X2 == TRUE)
    {
        if(x2 == 1)
        {
            (*y) -= 6;
            (*x) += 18;
            fichaMaster((*x),(*y),GREEN);
            opc = 2;
            (*diagonal) = -1;
        }
        else
        {
            (*y) -= 3;
            (*x) += 9;
            fichaMaster((*x),(*y),GREEN);
            opc = 6;
        }
        X2 = FALSE;
    }
    else if(x3 != 0 && X3 == TRUE)
    {
        if(x3 == 1)
        {
            (*y) += 6;
            (*x) -= 18;
            fichaMaster((*x),(*y),GREEN);
            opc = 3;
            (*diagonal) = -1;
        }
        else
        {
            (*y) += 3;
            (*x) -= 9;
            fichaMaster((*x),(*y),GREEN);
            opc = 7;
        }
        X3 = FALSE;
    }
    else if(x4 != 0 && X4 == TRUE)
    {
        if(x4 == 1)
        {
            (*y) += 6;
            (*x) += 18;
            fichaMaster((*x),(*y),GREEN);
            opc = 4;
            (*diagonal) = 1;
        }
        else
        {
            (*y) += 3;
            (*x) += 9;
            fichaMaster((*x),(*y),GREEN);
            opc = 8;
        }
        X4 = FALSE;
    }

    if(X1 == FALSE && X2 == FALSE && X3 == FALSE && X4 == FALSE)
    {
        X1 = TRUE;
        X2 = TRUE;
        X3 = TRUE;
        X4 = TRUE;
    }



    return opc;

}

void moverDama(int x, int y,int tablero[DIM][DIM], int fichaC, int ***escape,int diagonal,int opc, int x1, int x2, int x3, int x4)
{
    int t;
    int contador = 1;           ///y esto dejarlo hasta cambiar el escape
    int movimiento = 1;         ///arreglarlo con el ESC
    int accion = 1;                ///Cambiar esto cuando pueda comer  /// comer = 1 mover = 0
    int flag = 0;
    int tecla;

    do
    {
        do
        {
            if(turno == 1)
            {
                fflush(stdin);
                t = getch();
            }
            else
            {
                fflush(stdin);
                t = toupper(getch());
            }
        }
        while(t!=DER && t!= IZQ && t!= D && t!= A && t!= SPACE && t!=ENTER && t!=ESCAPE);

        if(turno == 1 && (t==DER || t==IZQ))
        {
            tecla = t;
            t = MOV;
        }
        else if(turno == 2 && (t==D || t==A))
        {
            t = MOV;
        }
        else if(turno == 2 && t==SPACE)
        {
            t = ENTER;
        }
        else if(turno == 2 && t==ENTER)
        {
            t = 0;
        }

        switch(t)
        {
        case ENTER:
            vertical++;   ///No estaba
            EnterCaseDamas(x,y,tablero,fichaC,accion,diagonal,opc);
            flag = -1;
            break;

        case ESCAPE:
            detector = 0;
            EscapeCase(x,y,contador,movimiento,tablero);
            flag = -1;
            (***escape) = 1;
            break;

        case MOV:
            //seleccionarMovimiento(tablero,tecla,&x,&y,&opc,&diagonal,&accion,x1,x2,x3,x4);
            break;
        }
    }
    while(flag == 0);
}

void seleccionarMovimiento(int tablero[DIM][DIM],int tecla,int *x, int *y, int *posActual, int *diagonal, int *accion, int x1, int x2, int x3, int x4)
{

    int flag = 0;
    int xCopia,yCopia,diagonalCopia;

    do
    {
        xCopia = (*x);
        yCopia = (*y);
        diagonalCopia = (*diagonal);
        switch (tecla)
        {
        case IZQ:

            (*posActual) = imprimePrimeraOpcion(x1,x2,x3,x4,&xCopia,&yCopia,&diagonalCopia);
            break;


        case DER:

            break;

        case ENTER:

            break;

        case ESCAPE:

            break;

        }
        (*x) = xCopia;
        (*y) = yCopia;
        (*diagonal) = diagonalCopia;

    }
    while(flag == 0);


}

void EnterCaseDamas(int x, int y, int tablero[DIM][DIM],int fichaC,int accion,int diagonal,int opc)
{
    int i=0,j=0;

    FichaToMatrix(x,y,&i,&j);
    if(accion == 1)
    {
        detector = 3;
        comerDamas(x,y, tablero, fichaC, diagonal,opc);
    }
    else
    {
        detector = 2;
        tablero[i][j] = fichaC;
        posicionIndices(i,j,2);
    }

    if(turno == 1)
    {
        turno = 2;
    }
    else
    {
        turno = 1;
    }

    imprimirFichas(tablero);

}

void comerDamas(int x, int y, int tablero[DIM][DIM],int fichaC, int diagonal,int opc)
{
    int i=0,j=0;
    int flag = 0;

    FichaToMatrix(x,y,&i,&j);
    tablero[i][j] = fichaC;
    posicionIndices(i,j,2);

    if(opc == 1 || opc == 2)
    {
        ///Comen las Fichas
        if(diagonal == -1)
        {
            tablero[i+1][j+1] = 0;
        }
        else if(diagonal == 1)
        {
            tablero[i+1][j-1] = 0;
        }
    }
    else if(opc == 3 || opc == 4)
    {
        if(diagonal == 1)
        {
            tablero[i-1][j-1] = 0;
        }
        else if(diagonal == -1)
        {
            tablero[i-1][j+1] = 0;
        }
    }


    ///Crear el rebote.

    puedeComer(tablero,i,j,&flag);   ///Cambiar al puede comer damas

    comerEnRebote(tablero,fichaC,flag,i,j);

    imprimirFichas(tablero);
}

void imprimirPosicionesVioletas(int x1, int x2, int x3, int x4,int x, int y)
{

    int a = x;
    int b = y;

    if(x1 == 1)
    {
        ///X1 = TRUE;
        y -= 6;
        x -= 18;
        fichaMaster(x,y,LILAC);
        x = a;
        y = b;
    }
    else if(x1 == 2)
    {
        ///X1 = TRUE;
        y -= 3;
        x -= 9;
        fichaMaster(x,y,LILAC);
        x = a;
        y = b;
    }

    if(x2 == 1)
    {
        ///  X2 = TRUE;
        y -= 6;
        x += 18;
        fichaMaster(x,y,LILAC);
        x = a;
        y = b;
    }
    else if(x2 == 2)
    {
        ///X2 = TRUE;
        y -= 3;
        x += 9;
        fichaMaster(x,y,LILAC);
        x = a;
        y = b;
    }

    if(x3 == 1)
    {
        ///X3 = TRUE;
        y += 6;
        x -= 18;
        fichaMaster(x,y,LILAC);
        x = a;
        y = b;
    }
    else if(x3 == 2)
    {
        ///X3 = TRUE;
        y += 3;
        x -= 9;
        fichaMaster(x,y,LILAC);
        x = a;
        y = b;
    }

    if(x4 == 1)
    {
        ///X4 = TRUE;
        y += 6;
        x += 18;
        fichaMaster(x,y,LILAC);
        x = a;
        y = b;
    }
    else if(x4 == 2)
    {
        ///X4 = TRUE;
        y += 3;
        x += 9;
        fichaMaster(x,y,LILAC);
        x = a;
        y = b;
    }

}

void inicioJuego(int tiempo)
{

    system("MODE 93,45");
    sem_init(&semaforo,1,0);
    pthread_t hilo1, hilo2;

    pthread_create(&hilo2,NULL,ejecutar,(void*)tiempo);

    if(tiempo != NULL)
    {
        pthread_create(&hilo1,NULL,reloj,(void*)tiempo);
        pthread_join(hilo1,NULL);
    }

    pthread_join(hilo2,NULL);
    system("MODE 93,40");
    finDelJuego = FALSE;
    turno = 1;
    vertical = 32;

}

void menuDetalles(NODO *lista,ARBOL *aux,int *min,JUGADOR *J1,JUGADOR *J2) ///No se puede  meter a la libreria
{

    char c;
    int y = 12;
    int x = 10;
    int i = 0;
    int bandera = 1;

    system("cls");
    hidecursor(0);

//MENU

    tituloDamas(2,0);


    cuadritoEstetico1();
    gotoxy(8,12);
    color(RED);
    printf("JUGADOR");
    gotoxy(10,13);
    printf("vs");
    gotoxy(9,14);
    printf("I.A."RESET);
    gotoxy(20,13);
    printf("(Proximamente)");

    cuadritoEstetico2();
    gotoxy(8,20);
    printf("JUGADOR");
    gotoxy(10,21);
    printf("vs");
    gotoxy(8,22);
    printf("JUGADOR");


    cuadritoEstetico3();
    gotoxy(65,11);
    printf("TIEMPO");
    gotoxy(67,13);
    printf("05");
    gotoxy(62,13);
    printf("<-");
    gotoxy(72,13);
    printf("->");



    gotoxy(70,38);
    printf("By Papa,Roselli,Huerta");



    while(bandera == 1)
    {

        c = getch();

        if(c == -32)
        {
            c = getch();

            if(c == 72)            //Arriba
            {
                if(y == LIMSUP)      //Limite superior
                {
                    y = 14;      //Limite inferior
                }
                else
                {
                    y = y - 2;
                }
            }
            if(c == 80)           //Abajo
            {

                if(y == 14)        //Limite inferior
                {
                    y = LIMSUP;    //Limite superior
                }
                else
                {
                    y = y + 2;
                }
            }
            if(c == 77)         //Derecha
            {
                gotoxy(72,13);
                color(RED);
                printf("->");
                Sleep(100);
                gotoxy(72,13);
                printf(RESET"->");
                Sleep(0);
                if(x == 12)
                {
                    x = 8;
                }
                else
                {
                    x = x + 2;
                }
            }
            if(c == 75)        // Del Caño
            {
                gotoxy(62,13);
                color(RED);
                printf("<-");
                Sleep(100);
                gotoxy(62,13);
                printf(RESET"<-");
                Sleep(0);
                if(x == 8)
                {
                    x = 12;
                }
                else
                {
                    x = x - 2;
                }

            }
        }

        //Funcion para cambiar de color los titulos.
        menuColoresDetalles(y,x);


        if(c==13)                      //Acciones al presionar Enter.
        {
            switch (y)
            {

            case 12:

                break;

            case 14:

                (*min) = relojYcolores(x);
                (*J1) = menuElegirUsuario(lista,aux,1);
                (*J2) = menuElegirUsuario(lista,aux,2);
                bandera = 0;
                break;

            }


        }
        if(c==27)            //Tecla ESC volver al menu.
        {
            menuPrincipal(lista,aux);
        }


    }
}

JUGADOR menuElegirUsuario(NODO * lista,ARBOL *aux,int Jug)
{
    int y = 8;
    char c;
    int i;
    int flag = 1;
    JUGADOR J;

    system("cls");
    hidecursor(0);

    //MENU

    tituloDamas(2,0);

    if(Jug == 1)
    {

        gotoxy(7,12);
        printf(" _________    ____        ");
        gotoxy(7,13);
        printf("/________/\\  /___/\\       ");
        gotoxy(7,14);
        printf("\\__.::.__\\/  \\_::\\ \\      ");
        gotoxy(7,15);
        printf("  /_\\::\\ \\     \\::\\ \\     ");
        gotoxy(7,16);
        printf("  \\:.\\::\\ \\    _\\: \\ \\__  ");
        gotoxy(7,17);
        printf("   \\: \\  \\ \\  /__\\: \\__/\\ ");
        gotoxy(7,18);
        printf("    \\_____\\/  \\________\\/ ");
        gotoxy(7,19);
        printf("                          ");


    }
    else
    {

        color(RED);
        gotoxy(7,12);
        printf(" _________    _____       ");
        gotoxy(7,13);
        printf("/________/\\  /_____/\\     ");
        gotoxy(7,14);
        printf("\\__.::.__\\/  \\:::_:\\ \\    ");
        gotoxy(7,15);
        printf("  /_\\::\\ \\       _\\:\\|    ");
        gotoxy(7,16);
        printf("  \\:.\\::\\ \\     /::_/__   ");
        gotoxy(7,17);
        printf("   \\: \\  \\ \\    \\:\\____/\\ ");
        gotoxy(7,18);
        printf("    \\_____\\/     \\_____\\/ ");
        gotoxy(7,19);
        printf("                          ",RESET);
        color(WHITE);

    }

    gotoxy(35,12);
    color(RED);
    printf("CREAR NUEVO USUARIO"RESET);
    gotoxy(30,14);
    printf("INGRESAR CON USUARIO EXISTENTE");


    gotoxy(70,38);
    printf("By Papa,Roselli,Huerta");



    while(flag == 1)
    {

        c = getch();

        if(c == -32)
        {
            c = getch();

            if(c == 72)            /*Arriba*/
            {
                if(y == 8)      //Limite superior
                {
                    y = 10;      //Limite inferior
                }
                else
                {
                    y = y - 2;
                }
            }
            if(c == 80)          /*Abajo*/
            {

                if(y == 10)        //Limite inferior
                {
                    y = 8;    //Limite superior
                }
                else
                {
                    y = y + 2;
                }
            }
        }

        //Funcion para cambiar de color los titulos.
        menuColoresElegirUsuarios(y);


        if(c==13)                      ///Acciones al presionar Enter.
        {
            switch (y)
            {

            case 8:
                system("cls");
                cargarArchivo(Jug);
                J = buscarUltimaEstructura();
                flag = 0;
                break;

            case 10:
                system("cls");
                J = usuarioExistente(aux,Jug);
                flag = 0;
                break;
            }

        }


    }

    return J;
}

void cargarArchivo(int Jug)
{
    JUGADOR J;
    FILE *file = fopen(ARCHIVO,"ab");
    int res;
    int i;

    if(file == NULL)
    {
        printf("File not found.\n");
        fflush(stdout);
    }
    else
    {
        tituloDamas(2,0);

        if(Jug == 1)
        {

            gotoxy(7,12);
            printf(" _________    ____        ");
            gotoxy(7,13);
            printf("/________/\\  /___/\\       ");
            gotoxy(7,14);
            printf("\\__.::.__\\/  \\_::\\ \\      ");
            gotoxy(7,15);
            printf("  /_\\::\\ \\     \\::\\ \\     ");
            gotoxy(7,16);
            printf("  \\:.\\::\\ \\    _\\: \\ \\__  ");
            gotoxy(7,17);
            printf("   \\: \\  \\ \\  /__\\: \\__/\\ ");
            gotoxy(7,18);
            printf("    \\_____\\/  \\________\\/ ");
            gotoxy(7,19);
            printf("                          ");


        }
        else
        {

            color(RED);
            gotoxy(7,12);
            printf(" _________    _____       ");
            gotoxy(7,13);
            printf("/________/\\  /_____/\\     ");
            gotoxy(7,14);
            printf("\\__.::.__\\/  \\:::_:\\ \\    ");
            gotoxy(7,15);
            printf("  /_\\::\\ \\       _\\:\\|    ");
            gotoxy(7,16);
            printf("  \\:.\\::\\ \\     /::_/__   ");
            gotoxy(7,17);
            printf("   \\: \\  \\ \\    \\:\\____/\\ ");
            gotoxy(7,18);
            printf("    \\_____\\/     \\_____\\/ ");
            gotoxy(7,19);
            printf("                          ",RESET);
            color(WHITE);

        }


        gotoxy(33,14);
        printf("Ingrese Nick: ");
        verificarNombre(J.nombre);

        printf("\n\n");
        gotoxy(33,16);
        printf("Ingrese Edad: ");
        scanf("%d",&J.edad);

        J.ganadas = 0;
        J.empatadas = 0;
        J.perdidas = 0;

        J.baja ='n';

        fwrite(&J,sizeof(JUGADOR),1,file);

        fclose(file);
    }
}

void verificarNombre(char nombre[30])
{
    JUGADOR J;
    int res;
    FILE *file = fopen(ARCHIVO,"rb");

    if(file!=NULL)
    {
        do
        {
            res = 0;
            fflush(stdin);
            gets(nombre);

            while(res==0 && fread(&J,sizeof(JUGADOR),1,file)>0)
            {
                if(strcmpi(nombre,J.nombre) == 0)
                {
                    res = 1;
                }
            }

            if(res==1)
            {
                gotoxy(23,13);
                printf("(No se puede ingresar Nick repetido)");
                gotoxy(43,14);
                printf("                                      ");
                gotoxy(23,14);
                printf("Ingrese un Nick valido: ");
                rewind(file);
            }
        }
        while(res==1);

        fclose(file);
    }
}

JUGADOR buscarUltimaEstructura()
{

    int res;
    JUGADOR J;
    FILE *file = fopen(ARCHIVO,"ab");

    fseek(file,0,SEEK_END);
    res = ftell(file) - sizeof(JUGADOR);
    fseek(file,res,SEEK_SET);
    fread(&J,sizeof(JUGADOR),1,file);

    fclose(file);

    return J;
}

JUGADOR usuarioExistente(ARBOL *aux,int Jug){

    char name[30];
    char control ='n';
    JUGADOR J;

    FILE *file = fopen(ARCHIVO,"rb");


    if(file == NULL)
    {
        printf("File not found.\n");
        fflush(stdout);
    }
    else
    {

        tituloDamas(2,0);

        if(Jug == 1)
        {
            gotoxy(7,12);
            printf(" _________    ____        ");
            gotoxy(7,13);
            printf("/________/\\  /___/\\       ");
            gotoxy(7,14);
            printf("\\__.::.__\\/  \\_::\\ \\      ");
            gotoxy(7,15);
            printf("  /_\\::\\ \\     \\::\\ \\     ");
            gotoxy(7,16);
            printf("  \\:.\\::\\ \\    _\\: \\ \\__  ");
            gotoxy(7,17);
            printf("   \\: \\  \\ \\  /__\\: \\__/\\ ");
            gotoxy(7,18);
            printf("    \\_____\\/  \\________\\/ ");
            gotoxy(7,19);
            printf("                          ");
        }
        else
        {
            color(RED);
            gotoxy(7,12);
            printf(" _________    _____       ");
            gotoxy(7,13);
            printf("/________/\\  /_____/\\     ");
            gotoxy(7,14);
            printf("\\__.::.__\\/  \\:::_:\\ \\    ");
            gotoxy(7,15);
            printf("  /_\\::\\ \\       _\\:\\|    ");
            gotoxy(7,16);
            printf("  \\:.\\::\\ \\     /::_/__   ");
            gotoxy(7,17);
            printf("   \\: \\  \\ \\    \\:\\____/\\ ");
            gotoxy(7,18);
            printf("    \\_____\\/     \\_____\\/ ");
            gotoxy(7,19);
            printf("                          ",RESET);
            color(WHITE);
        }

        do
        {
            gotoxy(33,14);
            printf("Ingrese Nick: ");
            fflush(stdin);
            gets(name);

            if(existeNombre(aux,name) == 1)
            {
                J = retornarJugador(name);
                if(J.baja == 's')
                {
                    gotoxy(27,13);
                    printf("(El jugador que ingreso esta dado de baja)", name);
                    gotoxy(43,14);
                    printf("                                      ");
                }
                else
                {
                    control='s';
                }
            }
            else
            {
                ///El jugador no existe
                gotoxy(27,13);
                printf("(El jugador no existe, intente nuevamente)", name);
                gotoxy(43,14);
                printf("                                      ");


            }

        }
        while (control =='n');

        fclose(file);

    }

    return J;
}

JUGADOR retornarJugador(char nombre[30])
{

    JUGADOR J;
    int flag = 0;
    int pos = 0;
    FILE *file=fopen(ARCHIVO, "rb");

    if(file != NULL)
    {
        while(flag == 0 && fread(&J,sizeof(JUGADOR),1,file)>0)
        {

            if(strcmpi(nombre,J.nombre) == 0)
            {
                flag = 1;
            }
        }
    }




    return J;
}

void menuJugadores(NODO * lista, ARBOL *aux)
{
    int y = 8;
    char c;
    char d;

    system("cls");
    hidecursor(0);

    //MENU

    tituloDamas(2,0);

    gotoxy(37,12);
    color(RED);
    printf("MEJORES JUGADORES"RESET);
    gotoxy(35,14);
    printf("DAR DE BAJA UN JUGADOR");

    gotoxy(70,38);
    printf("By Papa,Roselli,Huerta");



    do
    {

        c = getch();

        if(c == -32)
        {
            c = getch();

            if(c == 72)            /*Arriba*/
            {
                if(y == 8)      //Limite superior
                {
                    y = 10;      //Limite inferior
                }
                else
                {
                    y = y - 2;
                }
            }
            if(c == 80)           /*Abajo*/
            {

                if(y == 10)        //Limite inferior
                {
                    y = 8;    //Limite superior
                }
                else
                {
                    y = y + 2;
                }
            }
        }

        //Funcion para cambiar de color los titulos.
        menuColoresJugadores(y);


        if(c==13)                      //Acciones al presionar Enter.
        {
            switch (y)
            {

            case 8:
                system("cls");
                lista = ordenarGanadas(lista);
                recorrerYmostrarMejores(lista);
                lista = inicLista();
                while(d!=27 && d!=75)
                {
                    d = getch();
                }
                if(d==27 || d==75)
                {
                    system("cls");
                    menuJugadores(lista,aux);
                }
                break;

            case 10:
                system("cls");
                bajaJugadores(lista,aux);
                break;
            }

        }

        if(c==27)            //Tecla ESC volver al menu.
        {
            menuPrincipal(lista,aux);
        }


    }
    while(1);

}

NODO * ordenarGanadas(NODO *lista)
{

    FILE *file = fopen(ARCHIVO,"rb");
    JUGADOR J;
    NODO * nuevo = NULL;

    if(file != NULL)
    {
        while(fread(&J,sizeof(JUGADOR),1,file)>0)
        {
            nuevo = crearNodo(J);
            lista = agregarOrdenado(lista,nuevo);
        }

        fclose(file);
    }

    return lista;
}

void bajaJugadores(NODO * lista,ARBOL *aux)
{

    char name[30];
    char control;
    char d;
    FILE *file = fopen(ARCHIVO,"r+b");


    if(file == NULL)
    {
        printf("File not found.\n");
        fflush(stdout);
    }
    else
    {
        do
        {
            system("cls");
            tituloDamas(2,0);

            gotoxy(33,14);
            printf("Ingrese Nick: ");
            fflush(stdin);
            gets(name);

            if(existeNombre(aux,name) == 1)
            {
                bajaJugador(buscarPosicionNombre(name));

            }
            else
            {
                /// El cliente no existe
                system("cls");
                tituloDamas(2,0);
                gotoxy(25,16);
                printf("El jugador con nick %s no existe.", name);

            }
            gotoxy(29,19);
            printf("Desea quitar algun otro jugador?");
            flechasSN(&control,21,23);

        }
        while (control =='s');

        fclose(file);

        if(control == 'n')
        {
            system("cls");
            menuJugadores(lista,aux);
        }
    }

}

int existeNombre(ARBOL *aux,char nombre[30])
{

    int res = 0;
    FILE *file = fopen(ARCHIVO,"rb");

    if(file!=NULL)
    {

        while(res==0 && aux !=NULL)
        {
            if(strcmpi(nombre,aux->nombre) > 0)
            {

                aux = aux->der;
            }
            else
            {
                if(strcmpi(nombre,aux->nombre) < 0)
                {

                    aux = aux->izq;
                }

            }
            if(strcmpi(nombre,aux->nombre) == 0)
            {
                res = 1;
            }
        }

        fclose(file);
    }


    return res;
}

int buscarPosicionNombre(char nombre[30])
{

    JUGADOR J;
    int flag = 0;
    int pos = 0;
    FILE *file=fopen(ARCHIVO, "rb");

    if(file != NULL)
    {
        while(flag == 0 && fread(&J,sizeof(JUGADOR),1,file)>0)
        {

            if(strcmpi(nombre,J.nombre) == 0)
            {
                flag = 1;
            }
        }
    }

    pos = (ftell(file)/sizeof(JUGADOR));
    pos = pos-1;
    fclose(file);


    return pos;
}

void bajaJugador(int pos)
{
    JUGADOR J;
    FILE *file=fopen(ARCHIVO, "r+b");

    if(file!=NULL)
    {
        fseek(file, sizeof(JUGADOR)*(pos), SEEK_SET);
        fread(&J,sizeof(JUGADOR),1,file);

        J = eliminarJugador(J);

        fseek(file, sizeof(JUGADOR)*(-1), SEEK_CUR);
        fwrite(&J,sizeof(JUGADOR),1,file);

        fclose(file);
    }
}

JUGADOR eliminarJugador(JUGADOR J)
{

    char control = 'n';



    gotoxy(32,19);
    printf("Desea quitar al jugador?");

    flechasSN(&control,21,23);
    if (control =='s')
    {
        if(J.baja =='n')
        {
            system("cls");
            tituloDamas(2,0);
            gotoxy(24,14);
            color(RED);
            printf("*/ELIMINADO/*  %s",J.nombre);
            gotoxy(53,14);
            printf("*/ELIMINADO*/");
            color(WHITE);
            J.baja ='s';
        }
        else
        {
            gotoxy(33,14);
            printf("Ingrese Nick: %s",J.nombre);
            gotoxy(29,17);
            printf("El jugador ya esta dado de baja.");
        }

    }
    return J;
}

void controles(NODO * lista,ARBOL *aux)
{

    int vel = 2;
    int i;
    char j = 254;
    char c;

    cuadroEstetico();

    ///CUADRO CONTROLES
    gotoxy(40,2);
    color(RED);
    printf("%c",TRI_ARR);

    gotoxy(52,2);
    printf("%c"RESET,TRI_ARR);

    gotoxy(40,1);
    color(WHITE);
    printf("%c",VERTIC);

    gotoxy(52,1);
    printf("%c",VERTIC);

    gotoxy(40,0);
    color(RED);
    printf("%c",SUP_I);

    gotoxy(52,0);
    printf("%c"RESET,SUP_D);

    for(i=0; i<6; i++)
    {
        Sleep(vel);
        if(i % 2 == 0)
        {
            gotoxy(41+i,0);
            color(WHITE);
            printf("%c",HORIZ);

            gotoxy(51-i,0);
            printf("%c"RESET,HORIZ);
        }
        else
        {
            gotoxy(41+i,0);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(51-i,0);
            printf("%c"RESET,HORIZ);
        }
    }
    ///TERMINADO
    gotoxy(42,1);
    printf("CONTROLES");


    for(i=0; i<40; i++)
    {
        Sleep(vel);
        if(i % 2 == 0)
        {
            gotoxy(46+i,29);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(46-i,29);
            printf("%c"RESET,HORIZ);
        }
        else
        {
            gotoxy(46+i,29);
            printf("%c",HORIZ);

            gotoxy(46-i,29);
            printf("%c",HORIZ);
        }
    }

    color(WHITE);
    gotoxy(6,29);
    printf("%c",TRI_DER);

    gotoxy(86,29);
    printf("%c"RESET,TRI_IZQ);

    ///CUADRO AMBOS JUGADORES
    gotoxy(36,29);
    color(RED);
    printf("%c",TRI_ARR);

    gotoxy(54,29);
    color(RED);
    printf("%c"RESET,TRI_ARR);

    gotoxy(54,28);
    color(WHITE);
    printf("%c",VERTIC);

    gotoxy(36,28);
    printf("%c",VERTIC);

    gotoxy(36,27);
    color(RED);
    printf("%c",SUP_I);

    gotoxy(54,27);
    color(RED);
    printf("%c"RESET,SUP_D);

    for(i=0; i<10; i++)
    {
        Sleep(vel);
        if(i % 2 == 0)
        {
            gotoxy(37+i,27);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(53-i,27);
            printf("%c"RESET,HORIZ);
        }
        else
        {
            gotoxy(37+i,27);
            printf("%c",HORIZ);

            gotoxy(53-i,27);
            printf("%c",HORIZ);
        }
    }
    ///TERMINADO


    gotoxy(8,4);
    printf("%c JUGADOR 1:",j);

    gotoxy(8,6);
    printf("MOVER EL CASILLERO POR EL TABLERO:");

    teclaARR(20,8);
    teclaIZQ(12,12);
    teclaABJ(20,12);
    teclaDER(28,12);

    gotoxy(8,17);
    printf("SELECCIONAR FICHA:");
    teclaENTER(18,20);

    gotoxy(52,4);
    color(RED);
    printf("%c JUGADOR 2:",j);

    gotoxy(52,6);
    printf("MOVER EL CASILLERO POR EL TABLERO:");

    teclaW(64,8);
    teclaA(56,12);
    teclaS(64,12);
    teclaD(72,12);

    gotoxy(52,17);
    printf("SELECCIONAR FICHA:");
    teclaBarraEspaciadora(53,22);


    gotoxy(38,28);
    printf(RESET"AMBOS JUGADORES");
    color(RED);

    gotoxy(14,31);
    printf("PARA DEBUGGEAR EL TABLERO:"RESET);
    teclaAsterisco(24,33);

    gotoxy(52,31);
    printf(RESET"PARA PAUSAR O DESELECCIONAR:");
    color(RED);
    teclaESC(64,33);

    gotoxy(76,37);
    printf("REGLAS--->"RESET);

    gotoxy(7,37);
    printf("<---MENU");

    while(c!=75 && c!=27 && c!=77)
    {
        c = getch();
    }
    if(c==75 || c==27)
    {
        system("cls");
        menuPrincipal(lista,aux);
    }
    else if(c==77)
    {

        system("cls");
        reglas(lista,aux);
    }

}

void reglas(NODO * lista,ARBOL *aux)
{

    char j = 254;
    char c;
    int i;
    int vel = 2;

    cuadroEstetico();

    ///CUADRO REGLAS
    gotoxy(41,2);
    color(RED);
    printf("%c",TRI_ARR);

    gotoxy(50,2);
    printf("%c"RESET,TRI_ARR);

    gotoxy(41,1);
    color(WHITE);
    printf("%c",VERTIC);

    gotoxy(50,1);
    printf("%c",VERTIC);

    gotoxy(41,0);
    color(RED);
    printf("%c",SUP_I);

    gotoxy(50,0);
    printf("%c"RESET,SUP_D);

    for(i=0; i<6; i++)
    {
        Sleep(vel);
        if(i % 2 == 0)
        {
            gotoxy(42+i,0);
            color(WHITE);
            printf("%c",HORIZ);

            gotoxy(49-i,0);
            printf("%c"RESET,HORIZ);
        }
        else
        {
            gotoxy(42+i,0);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(49-i,0);
            printf("%c"RESET,HORIZ);
        }
    }
    ///TERMINADO
    gotoxy(43,1);
    printf("REGLAS");

    gotoxy(8,4);
    printf("%c Se juega por turnos alternos. Empieza a jugar quien tiene las fichas",j);
    gotoxy(8,5);
    printf("  blancas. En su turno cada jugador mueve una pieza propia.");

    gotoxy(8,8);
    color(RED);
    printf("%c Las piezas se mueven (cuando no comen) una posicion adelante (nunca",j);
    gotoxy(8,9);
    printf("  hacia atras) en diagonal a la derecha o a la izquierda."RESET);

    gotoxy(8,12);
    printf("%c Una pieza puede comer cuando tiene una ficha enemiga en diagonal un casi",j);
    gotoxy(8,13);
    printf("  llero adelante,y el casillero atras de la ficha enemiga se encuentra vacio. ");

    gotoxy(8,16);
    color(RED);
    printf("%c Se obtiene una ficha Dama si una ficha normal llega al borde opuesto del",j);
    gotoxy(8,17);
    printf("  tablero."RESET);

    gotoxy(8,20);
    printf("%c Una ficha Dama, tanto para moverse como para comer, puede avanzar tantos",j);
    gotoxy(8,21);
    printf("  casilleros como desee hacia delante y hacia atras, siempre en diagonal.");

    gotoxy(8,24);
    color(RED);
    printf("%c La ficha Dama tiene movimientos largos, pero se detiene directamente",j);
    gotoxy(8,25);
    printf("  luego de haber comido."RESET);

    gotoxy(8,28);
    printf("%c Un jugador gana si come todas las fichas enemigas. Tambien, si ningun",j);
    gotoxy(8,29);
    printf("  jugador puede comer las fichas restantes enemigas, el que haya usado ");
    gotoxy(8,30);
    printf("  menos tiempo ganara la partida.");

    gotoxy(8,33);
    color(RED);
    printf("%c Si nungun jugador puede realizar movimientos, se declarara empate",j);
    gotoxy(8,34);
    printf("  automaticamente."RESET);

    gotoxy(7,37);
    printf("<---CONTROLES"RESET);

    while(c!=75 && c!= 27 )
    {

        c = getch();
    }
    if(c == 75 || c == 27)
    {
        system("cls");
        controles(lista,aux);
    }
}

