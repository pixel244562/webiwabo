#include <stdio.h>
#include <raylib.h>
#include <global.h>
#include <visual.h>

void draw(estadojuego *juego){
    BeginDrawing();
        int tile_width = 80;
        int tile_offset = 10;

        for(int y = 0; y<FILAS; y++){
            for(int x = 0; x<COLUMNAS; x++){
                DrawRectangle(x*(tile_width+tile_offset), y*(tile_width+tile_offset), tile_width, tile_width, GREEN);
                DrawRectangle(x*(tile_width+tile_offset) + tile_width-5, y*(tile_width+tile_offset) + tile_width-5, 5, 5, RED);
                DrawRectangle(x*(tile_width+tile_offset), y*(tile_width+tile_offset), 5, 5, BLUE);
            }
        }
        
        for (int i = 0; i<MAX_ZOMBIES; i++) {
            zombie *z = &juego->lista_zombies[i];
        
            if (z->activo){
                int z_x = (z->columna * (tile_width + tile_offset)) + (tile_width / 2);
                int z_y = (z->fila * (tile_width + tile_offset)) + (tile_width / 2);
            
                DrawCircle(z_x, z_y, 30, DARKGREEN);
            }
        }
        
    EndDrawing();
}

