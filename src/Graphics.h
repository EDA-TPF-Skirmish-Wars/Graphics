//////////////////////////////////////////////////////////
//              GRAPHICS.H                              //
// ALLEGRO NECESITA ESTAR INICIALIZADO                  //
//////////////////////////////////////////////////////////

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define DEBUG

#include <iostream>
#include <vector>

#ifdef  DEBUG
    #include "./dummys/dummys.h"
#endif

#ifdef __linux__
    #include <allegro5/allegro.h>
#elif _WIN32
    #include <allegro5/allegro>
#endif

typedef enum {hola,hola1,hola2}ACTION;
typedef enum {CHAU,CHAU1,CHAU2}ELEMENTO;
typedef enum {G_LOAD_GRAPHICS_ERROR, G_NO_ERROR,G_LOAD_BITMAP_ERROR}errors_s;


class Graphics
{
public:
    Graphics(std::vector<MartusTerrains> newTerrainList, 
                std::vector<MartusUnidades> newUnitList, 
                std::vector<MartusBuildings> newBuildingList);
    ~Graphics();
    //introduction(); //poner algun presentacion al juego para hacerlo mas copado
    errors_s updateGraphics(std::vector<MartusUnidades> unitList,
                            std::vector<MartusBuildings> buildingList);
    ACTION getUserAction();
protected:
    std::vector<MartusUnidades> unitList;
    std::vector<MartusBuildings> buildingList;
    std::vector<MartusTerrains> terrainList;
private:
    errors_s showLine(unsigned int i);
    errors_s drawTerrain(MartusTerrains terrainToDraw);
    errors_s drawBuilding(MartusBuildings buildingToDraw);
    errors_s drawUnit(MartusUnidades unitToDraw);
    errors_s loadGraphics();
    ALLEGRO_DISPLAY * display = NULL;
    errors_s loadBitmaps();
    errors_s error;
};

#endif