#include "levelHandler.h"
#include <fstream>
#include <vector>
#include <stdio.h>
#include "levelEditor.h"

levelHandler::levelHandler()
{
}


levelHandler::~levelHandler()
{
}


void Guardar(const std::vector<GameObject>& objetosEditor, const std::string& nombreArchivo, int tamañoVector){
     std::ofstream archivo("/../niveles/"+nombreArchivo); 
     if (!archivo.is_open()) { 
         std::cerr << "No se pudo abrir el archivo para escribir." << std::endl; 
         return; 
         } 
         for (const auto& objeto : objetosEditor) { 
           for(int i=0;i<tamañoVector;i++){
               archivo<<objeto.x0<<" "<<objeto.x1<<" "<<objeto.y0<<" "<<objeto.y1<<" "<<objeto.w<<" "<<objeto.h<<" "<<reinterpret_cast<uintptr_t>(objeto.textura) << "\n";
           }
 } 
 archivo.close(); 
 std::cout << "Datos guardados en " << nombreArchivo << std::endl;
}