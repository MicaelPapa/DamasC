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

void menuColoresPrincipal(int y) {

    if(y == 12) {
        gotoxy(42,12);
        color(RED);
        printf("Jugar"RESET);
    }
    if(y != 12) {
        gotoxy(42,12);
        color(WHITE);
        printf("Jugar"RESET);
    }
    if(y == 14) {
        gotoxy(39,14);
        color(RED);
        printf("Como jugar?"RESET);
    }
    if(y != 14) {
        gotoxy(39,14);
        color(WHITE);
        printf("Como jugar?"RESET);
    }
    if(y == 16) {
        gotoxy(40,16);
        color(RED);
        printf("Jugadores"RESET);
    }
    if(y != 16) {
        gotoxy(40,16);
        color(WHITE);
        printf("Jugadores"RESET);
    }
    if(y == 18) {
        gotoxy(42,18);
        color(RED);
        printf("Salir"RESET);
    }
    if(y != 18) {
        gotoxy(42,18);
        color(WHITE);
        printf("Salir"RESET);
    }

}

void menuColoresDetalles(y,x) {

    if(y == 12) {
        gotoxy(8,12);
        color(RED);
        printf("JUGADOR");
        gotoxy(10,13);
        printf("vs");
        gotoxy(9,14);
        printf("I.A."RESET);
    }
    if(y != 12) {
        gotoxy(8,12);
        color(WHITE);
        printf("JUGADOR");
        gotoxy(10,13);
        printf("vs");
        gotoxy(9,14);
        printf("I.A."RESET);
    }

    if(y == 14) {
        gotoxy(8,20);
        color(RED);
        printf("JUGADOR");
        gotoxy(10,21);
        printf("vs");
        gotoxy(8,22);
        printf("JUGADOR"RESET);
    }
    if(y != 14) {
        gotoxy(8,20);
        color(WHITE);
        printf("JUGADOR");
        gotoxy(10,21);
        printf("vs");
        gotoxy(8,22);
        printf("JUGADOR"RESET);
    }

    if(x == 8) {
        gotoxy(67,13);
        printf("00");

    }

    if(x == 10) {
        gotoxy(67,13);
        printf("05");

    }
    if(x == 12) {
        gotoxy(67,13);
        printf("10");
    }
}

void cuadritoEstetico1() {

    int vel = 10;
    int i;

    for(i=0; i<4; i++) {
        Sleep(vel);
        if(i % 2 == 0) {
            gotoxy(7+i,15);
            printf("%c",HORIZ);

            gotoxy(15-i,11);
            printf("%c",HORIZ);

        } else {
            gotoxy(7+i,15);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(15-i,11);
            printf("%c"RESET,HORIZ);
        }
    }

    gotoxy(16,11);
    color(RED);
    printf("%c",SUP_D);

    gotoxy(6,15);
    printf("%c"RESET,INF_I);

    for(i=0; i<3; i++) {
        Sleep(vel);

        if(i % 2 == 0) {
            gotoxy(16,12+i);
            printf("%c",VERTIC);

            gotoxy(6,14-i);
            printf("%c",VERTIC);
        } else {
            gotoxy(16,12+i);
            color(RED);
            printf("%c",VERTIC);

            gotoxy(6,14-i);
            printf("%c"RESET,VERTIC);

        }
    }

    gotoxy(6,11);
    color(RED);
    printf("%c",SUP_I);

    gotoxy(16,15);
    printf("%c"RESET,INF_D);

    for(i=0; i<5; i++) {
        Sleep(vel);

        if(i % 2 == 0) {
            gotoxy(15-i,15);
            printf("%c",HORIZ);

            gotoxy(7+i,11);
            printf("%c",HORIZ);
        } else {
            gotoxy(15-i,15);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(7+i,11);
            printf("%c"RESET,HORIZ);
        }
    }
}



void cuadritoEstetico2() {

    int vel = 10;
    int i;

    for(i=0; i<4; i++) {
        Sleep(vel);
        if(i % 2 == 0) {
            gotoxy(7+i,23);
            printf("%c",HORIZ);

            gotoxy(15-i,19);
            printf("%c",HORIZ);

        } else {
            gotoxy(7+i,23);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(15-i,19);
            printf("%c"RESET,HORIZ);
        }
    }

    gotoxy(16,19);
    color(RED);
    printf("%c",SUP_D);

    gotoxy(6,23);
    printf("%c"RESET,INF_I);

    for(i=0; i<3; i++) {
        Sleep(vel);

        if(i % 2 == 0) {
            gotoxy(16,20+i);
            printf("%c",VERTIC);

            gotoxy(6,22-i);
            printf("%c",VERTIC);
        } else {
            gotoxy(16,20+i);
            color(RED);
            printf("%c",VERTIC);

            gotoxy(6,22-i);
            printf("%c"RESET,VERTIC);

        }
    }

    gotoxy(6,19);
    color(RED);
    printf("%c",SUP_I);

    gotoxy(16,23);
    printf("%c"RESET,INF_D);

    for(i=0; i<5; i++) {
        Sleep(vel);

        if(i % 2 == 0) {
            gotoxy(15-i,23);
            printf("%c",HORIZ);

            gotoxy(7+i,19);
            printf("%c",HORIZ);
        } else {
            gotoxy(15-i,23);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(7+i,19);
            printf("%c"RESET,HORIZ);
        }

    }


}

void cuadritoEstetico3() {

    int vel = 10;
    int i;

    for(i=0; i<2; i++) {
        Sleep(vel);
        if(i % 2 == 0) {
            gotoxy(66+i,12);
            printf("%c",HORIZ);

            gotoxy(69-i,14);
            printf("%c",HORIZ);



        } else {
            gotoxy(66+i,12);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(69-i,14);
            printf("%c"RESET,HORIZ);

        }
    }

    gotoxy(70,12);
    color(RED);
    printf("%c",SUP_D);

    gotoxy(65,14);
    printf("%c"RESET,INF_I);

    gotoxy(65,13);
    printf("%c",VERTIC);

    gotoxy(70,13);
    printf("%c",VERTIC);

    gotoxy(65,12);
    color(RED);
    printf("%c",SUP_I);

    gotoxy(70,14);
    printf("%c"RESET,INF_D);

    for(i=0; i<2; i++) {
        Sleep(vel);

        if(i % 2 == 0) {
            gotoxy(69-i,12);
            printf("%c",HORIZ);

            gotoxy(66+i,14);
            printf("%c",HORIZ);
        } else {
            gotoxy(69-i,12);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(66+i,14);
            printf("%c"RESET,HORIZ);
        }

    }
}

int relojYcolores(int x) {

    char c;
    int resultado = x;
    if(x == 8) {
        gotoxy(67,13);
        color(RED);
        printf("00"RESET);
    } else if(x == 10) {
        gotoxy(67,13);
        color(RED);
        printf("05"RESET);
    } else if(x == 12) {
        gotoxy(67,13);
        color(RED);
        printf("10"RESET);
    }


    do {

        c = getch();

        if(c == -32) {
            c = getch();

            if(c == 77) {       //Derecha
                gotoxy(72,13);
                color(RED);
                printf("->");
                Sleep(100);
                gotoxy(72,13);
                printf(RESET"->");
                Sleep(0);
                if(x == 12) {
                    x = 8;
                } else {
                    x = x + 2;
                }
            }
            if(c == 75) {      // Del Caño
                gotoxy(62,13);
                color(RED);
                printf("<-");
                Sleep(100);
                gotoxy(62,13);
                printf(RESET"<-");
                Sleep(0);
                if(x == 8) {
                    x = 12;
                } else {
                    x = x - 2;
                }

            }
        }
        if(x == 8) {
            gotoxy(67,13);
            color(RED);
            printf("00"RESET);
        }

        if(x == 10) {
            gotoxy(67,13);
            color(RED);
            printf("05"RESET);

        }
        if(x == 12) {
            gotoxy(67,13);
            color(RED);
            printf("10"RESET);

        }

        if(c==13) {                    //Acciones al presionar Enter.
            switch (x) {

            case 8:
                resultado = NULL;
                break;

            case 10:
                resultado = x-6;
                break;

            case 12:
                resultado = x-3;
                break;

            }

        }

    } while((resultado == 8) || (resultado == 10) ||(resultado == 12));

    return resultado;
}

void menuColoresElegirUsuarios(int y) {
    if(y == 8) {
        gotoxy(35,12);
        color(RED);
        printf("CREAR NUEVO USUARIO"RESET);
    }
    if(y != 8) {
        gotoxy(35,12);
        color(WHITE);
        printf("CREAR NUEVO USUARIO"RESET);
    }

    if(y == 10) {
        gotoxy(30,14);
        color(RED);
        printf("INGRESAR CON USUARIO EXISTENTE"RESET);
    }
    if(y != 10) {
        gotoxy(30,14);
        color(WHITE);
        printf("INGRESAR CON USUARIO EXISTENTE"RESET);
    }
}

void menuColoresJugadores(int y) {

    if(y == 8) {
        gotoxy(37,12);
        color(RED);
        printf("MEJORES JUGADORES"RESET);
    }
    if(y != 8) {
        gotoxy(37,12);
        color(WHITE);
        printf("MEJORES JUGADORES"RESET);
    }

    if(y == 10) {
        gotoxy(35,14);
        color(RED);
        printf("DAR DE BAJA UN JUGADOR"RESET);
    }
    if(y != 10) {
        gotoxy(35,14);
        color(WHITE);
        printf("DAR DE BAJA UN JUGADOR"RESET);
    }
}

void tituloMejoresJugadores() {

    color(7); //CAMBIAR A RED
    gotoxy(25,0);
    printf(" _____  _____ ______           __   _____ ");
    color(12);
    gotoxy(25,1);
    printf("|_   _||  _  || ___ \\         /  | |  _  |");
    color(7);
    gotoxy(25,2);
    printf("  | |  | | | || |_/ /         `| | | |/' |");
    color(12);
    gotoxy(25,3);
    printf("  | |  | | | ||  __/           | | |  /| |");
    color(7);
    gotoxy(25,4);
    printf("  | |  \\ \\_/ /| |             _| |_\\ |_/ /");
    color(12);
    gotoxy(25,5);
    printf("  \\_/   \\___/ \\_|             \\___/ \\___/ ");

}

void recuadroMejoresJugadores() {
    int i;
    int vel = 4;
    int bandera = 1;

    tituloMejoresJugadores();

    for(i=0; i<40; i++) {
        Sleep(vel);
        if(i % 2 == 0) {
            gotoxy(46+i,7);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(46-i,38);
            printf("%c"RESET,HORIZ);
        } else {
            gotoxy(46+i,7);
            printf("%c",HORIZ);

            gotoxy(46-i,38);
            printf("%c",HORIZ);
        }
    }

    gotoxy(86,7);
    color(RED);
    printf("%c",SUP_D);

    gotoxy(6,38);
    printf("%c"RESET,INF_I);

    for(i=0; i<30; i++) {
        Sleep(vel);

        if(i % 2 == 0) {
            gotoxy(86,8+i);
            color(RED);
            printf("%c",VERTIC);

            gotoxy(6,37-i);
            printf("%c"RESET,VERTIC);
        } else {
            gotoxy(86,8+i);
            printf("%c",VERTIC);

            gotoxy(6,37-i);
            printf("%c",VERTIC);

        }
    }

    gotoxy(6,7);
    color(RED);
    printf("%c",SUP_I);

    gotoxy(86,38);
    printf("%c"RESET,INF_D);

    for(i=0; i<40; i++) {
        Sleep(vel);

        if(i % 2 == 0) {
            gotoxy(85-i,38);
            printf("%c",HORIZ);

            gotoxy(7+i,7);
            printf("%c",HORIZ);
        } else {
            gotoxy(85-i,38);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(7+i,7);
            printf("%c"RESET,HORIZ);
        }

    }

    gotoxy(2,39);
    printf("Presione ESCAPE para regresar al menu anterior");
}

void menuColoresSINO(int y,int sup,int inf) {

    if(y == sup) {
        gotoxy(43,sup);
        color(RED);
        printf("SI"RESET);
    }
    if(y != sup) {
        gotoxy(43,sup);
        color(WHITE);
        printf("SI"RESET);
    }

    if(y == inf) {
        gotoxy(43,inf);
        color(RED);
        printf("NO"RESET);
    }
    if(y != inf) {
        gotoxy(43,inf);
        color(WHITE);
        printf("NO"RESET);
    }
}

void cuadroEstetico() {

    int vel = 1;
    int i;

    for(i=0; i<40; i++) {
        Sleep(vel);
        if(i % 2 == 0) {

            gotoxy(46+i,2);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(46-i,38);
            printf("%c"RESET,HORIZ);
        } else {
            gotoxy(46+i,2);
            printf("%c",HORIZ);

            gotoxy(46-i,38);
            printf("%c",HORIZ);
        }
    }

    gotoxy(86,2);
    color(RED);
    printf("%c",SUP_D);

    gotoxy(6,38);
    printf("%c"RESET,INF_I);

    for(i=0; i<35; i++) {
        Sleep(vel);

        if(i % 2 == 0) {
            gotoxy(86,3+i);
            printf("%c",VERTIC);

            gotoxy(6,37-i);
            printf("%c",VERTIC);
        } else {
            gotoxy(86,3+i);
            color(RED);
            printf("%c",VERTIC);

            gotoxy(6,37-i);
            printf("%c"RESET,VERTIC);

        }
    }

    gotoxy(6,2);
    color(RED);
    printf("%c",SUP_I);

    gotoxy(86,38);
    printf("%c"RESET,INF_D);

    for(i=0; i<40; i++) {
        Sleep(vel);

        if(i % 2 == 0) {
            gotoxy(85-i,38);
            printf("%c",HORIZ);

            gotoxy(7+i,2);
            printf("%c",HORIZ);
        } else {
            gotoxy(85-i,38);
            color(RED);
            printf("%c",HORIZ);

            gotoxy(7+i,2);
            printf("%c"RESET,HORIZ);
        }
    }
}



















void teclaARR(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("||ARR||");
    gotoxy(x,y+2);
    printf("||___||");
    gotoxy(x,y+3);
    printf("|/___\\|");

}

void teclaDER(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("||DER||");
    gotoxy(x,y+2);
    printf("||___||");
    gotoxy(x,y+3);
    printf("|/___\\|");

}

void teclaIZQ(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("||IZQ||");
    gotoxy(x,y+2);
    printf("||___||");
    gotoxy(x,y+3);
    printf("|/___\\|");

}

void teclaABJ(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("||ABJ||");
    gotoxy(x,y+2);
    printf("||___||");
    gotoxy(x,y+3);
    printf("|/___\\|");

}

void teclaW(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("|| W ||");
    gotoxy(x,y+2);
    printf("||___||");
    gotoxy(x,y+3);
    printf("|/___\\|");

}

void teclaA(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("|| A ||");
    gotoxy(x,y+2);
    printf("||___||");
    gotoxy(x,y+3);
    printf("|/___\\|");

}

void teclaS(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("|| S ||");
    gotoxy(x,y+2);
    printf("||___||");
    gotoxy(x,y+3);
    printf("|/___\\|");

}

void teclaD(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("|| D ||");
    gotoxy(x,y+2);
    printf("||___||");
    gotoxy(x,y+3);
    printf("|/___\\|");

}

void teclaAsterisco(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("|| * ||");
    gotoxy(x,y+2);
    printf("||___||");
    gotoxy(x,y+3);
    printf("|/___\\|");

}

void teclaBarraEspaciadora(int x, int y)
{

    gotoxy(x,y);
    printf(" __________________________");
    gotoxy(x,y+1);
    printf("||    BARRA ESPACIADORA    ||");
    gotoxy(x,y+2);
    printf("||_________________________||");
    gotoxy(x,y+3);
    printf("|/_________________________\\|");

}

void teclaENTER(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("||<-- |");
    gotoxy(x,y+2);
    printf("||____|____");
    gotoxy(x,y+3);
    printf("||         ||");
    gotoxy(x,y+4);
    printf("||  ENTER  ||");
    gotoxy(x,y+5);
    printf("||_________||");
    gotoxy(x,y+6);
    printf("|/_________\\|");

}

void teclaESC(int x, int y)
{

    gotoxy(x,y);
    printf(" _____");
    gotoxy(x,y+1);
    printf("||ESC||");
    gotoxy(x,y+2);
    printf("||___||");
    gotoxy(x,y+3);
    printf("|/___\\|");

}

void flechasSN(char *control,int sup,int inf)
{

    int limsup = sup;
    int liminf =inf;
    int y = limsup;
    int bandera = 1;
    char c;

    hidecursor(0);
    //Si o No
    gotoxy(43,limsup);
    color(RED);
    printf("SI"RESET);
    gotoxy(43,liminf);
    printf("NO");

    do
    {
        c = getch();

        if(c == -32)           //Numero identificador de la flecha. Apartir de aca se configura el movimiento de la flecha
        {



            c = getch();
            if(c == 72)
                if(y == limsup)      //Limite superior
                {
                    y=liminf;      //Limite inferior
                }
                else
                {
                    y=y-2;
                }
            if(c == 80)

                if(y==liminf)        //Limite inferior
                {
                    y = limsup;    //Limite superior

                }
                else
                {
                    y=y+2;
                }


        }
        //Cambia de color las flechas:
        menuColoresSINO(y,limsup,liminf);


        if(c == 13)                      //Acciones al presionar Enter.
        {
            bandera = 0;
            if(y == limsup)
            {
                *control = 's';
            }
            if(y == liminf)
            {
                *control = 'n';
            }
        }

    }
    while(bandera == 1);
}
