#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "global.h"

// aun no tengo entendido que valores deben tener los OFFSET, por lo que los dejo en 0 por ahora y el ancho y alto en un valor cualquiera.
#define OFFSET_X 0
#define OFFSET_Y 0
#define ANCHO_CASILLA 100
#define ALTO_CASILLA 100

static int planta_seleccionada = GIRASOL; // la planta estática seleccionada actualmente

// CARGAR ARCHIVO DE CONFIGURACION
int cargar_config(const char *nombre_archivo, estadojuego *juego){
    FILE* archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        return 0; // error al abrir el archivo
    }
    char clave[30];
    int valor;
    // LEE CADA CONFIGURACION EN UN PAR DE CLAVE Y VALOR, Y SE ADHIERE A LA ESTRUCTURA DEL JUEGO
    // aun no tengo claro que configuraciones implementar, dejo la base:
    while (fscanf(archivo, "%s %d", clave, &valor) == 2) {
        if (strcmp(clave, "CONFIGURACION") == 0) {
            juego->configuracion = valor;
        } else if (strcmp(clave, "CONFIGURACION_2") == 0) {
            juego->configuracion2 = valor;
        } else if (strcmp(clave, "CONFIGURACION_3") == 0) {
            juego->configuracion3 = valor;
        }
    }
    fclose(archivo);
    return 1;
}

// ENTRADA DE MOUSE Y TECLAS (beta)
void procesar_entrada(estadojuego* juego){
    // procesa qué planta tiene seleccionada actualmente el jugador
    if (IsKeyPressed(KEY_ONE)){
        planta_seleccionada = GIRASOL;
    }
    if (IsKeyPressed(KEY_TWO)){
        planta_seleccionada = LANZAGUISANTES;
    }
    if (IsKeyPressed(KEY_THREE)){
        planta_seleccionada = NUEZ;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        // obtenemos la posición del mouse
        Vector2 mouse_pos = GetMousePosition();

        // calculo la fila y columna de la casilla donde se hizo click
        int fila = (mouse_pos.y - OFFSET_Y) / ALTO_CASILLA;
        int columna = (mouse_pos.x - OFFSET_X) / ANCHO_CASILLA;

        // verificacion que la casilla esté dentro del tablero
        if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS){
            if (juego->tablero[fila][columna].planta_actual == NULL){

                int costo = 0;
                int vida_inicial = 0;
                int cd_inicial = CD_PLANTA;

                // escribi en este tipo de sintaxys para que sea mas facil el hecho de agregar plantas despues
                switch (planta_seleccionada) {
                    case GIRASOL:
                        costo = COSTO_GIRASOL;
                        vida_inicial = VIDA_GIRASOL;
                        cd_inicial = CD_GIRASOL;
                        break;
                    case LANZAGUISANTES:
                        costo = COSTO_LANZAGUISANTES;
                        vida_inicial = VIDA_LANZAGUISANTES;
                        cd_inicial = CD_LANZAGUISANTES;
                        break;
                    case NUEZ:
                        costo = COSTO_NUEZ;
                        vida_inicial = VIDA_NUEZ;
                        cd_inicial = CD_NUEZ;
                        break;
                    default:
                        return; // porciacaso evita plantar si no se cumple algo
                }

                // verificacion de si hay soles suficientes
                if (juego->soles >= costo){
                    // buscamos un espacio libre
                    for(int i = 0; i < MAX_PLANTAS; i++){
                        if(juego->lista_plantas[i].activo == 0){
                            juego->lista_plantas[i].tipo = planta_seleccionada;
                            juego->lista_plantas[i].fila = fila;
                            juego->lista_plantas[i].columna = columna;
                            juego->lista_plantas[i].vida = vida_inicial;
                            juego->lista_plantas[i].cd = cd_inicial;
                            juego->lista_plantas[i].activo = 1;
                            juego->tablero[fila][columna].planta_actual = &juego->lista_plantas[i];
                            //se reduce la cantidad de soles disponibles
                            juego->soles -= costo;
                            break;
                        }
                    }
                }
            }
        }
    }
}