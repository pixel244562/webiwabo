#ifndef GLOBAL_H
#define GLOBAL_H
//Window
#define SCREEN_WIDTH 800+300
#define SCREEN_HEIGHT 440
//Base
#define FILAS 5
#define COLUMNAS 9
#define MAX_PLANTAS ((FILAS) * (COLUMNAS))
#define MAX_ZOMBIES 100
#define MAX_PROYECTILES 200
#define CASA_HP_INICIAL 1
#define SOLES_INICIALES 50
//Zombies
#define Z_DMG 20
//Plantas
#define SOLES_GIRASOL 25
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

typedef struct {
    int tipo; //1: común, 2: cono, 3: cubo, 4: bandera
    int vida;
    char fila;
    char columna;
    char activo;
    char velocidad; //Cada cuantos ticks el zombie ejecuta una acción SIEMPRE OCUPARLO CON VALORES >= 1 o cosas raras podrían pasar
} zombie;

typedef struct{
    int tipo; //3 Lanzaguisantes, 4 girasol, 5 nuez
    int vida;
    char fila;
    char columna;
    int cd;
    char activo;
} planta;

typedef struct{
    int activo;
    int dmg;
    char fila;
    char columna;
} proyectil;

typedef struct{
    int tipo; //0: Cesped, esto puede sernos util para despues añadir obstaculos y más modos de juego - Adrián
    planta* planta_actual;
} casilla;

typedef struct{
    casilla** tablero; //Tarea 1

    //Entidades
    zombie lista_zombies[MAX_ZOMBIES];
    proyectil lista_proyectiles[MAX_PROYECTILES];
    planta lista_plantas[MAX_PLANTAS];

    //Valores generales
    int partida;
    int soles;
    int vida_casa;
    int ticks; //Reloj interno del juego para movimientos, cooldown, etc.

    //Oleadas
    int oleadas_restantes;
    int fase;
    int zombies_pendientes;
    int ticks_oleada_actual;

} estadojuego;
#endif