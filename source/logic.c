#include <stdio.h>
#include <global.h>

void resultado(estadojuego* juego){
    if (juego -> vida_casa <= 0){
        juego -> partida = PARTIDA_LOSS;
    }
}

void sortZombieByRank(estadojuego* juego){   
    zombie* z_arr = juego -> lista_zombies;
    zombie aux;
    int i, j;

    for (i = 1; i < MAX_ZOMBIES; i++) {
        /* Si ya esta en su posicion, se salta sin copiar nada */
        if (z_arr[i - 1].fila <= z_arr[i].fila)
            continue;

        aux = z_arr[i];
        j = i - 1;

        while (j >= 0 && z_arr[j].fila > aux.fila) {
            z_arr[j + 1] = z_arr[j];
            j--;
        }
        z_arr[j + 1] = aux;
    }
}

void impacto(zombie * z, proyectil * p){
    /*impacto:
    Funcion que dado un zombie z y un proyectil p, resta
    a la vida del zombie el daño infligido por el proyectil
    */
    z -> vida -= p -> dmg;

    if (z -> vida <= 0){
        z -> activo = 0; //Zombie x_x - Adrián
    }
    p -> activo = 0; //El proyectil se va por cigarrillos
}

void accion_zombies(estadojuego *juego){
    for(int i = 0; i < MAX_ZOMBIES; i++){
        zombie *z = &juego->lista_zombies[i];

        if(z->activo == 0) continue; //No hay zombie, pasa el siguiente
        if(juego->ticks % z->velocidad != 0) continue; // Aun no han pasado suficientes ticks para que actue

        if (z->columna == 0){ //Llego a la casa, por lo tanto se desactiva y resta vida a la casa
            z->activo = 0;
            juego->vida_casa--;
        } 
        else { //Intenta actuar o moverse
            planta *plant = NULL;
            for (int p_id = 0; p_id < MAX_PLANTAS; p_id++) {
                planta *p = &juego->lista_plantas[p_id];
                if (p->activo && p->fila == z->fila && p->columna == z->columna - 1) {
                    plant = p;
                    break;
                }
            }

            if (plant != NULL) { // Si hay planta al frente, la empieza a comer
                plant->vida -= Z_DMG;

                if (plant->vida <= 0) { // Termina de comérsela
                    plant->activo = 0;
                }
            }
            else
                z->columna--; // Avanza una celda

        }
    }
}


void comportamiento_plantas(estadojuego* juego) {
    for (int i = 0; i < MAX_PLANTAS; i++) {
        planta* p_actual = &juego->lista_plantas[i];

        if (p_actual->vida > 0) {//La planta debe estar viva
            
            // LANZAGUISANTES
            if (p_actual->tipo == 1) {
                
                if (juego->ticks % p_actual->cd == 0) {//Pasaron suficientes clicks para cumplir el cooldown
                    // ¿ Hay zombie al que disparar ?
                    int shoot_signal = 0;
                    for(int id = 0; id<MAX_ZOMBIES; id++){
                        zombie *z = &juego->lista_zombies[id];
                        if(z->activo && z->fila == p_actual->fila && z->columna < COLUMNAS){
                            shoot_signal = 1;
                            break;
                        }
                    }
                    // Disparo: Necesitamos generar un proyectil
                    if(shoot_signal == 1){
                        for(int j = 0; j < MAX_PROYECTILES; j++) {
                            if (juego->lista_proyectiles[j].activo == 0) {
                                juego->lista_proyectiles[j].activo = 1;
                                juego->lista_proyectiles[j].fila = p_actual->fila;
                                juego->lista_proyectiles[j].columna = p_actual->columna + 1; // Nace justo a la derecha del tubo
                                juego->lista_proyectiles[j].dmg = 20;
                            
                                break; //Disparo unico, puedo adaptar la logica del lanza guisantes para por ejemplo una repetidora
                                //O uno de esos que disparan en 3 filas a la vez (Esta sería mas facil) - Adrián
                            }
                        }
                        
                    }
                    
                }
            }
            
            //GIRASOL
            else if (p_actual->tipo == 2) {
                
                if (juego->ticks % p_actual->cd == 0) {//Cooldown
                    juego->soles += SOLES_GIRASOL;
                }
            }
        }
        else
            p_actual->activo = 0;
    }
}

void zombie_spawn(int x, int y, int type, estadojuego *juego){
    int id;
    // encuentra el primero espacio inactivo
    for(int i = 0; i < MAX_ZOMBIES; i++){
        zombie *z = &juego->lista_zombies[i];
        if(z->activo == 0){
            id = i;
            break;
        }
    }

    juego->lista_zombies[id].activo = 1;
    juego->lista_zombies[id].tipo = type;
    juego->lista_zombies[id].fila = y;
    juego->lista_zombies[id].columna = x;
    // define las caracteristicas de cada tipo de zombie
    switch(type){
        case 1: // regular zombie
            juego->lista_zombies[id].vida = 100;
            juego->lista_zombies[id].velocidad = 100;
            break;
        case 2: // cone head
            juego->lista_zombies[id].vida = 150;
            juego->lista_zombies[id].velocidad = 100;
            break;
        case 3: // bucket head
            juego->lista_zombies[id].vida = 200;
            juego->lista_zombies[id].velocidad = 100;
            break;
        case 4: // flag
            juego->lista_zombies[id].vida = 100;
            juego->lista_zombies[id].velocidad = 70;
            break;

    }
    sortZombieByRank(juego);
}

void place_plant(int x, int y, int type, estadojuego *juego){
    int id;
    // encuentra el primero espacio inactivo
    for(int i = 0; i < MAX_PLANTAS; i++){
        planta *p = &juego->lista_plantas[i];
        if(p->activo == 0){
            id = i;
            break;
        }
    }
    juego->lista_plantas[id].activo = 1;
    juego->lista_plantas[id].tipo = type;
    juego->lista_plantas[id].fila = y;
    juego->lista_plantas[id].columna = x;
    // define las caracteristicas de cada tipo de planta
    switch(type){ // 1 Lanzaguisantes, 2 girasol, 3 nuez
        case 1: 
            juego->lista_plantas[id].vida = 100;
            juego->lista_plantas[id].cd = 60;
            break;
        case 2:
            juego->lista_plantas[id].vida = 100;
            juego->lista_plantas[id].cd = 90;
            break;
        case 3:
            juego->lista_plantas[id].vida = 200;
            juego->lista_plantas[id].cd = 0;
            break;
    }
}

void proyectil_update(estadojuego * juego){

    for (int i = 0; i < MAX_PROYECTILES; i++){

        proyectil* proyectil_actual = &juego ->lista_proyectiles[i];

        if (proyectil_actual->activo == 0) continue;
        
        //IMPACTO
        for (int j= 0; j < MAX_ZOMBIES; j ++){
            zombie* zombie_actual = &juego -> lista_zombies[j];

            if (zombie_actual -> activo == 0) continue; // ¿Zombie activo?
            if (zombie_actual->fila != proyectil_actual->fila) continue; // ¿Igual fila?
            if (zombie_actual->columna == proyectil_actual->columna) { // ¿Igual columa?
                impacto(zombie_actual, proyectil_actual); // impacta
                break;
            }
        }

        if (proyectil_actual->activo == 0) continue;
        
        //MOVIMIENTO
        proyectil_actual -> columna ++;


        if (proyectil_actual -> columna >= COLUMNAS){
            proyectil_actual -> activo = 0;
            continue;
        }

        
    }
}

void waves(int oleadas, estadojuego* juego){
    int tiempo_oleada;
    if(juego->oleada_actual == 0){
        tiempo_oleada = 250;
    }
    else
        tiempo_oleada = 700;
    if (juego -> oleada_actual <= oleadas){
        juego -> ticks_oleada_actual++;
        if (juego -> ticks_oleada_actual >= tiempo_oleada){
            // void zombie_spawn(int x, int y, int type, estadojuego *juego);
            // int GetRandomValue(int min, int max); Get a random value between min and max (both included)
            // 1 zombie bandera
            zombie_spawn(
                GetRandomValue(9,15), // x
                GetRandomValue(0,4), // y
                4, // flag zombie
                juego
            );
            for(int i=0; i<5; i++){
                zombie_spawn(
                    GetRandomValue(9,15), // x
                    GetRandomValue(0,4), // y
                    GetRandomValue(1,3), // type
                    juego
                );
            }
            juego->ticks_oleada_actual = 0;
            juego->oleada_actual++;
        }
    }
}

int sun_cost( int plant_id, estadojuego* juego){
    int coste;
    switch(plant_id){
        case 1: // peashooter
            coste = 100; break;
        case 2: // sunflower
            coste = 50; break;
        case 3: // wall-nut
            coste = 50; break;
        case 4: // garlic
           coste = 50; break;
        default:
            coste = 0;
    }
    if(juego->soles < coste){
        // coste negativo se interpreta como insuficiente
        coste = -1;
    }
    else
        juego->soles = juego->soles-coste;
    return coste;
}


void update(estadojuego* juego){
    //if (juego -> partida != PARTIDA_JUGANDO) return;

    proyectil_update(juego);
    accion_zombies(juego);
    comportamiento_plantas(juego);
    waves(4,juego);
    resultado(juego);
    juego -> ticks++;
}
