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
                DrawRectangle(x*(tile_width+tile_offset), y*(tile_width+tile_offset), tile_width, tile_width, (Color){ 182, 255, 92, 255 });
                DrawRectangle(x*(tile_width+tile_offset) + tile_width-5, y*(tile_width+tile_offset) + tile_width-5, 5, 5, RED);
                DrawRectangle(x*(tile_width+tile_offset), y*(tile_width+tile_offset), 5, 5, BLUE);
            }
        }
        
        for(int i = 0; i<MAX_ZOMBIES; i++){
            zombie *z = &juego->lista_zombies[i];
        
            if(z->activo){
                int z_x = (z->columna * (tile_width + tile_offset)) + (tile_width / 2);
                int z_y = (z->fila * (tile_width + tile_offset)) + (tile_width / 2);
                switch(z->tipo){
                    case 1: // zombie común
                        DrawCircle(z_x, z_y, 30, LIME); break;
                    case 2: // zombie cono
                        if(z->vida > 100){
                            DrawCircle(z_x, z_y, 30, ORANGE);
                            DrawCircle(z_x, z_y, 23, LIME);
                            break;
                        }
                        else{
                            DrawCircle(z_x, z_y, 30, LIME); break;}
                }
            }
        }
        for(int i = 0; i<MAX_PLANTAS; i++){
            planta *p = &juego->lista_plantas[i];

            if(p->activo){
                int p_x = (p->columna * (tile_width + tile_offset)) + (tile_width / 2);
                int p_y = (p->fila * (tile_width + tile_offset)) + (tile_width / 2);
                switch(p->tipo){
                    case 1: // lanzaguizantes
                        DrawCircle(p_x, p_y, 30, DARKGREEN); break;
                }
            }
        }
        for(int i = 0; i<MAX_PROYECTILES; i++){
            proyectil *p = &juego->lista_proyectiles[i];
            if(p->activo == 1){
                int p_x = (p->columna * (tile_width + tile_offset)) + (tile_width / 2);
                int p_y = (p->fila * (tile_width + tile_offset)) + (tile_width / 2);
                DrawCircle(p_x, p_y, 10, WHITE); break;
            }
        }
        
    EndDrawing();
}

