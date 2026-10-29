#include <stdio.h>
#include "global.h"
#include "visual.h"
#include <raylib.h>

int main(){
    const int width = 800;
    const int height = 440;
    InitWindow(width, height, "webi wabo");
    SetTargetFPS(30);

    estadojuego juego;
    juego.soles = 50;
    juego.vida_casa = 5;
    juego.oleada = 1;
    juego.ticks = 0;

    // game loop
    while (!WindowShouldClose()) {

        juego.ticks++;
        draw();
    }
    CloseWindow();

    return 0;
}