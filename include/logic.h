#ifndef LOGIC_H
#define LOGIC_H

#include "global.h"

void accion_zombies(estadojuego *juego);
void zombie_spawn(int x, int y, int type, estadojuego *juego);
void impacto(zombie * z, proyectil * p, estadojuego *juego);
void comportamiento_plantas(estadojuego* juego);
void proyectil_update(estadojuego * juego);
void update(estadojuego* juego);
void place_plant(int x, int y, int type, estadojuego *juego);
void resultado(estadojuego* juego);
void sortZombieByRank(estadojuego* juego);
int sun_cost( int plant_id, estadojuego* juego);
void waves(int oleadas, estadojuego *juego);
void spawn_sun(int x, int y, int move, estadojuego* juego);
void naturally_spawn_sun(estadojuego *juego);
int get_seed_cd(int tipo);
// sfx
void sfx_load(estadojuego* juego);
void sfx_unload(estadojuego* juego);
#endif
