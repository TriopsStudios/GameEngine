//GameEngine es una libreria para la simplificacion del uso de SDL2//
//Creada por Alejandro Martinez de TRIOPS STUDIOS//
//2022
#include "GameEngine.h"
#include <string>
#include "gameEngineImage.h"


#include <stdio.h>

GameEngine::GameEngine()
{
	window = NULL;
	surface = NULL;
	image = NULL;
	renderer = NULL;
	texture = NULL;
	iAlto = 0;
	iAncho = 0;
}


GameEngine::~GameEngine()
{
}


//IinicializarSistemas. Inicializa los sistemas de SDL que le pasemos y los sistemas PNG y JPG de SDL_Image. Debe ir siempre al principio del programa
void GameEngine::InicializarSistemas(Uint32 _flags) {
	if (SDL_Init(_flags) < 0) std::cout << "Error in SDL_Init";
	int imgFlags = IMG_INIT_PNG|IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "Error en IMG_init:" , IMG_GetError();
		
	}
	
}

//CrearVentana. Crea y devuelve una ventana que sera mostrada por defecto. El retorno de la funcion debe ser almacenado en un struct de tipo SDL_Window
SDL_Window* GameEngine::CrearVentana(std::string _nombreVentana, int _x, int _y, int _w, int _h, Uint32 _flags) {
	window = SDL_CreateWindow(_nombreVentana.c_str(), _x, _y, _w, _h, _flags);
	if (window == NULL) {
		std::cout << "Error in SDL_CreateWindow: ", SDL_GetError();
	}
	return window;
}

//CrearSurface. Crea una surface en la ventana que elijamos y nos la devuelve. El retorno de la funcion debe ser almacenado en un struc de tipo SDL_Surface. 
//Esta funcion se utiliza para poner la surface principal a una ventana
SDL_Surface* GameEngine::CrearSurface(SDL_Window* _window) {
		surface = SDL_GetWindowSurface(_window);
		return surface;
	}

//Colorea una surface con codigo RGB
void GameEngine::ColorearRectangulo(SDL_Surface* _surface, int colorUno, int colorDos, int colorTres) {
    
    if (_surface == NULL) {
    std::cout << "Superficie NULL!" << std::endl;
}

	else SDL_FillRect(_surface, NULL, SDL_MapRGB(surface->format, colorUno, colorDos, colorTres));
    
}

//Destruye la ventana
void GameEngine::Close(SDL_Window* _window) {
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

//Limpia una surface. Se deberian limpiar todas las surface antes de cerrar el programa para liberar memoria
void GameEngine::LimpiarSurface(SDL_Surface* _surface) {
	SDL_FreeSurface(_surface);
}

//Carga una imagen BMP y se optimiza. El valor retornado ha de ser almacenado en una estructura de tipo SDL_Surface
SDL_Surface* GameEngine::CargarImagen(const char* file, SDL_Surface* _surface) {
	SDL_Surface* optimizedSurface = NULL;
	image = SDL_LoadBMP(file);
	if (image == NULL) {
		std::cout << "ERROR SDL: No se pudo cargar la imagen: "<<file<< SDL_GetError();
	}
	else {
		//Si carga la imagen la convertimos en formato optimizado:
		optimizedSurface = SDL_ConvertSurface(image, _surface->format, 0);
		if(optimizedSurface == NULL) std::cout << "No se pudo cargar la imagen optimizada: "<< SDL_GetError();
		else {
            SDL_FreeSurface(image);
			return optimizedSurface;
			
		}
	}
}

//Carga una imagen JPG o PNG y se optimiza. El valor retornado ha de ser almacenado en una estructura de tipo SDL_Surface
SDL_Surface* GameEngine::CargarImagenSDLImage(std::string file, SDL_Surface* _surface) {
	SDL_Surface* optimizedSurface = NULL;
	image = IMG_Load(file.c_str());
	if (image == NULL) {
		std::cout << "ERROR SDL IMAGE: No se pudo cargar la imagen: "<< file<< IMG_GetError();
	}
	else {
		//Si carga la imagen la convertimos en formato optimizado:
		optimizedSurface = SDL_ConvertSurface(image, _surface->format, 0);
		if (optimizedSurface == NULL) std::cout << "No se pudo cargar la imagen optimizada: "<< SDL_GetError();
		else {
			return optimizedSurface;
			SDL_FreeSurface(image);
		}
	}
}

//Vuelca la imagen de una SDL_Surface a otra Surface, normalmente la surface de la ventana
void GameEngine::MostrarImagen(SDL_Surface* _surfaceSource,const SDL_Rect* _rectSource,SDL_Surface* _SurfaceDestination,SDL_Rect* _rectCopy) {
	SDL_BlitSurface(_surfaceSource, _rectSource, _SurfaceDestination, _rectCopy);
}

//Vuelca la imagen de una SDL_Surface a otra Surface pero ajustada a unos valores que han de ser dados por una structura SDL_Rect previamente seteada
void GameEngine::MostrarImagenAjustada(SDL_Surface* _surfaceSource, SDL_Surface* _sourfaceDestino, SDL_Rect _rect) {
	SDL_BlitScaled(_surfaceSource, NULL, _sourfaceDestino, &_rect);
	
}
//Crea un renderer. Deber�a ser usado al principio del programa si se van a renderizar texturas
SDL_Renderer* GameEngine::CrearRenderer(SDL_Window* _window, int _index, Uint32 flags) {
	
	renderer = SDL_CreateRenderer(_window, _index, flags);
	if (renderer == NULL) {
		std::cout << "ERROR SDL_CreateRenderer: "<< SDL_GetError();
	}
	return renderer;
}

//Carga una imagen a traves de IMG_Load y la convierte en una textura. Devuelve la textura.
SDL_Texture* GameEngine::CargarTextura(std::string file, SDL_Renderer* renderer) {
	image = IMG_Load(file.c_str());
	if (image == NULL) {
		std::cout << "ERROR SDL IMAGE en CargarTextura: No se pudo cargar la imagen: "<< file<< IMG_GetError();
       return nullptr;
	}
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (texture == NULL) {
		std::cout << "ERROR en SDL_CreateTextureFromSurface: No se pudo cargar la imagen: "<< SDL_GetError();
        return nullptr;
	}
	iAlto = image->h;
	iAncho = image->w;
	return texture;
	SDL_FreeSurface(image);
}

//Carga textura y aplica transparencia
SDL_Texture* GameEngine::CargarTextura(std::string file, SDL_Renderer* renderer, int r, int g, int b) {
	image = IMG_Load(file.c_str());
	if (image == NULL) {
		std::cout << "ERROR SDL IMAGE en CargarTextura: No se pudo cargar la imagen: "<< file<< IMG_GetError();
	}

	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, r, g, b));


	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (texture == NULL) {
		std::cout << "ERROR en SDL_CreateTextureFromSurface: No se pudo cargar la imagen: ", SDL_GetError();
	}
	iAlto = image->h;
	iAncho = image->w;
	return texture;
	SDL_FreeSurface(image);
}



//Crea un rectangulo predefinido, con los parametros deseados. Hay que pasarle un renderer que controle todos los procesos y los valores RGB-A
void GameEngine::CrearRectangulo(SDL_Rect rect, int x, int y, int w, int h, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {

	rect = { x, y,  w, h};
	if (SDL_SetRenderDrawColor(renderer, r, g, b, a) < 0){
		std::cout << "ERROR en SETRENDERDRAWCOLOR ", SDL_GetError();
	}
	if (SDL_RenderFillRect(renderer, &rect) < 0) {
		std::cout << "ERROR en RenderFillRect ", SDL_GetError();
	}
	
}

void GameEngine::MostrarTextura(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h) {
	//SDL_RenderClear(renderer);
	SDL_Rect renderRect = { x, y, w, h };
    
    
	//Render texture to screen
	 SDL_RenderCopy(renderer, texture, NULL, &renderRect);

}

void GameEngine::MostrarTexturaConViewport(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* viewport ) {
	//SDL_RenderClear(renderer);
	if (SDL_RenderSetViewport(renderer, viewport) < 0) {
		std::cout << "ERROR en RenderSetViewport (MostrarTexturaConViewport)"<< SDL_GetError()<<"\n";
	}
	//Render texture to screen
	else SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void GameEngine::RefrescarRender(SDL_Renderer* renderer){
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Color negro
   //SDL_RenderClear(renderer);
   
    SDL_RenderPresent(renderer);



}
void GameEngine::LimpiarRender(SDL_Renderer* renderer){
    
  
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Color negro
   SDL_RenderClear(renderer);


}


void GameEngine::RefrescarRender(SDL_Renderer* renderer, void (*func)()){
   //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Color negro
   // SDL_RenderClear(renderer);
    func();
    SDL_RenderPresent(renderer);



}

void GameEngine::DibujarLinea(SDL_Renderer* renderer, int x, int y,int x2, int y2){
    // Establecer el color de dibujo (rojo en este caso) 
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
    // Dibujar la línea 
    if (SDL_RenderDrawLine(renderer, x, y, x2, y2) != 0) { 
        std::cout << "Error al dibujar la línea: " << SDL_GetError() << std::endl; 
        } 
}

