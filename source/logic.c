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
                            juego->lista_proyectiles[j].dmg = 20;
                            
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
    }
}

void proyectil_update(){

}