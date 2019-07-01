#ifndef DAMAS_H_INCLUDED
#define DAMAS_H_INCLUDED

///Constantes colores:
#define RESET                   "\033[1m\033[37m"
#define BLACK                   0
#define DARK_BLUE               1
#define DARK_GREEN              2
#define LIGHTBLUE_DIFFERENT     3
#define DARK_RED                4
#define LILAC                   5
#define DARK_YELLOW             6
#define LIGHT_GREY              7
#define GREY                    8
#define BLUE                    9
#define GREEN                   10
#define LIGHTBLUE               11
#define RED                     12
#define VIOLET                  13
#define YELLOW                  14
#define WHITE                   15

///Constantes de Inicio:
#define XX 20
#define YY 12
#define LIMSUP 12
#define LIMINF 18


///Constantes teclas:
#define ENTER 13
#define ESCAPE 27
#define SPACE 32
#define ASTERISCO 42

///Constantes area de juego:
#define SUP_I 201
#define SUP_D 187
#define HORIZ 205
#define VERTIC 186
#define INF_I 200
#define INF_D 188
#define DIM 8
#define TABLERO 8
#define TRI_IZQ 185
#define TRI_DER 204
#define TRI_ABJ 203
#define TRI_ARR 202
#define TRI_ESTRELLA 206
#define MOV 1000

///Constantes ficha:
#define FICHA 219
#define SHADOW 177
#define SHADOWDOS 176
#define REINA 178

///Constantes Menu Colores Pause
#define OPCION_SUP 30
#define OPCION_INF 32

///Prototipos
HWND GetConsoleHwnd(void);
void introDamas();
void tituloDamas1();
void tituloDamas(int y, int vel);
void indices();
void tablero_damas();
void imprimirFichas(int[DIM][DIM]);
void ficha(int,int,int);
void casillero(int,int,int);
void esquinas_tablero();
void casillero_auxiliar(int,int,int);
void modificar_esquinas(int,int);
void cuadroEstructura();
void fichaMaster(int x, int y, int tono);
void playerTwoWin();
void playerOneWin();
void tiedPlayers();
void timeIsOver();
void logoPause();
void menuColoresPausa(int y);


#endif // DAMAS_H_INCLUDED
