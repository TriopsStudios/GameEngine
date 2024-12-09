#pragma once
#include "GameEngine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class gameEngineImage
{

private:
	int ancho;
	int alto;
	SDL_Surface* image;
	SDL_Texture* texture;

public:
	gameEngineImage();
	~gameEngineImage();
	void setAnchoImagen(int);
	void setAltoImagen(int);
	void GEICargarTextura(std::string, SDL_Renderer*); //GEICargarTextura[1] Carga una textura
    void GEICargarTextura(std::string, SDL_Renderer*, int, int, int); //GEICargarTextura[2]Sobrecarga para aplicar transparencia
	void GEIMostrarTextura(SDL_Renderer*, int, int); //GEIMostrarTextura[1]int x, int y, el ancho y el alto son los propios de la imagen
	void GEIMostrarTextura(SDL_Renderer*, int, int, SDL_Rect*); //GEIMostrarTextura[1.2]int x, int y, el ancho y el alto son los propios de la imagen. Puede hacler clip rendering
	void GEIMostrarTextura(SDL_Renderer*, int, int, int, int); //GEIMostrarTexturaS[2]: int x, int y, int w, int h
	void GEIMostrarTextura(SDL_Renderer*, int, int, int, int, SDL_Rect*); //GEIMostrarTextura[2.2]: Puede hacer clip rendering
	void GEIMostrarTextura(SDL_Renderer*, int, int, int, int, SDL_Rect*, const double, const SDL_Point*, const SDL_RendererFlip);//GEIMostrarTextura[3]: Tiene todas las funcionalidades de [2.2] y ademas puede rotar y voltear
	//Para esta anterior funcion si se desea no modificar el ancho, el alto o hacer clipping, dejar estos valores en NULL
	

	void GEIMostrarTexturaConViewport(SDL_Renderer*, SDL_Rect*);
	void GEIModularColor(Uint8, Uint8, Uint8);
	void GEIfree();
	void SetModoBlend(); //Setea el modo alpha en una imagen
	void AplicarAlphaBlending(Uint8); //Aplica el alpha blending a una imagen con modo alpha
	SDL_Texture* GetTexture();
	
	
};

