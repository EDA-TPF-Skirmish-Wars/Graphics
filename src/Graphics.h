#include <iostream>
#include "martu.h"
#include <allegro5/allegro>


class Graphics
{
public:
    Graphics(MARTUS_MAP * newMap, std::list<MARTUS_UNIDADES> newUnityList, std::list<MARTUS_BUILDINGS> newBuildingList);
    ~Graphics();
    introduction(); //poner algun presentacion al juego para hacerlo mas copado
    updateGraphics(std::list<MARTUS_UNIDADES> unityList,std::list<MARTUS_BUILDINGS> buildingList);
    getUserAction();
    showOnScreen();
protected:
    std::list<MARTUS_UNIDADES> unityList;
    std::list<MARTUS_BUILDINGS> buildingList;
    MARTUS_MAP * map;
private:
    ALLEGRO_DISPLAY * display = NULL;
};
