#ifndef GLOBAL_H
#define GLOBAL_H

#define FILAS 5
#define COLUMNAS 9
#define MAX_ZOMBIES 100
#define MAX_PROYECTILES 200
#define Z_DMG 20
#define MAX_PLANTAS (FILAS * COLUMNAS)
#define GIRASOL 3
#define LANZAGUISANTES 4
#define SOLES_GIRASOL 25

typedef struct {
    int tipo; //1: común, 2: cono, 3: cubo, 4: bandera
    int vida;
    char fila;
    char columna;
    char activo;
    char velocidad; //Cada cuantos ticks el zombie ejecuta una acción SIEMPRE OCUPARLO CON VALORES >= 1 o cosas raras podrían pasar
} zombie;

typedef struct{
    int tipo; //3 Lanzaguisantes, 4 girasol, 5 papa
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
    int soles;
    int vida_casa;
    int oleada;
    int ticks; //Reloj interno del juego para movimientos, cooldown, etc.

} estadojuego;
#endif