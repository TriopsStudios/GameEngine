#ifndef LEVELHANDLER_H 
#define LEVELHANDLER_H

#include <fstream>
#include <vector>
#include "levelEditor.h"
class levelHandler{
private:
struct GameObject{
  
int x0,x1,y0,y1,w,h;
SDL_Texture* textura;
  
};
public:   

void Guardar(const std::vector<GameObject>& objetosEditor, const std::string& nombreArchivo, int tamañoVector);

levelHandler();
~levelHandler();
};

#endif