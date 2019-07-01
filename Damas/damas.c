#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "gotoxy.h"
#include "damas.h"
#include "game.h"
#include <ctype.h>

HWND GetConsoleHwnd(void)
{
#define MY_BUFSIZE 1024 /// Buffer size for console window titles.
    HWND hwndFound;         /// This is what is returned to the caller.
    char pszNewWindowTitle[MY_BUFSIZE]; /// Contains fabricated
    /// WindowTitle.
    char pszOldWindowTitle[MY_BUFSIZE]; /// Contains original
    /// WindowTitle.

    GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE); /// Fetch current window title.
    wsprintf(pszNewWindowTitle,"%d/%d",GetTickCount(),GetCurrentProcessId()); /// Format a "unique" NewWindowTitle.
    SetConsoleTitle(pszNewWindowTitle); /// Change current window title.
    Sleep(40); /// Ensure window title has been updated.
    hwndFound=FindWindow(NULL, pszNewWindowTitle); /// Look for NewWindowTitle.
    SetConsoleTitle(pszOldWindowTitle); /// Restore original window title.

    return(hwndFound);
}


void introDamas()
{
    int i;
    int vel = 10;
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

    tituloDamas1();

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

void tituloDamas1()
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

void tituloDamas(int y, int vel)
{

    Sleep(vel);
    gotoxy(12,y);
    printf("  _____          __  __           _____     _____ _   _       _____ ");
    Sleep(vel);
    gotoxy(12,y+1);
    color(RED);
    printf(" |  __ \\   /\\   |  \\/  |   /\\    / ____|   |_   _| \\ | |     / ____|"RESET);
    Sleep(vel);
    gotoxy(12,y+2);
    color(WHITE);
    printf(" | |  | | /  \\  | \\  / |  /  \\  | (___       | | |  \\| |    | |     "RESET);
    Sleep(vel);
    gotoxy(12,y+3);
    color(RED);
    printf(" | |  | |/ /\\ \\ | |\\/| | / /\\ \\  \\___ \\      | | | . ` |    | |     "RESET);
    Sleep(vel);
    gotoxy(12,y+4);
    color(WHITE);
    printf(" | |__| / ____ \\| |  | |/ ____ \\ ____) |    _| |_| |\\  |    | |____ "RESET);
    Sleep(vel);
    gotoxy(12,y+5);
    color(RED);
    printf(" |_____/_/    \\_\\_|  |_/_/    \\_\\_____/    |_____|_| \\_|     \\_____|"RESET);

}
void indices()
{
    int a = 0;
    int b = 8;
    int c = 2;
    int d = 14;

    char letras[9]= {'A','B','C','D','E','F','G','H'};

    color(YELLOW);
///For para insertar los numeros.
    for(a=0; a < 8; a++)
    {
        gotoxy(3,c);
        printf("%i", b);
        b--;
        c = c+3;
    }
///For para insertar las letras.
    b = 8;
    for(a=0; a < 8; a++)
    {
        gotoxy(d,27);
        printf("%c", letras[a]);
        b--;
        d = d + 9;
    }
}

void tablero_damas()
{
    int i,j;
    int x=19;
    int y=4;

    gotoxy(10,1);
    color(YELLOW);
    printf("%c",SUP_I);

    for(i=0; i<71; i++)
    {
        printf("%c",HORIZ);
    }

    printf("%c",SUP_D);

    for(i=2; i<25; i++)
    {
        gotoxy(10,i);
        printf("%c",VERTIC);
    }

    for(i=2; i<25; i++)
    {
        gotoxy(82,i);
        printf("%c",VERTIC);
    }

    gotoxy(10,25);
    printf("%c",INF_I);
    for(i=0; i<71; i++)
    {
        printf("%c",HORIZ);
    }

    printf("%c",INF_D);

    for(i=0; i<TABLERO; i++)
    {
        gotoxy(11,y);
        for(j=0; j<71; j++)
        {
            printf("%c",HORIZ);
        }
        y += 3;
    }

    for(i=0; i<TABLERO; i++)
    {
        gotoxy(x,20);
        for(j=2; j<25; j++)
        {
            gotoxy(x,j);
            printf("%c",VERTIC);
        }
        x += 9;
    }
    esquinas_tablero();
}

void esquinas_tablero()
{
    int i,j;

    for(i=4; i<23; i+=3)
    {
        gotoxy(82,i);
        printf("%c",TRI_IZQ);
        gotoxy(10,i);
        printf("%c",TRI_DER);
    }

    for(i=19; i<82; i+=9)
    {
        gotoxy(i,1);
        printf("%c",TRI_ABJ);
        gotoxy(i,25);
        printf("%c",TRI_ARR);
    }

    for(i=4; i<25; i+=3)
    {
        j = 19;
        gotoxy(j,i);
        for(j=19; j<82; j+=9)
        {
            gotoxy(j,i);
            printf("%c",TRI_ESTRELLA);
        }
    }
}

void imprimirFichas(int tablero[DIM][DIM])
{
    int i,j;
    int x = 0;
    int y = 0;

    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
        {
            if(tablero[i][j] == 2)
            {
                x = 13 + (9*j);
                y = 2 + (3*i);
                ficha(x,y,RED);
            }
            else if(tablero[i][j] == 1)
            {
                x = 13 + (9*j);
                y = 2 + (3*i);
                ficha(x,y,WHITE);
            }
            else if(tablero[i][j] == 3)
            {
                x = 13 + (9*j);
                y = 2 + (3*i);
                fichaMaster(x,y,WHITE);
            }
            else if(tablero[i][j] == 4)
            {
                x = 13 + (9*j);
                y = 2 + (3*i);
                fichaMaster(x,y,RED);
            }
            else if(tablero[i][j] == 0)
            {
                x = 13 + (9*j);
                y = 2 + (3*i);
                ficha(x,y,BLACK);
            }
        }
    }
}

void ficha(int x, int y, int tono)
{
    gotoxy(x,y);
    color(tono);
    printf("%c%c%c%c",FICHA,FICHA,SHADOW,SHADOW);
    gotoxy(x,y+1);
    printf("%c%c%c%c",SHADOW,SHADOW,FICHA,FICHA);
}

void fichaMaster(int x, int y, int tono)
{
    gotoxy(x,y);
    color(tono);
    printf("%c%c%c%c",FICHA,REINA,SHADOW,SHADOWDOS);
    gotoxy(x,y+1);
    printf("%c%c%c%c",FICHA,REINA,SHADOW,SHADOWDOS);
}


void casillero(int x, int y, int tono)
{
    int i;

    gotoxy(x,y);
    color(tono);

    printf("%c",SUP_I);

    for(i=0; i<8; i++)
    {
        printf("%c", HORIZ);
    }

    printf("%c", SUP_D);

    gotoxy(x,y+1);
    printf("%c", VERTIC);
    gotoxy(x,y+2);
    printf("%c", VERTIC);
    gotoxy(x+9,y+1);
    printf("%c", VERTIC);
    gotoxy(x+9,y+2);
    printf("%c", VERTIC);

    gotoxy(x,y+3);
    printf("%c", INF_I);

    for(i=0; i<8; i++)
    {
        printf("%c", HORIZ);
    }

    printf("%c"RESET, INF_D);
}

void casillero_auxiliar(int x, int y, int tono)
{
    int i;

    gotoxy(x+1,y);
    color(tono);

    for(i=0; i<8; i++)
    {
        printf("%c", HORIZ);
    }

    gotoxy(x,y+1);
    printf("%c", VERTIC);
    gotoxy(x,y+2);
    printf("%c", VERTIC);
    gotoxy(x+9,y+1);
    printf("%c", VERTIC);
    gotoxy(x+9,y+2);
    printf("%c", VERTIC);

    gotoxy(x+1,y+3);

    for(i=0; i<8; i++)
    {
        printf("%c", HORIZ);
    }
    modificar_esquinas(x,y);
}

void modificar_esquinas(int x, int y)
{
    int flag = 0;

    if(x == 10 && y == 1 && flag == 0)
    {
        gotoxy(x,y);
        printf("%c",SUP_I);
        gotoxy(x+9,y);
        printf("%c",TRI_ABJ);
        gotoxy(x,y+3);
        printf("%c",TRI_DER);
        gotoxy(x+9,y+3);
        printf("%c",TRI_ESTRELLA);
        flag = 1;
    }
    if(x == 10 && y == 22 && flag == 0)
    {
        gotoxy(x,y);
        printf("%c",TRI_DER);
        gotoxy(x+9,y);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x,y+3);
        printf("%c",INF_I);
        gotoxy(x+9,y+3);
        printf("%c",TRI_ARR);
        flag = 1;
    }
    if(x == 73 && y == 1 && flag == 0)
    {
        gotoxy(x,y);
        printf("%c",TRI_ABJ);
        gotoxy(x+9,y);
        printf("%c",SUP_D);
        gotoxy(x,y+3);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x+9,y+3);
        printf("%c",TRI_IZQ);
        flag = 1;
    }
    if(x == 73 && y == 22 && flag == 0)
    {
        gotoxy(x,y);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x+9,y);
        printf("%c",TRI_IZQ);
        gotoxy(x,y+3);
        printf("%c",TRI_ARR);
        gotoxy(x+9,y+3);
        printf("%c",INF_D);
        flag = 1;
    }
    if(x > 10 && x <73 && y == 1 && flag == 0)
    {
        gotoxy(x,y);
        printf("%c",TRI_ABJ);
        gotoxy(x+9,y);
        printf("%c",TRI_ABJ);
        gotoxy(x,y+3);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x+9,y+3);
        printf("%c",TRI_ESTRELLA);
        flag = 1;
    }
    if(x > 10 && x < 73 && y == 22 && flag == 0)
    {
        gotoxy(x,y);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x+9,y);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x,y+3);
        printf("%c",TRI_ARR);
        gotoxy(x+9,y+3);
        printf("%c",TRI_ARR);
        flag = 1;
    }
    if(x == 10 && y > 1 && y < 22 && flag == 0)
    {
        gotoxy(x,y);
        printf("%c",TRI_DER);
        gotoxy(x+9,y);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x,y+3);
        printf("%c",TRI_DER);
        gotoxy(x+9,y+3);
        printf("%c",TRI_ESTRELLA);
        flag = 1;
    }
    if(x == 73 && y > 1 && y < 22 && flag == 0)
    {
        gotoxy(x,y);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x+9,y);
        printf("%c",TRI_IZQ);
        gotoxy(x,y+3);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x+9,y+3);
        printf("%c",TRI_IZQ);
        flag = 1;
    }
    if(x > 10 && x < 73 && y > 1 && y < 22 && flag == 0)
    {
        gotoxy(x,y);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x+9,y);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x,y+3);
        printf("%c",TRI_ESTRELLA);
        gotoxy(x+9,y+3);
        printf("%c",TRI_ESTRELLA);
        flag = 1;
    }
}

void cuadroEstructura()
{
    int i;
    int x = 6;
    int y = 30;

    color(YELLOW);

    gotoxy(x,y);
    printf("%c",SUP_I);

    for(i=0; i<80; i++)
    {
        printf("%c", HORIZ);
    }

    printf("%c", SUP_D);


    for(i=1; i<13; i++)
    {
        gotoxy(x,y+i);
        printf("%c", VERTIC);
        gotoxy(x+81,y+i);
        printf("%c", VERTIC);
        gotoxy(x+63,y+i);
        printf("%c", VERTIC);
    }


    gotoxy(x,y+i);
    printf("%c", INF_I);

    for(i=0; i<80; i++)
    {
        printf("%c", HORIZ);
    }

    printf("%c", INF_D);

    gotoxy(x,32);
    printf("%c",TRI_DER);
    for(i=0; i<62; i++)
    {
        printf("%c", HORIZ);
    }

    printf("%c",TRI_IZQ);

    gotoxy(69,43);
    printf("%c",TRI_ARR);

    gotoxy(69,30);
    printf("%c",TRI_ABJ);

    gotoxy(28,30);
    printf("%c",TRI_ABJ);

    gotoxy(28,31);
    printf("%c",VERTIC);

    gotoxy(28,32);
    printf("%c",TRI_ARR);
}

void timeIsOver()
{
    int vel = 100;

    Sleep(vel);
    gotoxy(15,2);
    color(WHITE);
    printf(" _________    ________       ___ __ __       ______       ");
    Sleep(vel);
    gotoxy(15,3);
    color(RED);
    printf("/________/\\  /_______/\\     /__//_//_/\\     /_____/\\      ");
    Sleep(vel);
    gotoxy(15,4);
    color(WHITE);
    printf("\\__.::.__\\/  \\__.::._\\/     \\::\\| \\| \\ \\    \\::::_\\/_     ");
    Sleep(vel);
    gotoxy(15,5);
    color(RED);
    printf("   \\::\\ \\       \\::\\ \\       \\:.      \\ \\    \\:\\/___/\\    ");
    Sleep(vel);
    gotoxy(15,6);
    color(WHITE);
    printf("    \\::\\ \\      _\\::\\ \\__     \\:.\\-/\\  \\ \\    \\::___\\/_   ");
    Sleep(vel);
    gotoxy(15,7);
    color(RED);
    printf("     \\::\\ \\    /__\\::\\__/\\     \\. \\  \\  \\ \\    \\:\\____/\\  ");
    Sleep(vel);
    gotoxy(15,8);
    color(WHITE);
    printf("      \\__\\/    \\________\\/      \\__\\/ \\__\\/     \\_____\\/  ");

    Sleep(vel);
    gotoxy(32,10);
    color(WHITE);
    printf(" ________       ______       ");
    Sleep(vel);
    gotoxy(32,11);
    color(RED);
    printf("/_______/\\     /_____/\\      ");
    Sleep(vel);
    gotoxy(32,12);
    color(WHITE);
    printf("\\__.::._\\/     \\::::_\\/_     ");
    Sleep(vel);
    gotoxy(32,13);
    color(RED);
    printf("   \\::\\ \\       \\:\\/___/\\    ");
    Sleep(vel);
    gotoxy(32,14);
    color(WHITE);
    printf("   _\\::\\ \\__     \\_::._\\:\\   ");
    Sleep(vel);
    gotoxy(32,15);
    color(RED);
    printf("  /__\\::\\__/\\      /____\\:\\  ");
    Sleep(vel);
    gotoxy(32,16);
    color(WHITE);
    printf("  \\________\\/      \\_____\\/  ");

    Sleep(vel);
    gotoxy(20,18);
    color(WHITE);
    printf(" ______        __   __       ______        ______        ");
    Sleep(vel);
    gotoxy(20,19);
    color(RED);
    printf("/_____/\\      /_/\\ /_/\\     /_____/\\      /_____/\\       ");
    Sleep(vel);
    gotoxy(20,20);
    color(WHITE);
    printf("\\:::_ \\ \\     \\:\\ \\\\ \\ \\    \\::::_\\/_     \\:::_ \\ \\      ");
    Sleep(vel);
    gotoxy(20,21);
    color(RED);
    printf(" \\:\\ \\ \\ \\     \\:\\ \\\\ \\ \\    \\:\\/___/\\     \\:(_) ) )_    ");
    Sleep(vel);
    gotoxy(20,22);
    color(WHITE);
    printf("  \\:\\ \\ \\ \\     \\:\\_/.:\\ \\    \\::___\\/_     \\: __ `\\ \\   ");
    Sleep(vel);
    gotoxy(20,23);
    color(RED);
    printf("   \\:\\_\\ \\ \\     \\ ..::/ /     \\:\\____/\\     \\ \\ `\\ \\ \\  ");
    Sleep(vel);
    gotoxy(20,24);
    color(WHITE);
    printf("    \\_____\\/      \\___/_/       \\_____\\/      \\_\\/ \\_\\/  ");
}

void tiedPlayers()
{
    int vel = 100;

    Sleep(vel);
    gotoxy(17,12);
    color(WHITE);
    printf(" _________    ________       ______        ______       ");
    Sleep(vel);
    gotoxy(17,13);
    color(RED);
    printf("/________/\\  /_______/\\     /_____/\\      /_____/\\      ");
    Sleep(vel);
    gotoxy(17,14);
    color(WHITE);
    printf("\\__.::.__\\/  \\__.::._\\/     \\::::_\\/_     \\:::_ \\ \\     ");
    Sleep(vel);
    gotoxy(17,15);
    color(RED);
    printf("   \\::\\ \\       \\::\\ \\       \\:\\/___/\\     \\:\\ \\ \\ \\    ");
    Sleep(vel);
    gotoxy(17,16);
    color(WHITE);
    printf("    \\::\\ \\      _\\::\\ \\__     \\::___\\/_     \\:\\ \\ \\ \\   ");
    Sleep(vel);
    gotoxy(17,17);
    color(RED);
    printf("     \\::\\ \\    /__\\::\\__/\\     \\:\\____/\\     \\:\\/.:| |  ");
    Sleep(vel);
    gotoxy(17,18);
    color(WHITE);
    printf("      \\__\\/    \\________\\/      \\_____\\/      \\____/_/  ");
}

void playerOneWin()
{
    int vel = 100;

    Sleep(vel);
    gotoxy(5,2);
    color(WHITE);
    printf(" ______      __            ________        __  __      ______        ______        ");
    Sleep(vel);
    gotoxy(5,3);
    color(RED);
    printf("/_____/\\    /_/\\          /_______/\\      /_/\\/_/\\    /_____/\\      /_____/\\       ");
    Sleep(vel);
    gotoxy(5,4);
    color(WHITE);
    printf("\\:::_ \\ \\   \\:\\ \\         \\::: _  \\ \\     \\ \\ \\ \\ \\   \\::::_\\/_     \\:::_ \\ \\      ");
    Sleep(vel);
    gotoxy(5,5);
    color(RED);
    printf(" \\:(_) \\ \\   \\:\\ \\         \\::(_)  \\ \\     \\:\\_\\ \\ \\   \\:\\/___/\\     \\:(_) ) )_    ");
    Sleep(vel);
    gotoxy(5,6);
    color(WHITE);
    printf("  \\: ___\\/    \\:\\ \\____     \\:: __  \\ \\     \\::::_\\/    \\::___\\/_     \\: __ `\\ \\   ");
    Sleep(vel);
    gotoxy(5,7);
    color(RED);
    printf("   \\ \\ \\       \\:\\/___/\\     \\:.\\ \\  \\ \\      \\::\\ \\     \\:\\____/\\     \\ \\ `\\ \\ \\  ");
    Sleep(vel);
    gotoxy(5,8);
    color(WHITE);
    printf("    \\_\\/        \\_____\\/      \\__\\/\\__\\/       \\__\\/      \\_____\\/      \\_\\/ \\_\\/  ");

    Sleep(vel);
    gotoxy(25,10);
    color(WHITE);
    printf(" ______        ___   __        ______       ");
    Sleep(vel);
    gotoxy(25,11);
    color(RED);
    printf("/_____/\\      /__/\\ /__/\\     /_____/\\      ");
    Sleep(vel);
    gotoxy(25,12);
    color(WHITE);
    printf("\\:::_ \\ \\     \\::\\_\\\\  \\ \\    \\::::_\\/_     ");
    Sleep(vel);
    gotoxy(25,13);
    color(RED);
    printf(" \\:\\ \\ \\ \\     \\:. `-\\  \\ \\    \\:\\/___/\\    ");
    Sleep(vel);
    gotoxy(25,14);
    color(WHITE);
    printf("  \\:\\ \\ \\ \\     \\:. _    \\ \\    \\::___\\/_   ");
    Sleep(vel);
    gotoxy(25,15);
    color(RED);
    printf("   \\:\\_\\ \\ \\     \\. \\`-\\  \\ \\    \\:\\____/\\  ");
    Sleep(vel);
    gotoxy(25,16);
    color(WHITE);
    printf("    \\_____\\/      \\__\\/ \\__\\/     \\_____\\/  ");

    Sleep(vel);
    gotoxy(25,18);
    color(WHITE);
    printf(" __ __ __        ________       ___   __       ");
    Sleep(vel);
    gotoxy(25,19);
    color(RED);
    printf("/_//_//_/\\      /_______/\\     /__/\\ /__/\\     ");
    Sleep(vel);
    gotoxy(25,20);
    color(WHITE);
    printf("\\:\\\\:\\\\:\\ \\     \\__.::._\\/     \\::\\_\\\\  \\ \\    ");
    Sleep(vel);
    gotoxy(25,21);
    color(RED);
    printf(" \\:\\\\:\\\\:\\ \\       \\::\\ \\       \\:. `-\\  \\ \\   ");
    Sleep(vel);
    gotoxy(25,22);
    color(WHITE);
    printf("  \\:\\\\:\\\\:\\ \\      _\\::\\ \\__     \\:. _    \\ \\  ");
    Sleep(vel);
    gotoxy(25,23);
    color(RED);
    printf("   \\:\\\\:\\\\:\\ \\    /__\\::\\__/\\     \\. \\`-\\  \\ \\ ");
    Sleep(vel);
    gotoxy(25,24);
    color(WHITE);
    printf("    \\_______\\/    \\________\\/      \\__\\/ \\__\\/ "RESET);
}

void playerTwoWin()
{
    int vel = 100;

    Sleep(vel);
    gotoxy(5,2);
    color(WHITE);
    printf(" ______      __            ________        __  __      ______        ______        ");
    Sleep(vel);
    gotoxy(5,3);
    color(RED);
    printf("/_____/\\    /_/\\          /_______/\\      /_/\\/_/\\    /_____/\\      /_____/\\       ");
    Sleep(vel);
    gotoxy(5,4);
    color(WHITE);
    printf("\\:::_ \\ \\   \\:\\ \\         \\::: _  \\ \\     \\ \\ \\ \\ \\   \\::::_\\/_     \\:::_ \\ \\      ");
    Sleep(vel);
    gotoxy(5,5);
    color(RED);
    printf(" \\:(_) \\ \\   \\:\\ \\         \\::(_)  \\ \\     \\:\\_\\ \\ \\   \\:\\/___/\\     \\:(_) ) )_    ");
    Sleep(vel);
    gotoxy(5,6);
    color(WHITE);
    printf("  \\: ___\\/    \\:\\ \\____     \\:: __  \\ \\     \\::::_\\/    \\::___\\/_     \\: __ `\\ \\   ");
    Sleep(vel);
    gotoxy(5,7);
    color(RED);
    printf("   \\ \\ \\       \\:\\/___/\\     \\:.\\ \\  \\ \\      \\::\\ \\     \\:\\____/\\     \\ \\ `\\ \\ \\  ");
    Sleep(vel);
    gotoxy(5,8);
    color(WHITE);
    printf("    \\_\\/        \\_____\\/      \\__\\/\\__\\/       \\__\\/      \\_____\\/      \\_\\/ \\_\\/  ");

    Sleep(vel);
    gotoxy(25,10);
    color(WHITE);
    printf(" _________    __ __ __        ______       ");
    Sleep(vel);
    gotoxy(25,11);
    color(RED);
    printf("/________/\\  /_//_//_/\\      /_____/\\      ");
    Sleep(vel);
    gotoxy(25,12);
    color(WHITE);
    printf("\\__.::.__\\/  \\:\\\\:\\\\:\\ \\     \\:::_ \\ \\     ");
    Sleep(vel);
    gotoxy(25,13);
    color(RED);
    printf("   \\::\\ \\     \\:\\\\:\\\\:\\ \\     \\:\\ \\ \\ \\    ");
    Sleep(vel);
    gotoxy(25,14);
    color(WHITE);
    printf("    \\::\\ \\     \\:\\\\:\\\\:\\ \\     \\:\\ \\ \\ \\   ");
    Sleep(vel);
    gotoxy(25,15);
    color(RED);
    printf("     \\::\\ \\     \\:\\\\:\\\\:\\ \\     \\:\\_\\ \\ \\  ");
    Sleep(vel);
    gotoxy(25,16);
    color(WHITE);
    printf("      \\__\\/      \\_______\\/      \\_____\\/  ");

    Sleep(vel);
    gotoxy(25,18);
    color(WHITE);
    printf(" __ __ __        ________       ___   __       ");
    Sleep(vel);
    gotoxy(25,19);
    color(RED);
    printf("/_//_//_/\\      /_______/\\     /__/\\ /__/\\     ");
    Sleep(vel);
    gotoxy(25,20);
    color(WHITE);
    printf("\\:\\\\:\\\\:\\ \\     \\__.::._\\/     \\::\\_\\\\  \\ \\    ");
    Sleep(vel);
    gotoxy(25,21);
    color(RED);
    printf(" \\:\\\\:\\\\:\\ \\       \\::\\ \\       \\:. `-\\  \\ \\   ");
    Sleep(vel);
    gotoxy(25,22);
    color(WHITE);
    printf("  \\:\\\\:\\\\:\\ \\      _\\::\\ \\__     \\:. _    \\ \\  ");
    Sleep(vel);
    gotoxy(25,23);
    color(RED);
    printf("   \\:\\\\:\\\\:\\ \\    /__\\::\\__/\\     \\. \\`-\\  \\ \\ ");
    Sleep(vel);
    gotoxy(25,24);
    color(WHITE);
    printf("    \\_______\\/    \\________\\/      \\__\\/ \\__\\/ "RESET);
}

void logoPause()
{
    color(WHITE);
    gotoxy(12,5);
    printf(" ______      ________        __  __        ______        ______       ");
    color(RED);
    gotoxy(12,6);
    printf("/_____/\\    /_______/\\      /_/\\/_/\\      /_____/\\      /_____/\\      ");
    color(WHITE);
    gotoxy(12,7);
    printf("\\:::_ \\ \\   \\::: _  \\ \\     \\:\\ \\:\\ \\     \\::::_\\/_     \\::::_\\/_     ");
    color(RED);
    gotoxy(12,8);
    printf(" \\:(_) \\ \\   \\::(_)  \\ \\     \\:\\ \\:\\ \\     \\:\\/___/\\     \\:\\/___/\\    ");
    color(WHITE);
    gotoxy(12,9);
    printf("  \\: ___\\/    \\:: __  \\ \\     \\:\\ \\:\\ \\     \\_::._\\:\\     \\::___\\/_   ");
    color(RED);
    gotoxy(12,10);
    printf("   \\ \\ \\       \\:.\\ \\  \\ \\     \\:\\_\\:\\ \\      /____\\:\\     \\:\\____/\\  ");
    color(WHITE);
    gotoxy(12,11);
    printf("    \\_\\/        \\__\\/\\__\\/      \\_____\\/      \\_____\\/      \\_____\\/  "RESET);

    color(WHITE);
    gotoxy(12,13);
    printf(" ______        ________        ___ __ __       ________        ______       ");
    color(RED);
    gotoxy(12,14);
    printf("/_____/\\      /_______/\\      /__//_//_/\\     /_______/\\      /_____/\\      ");
    color(WHITE);
    gotoxy(12,15);
    printf("\\:::_ \\ \\     \\::: _  \\ \\     \\::\\| \\| \\ \\    \\::: _  \\ \\     \\::::_\\/_     ");
    color(RED);
    gotoxy(12,16);
    printf(" \\:\\ \\ \\ \\     \\::(_)  \\ \\     \\:.      \\ \\    \\::(_)  \\ \\     \\:\\/___/\\   ");
    color(WHITE);
    gotoxy(12,17);
    printf("  \\:\\ \\ \\ \\     \\:: __  \\ \\     \\:.\\-/\\  \\ \\    \\:: __  \\ \\     \\_::._\\:\\   ");
    color(RED);
    gotoxy(12,18);
    printf("   \\:\\/.:| |     \\:.\\ \\  \\ \\     \\. \\  \\  \\ \\    \\:.\\ \\  \\ \\      /____\\:\\  ");
    color(WHITE);
    gotoxy(12,19);
    printf("    \\____/_/      \\__\\/\\__\\/      \\__\\/ \\__\\/     \\__\\/\\__\\/      \\_____\\/  ");
}

void menuColoresPausa(int y)
{
    if(y == OPCION_SUP)
    {
        gotoxy(42,OPCION_SUP);
        color(RED);
        printf("RESUME"RESET);
    }
    if(y != OPCION_SUP)
    {
        color(WHITE);
        gotoxy(42,OPCION_SUP);
        printf("RESUME"RESET);
    }
    if(y == OPCION_INF)
    {
        color(RED);
        gotoxy(42,OPCION_INF);
        printf("EXIT"RESET);
    }
    if(y != OPCION_INF)
    {
        color(WHITE);
        gotoxy(42,OPCION_INF);
        printf("EXIT"RESET);
    }
}

