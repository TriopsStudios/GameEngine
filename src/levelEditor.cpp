#include "GameEngine.h"
#include "levelHandler.h"
#include <filesystem> 
#include <fstream>
#include <vector> 
namespace fs = std::filesystem;

#define ANCHO 800
#define ALTO 800
#define XROW 6
#define YROW 6
#define ANCHOPALETA 800
#define ALTOPALETA 200
#define DEBUG std::cout<<
#define END std::endl
#define MAXIMOFILA 4

GameEngine handleLevel;
levelHandler* levelH;
SDL_Renderer* render;
SDL_Renderer* renderPaleta;
SDL_Window* mainV;
SDL_Window* paleta;
SDL_Event evento;

int tamañoVectorG = 0;//global
int texturaSeleccionada = 0;

struct GameObject{
  
int x0,x1,y0,y1,w,h;
SDL_Texture* textura;
  
};


std::vector<SDL_Texture*> texturas; //texturas para la paleta
std::vector<SDL_Texture*> texturasE; //las mismas texturas pero para el editor. Por algun motivo SDL no deja compartir texturas entre distintos renders
std::vector<GameObject> objetosPaleta;
std::vector<GameObject> objetosEditor(XROW*YROW);




//void MostrarTexturasEditor(SDL_Renderer* render);
int CargarTexturasEditor();
void DibujarGrilla();
void MostrarTexturasPaleta();
void MostrarTexturasEditor();

int LevelEditorMain(){
    
    //Inicializar vector de editor
    
    int separador = 0;
     int separadorVertical = 0;
     int a = 1;
     int finalSeparador = (ANCHO/XROW) * XROW- (ANCHO/XROW);
     
    
    
    mainV = handleLevel.CrearVentana("Level Creator", 400,400, ANCHO,ALTO,0);
    paleta = handleLevel.CrearVentana("Paleta", 1600,400, ANCHOPALETA,ALTOPALETA,SDL_WINDOW_RESIZABLE);
    render = handleLevel.CrearRenderer(mainV, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    renderPaleta = handleLevel.CrearRenderer(paleta, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    
    if(CargarTexturasEditor()==0) std::cout<<"Cargadas todas las texturas del editor."<<std::endl;
    if(tamañoVectorG==0){
        DEBUG "tamañoVectorG=0. Error desconocido durante la Carga de Texturas" << END;
    }
    
for(int i=0; i<XROW*YROW;i++){
         
         objetosEditor[i].x0 = (ANCHO/XROW)*separador; 
    objetosEditor[i].x1 = objetosEditor[i].x0 + (ANCHO/XROW);
    objetosEditor[i].w = ANCHO/XROW;
    objetosEditor[i].h = ALTO/YROW;
    objetosEditor[i].y0 = 0 + separadorVertical;//(ALTO/YROW)*a;
    objetosEditor[i].y1 =  objetosEditor[i].y0 + (ALTO/YROW);//objetos[i][a].y0 + (ALTO/YROW);
    objetosEditor[i].textura = nullptr;
   
    //DEBUG "x0 = " << objetosEditor[i].x0<<" ";
    //DEBUG "y0 = " << objetosEditor[i].y0 << END;
    separador++;
    if(objetosEditor[i].x0==finalSeparador){
       
        separador = 0;
        separadorVertical = separadorVertical + (ALTO/YROW);
       
        a++;
    }
    }
    
/*
 * objetosPaleta[i].x0 = (ANCHOPALETA/MAXIMOFILA)*separador; 
    objetosPaleta[i].x1 = objetosPaleta[i].x0 + (ANCHOPALETA/MAXIMOFILA);
    objetosPaleta[i].w = ANCHOPALETA/MAXIMOFILA;
    objetosPaleta[i].h = ALTOPALETA;
    objetosPaleta[i].y0 = 0 + separadorVertical;//(ALTO/YROW)*a;
    objetosPaleta[i].y1 =  objetosPaleta[i].y0 + (ALTOPALETA);//objetos[i][a].y0 + (ALTO/YROW);
    objetosPaleta[i].textura = texturas[i];*/
 
    bool loop = true;
     DEBUG "y0: " <<objetosPaleta[0].y0<<END;
    DEBUG "y1: " <<objetosPaleta[0].y1<<END;
   while(loop==true){
       while (SDL_PollEvent(&evento)) { 
        if (evento.type == SDL_QUIT) { 
            loop = false;
           
            } 
        if(evento.type == SDL_KEYDOWN){
            switch(evento.key.keysym.sym){
                case SDLK_w:
                DEBUG "PULSO W"<< END;
                 //DEBUG objetosPaleta[tamañoVectorG-1].y0 <<END;
                
                for(int i=0; i<tamañoVectorG;i++){
                    if(objetosPaleta[tamañoVectorG-1].y0 > 0){
                    
                        objetosPaleta[i].y0 = objetosPaleta[i].y0 - 10;
                        objetosPaleta[i].y1 =  objetosPaleta[i].y0 + (ALTOPALETA);
                    }
                    
                }
                 
                 DEBUG "y0: " <<objetosPaleta[0].y0<<END;
                  DEBUG "y1: " <<objetosPaleta[0].y1<<END;
                  
                DEBUG "ALTOPALETA: "<<ALTOPALETA<<END;
                    break; 
                
                  
                  case SDLK_s:
                  DEBUG "PULSO S"<< END;
                  if(objetosPaleta[0].y1 < ALTOPALETA){
                      for(int i=0; i<tamañoVectorG;i++){
                        objetosPaleta[i].y0 = objetosPaleta[i].y0 + 10;
                        objetosPaleta[i].y1 =  objetosPaleta[i].y0 + (ALTOPALETA);
                      DEBUG "y1: " <<objetosPaleta[0].y1<<" / ALTOPALETA: "<<ALTOPALETA<<END;
                      }
                      
                  }
                
                  break;
            }
            case N:
            levelH.Guardar(objetosEditor, "nivel1",tamañoVectorG);
            break;
        }
            
       if (evento.type == SDL_MOUSEBUTTONDOWN) {
            if(evento.button.button == SDL_BUTTON_LEFT){
                if(evento.button.windowID == SDL_GetWindowID(paleta)){
                DEBUG "PALETA" << END;
                int xb = evento.button.x; 
                int yb = evento.button.y;
                
                 for(int i=0;i<tamañoVectorG;i++){
                    
                        if(xb>=objetosPaleta[i].x0 && xb<=objetosPaleta[i].x1 && yb>=objetosPaleta[i].y0 && yb<=objetosPaleta[i].y1){
                          int iteracionSeleccionada = i;
                           for(int i=0; i<tamañoVectorG;i++){
                            
                                if(objetosPaleta[iteracionSeleccionada].textura == texturas[i]){
                                    texturaSeleccionada = i;    
                                break;
                                }
                           }
                        }
                 }
                }
                                        
                
            }
            
            
        }
        
        
        if (evento.type == SDL_MOUSEMOTION) {
            if(evento.button.button == SDL_BUTTON_LEFT){
            if(evento.button.windowID == SDL_GetWindowID(mainV)){ //---
                
                int xb = evento.button.x; 
                int yb = evento.button.y;
                    for(int i=0;i<XROW*YROW;i++){
                        if(xb>=objetosEditor[i].x0 && xb<=objetosEditor[i].x1 && yb>=objetosEditor[i].y0 && yb<=objetosEditor[i].y1){
                       //debugger
                      /* DEBUG "x0: "<<objetosEditor[i].x0<<END;
                       DEBUG "x1: "<<objetosEditor[i].x1<<END;
                       DEBUG "y0: "<<objetosEditor[i].y0<<END;
                       DEBUG "y1: "<<objetosEditor[i].y1<<END;*/
                            objetosEditor[i].textura = texturasE[texturaSeleccionada];
                        }
                    }

                }//---
            }
        }
            
        
    }
    handleLevel.LimpiarRender(renderPaleta);
    handleLevel.LimpiarRender(render);
    MostrarTexturasPaleta();
    MostrarTexturasEditor();
    DibujarGrilla();
       handleLevel.RefrescarRender(renderPaleta);
       handleLevel.RefrescarRender(render);
                  
      
       
   
       
       
   }
    handleLevel.Close(mainV);

    handleLevel.Close(paleta);
    return 0;
    
    
}




void DibujarGrilla(){
    for(int i=0;i<XROW;i++){
            handleLevel.DibujarLinea(render,(ANCHO/XROW)*i,0,(ANCHO/XROW)*i,ALTO);
        }
        
    for(int a=0;a<YROW;a++){
        handleLevel.DibujarLinea(render,0,(ALTO/YROW)*a,ANCHO,(ALTO/YROW)*a);
    }
    
    
}

int CargarTexturasEditor(){ //carga todas las texturas de la carpeta imagen y despues las pone en la paleta
    int total = 0;
    int contador = 0;
    float porcentaje;
    int posicionXbarra = 0;
    
    float largoBarra = ANCHOPALETA;
    
    std::string carpetaImagenes = "/home/alex/Documentos/GameEngine/Imagenes"; 
    for (const auto& entry : fs::directory_iterator(carpetaImagenes)) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") { 
         total++;
        
     }
      
         }
         
     for (const auto& entry : fs::directory_iterator(carpetaImagenes)) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") { 
         SDL_Texture* textura = handleLevel.CargarTextura(entry.path().string(), renderPaleta); 
         SDL_Texture* textura2 = handleLevel.CargarTextura(entry.path().string(), render);
     if (textura != nullptr && textura2 != nullptr) { 
         texturas.push_back(textura); 
         texturasE.push_back(textura2);
         contador++;
         
         porcentaje = (static_cast<float>(contador)/total);
         SDL_SetRenderDrawColor(renderPaleta, 0, 0, 0, 255); 
          SDL_RenderClear(renderPaleta);
         handleLevel.DibujarLinea(renderPaleta, posicionXbarra, 0, static_cast<int>(posicionXbarra + largoBarra*porcentaje),0);
         SDL_RenderPresent(renderPaleta);
         
         } 
         } 
     }
     
     int tamañoVector = static_cast<int>(texturas.size());
     tamañoVectorG = tamañoVector;
     objetosPaleta.resize(tamañoVector);
     
     
     int separador = 0;
     int separadorVertical = 0;
     
     int finalSeparador = (ANCHOPALETA/MAXIMOFILA) * MAXIMOFILA- (ANCHOPALETA/MAXIMOFILA);
     for(int i=0; i<tamañoVector;i++){
         
         objetosPaleta[i].x0 = (ANCHOPALETA/MAXIMOFILA)*separador; 
    objetosPaleta[i].x1 = objetosPaleta[i].x0 + (ANCHOPALETA/MAXIMOFILA);
    objetosPaleta[i].w = ANCHOPALETA/MAXIMOFILA;
    objetosPaleta[i].h = ALTOPALETA;
    objetosPaleta[i].y0 = 0 + separadorVertical;//(ALTO/YROW)*a;
    objetosPaleta[i].y1 =  objetosPaleta[i].y0 + (ALTOPALETA);//objetos[i][a].y0 + (ALTO/YROW);
    objetosPaleta[i].textura = texturas[i];
    separador++;
    if(objetosPaleta[i].x0==finalSeparador){
      
        separador = 0;
        separadorVertical = separadorVertical + (ALTOPALETA);
        
    }
    handleLevel.MostrarTextura(renderPaleta, objetosPaleta[i].textura, objetosPaleta[i].x0, objetosPaleta[i].y0, objetosPaleta[i].w, objetosPaleta[i].h); 
	
     
     }
   
         handleLevel.RefrescarRender(renderPaleta);

     return 0;
      
}    
         
void MostrarTexturasPaleta(){
    
    
     for(int i=0; i<tamañoVectorG;i++){

        handleLevel.MostrarTextura(renderPaleta, objetosPaleta[i].textura, objetosPaleta[i].x0, objetosPaleta[i].y0, objetosPaleta[i].w, objetosPaleta[i].h); 
 
    }
}

void MostrarTexturasEditor(){
    
     for(int i=0; i<XROW*YROW;i++){

        handleLevel.MostrarTextura(render, objetosEditor[i].textura, objetosEditor[i].x0, objetosEditor[i].y0, objetosEditor[i].w, objetosEditor[i].h); 
       
 
    }
}

  