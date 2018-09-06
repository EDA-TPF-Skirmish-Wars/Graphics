#include "./Graphics.h"
#include <allegro5/allegro.h>

using namespace std;

Graphics:::Graphics(newTerrainList,newUnitList,newBuildingList){
    this-terrainList = newTerrainList;
    this->unitList = newUnitList;
    this->buildingList = newBuildingList;
    al_init_display(this->display);
    return
}

Graphics::~Graphics(){
    al_destroy_display(display);
    //disallocate memory
    return;
}

void Graphics::updateGraphics(unitList,buildingList){
    this->unitList = unitList;;
    this->buildingList = buildingList;
    for(unsigned int u = 0 ; u < 12; u++){
        for(unsigned int i = 0 ; i < 16 ; i++){
            showLine(u);
        }
    }
    return;
}

void Graphics::showLine(unsigned int line){
    //Dibuja los elementos que se encuentran en la linea i del mapa, las lineas van de 0-11 y las columnas de 0-15
    list<terrains_d> terrainsInLine;
    list<buildings_d> buildingsInLine;
    list<units_d> unitsInLine;
    for(unsigned int j=line*16 ; j < (line+1)*16 ; j++){
        if(this->terrainList[j].getPosition().x == line)
            terrainsInLine.push_back(this->terrainList[j]);
    }
    for(unsigned int j=0 ; j <= this->buildingList.size() ; j++){
        if(this->buildingList[j].getPosition().x == line)
            buildingsInLine.push_back(this->buildingList[j]);
    }
    for(unsigned int j=0 ; j <= this->unitList.size() ; j++){
        if(this->unitList[j].getPosition().x == line)
            unitsInLine.push_back(this->unitList[j]);
    }
    //tengo cargado en las listas los elementos de la fila correspodiente
    for(unsigned int o = 0; o <= terrainsInLine.size(); o++){
        drawElement(terrainsInLine[o],line);
    }
    for(unsigned int o = 0; o <= buildingsInLine.size(); o++){
        drawElement(buildingsInLine[o],line);
    }
    for(unsigned int o = 0; o <= terrainsInLine.size(); o++){
        drawElement(buildingsInLine[o],line);
    }
    return;
}

void Graphics::drawElement(){
    return;
}


ACTION Graphics::getUSerAction(){
    return;
}

void Graphics::showOnScreen(){
    return;
}
