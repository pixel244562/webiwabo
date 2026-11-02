#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "global.h"
#include "logic.h"

#define move_x 445
#define move_y 150
#define tile_offset 5
#define tile_width 180

// ENTRADA DE MOUSE Y TECLAS
void procesar_entrada(estadojuego* juego){
    if (IsKeyPressed(KEY_ONE)){
        juego->selected_seed = 1;
    }
    if (IsKeyPressed(KEY_TWO)){
        juego->selected_seed = 2;
    }
    if (IsKeyPressed(KEY_THREE)){
        juego->selected_seed = 3;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        // obtenemos la posición del mouse
        Vector2 mouse_pos = GetMousePosition();
        
        // calculo la fila y columna de la casilla donde se hizo click
        int fila = (mouse_pos.y - move_y) / (tile_width+tile_offset);
        int columna = (mouse_pos.x - move_x) / (tile_width+tile_offset);
        
        Rectangle grass = {move_x, move_y, (tile_width+tile_offset)*8, (tile_width+tile_offset)*5};
        if (CheckCollisionPointRec(mouse_pos, grass)) {      
            juego->ultimo_clic_fila = fila;
            juego->ultimo_clic_columna = columna;
            // si hay semilla seleccionada intenta plantarla
            if (juego->selected_seed != 0){
                char can_plant = 1;
                // reviso que no existan plantas activas en la misma posición que se quiera plantar
                for(int i = 0; i<MAX_PLANTAS; i++){
                    planta *p = &juego->lista_plantas[i];
                    if(p->activo == 1){
                        if(p->columna == columna && p->fila == fila){
                            can_plant = 0;
                            juego->selected_seed = 0;
                        }
                    }
                }
                if(can_plant == 1)
                    place_plant(columna, fila, juego->seed_slot[juego->selected_seed-1],juego);
            }
        }
        else{
            juego->ultimo_clic_fila = -1;
            juego->ultimo_clic_columna = -1;
            juego->selected_seed = 0; // apretas fuera del pasto, dejas de seleccionar la semilla
        }
    }
}