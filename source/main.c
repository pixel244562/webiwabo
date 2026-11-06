#include <stdio.h>
#include "global.h"
#include "visual.h"
#include "logic.h"
#include "entrada.h"
#include <raylib.h>
#include <time.h>

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
    juego.oleada_previa = 0;
    juego.zombies_coming = 0;
    juego.c_intervalo = 0;
    juego.zombie_kills = 0;
    // semillas
    juego.selected_seed = 0;
    // semillas seleccionadas por defecto
    juego.seed_slot[0] = 1;
    juego.seed_slot[1] = 2;
    juego.seed_slot[2] = 3;
    juego.seed_slot[3] = 4;
    juego.seed_slot[4] = 5;
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
    // cooldown de semillas
    for (int i = 0; i < MAX_SEEDS; i++) {
        juego.seed_cd[i] = 0;
    }
    // carga las texturas
    texture_load(&juego);
    // carga la musica
    music_load(&juego);
    // semilla aleatoria
    SetRandomSeed(time(NULL));

    // game loop
    while (!WindowShouldClose()) {
        procesar_entrada(&juego);
        update(&juego); 
        music_update(&juego);
        draw(&juego);
    }
    music_unload(&juego);
    texture_unload(&juego);
    CloseWindow();
    

    return 0;
}