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

        int tile_width = 180;
        int tile_offset = 5;
        int move_x = 445;
        int move_y = 150;
        float rescale = 0.9f; // 10% más pequeño

        /* Para dibujar texturas:
        DrawTexture(Texture2D texture, int posX, int posY, Color tint);   
            // Draw a Texture2D
        DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint); 
            // Draw a Texture2D with rotation and scale
        */

        DrawTexture(juego->lawn_texture, 0, 0, WHITE);

        /*
        // (para visualizar dimensiones)
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
                int p_y = (p->fila * (tile_width + tile_offset)) + (tile_width / 2) + move_y-100;
                switch(p->tipo){
                    case 1: // lanzaguizantes
                        DrawTextureEx(
                            juego->peashooter_texture, 
                            (Vector2){ (float)(p_x - 100), (float)(p_y) }, 
                            0.0f,
                            rescale,
                            WHITE
                        );
                        break;
                    case 2:
                        DrawTextureEx(
                            juego->sunflower_texture, 
                            (Vector2){ (float)(p_x - 100), (float)(p_y) }, 
                            0.0f,
                            rescale,
                            WHITE
                        );
                        break;
                    case 3: // nuezDrawTexture(juego->bucket_texture, z_x-20, z_y-80, WHITE);
                        if(p->vida >= 150){
                            DrawTextureEx(
                                juego->wall_nut_1_texture, 
                                (Vector2){ (float)(p_x - 90), (float)(p_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                        }
                        else if(p->vida >= 100){
                            DrawTextureEx(
                                juego->wall_nut_2_texture, 
                                (Vector2){ (float)(p_x - 90), (float)(p_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                        }
                        else
                            DrawTextureEx(
                                juego->wall_nut_3_texture, 
                                (Vector2){ (float)(p_x - 90), (float)(p_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                        break;
                }
            }
        }
        // dibuja zombies
        for(int i = 0; i<MAX_ZOMBIES; i++){
            zombie *z = &juego->lista_zombies[i];
        
            if(z->activo){
                int z_x = (z->columna * (tile_width + tile_offset)) + (tile_width / 2) + move_x-100;
                int z_y = (z->fila * (tile_width + tile_offset)) + (tile_width / 2) + move_y-190;
                switch(z->tipo){
                    case 1: // zombie común
                        DrawTextureEx(
                            juego->zombie_texture, 
                            (Vector2){ (float)(z_x), (float)(z_y) }, 
                            0.0f,
                            rescale,
                            WHITE
                        );
                        break;
                    case 2: // zombie cono
                        if(z->vida > 100){
                            DrawTextureEx(
                                juego->zombie_texture, 
                                (Vector2){ (float)(z_x), (float)(z_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                            DrawTextureEx(
                                juego->cone_texture, 
                                (Vector2){ (float)(z_x-20), (float)(z_y-80) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                        break;
                        }
                        else{
                            DrawTextureEx(
                                juego->zombie_texture, 
                                (Vector2){ (float)(z_x), (float)(z_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                            break;
                        }
                    case 3: // zombie cubeta
                        if(z->vida > 100){
                            DrawTextureEx(
                                juego->zombie_texture, 
                                (Vector2){ (float)(z_x), (float)(z_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                            DrawTextureEx(
                                juego->bucket_texture, 
                                (Vector2){ (float)(z_x-20), (float)(z_y-70) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                            break;
                        }
                        else{
                            DrawTextureEx(
                                juego->zombie_texture, 
                                (Vector2){ (float)(z_x), (float)(z_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                            break;}
                    case 4: // bandera
                        DrawTextureEx(
                            juego->zombie_texture, 
                            (Vector2){ (float)(z_x), (float)(z_y) }, 
                            0.0f,
                            rescale,
                            GRAY
                        );
                        break;
                }
            }
        }
        // dibuja proyectiles
        for(int i = 0; i<MAX_PROYECTILES; i++){
            proyectil *p = &juego->lista_proyectiles[i];
            if(p->activo == 1){
                int p_x = (p->columna * (tile_width + tile_offset)) + (tile_width / 2) + move_x -100;
                int p_y = (p->fila * (tile_width + tile_offset)) + (tile_width / 2) + move_y -120;
                DrawTexture(juego->pea_texture,p_x, p_y, WHITE);
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
        // ultimo mouse clic (en coordenadas de pasto) -1 quiere decir fuera del pasto
        DrawText(TextFormat("Grass Click: (%d, %d)", juego->ultimo_clic_fila, juego->ultimo_clic_columna), 10, 10+60, 20, GREEN);
        // semilla seleccionada (numero de slot)
        DrawText(TextFormat("Selected Seed: %d", juego->selected_seed), 10, 10+80, 20, GREEN);
        switch(juego->selected_seed){
            case 1:
                switch(juego->seed_slot[0]){
                    case 1:
                        DrawText("Peashooter", 10, 10+100, 20, GREEN); break;
                    case 2:
                        DrawText("Sunflower", 10, 10+100, 20, GREEN); break;
                    case 3:
                        DrawText("Wall-nut", 10, 10+100, 20, GREEN); break;
                    default:
                        DrawText("None", 10, 10+100, 20, GREEN);
                }
                break;
            case 2:
                switch(juego->seed_slot[1]){
                    case 1:
                        DrawText("Peashooter", 10, 10+100, 20, GREEN); break;
                    case 2:
                        DrawText("Sunflower", 10, 10+100, 20, GREEN); break;
                    case 3:
                        DrawText("Wall-nut", 10, 10+100, 20, GREEN); break;
                    default:
                        DrawText("None", 10, 10+100, 20, GREEN);
                }
                break;
            case 3:
                switch(juego->seed_slot[2]){
                    case 1:
                        DrawText("Peashooter", 10, 10+100, 20, GREEN); break;
                    case 2:
                        DrawText("Sunflower", 10, 10+100, 20, GREEN); break;
                    case 3:
                        DrawText("Wall-nut", 10, 10+100, 20, GREEN); break;
                    default:
                        DrawText("None", 10, 10+100, 20, GREEN);
                }
                break;
            default:
                DrawText("None", 10, 10+100, 20, GREEN);
        }
        
        // resultado
        if(juego->partida == PARTIDA_LOSS){
            DrawRectangle(0 , 0 ,SCREEN_WIDTH ,SCREEN_HEIGHT , (Color){ 0, 0, 0, 200});
            DrawText(TextFormat("THE ZOMBIES ATE YOUR BRAINS!", juego->ticks), 20, 10+80, 60, WHITE);
        }
        

    EndDrawing();
}