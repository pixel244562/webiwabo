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

    // zombies inactivos
    for (int i = 0; i < MAX_ZOMBIES; i++) {
        juego.lista_zombies[i].activo = 0;
    }
    // plantas inactivas
    for (int i = 0; i < MAX_PLANTAS; i++) {
        juego.lista_plantas[i].activo = 0;
    }
    // proyectiles inactivos
    for (int i = 0; i < MAX_PROYECTILES; i++) {
        juego.lista_proyectiles[i].activo = 0;
    }

    place_plant(0,1,1, &juego);
    place_plant(6,2,3, &juego);
    zombie_spawn(8,2,1, &juego);
    zombie_spawn(7,1,2, &juego);
    zombie_spawn(8,1,3, &juego);
    zombie_spawn(8,3,4, &juego);

    // game loop
    while (!WindowShouldClose()) {
        update(&juego);
        draw(&juego);
    }
    CloseWindow();

    return 0;
}