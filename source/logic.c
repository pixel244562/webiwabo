#include <stdio.h>
#include <global.h>

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
        
        if(z->columna > 0){
            z->columna--;
        }
        if (z->columna == 0){ //Llego a la casa, por lo tanto se desactiva y resta vida a la casa
        z->activo = 0;
        juego->vida_casa--;
        }
    } 
    
    /*
    
    else { //Intenta actuar o moverse
        casilla *delante = &juego->tablero[z->fila][z->columna - 1]; //Puntero para la casilla siguiente

        if (delante->planta_actual != NULL){//Si hay planta al frente, el zombie empezará a comersela
            delante->planta_actual->vida -= Z_DMG;

            if (delante->planta_actual->vida <= 0){//Termina de comersela
                delante->planta_actual = NULL; 
            }
        }
        else {
            z->columna--;//Avanza una celda
        }
    }
    */
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
                        if(z->activo && z->fila == p_actual->fila){
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
        case 1:
            juego->lista_zombies[id].vida = 100;
            juego->lista_zombies[id].velocidad = 70;
            break;
        case 2:
            juego->lista_zombies[id].vida = 150;
            juego->lista_zombies[id].velocidad = 70;
            break;
    }
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
    switch(type){ // 1 Lanzaguisantes, 2 girasol, 3 papa
        case 1: 
            juego->lista_plantas[id].vida = 100;
            juego->lista_plantas[id].cd = 30;
            break;
        case 2:
            juego->lista_plantas[id].vida = 150;
            juego->lista_plantas[id].cd = 60;
            break;
    }
}

void proyectil_update(estadojuego * juego){

    for (int i = 0; i < MAX_PROYECTILES; i++){

        proyectil* proyectil_actual = &juego ->lista_proyectiles[i];

        if (proyectil_actual->activo == 0) continue;
        
        //MOVIMIENTO
        proyectil_actual -> columna ++;


        if (proyectil_actual -> columna >= COLUMNAS){
            proyectil_actual -> activo = 0;
            continue;
        }

        //IMPACTO
        for (int j= 0; j < MAX_ZOMBIES; j ++){
            zombie* zombie_actual = &juego -> lista_zombies[j];

            //Chequeo activo

            if (zombie_actual -> activo == 0) continue;

            //Chequeo ubicacion

            if ((zombie_actual -> columna != proyectil_actual -> columna) ||
             (zombie_actual -> fila != proyectil_actual -> fila)) continue;

            impacto(zombie_actual, proyectil_actual);
            break;
        }
    }
}

void update(estadojuego* juego){
    //if (juego -> partida != PARTIDA_JUGANDO) return;

    proyectil_update(juego);
    accion_zombies(juego);
    comportamiento_plantas(juego);
    //waves(juego); 

    juego -> ticks++;
    if(juego->ticks>1000)
        juego->ticks=0;

    //resultado(juego);
}