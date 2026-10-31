#include <stdio.h>
#include <raylib.h>
#include <global.h>
#include <visual.h>

void draw(estadojuego *juego){
    BeginDrawing();
        ClearBackground(BLACK);
        int tile_width = 80;
        int tile_offset = 10;
        int move_x = 300;

        // dibuja el tablero
        for(int y = 0; y<FILAS; y++){
            for(int x = 0; x<COLUMNAS; x++){
                DrawRectangle(x*(tile_width+tile_offset)+move_x, y*(tile_width+tile_offset), tile_width, tile_width, (Color){ 182, 255, 92, 255 });
                DrawRectangle(x*(tile_width+tile_offset)+move_x + tile_width-5, y*(tile_width+tile_offset) + tile_width-5, 5, 5, RED);
                DrawRectangle(x*(tile_width+tile_offset)+move_x, y*(tile_width+tile_offset), 5, 5, BLUE);
            }
        }
        // dibuja plantas
        for(int i = 0; i<MAX_PLANTAS; i++){
            planta *p = &juego->lista_plantas[i];

            if(p->activo){
                int p_x = (p->columna * (tile_width + tile_offset)) + (tile_width / 2) + move_x;
                int p_y = (p->fila * (tile_width + tile_offset)) + (tile_width / 2);
                switch(p->tipo){
                    case 1: // lanzaguizantes
                        DrawCircle(p_x, p_y, ((p->vida*30)/100), DARKGREEN); break;
                    case 3: // nuez
                        DrawCircle(p_x, p_y, ((p->vida*30)/200), BROWN);
                        
                        break;
                }
            }
        }
        // dibuja zombies
        for(int i = 0; i<MAX_ZOMBIES; i++){
            zombie *z = &juego->lista_zombies[i];
        
            if(z->activo){
                int z_x = (z->columna * (tile_width + tile_offset)) + (tile_width / 2) + move_x;
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
                    case 3: // zombie cubeta
                        if(z->vida > 100){
                            DrawCircle(z_x, z_y, 30, LIGHTGRAY);
                            DrawCircle(z_x, z_y, 23, LIME);
                            break;
                        }
                        else{
                            DrawCircle(z_x, z_y, 30, LIME); break;}
                    case 4: // bandera
                        DrawCircle(z_x, z_y, 20, LIME); break;
                }
            }
        }
        // dibuja proyectiles
        for(int i = 0; i<MAX_PROYECTILES; i++){
            proyectil *p = &juego->lista_proyectiles[i];
            if(p->activo == 1){
                int p_x = (p->columna * (tile_width + tile_offset)) + (tile_width / 2) + move_x;
                int p_y = (p->fila * (tile_width + tile_offset)) + (tile_width / 2);
                DrawCircle(p_x, p_y, 10, WHITE); break;
            }
        }
        /* funciones utiles:
        void DrawText(const char *text, int posX, int posY, int fontSize, Color color); Draw text (using default font)
        const char *TextFormat(const char *text, ...); Text formatting with variables (sprintf() style)
        */
        
        // texto ---------------------------------------------------------------------------------------------------
        DrawFPS(10, 10);
        // soles
        DrawText(TextFormat("Sun: %d", juego->soles), 150, 10, 20, YELLOW);
        // vida
        DrawText(TextFormat("Lives: %d", juego->vida_casa), 150, 10+20, 20, RED);
        // ticks y gametime
        DrawText(TextFormat("ticks: %d", juego->ticks), 10, 10+20, 20, LIGHTGRAY);
        DrawText(TextFormat("%d:%d:%d",(juego->ticks/(30*30))%60, (juego->ticks/30)%60, (juego->ticks)%60), 10, 10+40, 20, LIGHTGRAY);
        // resultado
        if(juego->partida == PARTIDA_LOSS){
            DrawRectangle(0 , 0 ,SCREEN_WIDTH ,SCREEN_HEIGHT , (Color){ 0, 0, 0, 200});
            DrawText(TextFormat("THE ZOMBIES ATE YOUR BRAINS!", juego->ticks), 20, 10+80, 60, GREEN);
        }
        

    EndDrawing();
}

