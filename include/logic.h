#ifndef LOGIC_H
#define LOGIC_H

#include "global.h"

void accion_zombies(estadojuego *juego);
void zombie_spawn(int x, int y, int type, estadojuego *juego);
void impacto(zombie * z, proyectil * p);
void comportamiento_plantas(estadojuego* juego);
void proyectil_update(estadojuego * juego);
void update(estadojuego* juego);
void place_plant(int x, int y, int type, estadojuego *juego);
void resultado(estadojuego* juego);
void sortZombieByRank(estadojuego* juego);
int sun_cost( int plant_id, estadojuego* juego);

#endif
