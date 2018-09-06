#include "./Graphics.h"
#define DISPLAY_WIDTH   800
#define DISPLAY_HEIGHT  600
#define TILE_SIDE   50

#ifdef __linux__
    #include <allegro5/allegro_image.h>
#elif _WIN32
    #include <allegro5/allegro_image>
#endif


Graphics::Graphics(std::vector<MartusTerrains> newTerrainList, 
                    std::vector<MartusUnidades> newUnitList, 
                    std::vector<MartusBuildings> newBuildingList){
    error = G_NO_ERROR;
    this->terrainList = newTerrainList;
    this->unitList = newUnitList;
    this->buildingList = newBuildingList;
    al_init_image_addon();
    this->display = al_create_display(DISPLAY_WIDTH,DISPLAY_HEIGHT);
    return;
}

Graphics::~Graphics(){
    al_destroy_display(display);
    //disallocate memory
    return;
}

errors_s Graphics::updateGraphics(std::vector<MartusUnidades> unitList,
                                std::vector<MartusBuildings> buildingList){
    this->unitList = unitList;
    this->buildingList = buildingList;
    errors_s error = G_NO_ERROR;
    for(unsigned int u = 0 ; u < 12; u++){
        for(unsigned int i = 0 ; i < 16 ; i++){
            error = showLine(u);
        }
    }
    return error;
}

errors_s Graphics::showLine(unsigned int line){
    //Dibuja los elementos que se encuentran en la linea i del mapa, las lineas van de 0-11 y las columnas de 0-15
    std::vector<MartusTerrains> terrainsInLine;
    std::vector<MartusBuildings> buildingsInLine;
    std::vector<MartusUnidades> unitsInLine;
    errors_s error;

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
        error = this->drawTerrain(terrainsInLine[o]);
    }
    for(unsigned int o = 0; o <= buildingsInLine.size(); o++){
        error = this->drawBuilding(buildingsInLine[o]);
    }
    for(unsigned int o = 0; o <= unitsInLine.size(); o++){
        error = this->drawUnit(unitsInLine[o]);
    }
    if(error == G_NO_ERROR)
        al_flip_display();
    return error;
}

errors_s Graphics::drawTerrain(MartusTerrains terrainToDraw){
    errors_s error = G_NO_ERROR;
#ifdef FOW
    if(terrainToDraw.getFog() == false){
#endif
        ALLEGRO_BITMAP * bmp = al_load_bitmap(terrainToDraw.getImagePath().c_str());
        if(bmp != NULL){
            al_draw_bitmap(bmp, terrainToDraw.getPosition().x * TILE_SIDE,
                            terrainToDraw.getPosition().y * TILE_SIDE , 0);
            al_destroy_bitmap(bmp);
        }
        else
            error = G_LOAD_BITMAP_ERROR;
#ifdef FOW
    }
#endif
    return error;
}

errors_s Graphics::drawBuilding(MartusBuildings buildingToDraw){
    errors_s error = G_NO_ERROR;
#ifdef FOW
    if(buildingToDraw.getFog() == false){
#endif
        ALLEGRO_BITMAP * bmp = al_load_bitmap(buildingToDraw.getImagePath().c_str());
        if(bmp != NULL){
            al_draw_bitmap(bmp, buildingToDraw.getPosition().x * TILE_SIDE,
                            buildingToDraw.getPosition().y * TILE_SIDE , 0);
            al_destroy_bitmap(bmp);
        }
        else
            error = G_LOAD_BITMAP_ERROR;
#ifdef FOW
    }
#endif
    return error;
}

errors_s Graphics::drawUnit(MartusUnidades unitToDraw){
    errors_s error = G_NO_ERROR;
#ifdef FOW
    if(unitToDraw.getFog() == false){
#endif
        ALLEGRO_BITMAP * bmp = al_load_bitmap(unitToDraw.getImagePath().c_str());
        
        if(bmp != NULL){
            al_draw_bitmap(bmp, unitToDraw.getPosition().x * TILE_SIDE,
                            unitToDraw.getPosition().y * TILE_SIDE , 0);
            al_destroy_bitmap(bmp);
        }
        else
            error = G_LOAD_BITMAP_ERROR;
#ifdef FOW
    }
#endif
    return error;
}

ACTION Graphics::getUserAction(){
    return hola1;
}

void Graphics::setTeam(int team){
    this->team = team;
    return;
}