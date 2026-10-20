#include <stdio.h>

void logic(int tablero[5][9], int soles);
void refresh(int tablero[5][9]);

int main(){ //Espacio de pruebas
    int test[5][9]; 
    /*Matriz solo de prueba, considerare provisionalmente
    0 = vacio
    1 = girasol
    2 = lanzaguisantes
    3 = zombie normal
    4 = flagged zombie */
    int suntest = 20;

    //Esqueleto para tests
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 9; j++){
            printf("Casilla %d,%d: ", i+1, j+1);
            scanf("%d", &test[i][j]);
        }
    }

    refresh(test);

    //Asumimos que paso un segundo, click, instante, etc

    logic(test, suntest);
    
    refresh(test);

}

void logic(int tablero[5][9], int soles){ 

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