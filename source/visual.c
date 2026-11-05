#include <stdio.h>
#include <raylib.h>
#include <global.h>
#include <visual.h>

void texture_load(estadojuego *juego){ // convierte las imagenes en texturas para el renderizado de las mismas
    //zombies
    juego->bucket_texture = LoadTexture("assets/bucket.png");
    juego->cone_texture = LoadTexture("assets/cone.png");
    juego->zombie_texture = LoadTexture("assets/zombie.png");
    juego->flag_zombie_texture = LoadTexture("assets/flag_zombie.png");
    //varios
    juego->lawn_texture = LoadTexture("assets/lawn.png");
    juego->pea_texture = LoadTexture("assets/pea.png");
    juego->fire_pea_texture = LoadTexture("assets/fire_pea.png");
    juego->sun_texture = LoadTexture("assets/sun.png");
    //plantas
    juego->peashooter_texture = LoadTexture("assets/peashooter.png");
    juego->sunflower_texture = LoadTexture("assets/sunflower.png");
    juego->wall_nut_1_texture = LoadTexture("assets/wall-nut_1.png");
    juego->wall_nut_2_texture = LoadTexture("assets/wall-nut_2.png");
    juego->wall_nut_3_texture = LoadTexture("assets/wall-nut_3.png");
    juego->garlic_texture = LoadTexture("assets/garlic.png");
    juego->garlic_texture_2 = LoadTexture("assets/garlic_2.png");
    juego->garlic_texture_3 = LoadTexture("assets/garlic_3.png");
    juego->torchwood_texture = LoadTexture("assets/torchwood.png");
    //semillas
    juego->garlic_seed_texture = LoadTexture("assets/seeds/garlic.png");
    juego->peashooter_seed_texture = LoadTexture("assets/seeds/peashooter.png");
    juego->sunflower_seed_texture = LoadTexture("assets/seeds/sunflower.png");
    juego->torchwood_seed_texture = LoadTexture("assets/seeds/torchwood.png");
    juego->wall_nut_seed_texture = LoadTexture("assets/seeds/wall-nut.png");

}

void texture_unload(estadojuego *juego){ // cierra las texturas
    //zombies
    UnloadTexture(juego->bucket_texture);
    UnloadTexture(juego->cone_texture);
    UnloadTexture(juego->zombie_texture);
    UnloadTexture(juego->flag_zombie_texture);
    //varios
    UnloadTexture(juego->lawn_texture);
    UnloadTexture(juego->pea_texture);
    UnloadTexture(juego->fire_pea_texture);
    UnloadTexture(juego->sun_texture);
    //plantas
    UnloadTexture(juego->peashooter_texture);
    UnloadTexture(juego->sunflower_texture);
    UnloadTexture(juego->wall_nut_1_texture);
    UnloadTexture(juego->wall_nut_2_texture);
    UnloadTexture(juego->wall_nut_3_texture);
    UnloadTexture(juego->garlic_texture);
    UnloadTexture(juego->garlic_texture_2);
    UnloadTexture(juego->garlic_texture_3);
    UnloadTexture(juego->torchwood_texture);
    //semillas
    UnloadTexture(juego->garlic_seed_texture);
    UnloadTexture(juego->peashooter_seed_texture);
    UnloadTexture(juego->sunflower_seed_texture);
    UnloadTexture(juego->torchwood_seed_texture);
    UnloadTexture(juego->wall_nut_seed_texture);
}

void draw(estadojuego *juego){
    BeginDrawing();
        ClearBackground(BLACK); // limpia la pantalla

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
        // dibujar las semillas con su coste
        const int h = 150, h2 = 25;
        // h+h2 = 175
        DrawTextureEx(
            juego->peashooter_seed_texture, 
            (Vector2){ 150.0f, (float)h }, 
            0.0f, 
            0.7f, 
            WHITE
        );
        DrawText("100", 301, 242, 75, GRAY);
        DrawText("100", 300, 240, 70, WHITE);

        DrawTextureEx(
            juego->sunflower_seed_texture, 
            (Vector2){ 150.0f, (float)(h*2 + h2) }, 
            0.0f, 
            0.7f, 
            WHITE
        );
        DrawText("50", 301+20, 242+h+h2+3, 75, GRAY);
        DrawText("50", 300+20, 240+h+h2+3, 70, WHITE);
        DrawTextureEx(
            juego->wall_nut_seed_texture, 
            (Vector2){ 150.0f, (float)(h*3 + (h2*2)) }, 
            0.0f, 
            0.7f, 
            WHITE
        );
        DrawText("50", 301+20, 242+(h+h2)*2+3, 75, GRAY);
        DrawText("50", 300+20, 240+(h+h2)*2+3, 70, WHITE);
        DrawTextureEx(
            juego->garlic_seed_texture, 
            (Vector2){ 150.0f, (float)(h*4 + (h2*3)) }, 
            0.0f, 
            0.7f, 
            WHITE
        );
        DrawText("50", 301+20, 242+(h+h2)*3+3, 75, GRAY);
        DrawText("50", 300+20, 240+(h+h2)*3+3, 70, WHITE);
        DrawTextureEx(
            juego->torchwood_seed_texture, 
            (Vector2){ 150.0f, (float)(h*5 + (h2*4)) }, 
            0.0f, 
            0.7f, 
            WHITE
        );
        DrawText("125", 301, 242+(h+h2)*4+3, 75, GRAY);
        DrawText("125", 300, 240+(h+h2)*4+3, 70, WHITE);

        // rectangulo para visualizar forma de colisión rectangular de semillas
        //DrawRectangle(150,150,230,162, (Color){ 182, 255, 92, 100 });
        //DrawRectangle(150,150+175,230,162, (Color){ 182, 255, 92, 100 });

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
                        if(p->vida >= 720){ // 1440 / 2
                            DrawTextureEx(
                                juego->wall_nut_1_texture, 
                                (Vector2){ (float)(p_x - 85), (float)(p_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                        }
                        else if(p->vida >= 480){ // 1440 / 3
                            DrawTextureEx(
                                juego->wall_nut_2_texture, 
                                (Vector2){ (float)(p_x - 85), (float)(p_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                        }
                        else
                            DrawTextureEx(
                                juego->wall_nut_3_texture, 
                                (Vector2){ (float)(p_x - 85), (float)(p_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                        break;
                    case 4:
                        if(p->vida >= 200){ // 400 / 2
                            DrawTextureEx(
                                juego->garlic_texture, 
                                (Vector2){ (float)(p_x - 85), (float)(p_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                        }
                        else if(p->vida >= 150){ // 400 / 3 con bastante aproximación
                            DrawTextureEx(
                                juego->garlic_texture_2, 
                                (Vector2){ (float)(p_x - 85), (float)(p_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                        }
                        else
                            DrawTextureEx(
                                juego->garlic_texture_3, 
                                (Vector2){ (float)(p_x - 85), (float)(p_y) }, 
                                0.0f,
                                rescale,
                                WHITE
                            );
                        break;
                    case 5:
                        DrawTextureEx(
                            juego->torchwood_texture, 
                            (Vector2){ (float)(p_x - 100), (float)(p_y) }, 
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
                int z_x = (int)z->pos_x;
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
                            juego->flag_zombie_texture, 
                            (Vector2){ (float)(z_x), (float)(z_y) }, 
                            0.0f,
                            rescale,
                            WHITE
                        );
                        break;
                }
            }
        }
        // dibuja proyectiles
        for(int i = 0; i<MAX_PROYECTILES; i++){
            proyectil *p = &juego->lista_proyectiles[i];
            if(p->activo == 1){
                int p_x = (int)p->pos_x;
                int p_y = (p->fila * (tile_width + tile_offset)) + (tile_width / 2) + move_y -120;
                if(p->tipo == 1){
                    DrawTexture(juego->pea_texture,p_x, p_y, WHITE);
                }
                else{
                    DrawTextureEx(
                            juego->fire_pea_texture, 
                            (Vector2){ (float)(p_x), (float)(p_y) }, 
                            0.0f,
                            0.6,
                            WHITE
                        );
                }
                
                
            }
        }
        for(int i = 0; i<MAX_INTERACTUABLES; i++){
            objeto *obj = &juego->lista_objetos[i];
            switch(obj->tipo){
                case 1:
                    int obj_x = (obj->x * (tile_width + tile_offset)) + (tile_width / 2) + move_x-100;
                    int obj_y = obj->y;

                    DrawTextureEx(
                        juego->sun_texture, 
                        (Vector2){ (float)(obj_x), (float)(obj_y) }, 
                        0.0f,
                        rescale,
                        WHITE
                    );
                    // para visualizar la colisisión de recogida con clic
                    // DrawCircle(centro_x, centro_y,90,(Color){ 182, 255, 92, 100 });
                    break;
                default:
                    break;
            }
        }
        // dibujar cantidad de soles
        DrawTextureEx(
            juego->sun_texture, 
            (Vector2){ 10.0f, 10.0f}, 
            0.0f,
            0.7f,
            WHITE
        );
        DrawText(TextFormat("%d", juego->soles), 171, 42, 95, GRAY);
        DrawText(TextFormat("%d", juego->soles), 170, 40, 90, WHITE);

        /* funciones utiles:
        void DrawText(const char *text, int posX, int posY, int fontSize, Color color); Draw text (using default font)
        const char *TextFormat(const char *text, ...); Text formatting with variables (sprintf() style)
        */
        
        // texto ---------------------------------------------------------------------------------------------------
        // DEBUGGING
        /*
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
        */
        // resultado
        if(juego->partida == PARTIDA_LOSS){
            DrawRectangle(0 , 0 ,SCREEN_WIDTH ,SCREEN_HEIGHT , (Color){ 0, 0, 0, 200});
            DrawText(TextFormat("THE ZOMBIES ATE YOUR BRAINS!", juego->ticks), 20, 10+80, 60, WHITE);
        }
        

    EndDrawing();
}