#include <stdio.h>
#include <string.h>
#include <time.h>
#include "raylib.h"
#include "global.h"
#include "visual.h"
#include "logic.h"

#define move_x 445
#define move_y 150
#define tile_offset 5
#define tile_width 180

// ENTRADA DE MOUSE Y TECLAS
void procesar_entrada(estadojuego* juego){
    if (IsKeyPressed(KEY_ONE)){
        juego->selected_seed = 1;
        ShowCursor();
    }
    if (IsKeyPressed(KEY_TWO)){
        juego->selected_seed = 2;
        ShowCursor();
    }
    if (IsKeyPressed(KEY_THREE)){
        juego->selected_seed = 3;
        ShowCursor();
    }
    if (IsKeyPressed(KEY_FOUR)){
        juego->selected_seed = 4;
        ShowCursor();
    }
    if (IsKeyPressed(KEY_FIVE)){
        juego->selected_seed = 5;
        ShowCursor();
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
                            PlaySound(juego->sfx_plant);
                        }
                        else
                            PlaySound(juego->sfx_buzzer);
                    }
                }
                else
                    PlaySound(juego->sfx_buzzer);
            }
            // la pala desactiva la planta
            if(juego->selected_seed == 6){
                for(int i = 0; i<MAX_PLANTAS; i++){
                    planta *p = &juego->lista_plantas[i];
                    if(p->activo == 1){
                        if(p->columna == columna && p->fila == fila){
                            p->vida = 0;
                            p->activo = 0;
                            juego->selected_seed = 0;
                            ShowCursor();
                            PlaySound(juego->sfx_shovel);
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
                PlaySound(juego->sfx_sun);
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

void cargar_config(estadojuego* juego){
    // lee el archivo config
    FILE* f = fopen("config.txt", "r");

    if (f == NULL)
        // si no hay archivo, detiene la funcion
        return;

    char token[64];
    float val;
    while (fscanf(f, "%63s %f", token, &val) == 2) {
        // mientras fscanf consiga leer 2 valores, una cadena y un float
        // compara palabras clave con strcmp y asigna el valor
        if (strcmp(token, "soles_iniciales") == 0)
            juego->soles = (int)val;
        else if(strcmp(token, "zombies_total") == 0)
            juego->zombies_total = (int)val;
        else if(strcmp(token, "vida_casa") == 0)
            juego->vida_casa = (int)val;
        else if(strcmp(token, "SetTargetFPS") == 0)
            SetTargetFPS((int)val);
        else if(strcmp(token, "SetMusicVolume") == 0){
            if (val < 0.0f)
                val = 0.0f;
            if (val > 1.0f)
                val = 1.0f;
            juego->volume = val;
        }
        else if(strcmp(token, "filtro_r") == 0){
            if (val < 0) val = 0;
            if (val > 255) val = 255;
            juego->filtro.r = (unsigned char)val;
        }
        else if(strcmp(token, "filtro_g") == 0){
            if (val < 0) val = 0;
            if (val > 255) val = 255;
            juego->filtro.g = (unsigned char)val;
        }
        else if(strcmp(token, "filtro_b") == 0){
            if (val < 0) val = 0;
            if (val > 255) val = 255;
            juego->filtro.b = (unsigned char)val;
        }
    }
    // cierra el archivo
    fclose(f);
}

void init(estadojuego* juego){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "webi wabo");
    ToggleFullscreen();

    // valores por defecto
    SetTargetFPS(30);
    juego->soles = 50;
    juego->vida_casa = 1;
    juego->volume = 0.8f;
    juego->zombies_total = 33;
    juego->filtro = WHITE;

    // reemplaza los valores por defecto
    cargar_config(juego);
    // arregla los casos de valores bajo/sobre el limite
    if (juego->vida_casa < 1) juego->vida_casa = 1;
    if (juego->zombies_total < 1) juego->zombies_total = 1;
    if (juego->zombies_total > 33) juego->zombies_total = 33;
    if (juego->vida_casa > juego->zombies_total) juego->vida_casa = juego->zombies_total;
    // valores no configurables
    juego->vida_casa_inicial = juego->vida_casa;
    juego->zombies_spawned = 0;
    juego->ticks = 0;
    juego->partida = PARTIDA_JUGANDO;
    // oleadas
    juego->ticks_oleada_actual = 0;
    juego->oleada_actual = 0;
    juego->c_intervalo = 0;
    juego->zombie_kills = 0;
    // semillas
    juego->selected_seed = 0;
    // semillas seleccionadas por defecto
    juego->seed_slot[0] = 1;
    juego->seed_slot[1] = 2;
    juego->seed_slot[2] = 3;
    juego->seed_slot[3] = 4;
    juego->seed_slot[4] = 5;
    // zombies inactivos
    for (int i = 0; i < MAX_ZOMBIES; i++) {
        juego->lista_zombies[i].activo = 0;
    }
    // plantas inactivas
    for (int i = 0; i < MAX_PLANTAS; i++) {
        juego->lista_plantas[i].activo = 0;
    }
    // proyectiles inactivos
    for (int i = 0; i < MAX_PROYECTILES; i++) {
        juego->lista_proyectiles[i].activo = 0;
    }
    // objetos tipo 0
    for (int i = 0; i < MAX_INTERACTUABLES; i++) {
        juego->lista_objetos[i].tipo = 0;
    }
    // cooldown de semillas
    for (int i = 0; i < MAX_SEEDS; i++) {
        juego->seed_cd[i] = 0;
    }
    // carga las texturas
    texture_load(juego);
    // carga la musica
    music_load(juego);
    // carga los efectos de sonido
    sfx_load(juego);
    juego->siren_played = 0;
    juego->losemusic_played = 0;
    juego->winmusic_played = 0;
    // semilla aleatoria
    SetRandomSeed(time(NULL));
}