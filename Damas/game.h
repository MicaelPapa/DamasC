#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

///Constantes flechas:
#define DER 77
#define IZQ 75
#define ARR 72
#define ABA 80

///Constantes letras
#define S 0x53
#define W 0x57
#define D 0x44
#define A 0x41
#define O_ACENTO 162

///Estructura movimiento
typedef struct
{
    char letraPartida;
    char numeroPartida;
    char letraLlegada;
    char numeroLlegada;
    int movWhite;
    int movRed;
} MOVIMIENTOS;

typedef struct
{
    int movsBlanco;
    int movsRojo;
    int queenRojo;
    int queenBlanco;
    int puntosRojo;
    int puntosBlanco;
} ESTADISTICAS;


///Prototipos
void llenarMatrix(int[DIM][DIM]);
void matrixToGotoxy(int,int,int*,int*);
void FichaToMatrix(int,int,int*,int*);
void casilleroToMatrix(int,int,int*,int*);
void posicion_matrix_cuadrado(int*,int*);
void borrarFichaMovida(int,int,int[DIM][DIM]);
void EscapeCase(int,int,int,int,int[DIM][DIM]);
int existeFicha(int,int);
void fichasEliminadas(int[DIM][DIM],int*,int*);
void HabilitadoMoverJug2(int tablero[DIM][DIM],int i, int j, int * flag);
void HabilitadoMoverJug1(int tablero[DIM][DIM],int i, int j, int *flag);
void estadisticasGame();
void cargarEstadisticas(int puntosW,int puntosR,int movRojo,int movBlanco,int reinasBlancas,int reinasRojas);

#endif // GAME_H_INCLUDED
