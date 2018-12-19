#include "./Graphics.h"
#define DISPLAY_WIDTH   800
#define DISPLAY_HEIGHT  600
#define DISPLAY_WIDTH_OFFSET    0
#define DISPLAY_HEIGHT_OFFSET    0
#define TILE_SIDE   50
#define LEFT_CLICK  1
#define OPTIONS_MENU_AMOUNT  10

#define WIDTH_POPUP     100
#define POPUP_LINE      15  
#define HEIGHT_POPUP    (POPUP_LINE * OPTIONS_MENU_AMOUNT)

#ifdef __linux__
    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_font.h>
#elif _WIN32
    #include <allegro5/allegro_image>
    #include <allegro5/allegro_primitives>
    #include <allegro5/allegro_font>
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
    al_init_primitives_addon();
    al_init_font_addon();
    font = al_load_font("resources/font.tga");
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
        error = showLine(u);
    }
    if(error == G_NO_ERROR){
        al_flip_display(display);
    }

    //Update class variables, and freeing memory
    this->unitList = newUnitList;
    this->buildingList = newBuildingList;
    this->newUnitList.clear();
    this->newBuildingList.clear();
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

    //FALTA HACER LA TRANSICION ENTRE MOVIMIENTOS PARA QUE EL JUEGO SE VEA MAS FLUIDO
    //tengo cargado en las listas los elementos de la fila correspodiente
    //dibujo cada elemento en su correspondiente lugar

    //CREO Q HABRIA QUE IMPRIMIR TODA LA PANTALLA EN NEGRO ANTES DE VOLVER A DIBUJAR

    for(unsigned int o = 0; o <= terrainsInLine.size(); o++){
        error = this->drawTerrain(terrainsInLine[o]);
    }
    for(unsigned int o = 0; o <= buildingsInLine.size(); o++){
        error = this->drawBuilding(buildingsInLine[o]);
    }
    for(unsigned int o = 0; o <= unitsInLine.size(); o++){
        error = this->drawUnit(unitsInLine[o]);
    }
    //if(error == G_NO_ERROR)
    //    al_flip_display();
    return error;
}

errors_s Graphics::drawTerrain(MartusTerrains terrainToDraw){
    errors_s error = G_NO_ERROR;
#ifdef FOW
    if(terrainToDraw.getFog() == false){
#endif
        ALLEGRO_BITMAP * bmp = al_load_bitmap(terrainToDraw.getImagePath().c_str());
        if(bmp != NULL){
            al_draw_bitmap(bmp, terrainToDraw.getPosition().x * TILE_SIDE + DISPLAY_WIDTH_OFFSET,
                            terrainToDraw.getPosition().y * TILE_SIDE + DISPLAY_HEIGHT_OFFSET, 0);
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
            al_draw_bitmap(bmp, buildingToDraw.getPosition().x * TILE_SIDE +DISPLAY_WIDTH_OFFSET,
                            buildingToDraw.getPosition().y * TILE_SIDE + DISPLAY_HEIGHT_OFFSET, 0);
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
            al_draw_bitmap(bmp, unitToDraw.getPosition().x * TILE_SIDE + DISPLAY_WIDTH_OFFSET,
                            unitToDraw.getPosition().y * TILE_SIDE + DISPLAY_HEIGHT_OFFSET, 0);
            al_destroy_bitmap(bmp);
        }
        else
            error = G_LOAD_BITMAP_ERROR;
#ifdef FOW
    }
#endif
    return error;
}

action_s Graphics::getUserAction(){
    ALLEGRO_EVENT ev;
    action_s action;
    action.act = A_NO_ACTION;
    //IMPRIMIR UN "YOUR TURN" O ALGO SIMILAR ANTES
    action getMouseAction();
    return action;
}

void Graphics::setTeam(int team){
    this->team = team;
    return;
}

/*std::vector<movement_s> Graphics::decodeMovements(){ //FINISH LATER
    std::vector<movement_s> movements;
    std::vector<unsigned int> temp;
    for(unsigned int i = 0; i < min(this->unitList.size(),this->newUnitList.size()); i++){
        if(!unitsAreEqual(unitList[i],newUnitList[i]));
            temp.push_back(i);
    }

}*/

action_s Graphics::getMouseAction(){
    ALLEGRO_EVENT ev;
    bool tmp = true;
    action_s temp;
    while(tmp){
        al_get_next_event(this->evQueue,&ev);
        switch(ev.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                tmp = false;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(ev.mouse.button == LEFT_CLICK)
                    tmp = false;
                break;
            default:
                break;
        }
    }
    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        int x = ev.mouse.x;
        int y = ev.mouse.y;
        x -= DISPLAY_WIDTH_OFFSET;
        y -= DISPLAY_HEIGHT_OFFSET;
        x /= TILE_SIDE;
        y /= TILE_SIDE;
        temp.act = A_NO_ACTION;
        temp = showPopUp(map.getOptions(xTile, yTile),xTile, yTile);
    }
    else 
        temp = A_CLOSE_GAME;
    return temp;
}

action_s Graphics::showPopUp(options_s opt, int xTile, int yTile){
    unsigned int amountOfLines = 0;
    if(opt.attackUpAvailable)
        amountOfLines++;
    else if(opt.attackDownAvailable)
        amountOfLines++;
    else if(opt.attackRightAvailable)
        amountOfLines++;
    else if(opt.attackLeftAvailable)
        amountOfLines++;
    else if(opt.buyAvailable)
        amountOfLines++;
    else if(opt.moveUpAvailable)
        amountOfLines++;
    else if(opt.moveDownAvailable)
        amountOfLines++;
    else if(opt.moveLeftAvailable)
        amountOfLines++;
    else if(opt.moveRightAvailable)
        amountOfLines++;
    else if(opt.passAvailable)
        amountOfLines++;
    
    int x,y;
    al_get_mouse_cursor_position(&x,&y);
    al_draw_filled_rectangle(x,y,x+WIDTH_POPUP, y+(POPUP_LINE*amountOfLines),al_map_rgb(255,255,255));

    amountOfLines = 1;
    if(opt.attackUpAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),x,y+POPUP_LINE*amountOfLines,0,"Press 'W' to attack Up!");
        amountOfLines++;
    }
    else if(opt.attackDownAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),x,y+POPUP_LINE*amountOfLines,0,"Press 'S' to attack Down!");
        amountOfLines++;
    }
    else if(opt.attackRightAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),x,y+POPUP_LINE*amountOfLines,0,"Press 'D' to attack Right!");
        amountOfLines++;
    }
    else if(opt.attackLeftAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),x,y+POPUP_LINE*amountOfLines,0,"Press 'A' to attack Left!");
        amountOfLines++;
    }
    else if(opt.buyAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),x,y+POPUP_LINE*amountOfLines,0,"Press 'B' to Buy!");
        amountOfLines++;
    }
    else if(opt.moveUpAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),x,y+POPUP_LINE*amountOfLines,0,"Press Up Arrow to Move Up!");
        amountOfLines++;
    }
    else if(opt.moveDownAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),x,y+POPUP_LINE*amountOfLines,0,"Press Down Arrow to Move Down!");
        amountOfLines++;
    }
    else if(opt.moveLeftAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),x,y+POPUP_LINE*amountOfLines,0,"Press Left Arrow to Move Left!");
        amountOfLines++;
    }
    else if(opt.moveRightAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),x,y+POPUP_LINE*amountOfLines,0,"Press Right Arrow to Move Right!");
        amountOfLines++;
    }
    else if(opt.passAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),x,y+POPUP_LINE*amountOfLines,0,"Press 'P' to Pass!");
        amountOfLines++;
    }

    al_flip_display(display);

    return getKeyboardAction(xTile,yTile);

}

action_s Graphics::getKeyboardAction(int xTile, int yTile){
    ALLEGRO_EVENT ev;
    action_s action;
    action.act = A_NO_ACTION;
    while(action.act == A_NO_ACTION){
        al_get_next_event(this->evQueue,&ev);
        switch(ev.type){
            case ALLEGRO_EVENT_KEY_DOWN:
                switch(ev.keyboard.keycode){
                    case ALLEGRO_KEY_W:
                        action.act = A_ATTACK;
                        action.positionFrom.x = xTile;
                        action.positionFrom.y = yTile; 
                        action.positionTo.x = xTile;
                        action.positionTo.y = yTile-1;
                        break;
                    case ALLEGRO_KEY_A:
                        action.act = A_ATTACK;
                        action.positionFrom.x = xTile;
                        action.positionFrom.y = yTile; 
                        action.positionTo.x = xTile-1;
                        action.positionTo.y = yTile;
                        break;
                    case ALLEGRO_KEY_S:
                        action.act = A_ATTACK;
                        action.positionFrom.x = xTile;
                        action.positionFrom.y = yTile; 
                        action.positionTo.x = xTile;
                        action.positionTo.y = yTile+1;
                        break;
                    case ALLEGRO_KEY_D:
                        action.act = A_ATTACK;
                        action.positionFrom.x = xTile;
                        action.positionFrom.y = yTile; 
                        action.positionTo.x = xTile+1;
                        action.positionTo.y = yTile;
                        break;
                    case ALLEGRO_KEY_B:
                        action.act = A_PURCHASE;
                        break;
                    case ALLEGRO_KEY_P:
                        action.act = A_PASS;
                        break;
                    case ALLEGRO_KEY_UP:
                        action.act = A_MOVE;
                        positionFrom.x = xTile;
                        positionFrom.y = yTile;
                        positionTo.x = xTile;
                        positionTo.y = yTile-1;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        action.act = A_MOVE;
                        positionFrom.x = xTile;
                        positionFrom.y = yTile;
                        positionTo.x = xTile;
                        positionTo.y = yTile+1;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        action.act = A_MOVE;
                        positionFrom.x = xTile;
                        positionFrom.y = yTile;
                        positionTo.x = xTile-1;
                        positionTo.y = yTile;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        action.act = A_MOVE;
                        positionFrom.x = xTile;
                        positionFrom.y = yTile;
                        positionTo.x = xTile+1;
                        positionTo.y = yTile;
                        break;
                    default:
                        action.act = A_NO_ACTION;
                        break;

                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                action.act = A_CLOSE_GAME;
                break;
            default:
                action.act = A_NO_ACTION;
                break;
        }
    }
    return action;
}