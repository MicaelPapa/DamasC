#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

///Constantes de Inicio:
#define LIMSUP 12
#define LIMINF 18

typedef struct {

    char nombre[30];
    int edad;
    int ganadas;
    int empatadas;
    int perdidas;
    char baja;

} JUGADOR;

typedef struct {

    JUGADOR jug;
    struct NODO *siguiente;

} NODO;

typedef struct
{
    char nombre[30];
    struct ARBOL * der;
    struct ARBOL * izq;
} ARBOL;


///Prototiposk
NODO * inicLista();
NODO * crearNodo(JUGADOR jug);
NODO * agregarPrincipioLista(NODO *lista, NODO *nuevo);
NODO * agregarOrdenado(NODO *lista, NODO *nuevo);
void mostrarJugador(JUGADOR jug);
void mostrarMejores(JUGADOR jug,int * y,int x);
void recorrerYmostrarMejores(NODO * lista);
ARBOL *archivoToArbol(ARBOL *aux);
ARBOL *insertar(ARBOL *aux,char nombre[30]);
ARBOL * crearArbol(char nombre[30]);
int inicArbol();
void menuPrincipal(NODO * lista,ARBOL *aux);

#endif // LISTAS_H_INCLUDED
