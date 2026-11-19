#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "visual.h"
#include "logic.h"
#include "entrada.h"
#include <raylib.h>

int main(){
    // calloc reserva memoria en el heap igual que malloc, pero la deja inicializada en 0.
    // evita valores basura en campos sin asignar
    estadojuego* juego = calloc(1, sizeof(estadojuego));
    if (juego == NULL) {
        // no hay memoria :(
        return 1;
    }

    init(juego);
    // game loop
    while (!WindowShouldClose()) {
        procesar_entrada(juego);
        update(juego); 
        music_update(juego);
        draw(juego);
    }
    music_unload(juego);
    sfx_unload(juego);
    texture_unload(juego);
    CloseWindow();

    free(juego);

    return 0;
}