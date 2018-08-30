#include "./Graphics.h"
#include <allegro5/allegro>

Graphics:::Graphics(newMap,newUnityList,newBuildingList)
{
    this->map = newMap;
    this->unityList = newUnityList;
    this->buildingList = newBuildingList;
    al_init_display(this->display);
    return
}

Graphics::~Graphics()
{
    al_destroy_display(display);
    //disallocate memory
    return;
}
