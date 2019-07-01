#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "reloj.h"

void tono(int x){
                                                                    /// Cambia la combinacion de color de fondo y frente
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

void cartesiano(int X,int Y){                                                /// Cambia las coordenadas del cursor
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X=X;
      dwPos.Y=Y;
      SetConsoleCursorPosition(hcon,dwPos);
}
