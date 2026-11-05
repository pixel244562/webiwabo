#include <stdio.h>
#include "global.h"
#include "visual.h"
#include "logic.h"
#include "entrada.h"
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
    // oleadas
    juego.ticks_oleada_actual = 0;
    juego.oleada_actual = 0;
    // semillas
    juego.selected_seed = 0;
    // semillas seleccionadas por defecto
    juego.seed_slot[0] = 1;
    juego.seed_slot[1] = 2;
    juego.seed_slot[2] = 3;
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
    // objetos tipo 0
    for (int i = 0; i < MAX_INTERACTUABLES; i++) {
        juego.lista_objetos[i].tipo = 0;
    }
    // carga las texturas
    texture_load(&juego);
    // carga la musica
    music_load(&juego);
    // game loop
    while (!WindowShouldClose()) {
        procesar_entrada(&juego);
        update(&juego); 
        music_update(&juego);
        draw(&juego);
    }
    music_unload(&juego);
    CloseWindow();

    texture_unload(&juego);

    return 0;
}