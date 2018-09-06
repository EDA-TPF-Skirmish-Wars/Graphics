//////////////////////////////////////////////////////////
//              GRAPHICS.H                              //
// ALLEGRO NECESITA ESTAR INICIALIZADO                  //
//////////////////////////////////////////////////////////

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define DEBUG
#define FOW

#include <iostream>
#include <vector>
#define TEAM1   0
#define TEAM2   1

#ifdef  DEBUG
    #include "./dummys/dummys.h"
#endif

#ifdef __linux__
    #include <allegro5/allegro.h>
#elif _WIN32
    #include <allegro5/allegro>
#endif

typedef struct{
    act_s act;
    position_s positionFrom;
    position_s positionTo;
}action_s;
typedef enum {A_NO_ACTION, A_CLOSE_GAME}act_s;
typedef enum {G_LOAD_GRAPHICS_ERROR, G_NO_ERROR,G_LOAD_BITMAP_ERROR}errors_s;



class Graphics
{
public:
    Graphics(std::vector<MartusTerrains> newTerrainList, 
                std::vector<MartusUnidades> newUnitList, 
                std::vector<MartusBuildings> newBuildingList);
    ~Graphics();
    void setTeam(int team); //TEAM0 o TEAM1
    //introduction(); //poner algun presentacion al juego para hacerlo mas copado
    errors_s updateGraphics(std::vector<MartusUnidades> unitList,
                            std::vector<MartusBuildings> buildingList);
    action_s getUserAction();
protected:
    std::vector<MartusUnidades> unitList;
    std::vector<MartusBuildings> buildingList;
    std::vector<MartusTerrains> terrainList;
    int team;
private:
    errors_s showLine(unsigned int i);
    errors_s drawTerrain(MartusTerrains terrainToDraw);
    errors_s drawBuilding(MartusBuildings buildingToDraw);
    errors_s drawUnit(MartusUnidades unitToDraw);
    errors_s loadGraphics();
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * evQueue = NULL;
    action_s getMouseAction(ALLEGRO_EVENT ev);
    action_s getKeyboardAction(ALLEGRO_EVENT ev);
};

#endif