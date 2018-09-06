#include "./Graphics.h"


Graphics::Graphics(std::vector<MartusTerrains> newTerrainList, 
                    std::vector<MartusUnidades> newUnitList, 
                    std::vector<MartusBuildings> newBuildingList){
    this->terrainList = newTerrainList;
    this->unitList = newUnitList;
    this->buildingList = newBuildingList;
    this->display = al_create_display(500,500);
    return;
}

Graphics::~Graphics(){
    al_destroy_display(display);
    //disallocate memory
    return;
}

void Graphics::updateGraphics(std::vector<MartusUnidades> unitList,
                                std::vector<MartusBuildings> buildingList){
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
    std::vector<MartusTerrains> terrainsInLine;
    std::vector<MartusBuildings> buildingsInLine;
    std::vector<MartusUnidades> unitsInLine;
    

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
        this->drawTerrain(terrainsInLine[o]);
    }
    for(unsigned int o = 0; o <= buildingsInLine.size(); o++){
        this->drawBuilding(buildingsInLine[o]);
    }
    for(unsigned int o = 0; o <= unitsInLine.size(); o++){
        this->drawUnit(unitsInLine[o]);
    }
    
    al_flip_display();
    return;
}

void Graphics::drawTerrain(MartusTerrains terrainToDraw){
    return;
}

void Graphics::drawBuilding(MartusBuildings buildingToDraw){
    return;
}

void Graphics::drawUnit(MartusUnidades unitToDraw){
    return;
}

ACTION Graphics::getUserAction(){
    return hola1;
}

void Graphics::showOnScreen(){
    return;
}
