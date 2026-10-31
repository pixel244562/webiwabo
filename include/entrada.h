#ifndef ENTRADA_H
#define ENTRADA_H

#include "global.h"

int cargar_config(const char* nombre_archivo, estadojuego* juego);
void procesar_entrada(estadojuego* juego);
int cargar_mapa(const char* nombre_archivo, estadojuego* juego);

#endif