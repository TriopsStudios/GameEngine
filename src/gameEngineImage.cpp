#include "gameEngineImage.h"
#include "GameEngine.h"



gameEngineImage::gameEngineImage()
{
	int ancho = 0;
	int alto = 0;
	image = NULL;
	texture = NULL;
}


gameEngineImage::~gameEngineImage()
{
}

void gameEngineImage::setAltoImagen(int y) {
	alto = y;
}

void gameEngineImage::setAnchoImagen(int x) {
	ancho = x;
}

//********************************************************************************************************************//
//***************************GEICargarTextura y sobrecargas***********************************************************//
//********************************************************************************************************************//

//Carga una imagen a traves de IMG_Load y la convierte en una textura. Devuelve la textura.
void gameEngineImage::GEICargarTextura(std::string file, SDL_Renderer* renderer) {
	image = IMG_Load(file.c_str());
	if (image == NULL) {
		std::cout << "ERROR SDL IMAGE en CargarTextura: No se pudo cargar la imagen: ", file, IMG_GetError();
	}
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (texture == NULL) {
		std::cout << "ERROR en SDL_CreateTextureFromSurface: No se pudo cargar la imagen: ", SDL_GetError();
	}

	alto = image->h;
	ancho = image->w;

	SDL_FreeSurface(image);
}

//Carga textura y aplica transparencia
void gameEngineImage::GEICargarTextura(std::string file, SDL_Renderer* renderer, int r, int g, int b) {
	image = IMG_Load(file.c_str());
	if (image == NULL) {
		std::cout << "ERROR SDL IMAGE en CargarTextura: No se pudo cargar la imagen: ", file, IMG_GetError();
	}

	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, r, g, b));


	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (texture == NULL) {
		std::cout << "ERROR en SDL_CreateTextureFromSurface: No se pudo cargar la imagen: ", SDL_GetError();
	}
	alto = image->h;
	ancho = image->w;
	SDL_FreeSurface(image);
}
//*******************************************************************************************************************//
//*******************************************************************************************************************//
//*******************************************************************************************************************//


//*******************************************************************************************************************//
//*************************GEIMostrarTextura y sobrecargas***********************************************************//
//*******************************************************************************************************************//
void gameEngineImage::GEIMostrarTexturaConViewport(SDL_Renderer* renderer, SDL_Rect* viewport) {
	//SDL_RenderClear(renderer);
	if (SDL_RenderSetViewport(renderer, viewport) < 0) {
		std::cout << "ERROR en RenderSetViewport (MostrarTexturaConViewport)", SDL_GetError(), "\n";
	}
	//Render texture to screen
	else SDL_RenderCopy(renderer, texture, NULL, NULL);
}

//GEIMostrarTextura[1]int x, int y, el ancho y el alto son los propios de la imagen
void gameEngineImage::GEIMostrarTextura(SDL_Renderer* renderer, int x, int y) {
	//SDL_RenderClear(renderer);
	SDL_Rect renderRect = { x, y, ancho, alto };
	//Render texture to screen
	SDL_RenderCopy(renderer, texture, NULL, &renderRect);

}  

//GEIMostrarTextura[1.2]int x, int y, el ancho y el alto son los propios de la imagen. Puede hacler clip rendering
void gameEngineImage::GEIMostrarTextura(SDL_Renderer* renderer, int x, int y, SDL_Rect* rect) {
	//SDL_RenderClear(renderer);
	SDL_Rect renderRect = { x, y, ancho, alto };
	//Render texture to screen
	SDL_RenderCopy(renderer, texture, rect, &renderRect);

}  
//GEIMostrarTexturaS[2]: int x, int y, int w, int h
void gameEngineImage::GEIMostrarTextura(SDL_Renderer* renderer, int x, int y, int w, int h) {
	//SDL_RenderClear(renderer);
	SDL_Rect renderRect = { x, y, w, h };
	//Render texture to screen
	SDL_RenderCopy(renderer, texture, NULL, &renderRect);

}

//GEIMostrarTexturas[2.2]: Puede hacer clip rendering
void gameEngineImage::GEIMostrarTextura(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Rect* rect) {
	//SDL_RenderClear(renderer);
	SDL_Rect renderRect = { x, y, w, h };
	//Render texture to screen
	SDL_RenderCopy(renderer, texture, rect, &renderRect);

}

//GEIMostrarTextura[3]: Tiene todas las funcionalidades de [2.2] y ademas puede rotar y voltear
//Para esta anterior funcion si se desea no modificar el ancho, el alto o hacer clipping, dejar estos valores en NULL
void gameEngineImage::GEIMostrarTextura(SDL_Renderer* renderer, int x, int y, int w, int h,SDL_Rect* rectClip, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
	SDL_Rect renderRect = {0,0,0,0};

	if (w == 0 && h == 0) {
		w = ancho;
		h = alto;
		SDL_Rect renderRect = { x,y, ancho, alto };
		SDL_RenderCopyEx(renderer, texture, rectClip, &renderRect, angle, center, flip);
	}
	else { 
		
		SDL_Rect renderRect = { x,y,w,h }; 
	
		SDL_RenderCopyEx(renderer, texture, rectClip, &renderRect, angle, center, flip);
	}

	
	
	
}




//******************************************************************************************************************//
//******************************************************************************************************************//
//******************************************************************************************************************//

void gameEngineImage::GEIfree(){

	SDL_DestroyTexture(texture);

}

//Modula el color de una textura. Debe ser llamada anters de la funcion para mostrar la textura
void gameEngineImage::GEIModularColor(Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetTextureColorMod(texture, r, g, b);
	
}

SDL_Texture* gameEngineImage::GetTexture() {
	return texture;
}

void gameEngineImage::SetModoBlend() {
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void gameEngineImage::AplicarAlphaBlending(Uint8 cantidadAlpha) {
	SDL_SetTextureAlphaMod(texture, cantidadAlpha);
}