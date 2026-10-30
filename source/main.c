#include <stdio.h>
#include "global.h"
#include "visual.h"
#include "logic.h"
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

    // inicio todos los zombies como inactivos
    for (int i = 0; i < MAX_ZOMBIES; i++) {
        juego.lista_zombies[i].activo = 0;
    }

    juego.lista_zombies[0].activo = 1;
    juego.lista_zombies[0].tipo = 1;
    juego.lista_zombies[0].vida = 100;
    juego.lista_zombies[0].fila = 2;
    juego.lista_zombies[0].columna = 8;
    juego.lista_zombies[0].velocidad = 30;

    // game loop
    while (!WindowShouldClose()) {
        accion_zombies(&juego);
        juego.ticks++;
        draw(&juego);
    }
    CloseWindow();

    return 0;
}