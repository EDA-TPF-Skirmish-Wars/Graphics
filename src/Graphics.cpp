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
    this->terrainList = newTerrainList;
    this->unitList = newUnitList;
    this->buildingList = newBuildingList;
    al_init_image_addon();
    this->evQueue = al_create_event_queue();
    al_register_event_source(this->evQueue,al_get_keyboard_event_source());
    al_register_event_source(this->evQueue,al_get_mouse_event_source());
    this->display = al_create_display(DISPLAY_WIDTH,DISPLAY_HEIGHT);
    al_register_event_source(this->evQueue,al_get_display_event_source(this->display));

    return;
}

Graphics::~Graphics(){
    al_destroy_display(display);
    //disallocate memory
    return;
}

errors_s Graphics::updateGraphics(std::vector<MartusUnidades> newUnitList,
                                std::vector<MartusBuildings> newBuildingList){
    this->newUnitList = newUnitList;
    this->newBuildingList = newBuildingList;
    errors_s error = G_NO_ERROR;
    for(unsigned int u = 0 ; u < 12; u++){
        for(unsigned int i = 0 ; i < 16 ; i++){
            error = showLine(u);
        }
    }
    //Update class variables, and freeing memory
    this->newUnitList.clear();
    this->newBuildingList.clear();
    this->unitList = newUnitList;
    this->buildingList = newBuildingList;
    return error;
}

errors_s Graphics::showLine(unsigned int line){
    //Dibuja los elementos que se encuentran en la linea i del mapa, las lineas van de 0-11 y las columnas de 0-15
    std::vector<MartusTerrains> terrainsInLine;     //Creo vectores con los los elementos de la linea a dibujar
    std::vector<MartusBuildings> buildingsInLine;
    std::vector<MartusUnidades> unitsInLine;
    errors_s error;
    //Cargo los elementos encontrados en la linea en cada vector
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

    this->showTransition(this->decodeMovements());
    //FALTA HACER LA TRANSICION ENTRE MOVIMIENTOS PARA QUE EL JUEGO SE VEA MAS FLUIDO
    //tengo cargado en las listas los elementos de la fila correspodiente
    //dibujo cada elemento en su correspondiente lugar
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

action_s Graphics::getUserAction(bool (* isTheActionValid)(action_s)){
    ALLEGRO_EVENT ev;
    action_s action;
    action.act = A_NO_ACTION;
    bool validity = false;
    if(!al_is_event_queue_empty(this->evQueue)){
        while(al_get_next_event(this->evQueue,&ev) || action.act == A_NO_ACTION){
            switch(ev.type){
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    al_destroy_display(this->display);
                    al_destroy_event_queue(this->evQueue);
                    action.act = A_CLOSE_GAME;
                    break;
                case ALLEGRO_EVENT_KEY_DOWN:
                    action = getKeyboardAction(ev);
                    validity = isTheActionValid(action);
                    break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                    action = getMouseAction(ev);
                    validity = isTheActionValid(action);
                    break;
                default:
                    break;
            }
        }
    }
    if(!validity)
        //DISPLAY ACTION NOT VALID DIALOG
    return action;
}

void Graphics::setTeam(int team){
    this->team = team;
    return;
}