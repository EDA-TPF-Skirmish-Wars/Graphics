#ifndef GRAPHICS_H
#define GRAPHICS_H

#define DEBUG

#include <iostream>
#include <list>

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
    Graphics(std::list<terrains_d> newTerrainList, std::list<units_d> newUnitList, std::list<buildings_d> newBuildingList);
    ~Graphics();
    //introduction(); //poner algun presentacion al juego para hacerlo mas copado
    void updateGraphics(std::list<units_d> unitList,std::list<buildings_d> buildingList);
    ACTION getUserAction();
    void showOnScreen();
protected:
    std::list<units_d> unitList;
    std::list<buildings_d> buildingList;
    std::list<terrains_d> terrainList;
private:
    void showLine(unsigned int i);
    void drawElement(ELEMENTO);
    ALLEGRO_DISPLAY * display = NULL;
};

#endif