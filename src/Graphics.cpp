#include "./Graphics.h"
#include "../Network/Timer.h"
#define DISPLAY_WIDTH   1100
#define DISPLAY_HEIGHT  600
#define DISPLAY_WIDTH_OFFSET    0
#define DISPLAY_HEIGHT_OFFSET    0
#define TILE_SIDE   50
#define LEFT_CLICK  1
#define OPTIONS_MENU_AMOUNT  10
#define FONT_SIZE_SMALL		20
#define FONT_SIZE_LARGE		40

#define WIDTH_POPUP     100
#define POPUP_LINE      15  
#define HEIGHT_POPUP    (POPUP_LINE * OPTIONS_MENU_AMOUNT)




Graphics::Graphics(std::vector<MartusTerrains> newTerrainList,
	std::vector<MartusUnidades> newUnitList,
	std::vector<MartusBuildings> newBuildingList) {
	this->graphicsError = G_NO_ERROR;
	this->terrainList = newTerrainList;
	this->unitList = newUnitList;
	this->buildingList = newBuildingList;
	al_init_image_addon();
	this->evQueue = al_create_event_queue();
	al_install_keyboard();
	al_install_mouse();
	al_register_event_source(this->evQueue, al_get_keyboard_event_source());
	al_register_event_source(this->evQueue, al_get_mouse_event_source());
	this->display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (display == NULL) {
		graphicsError = G_DISPLAY_ERROR;
	}
	al_register_event_source(this->evQueue, al_get_display_event_source(this->display));
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	font = al_load_font("resources/font.ttf", FONT_SIZE_SMALL, 0); //VER SI ESTOS 2 CEROS ESTAN BIEN
	if (font == NULL) {
		graphicsError = G_LOAD_FONT_ERROR;
	}
	fontLarge = al_load_ttf_font("resources/font.ttf", FONT_SIZE_LARGE, 0);
	if (fontLarge == NULL) {
		graphicsError = G_LOAD_FONT_ERROR;
	}
	if (graphicsError == G_NO_ERROR) {
		drawMap();
	}
	if (graphicsError == G_NO_ERROR) {
		al_flip_display();
	}
    return;
}

Graphics::~Graphics() {
	if (display != NULL) {
		al_destroy_display(display);
	}
	if (font != NULL) {
		al_destroy_font(font);
	}
	if (fontLarge != NULL) {
		al_destroy_font(fontLarge);
	}
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();
    //disallocate memory
    return;
}

errors_s Graphics::updateGraphics(std::vector<MartusUnidades> newUnitList,
                                std::vector<MartusBuildings> newBuildingList){
    this->unitList = newUnitList;
    this->buildingList = newBuildingList;
	showTransition();
	drawMap();
	if (graphicsError == G_NO_ERROR) {
		al_flip_display();
	}
    //Update class variables, and freeing memory
    return graphicsError;
}

void Graphics::drawMap() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for (unsigned int u = 0; u < 12; u++) {
		showLine(u);
	}
	string str = "./resources/frame.png";
	ALLEGRO_BITMAP * bmp = al_load_bitmap(str.c_str());
	al_draw_scaled_bitmap(bmp, 68, 55, 994,1490, 0, 0, TILE_SIDE * 16, TILE_SIDE * 12, 0);
	al_destroy_bitmap(bmp);
	str = "./resources/pop-up.png";
	bmp = al_load_bitmap(str.c_str());
	al_draw_scaled_bitmap(bmp, 0, 0, 575, 600, TILE_SIDE * 16, 0, TILE_SIDE * 6, TILE_SIDE *12 , 0);
	al_destroy_bitmap(bmp);
	return;
}

void Graphics::showLine(unsigned int line){
    //Dibuja los elementos que se encuentran en la linea i del mapa, las lineas van de 0-11 y las columnas de 0-15
    std::vector<MartusTerrains> terrainsInLine;     //Creo vectores con los los elementos de la linea a dibujar
    std::vector<MartusBuildings> buildingsInLine;
    std::vector<MartusUnidades> unitsInLine;
	
	//Cargo los elementos encontrados en la linea en cada vector
    for(unsigned int j=0 ; j < terrainList.size() ; j++){
        if(this->terrainList[j].getPosition().y == line)
            terrainsInLine.push_back(this->terrainList[j]);
    }
    for(unsigned int j=0 ; j < this->buildingList.size() ; j++){
        if(this->buildingList[j].getPosition().y == line)
            buildingsInLine.push_back(this->buildingList[j]);
    }
    for(unsigned int j=0 ; j < this->unitList.size() ; j++){
        if(this->unitList[j].getPosition().y == line)
            unitsInLine.push_back(this->unitList[j]);
    }

    //FALTA HACER LA TRANSICION ENTRE MOVIMIENTOS PARA QUE EL JUEGO SE VEA MAS FLUIDO
    //tengo cargado en las listas los elementos de la fila correspodiente
    //dibujo cada elemento en su correspondiente lugar

    //CREO Q HABRIA QUE IMPRIMIR TODA LA PANTALLA EN NEGRO ANTES DE VOLVER A DIBUJAR

    for(unsigned int o = 0; o < terrainsInLine.size(); o++){
        this->drawTerrain(terrainsInLine[o]);
    }
    for(unsigned int o = 0; o < buildingsInLine.size(); o++){
        this->drawBuilding(buildingsInLine[o]);
    }
    for(unsigned int o = 0; o < unitsInLine.size(); o++){
        this->drawUnit(unitsInLine[o]);
    }

	return;
}

void Graphics::drawTerrain(MartusTerrains terrainToDraw){
	if (graphicsError == G_NO_ERROR) {
#ifdef FOW
		if (terrainToDraw.getFog() == false) {
#endif
			ALLEGRO_BITMAP * bmp = al_load_bitmap(terrainToDraw.getImagePath().c_str());
			if (bmp != NULL) {
				//al_draw_bitmap(bmp, terrainToDraw.getPosition().x * TILE_SIDE + DISPLAY_WIDTH_OFFSET,
				//	terrainToDraw.getPosition().y * TILE_SIDE + DISPLAY_HEIGHT_OFFSET, 0);
				al_draw_scaled_bitmap(bmp, 0, 0, 51, 58, terrainToDraw.getPosition().x * TILE_SIDE + DISPLAY_WIDTH_OFFSET,
					terrainToDraw.getPosition().y * TILE_SIDE + DISPLAY_HEIGHT_OFFSET, TILE_SIDE, TILE_SIDE, 0);
				al_destroy_bitmap(bmp);
			}
			else
				graphicsError = G_LOAD_BITMAP_ERROR;
#ifdef FOW
		}
#endif
	}
	return;
}

void Graphics::drawBuilding(MartusBuildings buildingToDraw){
    //errors_s error = G_NO_ERROR;
	if (graphicsError == G_NO_ERROR) {
#ifdef FOW
		if (buildingToDraw.getFog() == false) {
#endif
			ALLEGRO_BITMAP * bmp = al_load_bitmap(buildingToDraw.getImagePath().c_str());
			if (bmp != NULL) {
				//al_draw_bitmap(bmp, buildingToDraw.getPosition().x * TILE_SIDE + DISPLAY_WIDTH_OFFSET,
				//	buildingToDraw.getPosition().y * TILE_SIDE + DISPLAY_HEIGHT_OFFSET, 0);
				al_draw_scaled_bitmap(bmp, 0, 0, 350, 350, buildingToDraw.getPosition().x * TILE_SIDE + DISPLAY_WIDTH_OFFSET,
					buildingToDraw.getPosition().y * TILE_SIDE + DISPLAY_HEIGHT_OFFSET, TILE_SIDE, TILE_SIDE, 0);
				al_destroy_bitmap(bmp);
			}
			else
				graphicsError = G_LOAD_BITMAP_ERROR;
#ifdef FOW
		}
#endif
	}
	return; //error;
}

void Graphics::drawUnit(MartusUnidades unitToDraw){
    //errors_s error = G_NO_ERROR;
	if (graphicsError == G_NO_ERROR) {
#ifdef FOW
		if (unitToDraw.getFog() == false) {
#endif
			ALLEGRO_BITMAP * bmp = al_load_bitmap(unitToDraw.getImagePath().c_str());

			if (bmp != NULL) {
				//al_draw_bitmap(bmp, unitToDraw.getPosition().x * TILE_SIDE + DISPLAY_WIDTH_OFFSET,
				//	unitToDraw.getPosition().y * TILE_SIDE + DISPLAY_HEIGHT_OFFSET, 0);
				al_draw_scaled_bitmap(bmp, 0,0,51,58, unitToDraw.getPosition().x * TILE_SIDE + DISPLAY_WIDTH_OFFSET,
					unitToDraw.getPosition().y * TILE_SIDE + DISPLAY_HEIGHT_OFFSET,TILE_SIDE,TILE_SIDE,0);
				al_destroy_bitmap(bmp);
			}
			else
				graphicsError = G_LOAD_BITMAP_ERROR;
#ifdef FOW
		}
#endif
	}
	return;// error;
}

action_s Graphics::getUserAction(){
    action_s action;
	action.act = A_NO_ACTION;
	drawMessage();
	action = getMouseAction();
    return action;
}

void Graphics::setTeam(int team){
    this->team = team;
    return;
}

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
		int xTile, yTile;
        xTile = (x - DISPLAY_WIDTH_OFFSET)/TILE_SIDE;
        yTile = (y - DISPLAY_HEIGHT_OFFSET)/TILE_SIDE;
        temp.act = A_NO_ACTION;
        temp = showPopUp(map.getOptions(xTile, yTile),xTile, yTile);
    }
    else 
        temp.act = A_CLOSE_GAME;
    return temp;
}

action_s Graphics::showPopUp(options_s opt, int xTile, int yTile){
	drawMap();
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

    amountOfLines = 1;
    if(opt.attackUpAvailable){
        al_draw_text(font,al_map_rgb(0,0,0),TILE_SIDE * 17,TILE_SIDE * (amountOfLines+1),0,"'W' to attack Up!");
        amountOfLines++;
    }
    else if(opt.attackDownAvailable){
        al_draw_text(font,al_map_rgb(0,0,0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1),0,"'S' to attack Down!");
        amountOfLines++;
    }
    else if(opt.attackRightAvailable){
        al_draw_text(font,al_map_rgb(0,0,0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1),0,"'D' to attack Right!");
        amountOfLines++;
    }
    else if(opt.attackLeftAvailable){
        al_draw_text(font,al_map_rgb(0,0,0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1),0,"'A' to attack Left!");
        amountOfLines++;
    }
    else if(opt.buyAvailable){
        al_draw_text(font,al_map_rgb(0,0,0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1),0,"'B' to Buy!");
        amountOfLines++;
    }
    else if(opt.moveUpAvailable){
        al_draw_text(font,al_map_rgb(0,0,0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1),0,"Up Arrow to Move Up!");
        amountOfLines++;
    }
    else if(opt.moveDownAvailable){
        al_draw_text(font,al_map_rgb(0,0,0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1),0,"Down Arrow to Move Down!");
        amountOfLines++;
    }
    else if(opt.moveLeftAvailable){
        al_draw_text(font,al_map_rgb(0,0,0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1),0,"Left Arrow to Move Left!");
        amountOfLines++;
    }
    else if(opt.moveRightAvailable){
        al_draw_text(font,al_map_rgb(0,0,0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1),0,"Right Arrow to Move Right!");
        amountOfLines++;
    }
    else if(opt.passAvailable){
        al_draw_text(font,al_map_rgb(0,0,0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1),0,"'P' to Pass!");
        amountOfLines++;
    }
    al_flip_display();

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
                        action.positionFrom.x = xTile;
						action.positionFrom.y = yTile;
						action.positionTo.x = xTile;
						action.positionTo.y = yTile-1;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        action.act = A_MOVE;
						action.positionFrom.x = xTile;
						action.positionFrom.y = yTile;
						action.positionTo.x = xTile;
						action.positionTo.y = yTile+1;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        action.act = A_MOVE;
						action.positionFrom.x = xTile;
						action.positionFrom.y = yTile;
						action.positionTo.x = xTile-1;
						action.positionTo.y = yTile;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        action.act = A_MOVE;
						action.positionFrom.x = xTile;
						action.positionFrom.y = yTile;
						action.positionTo.x = xTile+1;
						action.positionTo.y = yTile;
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

errors_s Graphics::getError() {
	return graphicsError;
}

void Graphics::showTransition() {
	if (graphicsError == G_NO_ERROR) {
		for (unsigned int i = 0; i < 255; i--) {
			al_clear_to_color(al_map_rgb(255-i, 255-i, 255-i));
			al_draw_text(fontLarge, al_map_rgb(i, i,i), TILE_SIDE * 3, TILE_SIDE * 4, 0,
				"Some changes have been happening during night!");
			al_flip_display();
			timerMiliseconds(10);
		}
		for (unsigned int i = 0; i < 255; i++) {
			al_clear_to_color(al_map_rgb(i, i, i));
			al_draw_text(fontLarge, al_map_rgb((255-i),(255-i), (255-i)), TILE_SIDE * 3, TILE_SIDE*4, 0, 
				"Some changes have been happening during night!");
			al_flip_display();
			timerMiliseconds(10);
		}
	}
	return;
}

void Graphics::drawMessage() {
	drawMap();
	//al_draw_filled_rectangle((DISPLAY_WIDTH / 2) - 50, (DISPLAY_HEIGHT / 2) - 50, (DISPLAY_WIDTH / 2) + 50,
	//	(DISPLAY_HEIGHT / 2) + 50, al_map_rgb(255, 255, 255));
	string str = "./resources/pop-up.png";
	ALLEGRO_BITMAP * bmp = al_load_bitmap(str.c_str());
	al_draw_scaled_bitmap(bmp, 0, 0, 575, 600, DISPLAY_WIDTH/4,DISPLAY_HEIGHT/4, TILE_SIDE * 5, TILE_SIDE*5, 0);
	al_destroy_bitmap(bmp);
	al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE*7, TILE_SIDE * 5, 0, "Your Turn!");
	if (graphicsError == G_NO_ERROR) {
		al_flip_display();
	}
	timerMiliseconds(1000);
	drawMap();
	if (graphicsError == G_NO_ERROR) {
		al_flip_display();
	}
	return;
}

void Graphics::displayActionInvalid() {
	drawMap();
	//al_draw_filled_rectangle((DISPLAY_WIDTH / 2) - 50, (DISPLAY_HEIGHT / 2) - 50, (DISPLAY_WIDTH / 2) + 50,
	//	(DISPLAY_HEIGHT / 2) + 50, al_map_rgb(255, 255, 255));
	string str = "./resources/pop-up.png";
	ALLEGRO_BITMAP * bmp = al_load_bitmap(str.c_str());
	al_draw_scaled_bitmap(bmp, 0, 0, 575, 600, DISPLAY_WIDTH / 4, DISPLAY_HEIGHT / 4, TILE_SIDE * 5, TILE_SIDE * 5, 0);
	al_destroy_bitmap(bmp);
	al_draw_text(font, al_map_rgb(0, 0, 0), (TILE_SIDE * 7)-10, TILE_SIDE * 5, 0, "Action Invalid!");
	if (graphicsError == G_NO_ERROR) {
		al_flip_display();
	}
	timerMiliseconds(2000);
	drawMap();
	if (graphicsError == G_NO_ERROR) {
		al_flip_display();
	}
	return;
}