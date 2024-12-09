#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gameEngineImage.h"
#include "GameEngine.h"
#include "levelEditor.h"

#define ANCHO 800
#define ALTO 800
#define XROW 6
#define YROW 6

GameEngine handle;



int main (){

   
    bool loop = 1;
handle.InicializarSistemas(SDL_INIT_VIDEO);










while(loop==1){

   int result = LevelEditorMain(); 
   if (result == 0) { 
       loop = false; 
       } 
       else { 
           loop = true; 
           }
}


    return 0;
}


/*void MostrarTexturas(){
    for(int i=0;i<XROW;i++){
        for(int a=0;a<YROW;a++){
    handle.MostrarTextura(render, objetos[i][a].textura,objetos[i][a].x0,objetos[i][a].y0,objetos[i][a].w,objetos[i][a].h);
        }
    }
    DibujarGrilla();
}*/

