#include <stdio.h>
#include <string.h> //Para sizeof
#include <stdlib.h>
#include "logic.h"
#include "global.h"


static int zombies_activos(estadojuego* juego){
    int contador = 0;
    for (int i = 0; i < MAX_ZOMBIES; i ++){
        zombie* z_actual = &juego ->lista_zombies[i];
        if (z_actual -> activo){
            contador ++;
        }

    }
    return contador;
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
void waves(estadojuego* juego){
    if (juego -> oleadas_restantes > 0){
        juego -> ticks_oleada_actual --;
        if (juego -> ticks_oleada_actual == 0){
            juego -> fase = FASE_OLEADA;
            juego -> zombies_pendientes = 20; //Temporal
        }
    }
    else{
        juego -> fase = FASE_FIN;
    }

}

void accion_zombies(estadojuego *juego){
    for (int i = 0; i < MAX_ZOMBIES; i++){
        zombie *z = &juego->lista_zombies[i];

        if (z->activo == 0) continue;                    //No hay zombie, pasa el siguiente
        if (juego->ticks % z->velocidad != 0) continue;  // Aun no han pasado suficientes ticks para que actue

        if (z->columna == 0){ //Llego a la casa, por lo tanto se desactiva y resta vida a la casa
            z->activo = 0;
            juego->vida_casa--;
        }
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
    }
}

void comportamiento_plantas(estadojuego* juego) {
    for (int i = 0; i < MAX_PLANTAS; i++) {
        planta* p_actual = &juego->lista_plantas[i];

        if (p_actual->vida > 0) {//La planta debe estar viva
            
            // LANZAGUISANTES
            if (p_actual->tipo == LANZAGUISANTES) {
                
                if (juego->ticks % p_actual->cd == 0) {//Pasaron suficientes clicks para cumplir el cooldown
                    
                    // Disparo: Necesitamos generar un proyectil
                    for (int j = 0; j < MAX_PROYECTILES; j++) {
                        if (juego->lista_proyectiles[j].activo == 0) {
                            juego->lista_proyectiles[j].activo = 1;
                            juego->lista_proyectiles[j].fila = p_actual->fila;
                            juego->lista_proyectiles[j].columna = p_actual->columna + 1; // Nace justo a la derecha del tubo
                            juego->lista_proyectiles[j].dmg = LANZAGUISANTES_DMG;
                            
                            break; //Disparo unico, puedo adaptar la logica del lanza guisantes para por ejemplo una repetidora
                            //O uno de esos que disparan en 3 filas a la vez (Esta sería mas facil) - Adrián
                        }
                    }
                }
            }
            
            //GIRASOL
            else if (p_actual->tipo == GIRASOL) {
                
                if (juego->ticks % p_actual->cd == 0) {//Cooldown
                    juego->soles += SOLES_GIRASOL;
                }
            }
        }
        else{
            p_actual -> activo = 0;
        }
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
    
void resultado(estadojuego* juego){
    if (juego -> vida_casa <= 0){
        juego -> partida = PARTIDA_LOSS;
        return;
    }

    if ((juego -> oleadas_restantes == 0) && (juego -> zombies_pendientes == 0)){
        juego -> partida = PARTIDA_WIN;
        return;
    }
    
}

void iniciar_estado(estadojuego *juego){
    memset(juego, 0, sizeof(estadojuego));
    juego->vida_casa = CASA_HP_INICIAL;
    juego->soles = 50;
    juego->oleadas_restantes = MAX_OLEADAS;
    juego->fase = FASE_PREPARACION;
    juego->ticks_oleada_actual = TICKS_PREPARACION;
}

void update(estadojuego* juego){
    if (juego -> partida != PARTIDA_JUGANDO) return;

    proyectil_update(juego);
    accion_zombies(juego);
    comportamiento_plantas(juego);
    waves(juego); 

    juego -> ticks ++;

    resultado(juego);
}

void sortZombieByRank(estadojuego* juego)
{   
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

