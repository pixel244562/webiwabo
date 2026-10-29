#include <stdio.h>
#include <raylib.h>
#include <global.h>
#include <visual.h>

void draw(){
    BeginDrawing();
        for(int y = 0; y<FILAS; y++){
            for(int x = 0; x<COLUMNAS; x++){
                DrawRectangle(x*90, y*90, 80, 80, GREEN);
                DrawRectangle(x*90+75, y*90+75, 5, 5, RED);
                DrawRectangle(x*90, y*90, 5, 5, BLUE);
            }
        }
    EndDrawing();
}

