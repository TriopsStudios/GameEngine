#ifndef GAMEENGINE_H 
#define GAMEENGINE_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gameEngineImage.h"
//#include "SDL_ttf.h"
class GameEngine
{
private:
	
	SDL_Surface* surface;
	SDL_Window* window;
	SDL_Surface* image;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	int iAlto; //ImagenAlto
	int iAncho; //ImagenAncho

	

public:
	void InicializarSistemas(Uint32);
	SDL_Window* CrearVentana(std::string, int, int, int, int, Uint32);
	SDL_Surface* CrearSurface(SDL_Window*);
	void ColorearRectangulo(SDL_Surface*, int, int, int);
	void Close(SDL_Window*);
	void LimpiarSurface(SDL_Surface*);
	SDL_Surface* CargarImagen(const char*,SDL_Surface*);
	SDL_Surface* CargarImagenSDLImage(std::string, SDL_Surface*);
	void MostrarImagen(SDL_Surface*, const SDL_Rect*, SDL_Surface*, SDL_Rect*);
	SDL_Renderer* CrearRenderer(SDL_Window*, int, Uint32);
	SDL_Texture* CargarTextura(std::string, SDL_Renderer*);
	SDL_Texture* CargarTextura(std::string, SDL_Renderer*, int, int, int); //Sobrecarga para aplicar transparencia
	void MostrarTextura(SDL_Renderer*, SDL_Texture*, int, int,int,int); //Los dos ultimos parametros son para la posicion
	void MostrarTexturaConViewport(SDL_Renderer*, SDL_Texture*, SDL_Rect*);
	void MostrarImagenAjustada(SDL_Surface*, SDL_Surface*, SDL_Rect );
	void CrearRectangulo(SDL_Rect, int, int, int, int, SDL_Renderer*, Uint8, Uint8, Uint8, Uint8);
     void RefrescarRender(SDL_Renderer* renderer);
       void LimpiarRender(SDL_Renderer* renderer);
    void RefrescarRender(SDL_Renderer* renderer, void (*func)());//Refrescar render con la llamada a MostrarTextura
    void DibujarLinea(SDL_Renderer*, int, int,int, int);

	GameEngine();
	~GameEngine();
};

#endif