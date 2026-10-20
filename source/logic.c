#include <stdio.h>

void logic(int tablero[5][9], int soles, int tiempo);
void refresh(int tablero[5][9]);

int main(){ //Espacio de pruebas
    int test[5][9] = {
        {0, 0, 0, 0, 0, 3, 3, 3, 0},
        {0, 0, 0, 0, 0, 0, 3, 0, 3},
        {1, 1, 1, 0, 3, 0, 3, 0, 3},
        {0, 0, 0, 0, 3, 3, 3, 3, 3},
        {0, 0, 0, 0, 0, 0, 3, 3, 3}
}; 
    /*Matriz solo de prueba, considerare provisionalmente
    0 = vacio
    1 = girasol
    2 = lanzaguisantes
    3 = zombie normal
    4 = flagged zombie */
    int suntest = 20;
    int clicks = 0;

    /*Esqueleto para tests si llego a necesitar llenarla mientras se ejecuta
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 9; j++){
            printf("Casilla %d,%d: ", i+1, j+1);
            scanf("%d", &test[i][j]);
        }
    }*/

    refresh(test);
    printf("%d", suntest);

    //Asumimos que paso un segundo, click, instante, etc

    logic(test, suntest, clicks);
    
    refresh(test);
    printf("%d", suntest);

}

void logic(int tablero[5][9], int soles, int tiempo){ 

    //Movimiento 
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 9; j++){
            if (tablero[i][j] == 3){ //Movimiento de zombie
                tablero[i][j-1] = 3;
                tablero[i][j] = 0;
            }
            if (tablero[i][j] == 4){ //Movimiento flagged zombie, temporalmente asumiremos que va de 2 en 2
                tablero[i][j-2] = 4;
                tablero[i][j] = 0;
            }
        }}

}

void refresh(int tablero[5][9]){ //Funcion para imprimir el tablero
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 9; j++){
            printf("%d ", tablero[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}