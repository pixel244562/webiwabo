#ifndef GLOBAL_H
#define GLOBAL_H

#include <raylib.h>
//Window
#define SCREEN_WIDTH 800+1120
#define SCREEN_HEIGHT 1080
//Base
#define tile_width 180
#define tile_offset 5
#define move_x 445
#define move_y 150
#define rescale 0.9f // 10% más pequeño

#define FILAS 5
#define COLUMNAS 8
#define MAX_PLANTAS ((FILAS) * (COLUMNAS))
#define MAX_ZOMBIES 50
#define MAX_SEEDS 5
#define MAX_PROYECTILES 100
#define MAX_INTERACTUABLES 20
#define MAX_CANCIONES 2
#define CASA_HP_INICIAL 1
//Estado partida
#define PARTIDA_JUGANDO 0
#define PARTIDA_WIN 1
#define PARTIDA_LOSS 2
//Oleadas
#define MAX_OLEADAS 4
#define TICKS_DESCANSO 30
#define TICKS_PREPARACION 60 //Inicio de partida, tiempo inicial para colocar plantas
#define FASE_PREPARACION 0
#define FASE_OLEADA 1
#define FASE_DESCANSO 2
#define FASE_FIN 3
//CDs de semillas (30 ticks = 1 sec)
#define SHORT_SEED_CD 300
#define MEDIUM_SEED_CD 450
#define LONG_SEED_CD 600

typedef struct {
    int tipo; //1: común, 2: cono, 3: cubo, 4: bandera
    int vida;
    char fila;
    char columna;
    char activo;
    char velocidad; //Cada cuantos ticks el zombie ejecuta una acción SIEMPRE OCUPARLO CON VALORES >= 1 o cosas raras podrían pasar
    float pos_x; // posición exacta (px)
} zombie;

typedef struct{
    int tipo; //1 Lanzaguisantes, 2 girasol, 3 nuez, 4 ajo, 5 plantorcha
    int vida;
    char fila;
    char columna;
    int cd;
    char activo;
} planta;

typedef struct{
    int activo;
    int tipo; // 1 guizante, 2 guizante de fuego
    int dmg;
    char fila; // fila de pasto
    char columna; // columna de pasto
    float pos_x; // posición exacta (px)
} proyectil;

typedef struct{
    int x;
    int y;
    int destino_y;
    int tipo; // 1: sol
    int move; // 0: don't move 1: move
} objeto;

typedef struct{
    //Entidades
    zombie lista_zombies[MAX_ZOMBIES];
    proyectil lista_proyectiles[MAX_PROYECTILES];
    planta lista_plantas[MAX_PLANTAS];
    objeto lista_objetos[MAX_INTERACTUABLES];

    //Texturas
    //  zombies
    Texture2D zombie_texture;
    Texture2D bucket_texture;
    Texture2D cone_texture;
    Texture2D flag_zombie_texture;

    //  varios
    Texture2D lawn_texture;
    Texture2D pea_texture;
    Texture2D fire_pea_texture;
    Texture2D sun_texture;
    Texture2D shovel_texture;
    //  plantas
    Texture2D peashooter_texture;
    Texture2D sunflower_texture;
    Texture2D wall_nut_1_texture;
    Texture2D wall_nut_2_texture;
    Texture2D wall_nut_3_texture;
    Texture2D garlic_texture;
    Texture2D garlic_texture_2;
    Texture2D garlic_texture_3;
    Texture2D torchwood_texture;
    //  semillas
    Texture2D garlic_seed_texture;
    Texture2D peashooter_seed_texture;
    Texture2D sunflower_seed_texture;
    Texture2D torchwood_seed_texture;
    Texture2D wall_nut_seed_texture;

    //Valores generales
    int partida;
    int soles;
    int vida_casa;
    int ticks; //Reloj interno del juego para movimientos, cooldown, etc.

    int ultimo_clic_fila;
    int ultimo_clic_columna;
    Vector2 mouse_pos;
    int selected_seed;
    int seed_slot[MAX_SEEDS];
    int seed_cd[MAX_SEEDS];

    //Oleadas
    int oleada_actual;
    int oleada_previa;
    int fase;
    int ticks_oleada_actual;
    int zombies_coming;
    int c_intervalo;
    int zombie_kills;


    //Musica
    Music backgroundMusic;
    float volume;
    bool pause;
    int cancion_actual;
    const char* playlist[MAX_CANCIONES];

} estadojuego;
#endif