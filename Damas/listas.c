#include "listas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define GREEN   "\033[1;32m"
#define RESET   "\033[1m\033[37m"
#define RED     12
#define WHITE   15

NODO * inicLista()
{
    return NULL;
}

NODO * crearNodo(JUGADOR jug)
{

    NODO * aux = (NODO*)malloc(sizeof(NODO));

    aux->jug = jug;

    aux->siguiente = NULL;

    return aux;
}

NODO * agregarPrincipioLista(NODO *lista, NODO *nuevo)
{

    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }

    return lista;
}

NODO * agregarOrdenado(NODO *lista, NODO *nuevo)
{
    int i = 0;

    if(lista == NULL)
    {
        lista = nuevo;
        i++;
    }
    else
    {
        if(nuevo->jug.ganadas > lista->jug.ganadas)
        {
            lista = agregarPrincipioLista(lista,nuevo);
            i++;
        }
        else
        {
            NODO * aux = lista;
            NODO * ante = aux;
            while(aux != NULL && nuevo->jug.ganadas <= aux->jug.ganadas && i < 10)
            {
                ante = aux;
                aux = aux->siguiente;
                i++;
            }
            ante->siguiente = nuevo;
            nuevo->siguiente = aux;
        }
    }
    return lista;
}

void mostrarJugador(JUGADOR jug)
{

    printf("\nNickname: %s\n",jug.nombre);
    printf("Edad: %d\n", jug.edad);
    printf("Ganadas: %d\n", jug.ganadas);
    printf("Empatadas: %d\n", jug.empatadas);
    printf("Perdidas: %d\n", jug.perdidas);
}

void mostrarMejores(JUGADOR jug,int * y,int x)
{

    gotoxy(7,(*y));
    if(jug.baja == 'n')
    {
        printf(" %i- NICKNAME: %s ",x,jug.nombre);
    }
    else if(jug.baja =='s')
    {
        color(RED);
        printf(" %i- NICKNAME: %s ",x,jug.nombre);
        gotoxy(50,(*y));
        printf("*/ELIMINADO*/");
        color(WHITE);
    }
    gotoxy(69,(*y));
    if(jug.baja == 'n')
    {
        printf("G: %i  E: %i  P: %i\n",jug.ganadas,jug.empatadas,jug.perdidas);
    }
    else if(jug.baja =='s')
    {
        color(RED);
        printf("G: %i  E: %i  P: %i\n",jug.ganadas,jug.empatadas,jug.perdidas);
        color(WHITE);
    }

}

void recorrerYmostrarMejores(NODO * lista)
{

    NODO *aux = lista;
    int y= 9;
    int i=0;
    int x = 1;


    recuadroMejoresJugadores();

    while(aux != NULL && i<10)
    {
        mostrarMejores(aux->jug,&y,x);
        aux = aux->siguiente;
        y = y + 3;
        i++;
        x++;
    }

}



int inicArbol()
{
    return NULL;
}

ARBOL * crearArbol(char nombre[30])
{
    ARBOL * aux = (ARBOL*)malloc(sizeof(ARBOL));
    strcpy(aux->nombre,nombre);
    aux->der = NULL;
    aux->izq = NULL;

    return aux;
}

ARBOL *insertar(ARBOL *aux,char nombre[30])
{
    if(aux == NULL)
        aux = crearArbol(nombre);
    else
    {
        if(strcmpi(nombre,aux->nombre) >= 0)
            aux->der = insertar(aux->der,nombre);
        else if(strcmpi(nombre,aux->nombre) < 0)
            aux->izq = insertar(aux->izq,nombre);
    }

    return aux;
}

ARBOL *archivoToArbol(ARBOL *aux)
{

    JUGADOR J;
    FILE *file = fopen("usuarios.bin","rb");


    if(file != NULL)
    {
        while(fread(&J,sizeof(JUGADOR),1,file)>0)
        {
            aux = insertar(aux,J.nombre);
        }


        fclose(file);
    }

    return aux;
}

void menuPrincipal(NODO * lista,ARBOL *aux)
{

    int y = 12;
    char c;
    int tiempo;
    JUGADOR J1;
    JUGADOR J2;

    system("cls");

    //MENU

    tituloDamas(2,0);

    gotoxy(42,12);
    color(RED);
    printf("Jugar"RESET);
    gotoxy(39,14);
    printf("Como jugar?");
    gotoxy(40,16);
    printf("Jugadores");
    gotoxy(42,18);
    printf("Salir");

    gotoxy(70,38);
    printf("By Papa,Roselli,Huerta");



    do
    {

        tituloDamas(2,0);

        gotoxy(70,38);
        printf("By Papa,Roselli,Huerta");

        c = getch();

        if(c == -32)
        {
            c = getch();

            if(c == 72)            /*Arriba*/
            {
                if(y == LIMSUP)      //Limite superior
                {
                    y = LIMINF;      //Limite inferior
                }
                else
                {
                    y = y - 2;
                }
            }
            if(c == 80)           /*Abajo*/
            {

                if(y == LIMINF)        //Limite inferior
                {
                    y = LIMSUP;    //Limite superior
                }
                else
                {
                    y = y + 2;
                }
            }
        }

        //Funcion para cambiar de color los titulos.
        menuColoresPrincipal(y);


        if(c==13)                      //Acciones al presionar Enter.
        {
            switch (y)
            {

            case 12:
                system("cls");
                menuDetalles(lista,aux,&tiempo,&J1,&J2);
                inicioJuego(tiempo);
                gotoxy(42,12);
                color(RED);
                printf("Jugar"RESET);
                gotoxy(39,14);
                printf("Como jugar?");
                gotoxy(40,16);
                printf("Jugadores");
                gotoxy(42,18);
                printf("Salir");
                break;

            case 14:
                system("cls");
                controles(lista,aux);
                break;

            case 16:
                system("cls");
                menuJugadores(lista,aux);
                break;

            case 18:
                color(0);
                exit(1);
                break;
            }

        }

        if(c==27)            //Tecla ESC volver al menu.
        {
            color(0);
            exit(1);
        }


    }
    while(1);
}



