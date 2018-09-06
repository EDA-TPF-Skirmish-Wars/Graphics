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


class Graphics
{
public:
    Graphics(std::vector<MartusTerrains> newTerrainList, 
                    std::vector<MartusUnidades> newUnitList, 
                    std::vector<MartusBuildings> newBuildingList);
    ~Graphics();
    //introduction(); //poner algun presentacion al juego para hacerlo mas copado
    void updateGraphics(std::vector<MartusUnidades> unitList,
                         std::vector<MartusBuildings> buildingList);
    ACTION getUserAction();
    void showOnScreen();
protected:
    std::vector<MartusUnidades> unitList;
    std::vector<MartusBuildings> buildingList;
    std::vector<MartusTerrains> terrainList;
private:
    void showLine(unsigned int i);
    void Graphics::drawTerrain(MartusTerrains terrainToDraw);
    void Graphics::drawBuilding(MartusBuildings buildingToDraw);
    void Graphics::drawUnit(MartusUnidades unitToDraw);
    ALLEGRO_DISPLAY * display = NULL;
};

#endif