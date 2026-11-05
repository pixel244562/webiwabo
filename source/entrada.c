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
    if (IsKeyPressed(KEY_FOUR)){
        juego->selected_seed = 4;
    }
    if (IsKeyPressed(KEY_FIVE)){
        juego->selected_seed = 5;
    }

    // input mouse

    // obtenemos la posición del mouse
    juego->mouse_pos = GetMousePosition();

    // pala
    Rectangle shovel_rect = {7*(tile_width+tile_offset)+move_x,
        4*(tile_width+tile_offset)+move_y,
        (tile_width+tile_offset),
        (tile_width+tile_offset)
    };

    // left click actions
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        
        // calculo la fila y columna de la casilla donde se hizo click
        int fila = (juego->mouse_pos.y - move_y) / (tile_width+tile_offset);
        int columna = (juego->mouse_pos.x - move_x) / (tile_width+tile_offset);

        if(CheckCollisionPointRec(juego->mouse_pos, shovel_rect) && juego->selected_seed == 0){
            juego->selected_seed = 6; // agarra la pala
            HideCursor();
        }

        Rectangle grass = {move_x, move_y, (tile_width+tile_offset)*8, (tile_width+tile_offset)*5};
        if(CheckCollisionPointRec(juego->mouse_pos, grass)) {      
            juego->ultimo_clic_fila = fila;
            juego->ultimo_clic_columna = columna;

            // si hay semilla seleccionada intenta plantarla
            if(juego->selected_seed != 0 && juego->selected_seed != 6){
                // si el cd de dicha planta es 0, intenta plantarla
                if(juego->seed_cd[juego->selected_seed-1] == 0){
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
                    if(can_plant == 1){
                        if(sun_cost(juego->seed_slot[juego->selected_seed-1],juego) >= 0){
                            place_plant(columna, fila, juego->seed_slot[juego->selected_seed-1],juego);
                            juego->selected_seed = 0;
                        }
                    }
                }
            }
            // la pala desactiva la planta
            if(juego->selected_seed == 6){
                for(int i = 0; i<MAX_PLANTAS; i++){
                    planta *p = &juego->lista_plantas[i];
                    if(p->activo == 1){
                        if(p->columna == columna && p->fila == fila){
                            p->activo = 0;
                            juego->selected_seed = 0;
                            ShowCursor();
                        }
                    }
                }
            }
            
        }
        else{
            juego->ultimo_clic_fila = -1;
            juego->ultimo_clic_columna = -1;
            juego->selected_seed = 0; // apretas fuera del pasto, dejas de seleccionar la semilla
            ShowCursor();
        }
        // collect sun
        for(int i=0; i<MAX_INTERACTUABLES; i++){
            objeto *obj = &juego->lista_objetos[i];

            // Check if point is inside circle
            //     bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);
            int obj_x = (obj->x * (tile_width + tile_offset)) + (tile_width / 2) + move_x-100;
            int obj_y = obj->y;
            float centro_x = obj_x + (juego->sun_texture.width * rescale) / 2.0f;
            float centro_y = obj_y + (juego->sun_texture.height * rescale) / 2.0f;
            if(obj->tipo == 1/*type sun*/ && CheckCollisionPointCircle(juego->mouse_pos,(Vector2){ centro_x, centro_y },90.0)){
                obj->tipo = 0;
                juego->soles+=25;
            } 
        }
        // select seed
        for(int i = 0; i<5; i++){
            Rectangle seed_rect = {150,150+175*i,230,162};
            if(CheckCollisionPointRec(juego->mouse_pos, seed_rect)){
                switch(i){
                    case 0:
                        juego->selected_seed = 1; break;
                    case 1:
                        juego->selected_seed = 2; break;
                    case 2:
                        juego->selected_seed = 3; break;
                    case 3:
                        juego->selected_seed = 4; break;
                    case 4:
                        juego->selected_seed = 5; break;
                }
            }

        }

    }

}

// soundtrack

void music_load(estadojuego* juego){
    InitAudioDevice();

    juego->volume = 0.8f;
    juego->pause = false;
    juego->cancion_actual = 0;
    
    juego->playlist[0] = "assets/soundtrack/ost1.mp3";
    juego->playlist[1] = "assets/soundtrack/ost2.mp3";
    
    juego->backgroundMusic = LoadMusicStream(juego->playlist[juego->cancion_actual]);

    juego->backgroundMusic.looping = false;

    PlayMusicStream(juego->backgroundMusic);
    SetMusicVolume(juego->backgroundMusic, juego->volume);
    SetMusicPan(juego->backgroundMusic, 0.0f);
    UpdateMusicStream(juego->backgroundMusic);
}
void music_update(estadojuego* juego) {
    //update de la musica
    UpdateMusicStream(juego->backgroundMusic);

    //seleccion de teclas
    if (IsKeyPressed(KEY_M)){
        juego->pause = !juego->pause;
        if (juego->pause) PauseMusicStream(juego->backgroundMusic);
        else ResumeMusicStream(juego->backgroundMusic);
    }
    if (IsKeyDown(KEY_DOWN)){
        juego->volume -= 0.05f;
        if (juego->volume < 0.0f) juego->volume = 0.0f;
        SetMusicVolume(juego->backgroundMusic, juego->volume);
    }
    else if (IsKeyDown(KEY_UP)){
        juego->volume += 0.05f;
        if (juego->volume > 1.0f) juego->volume = 1.0f;
        SetMusicVolume(juego->backgroundMusic, juego->volume);
    }
    //declaracion del tiempo de la musica ya reproducida y la total
    float tiempo_reproducido = GetMusicTimePlayed(juego->backgroundMusic);
    float duracion_total = GetMusicTimeLength(juego->backgroundMusic);

    //playlist de canciones
    //(como el calculo no es exacto, le resto 0.1f para que no se quede pegado en la primera cancion)
    if (tiempo_reproducido >= (duracion_total-2.0f)){
        UnloadMusicStream(juego->backgroundMusic);

        juego->cancion_actual++;
        if (juego->cancion_actual >= MAX_CANCIONES) {
            juego->cancion_actual = 0; 
        }

        juego->backgroundMusic = LoadMusicStream(juego->playlist[juego->cancion_actual]);
        juego->backgroundMusic.looping = false;
        PlayMusicStream(juego->backgroundMusic);
        SetMusicVolume(juego->backgroundMusic, juego->volume);
    }
}

void music_unload(estadojuego* juego){
    //unload de la musica y fin del dispositivo de audio
    UnloadMusicStream(juego->backgroundMusic);
    CloseAudioDevice();
}