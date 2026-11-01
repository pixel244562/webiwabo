#include <stdio.h>
#include "global.h"
#include "visual.h"
#include "logic.h"
#include <raylib.h>

int main(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "webi wabo");
    ToggleFullscreen();
    SetTargetFPS(30);

    estadojuego juego;
    juego.soles = 50;
    juego.vida_casa = CASA_HP_INICIAL;
    juego.ticks = 0;
    juego.partida = PARTIDA_JUGANDO;
    juego.oleadas_restantes = MAX_OLEADAS; // O el número que uses
    juego.zombies_pendientes = 0;          // O la cantidad inicial

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
    zombie_spawn(7,4,2, &juego);
    zombie_spawn(8,1,3, &juego);
    //zombie_spawn(7,3,4, &juego);
    // carga las texturas
    texture_load(&juego);
    // game loop
    while (!WindowShouldClose()) {
        update(&juego); 
        draw(&juego);
    }
    CloseWindow();

    texture_unload(&juego);

    return 0;
}