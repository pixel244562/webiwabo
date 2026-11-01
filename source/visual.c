#include <stdio.h>
#include <raylib.h>
#include <global.h>
#include <visual.h>

void texture_load(estadojuego *juego){ // convierte las imagenes en texturas para el renderizado de las mismas
    juego->bucket_texture = LoadTexture("assets/bucket.png");
    juego->cone_texture = LoadTexture("assets/cone.png");
    juego->garlic_texture = LoadTexture("assets/garlic.png");
    juego->lawn_texture = LoadTexture("assets/lawn.png");
    juego->pea_texture = LoadTexture("assets/pea.png");
    juego->peashooter_texture = LoadTexture("assets/peashooter.png");
    juego->sun_texture = LoadTexture("assets/sun.png");
    juego->sunflower_texture = LoadTexture("assets/sunflower.png");
    juego->wall_nut_1_texture = LoadTexture("assets/wall-nut_1.png");
    juego->wall_nut_2_texture = LoadTexture("assets/wall-nut_2.png");
    juego->wall_nut_3_texture = LoadTexture("assets/wall-nut_3.png");
    juego->zombie_texture = LoadTexture("assets/zombie.png");
}

void texture_unload(estadojuego *juego){ // cierra las texturas
    UnloadTexture(juego->bucket_texture);
    UnloadTexture(juego->cone_texture);
    UnloadTexture(juego->garlic_texture);
    UnloadTexture(juego->lawn_texture);
    UnloadTexture(juego->pea_texture);
    UnloadTexture(juego->peashooter_texture);
    UnloadTexture(juego->sun_texture);
    UnloadTexture(juego->sunflower_texture);
    UnloadTexture(juego->wall_nut_1_texture);
    UnloadTexture(juego->wall_nut_2_texture);
    UnloadTexture(juego->wall_nut_3_texture);
    UnloadTexture(juego->zombie_texture);
}

void draw(estadojuego *juego){
    BeginDrawing();
        ClearBackground(BLACK); // limpia la pantalla

        int tile_width = 190;
        int tile_offset = 5;
        int move_x = 360;
        int move_y = 70;

        /* Para dibujar texturas:
        DrawTexture(Texture2D texture, int posX, int posY, Color tint);   
        */

        DrawTexture(juego->lawn_texture, 0, 0, WHITE);

        /* // (para visualizar dimensiones)
        // dibuja el tablero
        for(int y = 0; y<FILAS; y++){
            for(int x = 0; x<COLUMNAS; x++){
                DrawRectangle(x*(tile_width+tile_offset)+move_x, y*(tile_width+tile_offset)+move_y, tile_width, tile_width, (Color){ 182, 255, 92, 100 });
                DrawRectangle(x*(tile_width+tile_offset)+move_x + tile_width-5, y*(tile_width+tile_offset) + tile_width-5 +move_y, 5, 5, RED);
                DrawRectangle(x*(tile_width+tile_offset)+move_x, y*(tile_width+tile_offset)+move_y, 5, 5, BLUE);
            }
        }
        */
        // dibuja plantas
        for(int i = 0; i<MAX_PLANTAS; i++){
            planta *p = &juego->lista_plantas[i];

            if(p->activo){
                int p_x = (p->columna * (tile_width + tile_offset)) + (tile_width / 2) + move_x;
                int p_y = (p->fila * (tile_width + tile_offset)) + (tile_width / 2) + move_y;
                switch(p->tipo){
                    case 1: // lanzaguizantes
                        DrawTexture(juego->peashooter_texture, p_x-120, p_y-120, WHITE); break;
                    case 3: // nuez
                        if(p->vida >= 150){
                            DrawTexture(juego->wall_nut_1_texture, p_x-90, p_y-120, WHITE);
                        }
                        else if(p->vida >= 100){
                            DrawTexture(juego->wall_nut_2_texture, p_x-90, p_y-120, WHITE);
                        }
                        else
                            DrawTexture(juego->wall_nut_3_texture, p_x-90, p_y-120, WHITE);
                        break;
                }
            }
        }
        // dibuja zombies
        for(int i = 0; i<MAX_ZOMBIES; i++){
            zombie *z = &juego->lista_zombies[i];
        
            if(z->activo){
                int z_x = (z->columna * (tile_width + tile_offset)) + (tile_width / 2) + move_x-110;
                int z_y = (z->fila * (tile_width + tile_offset)) + (tile_width / 2) + move_y-210;
                switch(z->tipo){
                    case 1: // zombie común
                        DrawTexture(juego->zombie_texture,z_x, z_y, WHITE); break;
                    case 2: // zombie cono
                        if(z->vida > 100){
                            DrawTexture(juego->zombie_texture, z_x, z_y, WHITE);
                            DrawTexture(juego->cone_texture, z_x-20, z_y-95, WHITE);
                            break;
                        }
                        else{
                            DrawTexture(juego->zombie_texture,z_x, z_y, WHITE); break;}
                    case 3: // zombie cubeta
                        if(z->vida > 100){
                            DrawTexture(juego->zombie_texture,z_x, z_y, WHITE);
                            DrawTexture(juego->bucket_texture, z_x-20, z_y-80, WHITE);
                            break;
                        }
                        else{
                            DrawTexture(juego->zombie_texture,z_x, z_y, WHITE); break;}
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
                int p_y = (p->fila * (tile_width + tile_offset)) + (tile_width / 2) + move_y;
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