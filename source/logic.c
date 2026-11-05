#include <stdio.h>
#include <global.h>

void resultado(estadojuego* juego){
    if (juego -> vida_casa <= 0){
        juego -> partida = PARTIDA_LOSS;
        }
    if (juego -> zombie_kills == 33){
        juego -> partida = PARTIDA_WIN;
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

void impacto(zombie * z, proyectil * p, estadojuego *juego){
    /*impacto:
    Funcion que dado un zombie z y un proyectil p, resta
    a la vida del zombie el daño infligido por el proyectil
    */
    z -> vida -= p -> dmg;

    if (z -> vida <= 0){
        z -> activo = 0; //Zombie x_x - Adrián
        juego->zombie_kills++;
    }
    p -> activo = 0; //El proyectil se va por cigarrillos
}

void accion_zombies(estadojuego *juego){
    for(int i = 0; i < MAX_ZOMBIES; i++){
        zombie *z = &juego->lista_zombies[i];

        if(z->activo == 0) continue; //No hay zombie, pasa el siguiente
        
        if(z->columna == 0){ //Llego a la casa, por lo tanto se desactiva y resta vida a la casa
            z->activo = 0;
            juego->vida_casa--;
        } 
        else{ //Intenta actuar o moverse
            planta *plant = NULL;
            for(int p_id = 0; p_id < MAX_PLANTAS; p_id++){
                planta *p = &juego->lista_plantas[p_id];
                if(p->activo && p->fila == z->fila){

                    float p_pos_x = (float)((p->columna * (tile_width + tile_offset)) + move_x - 100);
                    // comprueba que el zombie esté a la derecha y sea menor a distancia x de la planta + el margen
                    if (z->pos_x >= p_pos_x && z->pos_x <= p_pos_x + tile_width + 60.0f) {
                        plant = p;
                        break;
                    }
                }
            }

            if (plant != NULL) { // Si hay planta al frente, la empieza a comer
                if(juego->ticks % z->velocidad == 0){
                    plant->vida -= 20;
                    if (plant->tipo== 4){
                        if(z->fila == 0){
                            z->fila = 1;
                        }
                        else if(z->fila == 4){
                            z->fila = 3;
                        }
                        else{
                            z->fila += GetRandomValue(0, 1) * 2 - 1; // -1 o 1
                        }
                        z->pos_x-= 100; // el zombie se mueve más adelante para evitar maldad y abuso
                    }

                    if (plant->vida <= 0) { // Termina de comérsela
                        plant->activo = 0;
                    }
                }
                
            }
            else{
                if(z->tipo == 4){
                    z->pos_x -= 0.70f;
                }
                else{
                    z->pos_x -= 0.50f;
                }
                z->columna = (int)((z->pos_x - move_x + 100) / (tile_width + tile_offset));
            }

        }
    }
}

void spawn_sun(int x, int y, int move, estadojuego* juego){
    for(int i = 0; i < MAX_INTERACTUABLES; i++){
        objeto *obj = &juego->lista_objetos[i];
        // encuentra un espacio disponible
        if(obj->tipo == 0){
            if(move == 1){
                obj->move = 1; // el sol tiene que caer
                obj->destino_y = (y*(tile_width+tile_offset))+(tile_width/2)+move_y-85;
                obj->y = -300;
            }
            else{
                obj->move = 0; // sol estático
                obj->y = (y*(tile_width+tile_offset))+(tile_width/2)+move_y-85;
            }
            obj->tipo = 1; // asigna como sol
            obj->x = x;
            break;
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
                            proyectil *proyectil_actual = &juego->lista_proyectiles[j];
                            if (proyectil_actual->activo == 0) {
                                proyectil_actual->tipo = 1;
                                proyectil_actual->activo = 1;
                                proyectil_actual->fila = p_actual->fila;
                                proyectil_actual->pos_x = (float)((p_actual->columna * (tile_width + tile_offset)) + move_x);
                                proyectil_actual->columna = p_actual->columna; // Inicializamos su columna lógica
                                proyectil_actual->dmg = 20;
                            
                                break; //Disparo unico, puedo adaptar la logica del lanza guisantes para por ejemplo una repetidora
                                //O uno de esos que disparan en 3 filas a la vez (Esta sería mas facil) - Adrián
                            }
                        }
                        
                    }
                    
                }
            }
            
            //GIRASOL
            else if (p_actual->tipo == 2) {
                if (p_actual->cd == 0) {//Cooldown
                    spawn_sun(p_actual->columna, p_actual->fila, 0, juego);
                    p_actual->cd = 700;
                }
                p_actual->cd--;
            }
        }
        else
            p_actual->activo = 0;
    }
}

void zombie_spawn(int x, int y, int type, estadojuego *juego){
    int id = -1;
    // encuentra el primero espacio inactivo
    for(int i = 0; i < MAX_ZOMBIES; i++){
        zombie *z = &juego->lista_zombies[i];
        if(z->activo == 0){
            id = i;
            break;
        }
    }
    // si no encuentra espacio, ignora
    if(id == -1)
        return;
    zombie* z = &juego->lista_zombies[id];
    z->activo = 1;
    z->tipo = type;
    z->fila = y;
    z->columna = x;
    z->pos_x = (float)((x * (tile_width + tile_offset)) + move_x - 100);
    // define las caracteristicas de cada tipo de zombie
    switch(type){
        case 1: // regular zombie
            z->vida = 200;
            z->velocidad = 20;
            break;
        case 2: // cone head
            z->vida = 580;
            z->velocidad = 20;
            break;
        case 3: // bucket head
            z->vida = 900;
            z->velocidad = 20;
            break;
        case 4: // flag
            z->vida = 200;
            z->velocidad = 20;
            break;

    }
    sortZombieByRank(juego);
}

static void seed_cd_update(estadojuego*juego){
    for (int i = 0; i < MAX_SEEDS; i ++){
        if (juego->seed_cd[i] > 0){
            juego->seed_cd[i] --;
        }
    }
}

int get_seed_cd(int tipo){
    //Retorna los ticks de CD de cada planta
    switch(tipo){
        case 1: return SHORT_SEED_CD; //Lanzaguisantes
        case 2: return SHORT_SEED_CD; //Girasol 
        case 3: return LONG_SEED_CD; //Nuez
        default: return MEDIUM_SEED_CD;
    }
}

void place_plant(int x, int y, int type, estadojuego *juego){
    int id = -1;
    // encuentra el primero espacio inactivo
    for(int i = 0; i < MAX_PLANTAS; i++){
        planta *p = &juego->lista_plantas[i];
        if(p->activo == 0){
            id = i;
            break;
        }
    }
    if(id == -1)
        return;
    juego->lista_plantas[id].activo = 1;
    juego->lista_plantas[id].tipo = type;
    juego->lista_plantas[id].fila = y;
    juego->lista_plantas[id].columna = x;
    juego->seed_cd[type-1] = get_seed_cd(type);
    // define las caracteristicas de cada tipo de planta
    switch(type){ // 1 Lanzaguisantes, 2 girasol, 3 nuez, 4 ajo, 5 plantorcha
        case 1: 
            juego->lista_plantas[id].vida = 100;
            juego->lista_plantas[id].cd = 75;
            break;
        case 2:
            juego->lista_plantas[id].vida = 100;
            juego->lista_plantas[id].cd = 700;
            break;
        case 3:
            juego->lista_plantas[id].vida = 1440;
            juego->lista_plantas[id].cd = 0;
            break;
        case 4:
            juego->lista_plantas[id].vida = 400;
            juego->lista_plantas[id].cd = 0;
            break;
        case 5:
            juego->lista_plantas[id].vida = 100;
            juego->lista_plantas[id].cd = 0;
    }
}

void proyectil_update(estadojuego * juego){

    for (int i = 0; i < MAX_PROYECTILES; i++){

        proyectil* proyectil_actual = &juego ->lista_proyectiles[i];

        if (proyectil_actual->activo == 0) continue;
        
        /*MOVIMIENTO
        Primero, cambia la posición en pixeles,
        luego, es transformado a posición en columnas del tablero tipo entero.
        */
        proyectil_actual->pos_x += 14.0f;
        proyectil_actual->columna = (int)((proyectil_actual->pos_x - move_x + 100) / (tile_width + tile_offset));
        for(int id = 0; id < MAX_PLANTAS; id++){
            planta *p = &juego->lista_plantas[id];
            if(p->activo &&
                p->tipo == 5 &&
                p->fila == proyectil_actual->fila &&
                p->columna == proyectil_actual->columna){
                
                proyectil_actual->tipo = 2;
                proyectil_actual->dmg = 40;
                break;
            }
        }
        //IMPACTO
        for (int j= 0; j < MAX_ZOMBIES; j ++){
            zombie* zombie_actual = &juego -> lista_zombies[j];

            if (zombie_actual-> activo == 0) continue; // ¿Zombie activo?
            if (zombie_actual->fila != proyectil_actual->fila) continue; // ¿Igual fila?
            if (zombie_actual->columna == proyectil_actual->columna) { // ¿Igual columa?
                impacto(zombie_actual, proyectil_actual, juego); // impacta
                proyectil_actual -> activo = 0;
                break;
            }
        }

        if (proyectil_actual->activo == 0) continue;
        
        if (proyectil_actual -> columna >= COLUMNAS){
            proyectil_actual -> activo = 0;
            continue;
        }

        
    }
}

/*
static int elegir_tipo_zombie(int num_oleada){
    //Devuelve:
    //1 -> Zombie normal
    //2 -> Zombie con cono
    //3 -> Zombie con cubeta
    
    int porc_especial;
    int porc_cubeta;
    
    //Primero, cada oleada, la probabilidad de que spawnee un zombie especial(Con cubeta o cono, por ahora) va aumentando
    if (num_oleada < 1){
        porc_especial = 10;
    }
    else{
        porc_especial = 20 + 15 * (num_oleada - 1);
    }
    if(porc_especial > 80){ //El maximo porcentajes de especiales lo defini en 80% como maximo
        porc_especial = 80;
    }

    if(GetRandomValue(1, 100) > porc_especial ) return 1; //Primera tirada, ¿es normal o especial?
    //Si arroja un percentil mayor al asignado a los zombies especiales, retorna 1 (Normal)

    //Zombie con cubeta, pasando esa primera tirada, la funcion retornara 2 (Cono) o 3 (Cubeta)
    porc_cubeta = 4 + 4 * num_oleada;
    if (porc_cubeta > 30){
        porc_cubeta = 30;
    }

    if (GetRandomValue(1,100) <= porc_cubeta) return 3; //En una segunda tirada, si cae en el percentil de cubeta, retorna 3(Cubeta)
    return 2; //Sino, retorna 2 (Cono)
}
*/
void waves(int oleadas, estadojuego* juego){
    if (juego->oleada_actual >= oleadas)
        return;
    int cantidad[4] = {5, 7, 9, 12}; // zombies por oleada (33)
    int duracion = 2400;
    int n = cantidad[juego->oleada_actual];
    int intervalo = duracion / n; // distribuye los zombies

    juego->ticks_oleada_actual++;
    if(juego->ticks_oleada_actual % intervalo == 0){

        int x = GetRandomValue(9, 20);
        int y = GetRandomValue(0, 4);

        int tipo;

        // primera oleada
        if(juego->oleada_actual == 0)
            if(juego->c_intervalo != 4)
                tipo = 1;
            else
                tipo = 2;
        // oleadas intermedias
        else if(juego->oleada_actual != 0 && juego->oleada_actual != oleadas-1){
            if(juego->c_intervalo == 0)
                tipo = 4;
            else if(juego->c_intervalo < 4)
                tipo = 2;
            else
                tipo = 3;
        }
        // oleadas finales
        else{
            if(juego->c_intervalo == 0)
                tipo = 4;
            else if(juego->c_intervalo < 2)
                tipo = 1;
            else if(juego->c_intervalo < 6)
                tipo = 2;
            else
                tipo = 3;
        }
        juego->c_intervalo++;
        zombie_spawn(x, y, tipo, juego);
    }
    // si llega a la duración, la oleada termina
    if(juego->ticks_oleada_actual >= duracion){
    juego->ticks_oleada_actual = 0;
    juego->c_intervalo = 0;
    juego->oleada_actual++;
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
        case 5: // torchwood
            coste = 125; break;
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

void naturally_spawn_sun(estadojuego *juego){
    if(juego->ticks%300==299){
        spawn_sun(GetRandomValue(0,7),GetRandomValue(0,4),1,juego);
    }
    // disminuye la y de los soles hasta llegar al destino
    for(int i=0; i<MAX_INTERACTUABLES; i++){
        objeto *obj = &juego->lista_objetos[i];
        if(obj->tipo == 1 && obj->move == 1){ // si es sol y puede moverse
            if(obj->y < obj->destino_y){
                obj->y += 5;
            }
            else{
                obj->y = obj->destino_y;
                obj->move = 0;
            }
        }
    }
}


void update(estadojuego* juego){
    //if (juego -> partida != PARTIDA_JUGANDO) return;

    proyectil_update(juego);
    accion_zombies(juego);
    comportamiento_plantas(juego);
    waves(4,juego);
    naturally_spawn_sun(juego);
    seed_cd_update(juego);
    resultado(juego);
    juego -> ticks++;
}
