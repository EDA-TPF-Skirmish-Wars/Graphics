#include <iostream>
#include "./dummys/dummys.h"
#include <allegro5/allegro>


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
