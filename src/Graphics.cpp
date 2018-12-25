#include "./Graphics.h"
#include "../Network/Timer.h"
#define DISPLAY_WIDTH   1100
#define DISPLAY_HEIGHT  630
#define DISPLAY_WIDTH_OFFSET    15
#define DISPLAY_HEIGHT_OFFSET    15
#define TILE_SIDE   50
#define LEFT_CLICK  1
#define OPTIONS_MENU_AMOUNT  10
#define FONT_SIZE_SMALL		20
#define FONT_SIZE_LARGE		40

#define WIDTH_POPUP     100
#define POPUP_LINE      15  
#define HEIGHT_POPUP    (POPUP_LINE * OPTIONS_MENU_AMOUNT)




Graphics::Graphics(MartusMap map) {
	this->graphicsError = G_NO_ERROR;
	this->map = map;
	this->display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (display == NULL) {
		graphicsError = G_DISPLAY_ERROR;
	}
	this->evQueue = al_create_event_queue();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_register_event_source(this->evQueue, al_get_keyboard_event_source());
	al_register_event_source(this->evQueue, al_get_mouse_event_source());
	al_register_event_source(this->evQueue, al_get_display_event_source(this->display));
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	if (!al_install_audio()) {
		graphicsError = G_AUDIO_ERROR;
	}
	if (!al_init_acodec_addon()) {
		graphicsError = G_AUDIO_ERROR;
	}
	voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	if (voice == NULL) {
		graphicsError = G_AUDIO_ERROR;
	}
	mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	if (mixer == NULL) {
		graphicsError = G_AUDIO_ERROR;
	}
	if (!al_attach_mixer_to_voice(mixer, voice)) {
		graphicsError = G_AUDIO_ERROR;
	}
	sample = al_create_sample_instance(NULL);
	if (sample == NULL) {
		graphicsError = G_AUDIO_ERROR;
	}
	sample_data = al_load_sample("./resources/music.ogg");
	if (sample_data == NULL) {
		graphicsError = G_AUDIO_ERROR;
	}
	if (!al_set_sample(sample, sample_data)) {
		graphicsError = G_AUDIO_ERROR;
	}
	if (!al_attach_sample_instance_to_mixer(sample, mixer)) {
		graphicsError = G_AUDIO_ERROR;
	}
	al_set_sample_instance_playmode(sample, ALLEGRO_PLAYMODE_LOOP);
	al_play_sample_instance(sample);

	font = al_load_font("resources/font.ttf", FONT_SIZE_SMALL, 0); //VER SI ESTOS 2 CEROS ESTAN BIEN
	if (font == NULL) {
		graphicsError = G_LOAD_FONT_ERROR;
	}
	fontLarge = al_load_ttf_font("resources/font.ttf", FONT_SIZE_LARGE, 0);
	if (fontLarge == NULL) {
		graphicsError = G_LOAD_FONT_ERROR;
	}
	introduction();
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
	if (evQueue != NULL) {
		al_destroy_event_queue(evQueue);
	}
	al_set_sample(sample, NULL);
	al_destroy_sample(sample_data);
	al_destroy_sample_instance(sample);
	al_destroy_mixer(mixer);
	al_destroy_voice(voice);
	al_uninstall_audio();
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();
    //disallocate memory
    return;
}

errors_s Graphics::updateGraphics(MartusMap newMap){
	this->map = newMap;
	showTransition();
	drawMap();
	if (graphicsError == G_NO_ERROR) {
		al_flip_display();
	}
    return graphicsError;
}

void Graphics::drawMap() {
	if (graphicsError == G_NO_ERROR) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		for (unsigned int u = 0; u < 12; u++) {
			showLine(u);
		}
		string str = "./resources/frame.png";
		ALLEGRO_BITMAP * bmp = al_load_bitmap(str.c_str());
		al_draw_scaled_bitmap(bmp, 67, 55, 995, 1490, 0, 0, TILE_SIDE * 16 + (DISPLAY_WIDTH_OFFSET * 2),
			TILE_SIDE * 12 + (DISPLAY_HEIGHT_OFFSET * 2), 0);
		al_destroy_bitmap(bmp);
		reDrawSide();
	}
	return;
}

void Graphics::showLine(unsigned int line){
    //Dibuja los elementos que se encuentran en la linea i del mapa, las lineas van de 0-11 y las columnas de 0-15
    std::vector<MartusTerrains> terrainsInLine;     //Creo vectores con los los elementos de la linea a dibujar
    std::vector<MartusBuildings> buildingsInLine;
    std::vector<MartusUnidades> unitsInLine;
	
	//Cargo los elementos encontrados en la linea en cada vector
    for(unsigned int j=0 ; j < map.getTerrains().size() ; j++){
        if(this->map.getTerrains()[j].getPosition().y == line)
            terrainsInLine.push_back(this->map.getTerrains()[j]);
    }
    for(unsigned int j=0 ; j < this->map.getBuildings().size() ; j++){
        if(this->map.getBuildings()[j].getPosition().y == line)
            buildingsInLine.push_back(this->map.getBuildings()[j]);
    }
    for(unsigned int j=0 ; j < this->map.getUnits().size() ; j++){
        if(this->map.getUnits()[j].getPosition().y == line)
            unitsInLine.push_back(this->map.getUnits()[j]);
    }

    //tengo cargado en las listas los elementos de la fila correspodiente
    //dibujo cada elemento en su correspondiente lugar

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

			ALLEGRO_BITMAP * bmp = al_load_bitmap(getTerrainImagePath(terrainToDraw, map.getTerrains()).c_str());
			if (bmp != NULL) {
				al_draw_scaled_bitmap(bmp, 0, 0, 350,350, terrainToDraw.getPosition().x * TILE_SIDE + DISPLAY_WIDTH_OFFSET,
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
	if (graphicsError == G_NO_ERROR) {
#ifdef FOW
		if (buildingToDraw.getFog() == false || buildingToDraw.getTeam() == map.getTeam()) {
#endif
			ALLEGRO_BITMAP * bmp = al_load_bitmap(getBuildingImagePath(buildingToDraw.getTypeOfBuilding(),
				buildingToDraw.getTeam()).c_str());
			if (bmp != NULL) {
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
	if (graphicsError == G_NO_ERROR) {
#ifdef FOW
		if (unitToDraw.getFog() == false || unitToDraw.getTeam() == map.getTeam()) {
#endif
			ALLEGRO_BITMAP * bmp = al_load_bitmap(getUnitImagePath(unitToDraw.getTypeOfUnit(),
				unitToDraw.getTeam()).c_str());

			if (bmp != NULL) {
				al_draw_scaled_bitmap(bmp, 0,0,105,105, unitToDraw.getPosition().x * TILE_SIDE + DISPLAY_WIDTH_OFFSET, //51,58
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
	if (action.act == A_CLOSE_GAME) {
		al_destroy_display(display);
		display = NULL;
		graphicsError = G_GAME_CLOSED;
	}
    return action;
}

action_s Graphics::getMouseAction(){
    ALLEGRO_EVENT ev;
    bool tmp = true;
    action_s temp;
	if (graphicsError == G_NO_ERROR) {
		while (tmp) {
			al_get_next_event(this->evQueue, &ev);
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				tmp = false;
			}
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			int x = ev.mouse.x;
			int y = ev.mouse.y;
			int xTile, yTile;
			xTile = (x - DISPLAY_WIDTH_OFFSET) / TILE_SIDE;
			yTile = (y - DISPLAY_HEIGHT_OFFSET) / TILE_SIDE;
			temp.act = A_NO_ACTION;
			temp = showPopUp(map.getOptions(xTile, yTile), xTile, yTile);
		}
		else
			temp.act = A_CLOSE_GAME;
	}
	else {
		temp.act = A_CLOSE_GAME;
	}
    return temp;
}

action_s Graphics::showPopUp(options_s opt, int xTile, int yTile){
	reDrawSide();
    int amountOfLines = 1;
	if (graphicsError == G_NO_ERROR) {
		if (opt.attackUpAvailable) {
			al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1), 0, "'W' to attack Up!");
			amountOfLines++;
		}
		if (opt.attackDownAvailable) {
			al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1), 0, "'S' to attack Down!");
			amountOfLines++;
		}
		if (opt.attackRightAvailable) {
			al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1), 0, "'D' to attack Right!");
			amountOfLines++;
		}
		if (opt.attackLeftAvailable) {
			al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1), 0, "'A' to attack Left!");
			amountOfLines++;
		}
		if (opt.buyAvailable) {
			al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1), 0, "'B' to Buy!");
			amountOfLines++;
		}
		if (opt.moveUpAvailable) {
			al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1), 0, "Up Arrow to Move Up!");
			amountOfLines++;
		}
		if (opt.moveDownAvailable) {
			al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1), 0, "Down Arrow to Move Down!");
			amountOfLines++;
		}
		if (opt.moveLeftAvailable) {
			al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1), 0, "Left Arrow to Move Left!");
			amountOfLines++;
		}
		if (opt.moveRightAvailable) {
			al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1), 0, "Right Arrow to Move Right!");
			amountOfLines++;
		}
		if (opt.passAvailable) {
			al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17, TILE_SIDE * (amountOfLines + 1), 0, "'P' to Pass!");
			amountOfLines++;
		}
		al_flip_display();
	}

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
		for (unsigned int i = 255; i > 0; i--) {
			al_clear_to_color(al_map_rgb(i, i, i));
			al_draw_text(fontLarge, al_map_rgb((255 - i), (255 - i), (255 - i)), TILE_SIDE * 3, TILE_SIDE * 5, 0,
				"Some changes have been happening during night!");
			al_flip_display();
			timerMiliseconds(10);
		}
		timerMiliseconds(10);
		for (unsigned int i = 0; i < 255; i++) {
			al_clear_to_color(al_map_rgb(i, i, i));
			al_draw_text(fontLarge, al_map_rgb((255-i),(255-i), (255-i)), TILE_SIDE * 3, TILE_SIDE*5, 0, 
				"Some changes have been happening during night!");
			al_flip_display();
			timerMiliseconds(10);
		}
	}
	return;
}

void Graphics::drawMessage() {
	if (graphicsError == G_NO_ERROR) {
		reDrawSide();
		al_draw_text(font, al_map_rgb(0, 0, 0), TILE_SIDE * 17 , TILE_SIDE * 2, 0, "Your Turn!");
		al_flip_display();
	}
	return;
}

void Graphics::displayActionInvalid() {
	if (graphicsError == G_NO_ERROR) {
		string str = "./resources/pop-up.png";
		ALLEGRO_BITMAP * bmp = al_load_bitmap(str.c_str());
		if (bmp == NULL) {
			graphicsError = G_LOAD_BITMAP_ERROR;
		}
		else {
			al_draw_scaled_bitmap(bmp, 0, 0, 575, 600, DISPLAY_WIDTH / 4, DISPLAY_HEIGHT / 4, TILE_SIDE * 5, TILE_SIDE * 5, 0);
			al_destroy_bitmap(bmp);
			al_draw_text(font, al_map_rgb(0, 0, 0), (TILE_SIDE * 7) - 10, TILE_SIDE * 5, 0, "Action Invalid!");
		}
	}
	if (graphicsError == G_NO_ERROR) {
		al_flip_display();
		timerMiliseconds(1000);
	}
	drawMap();
	if (graphicsError == G_NO_ERROR) {
		al_flip_display();
	}
	return;
}

void Graphics::showDices(int yours, int enemys) {
	if (graphicsError == G_NO_ERROR) {
		al_draw_text(fontLarge, al_map_rgb(0, 0, 0), TILE_SIDE * 5, TILE_SIDE, 0, "The Dices Were:");
		string str1, str2, str3, str;
		str1 = std::to_string(yours);
		str2 = std::to_string(enemys);
		str = str1 + "   " + str2;
		al_draw_text(fontLarge, al_map_rgb(0, 0, 0), TILE_SIDE * 7, TILE_SIDE * 2, 0, str.c_str());
		if (yours > enemys) {
			al_draw_text(fontLarge, al_map_rgb(0, 0, 0), TILE_SIDE * 6, TILE_SIDE * 3, 0, "You Win!");
		}
		else {
			al_draw_text(fontLarge, al_map_rgb(0, 0, 0), TILE_SIDE * 6, TILE_SIDE * 3, 0, "You Lose :(");
		}
		al_flip_display();
		timerMiliseconds(100);
		drawMap();
		if (graphicsError == G_NO_ERROR) {
			al_flip_display();
		}
	}
	return;
}

string Graphics::getUnitImagePath(int typeOfUnit, int team) {
	string answer;
	switch (typeOfUnit) {
	case ANTIAIR:
		answer = "./resources/Images/units/antiair_";
		break;
	case APC:
		answer = "./resources/Images/units/apc_";
		break;
	case ARTILLERY:
		answer = "./resources/Images/units/artillery_";
		break;
	case INFANTRY:
		answer = "./resources/Images/units/infantry_";
		break;
	case MECH:
		answer = "./resources/Images/units/mech_";
		break;
	case MEDTANK:
		answer = "./resources/Images/units/medtank_";
		break;
	case RECON:
		answer = "./resources/Images/units/recon_";
		break;
	case ROCKET:
		answer = "./resources/Images/units/rocket_";
		break;
	case TANK:
		answer = "./resources/Images/units/tank_";
		break;
	default:
		break;
	}
	switch (team) {
	case TEAM_RED:
		answer = answer + "1.png";
		break;
	case TEAM_BLUE:
		answer = answer + "2.png";
		break;
	case TEAM_GREEN:
		answer = answer + "3.png";
		break;
	case TEAM_YELLOW:
		answer = answer + "4.png";
		break;
	default:
		answer.clear();
		break;

	}
	return answer;
}

string Graphics::getBuildingImagePath(int typeOfBuild, int team) {
	string answer;
	switch (typeOfBuild) {
	case CITY:
		answer = "./resources/Images/building/city_";
		break;
	case FACTORY:
		answer = "./resources/Images/building/factory_";
		break;
	case HQ:
		answer = "./resources/Images/building/hq_";
		break;
	default:
		break;
	}
	switch (team) {
	case TEAM_RED:
		answer = answer + "1.png";
		break;
	case TEAM_BLUE:
		answer = answer + "2.png";
		break;
	case TEAM_GREEN:
		answer = answer + "3.png";
		break;
	case TEAM_YELLOW:
		answer = answer + "4.png";
		break;
	case NO_TEAM:
		answer = answer + "0.png";
		break;
	default:
		answer.clear();
		break;
	}
	return answer;
}

string Graphics::getTerrainImagePath(MartusTerrains terrain, std::vector<MartusTerrains> list) {
	string answer;
	if (terrain.getTypeOfTerrain() == FOREST) {
		answer = "./resources/Images/terrain/forest.png";
	}
	else if (terrain.getTypeOfTerrain() == HILL) {
		answer = "./resources/Images/terrain/hill.png";
	}
	else if (terrain.getTypeOfTerrain() == PLAIN) {
		answer = "./resources/Images/terrain/plain.png";
	}
	else if (terrain.getTypeOfTerrain() == RIVER) { //RIO
		answer = "./resources/Images/terrain/";
		bool isThereOneUp, isThereOneDown, isThereOneLeft, isThereOneRight;
		isThereOneUp = false;
		isThereOneDown = false;
		isThereOneLeft = false;
		isThereOneRight = false;
		for (unsigned int i = 0; i < list.size(); i++) {
			if (list[i].getPosition().x == terrain.getPosition().x && (list[i].getPosition().y) == terrain.getPosition().y - 1 &&
				list[i].getTypeOfTerrain() == terrain.getTypeOfTerrain()) {
				isThereOneUp = true;
			}
			else if (list[i].getPosition().x == terrain.getPosition().x && (list[i].getPosition().y) == terrain.getPosition().y + 1 &&
				list[i].getTypeOfTerrain() == terrain.getTypeOfTerrain()) {
				isThereOneDown = true;
			}
			else if ((list[i].getPosition().x) == terrain.getPosition().x - 1 && (list[i].getPosition().y) == terrain.getPosition().y &&
				list[i].getTypeOfTerrain() == terrain.getTypeOfTerrain()) {
				isThereOneLeft = true;
			}
			else if ((list[i].getPosition().x) == terrain.getPosition().x + 1 && (list[i].getPosition().y) == terrain.getPosition().y &&
				list[i].getTypeOfTerrain() == terrain.getTypeOfTerrain()) {
				isThereOneRight = true;
			}
		}
		answer = answer + "r_";
		string str;
		if (isThereOneUp) {
			str = "u";
		}
		if (isThereOneLeft) {
			str = str + "l";
		}
		if (isThereOneRight) {
			str = str + "r";
		}
		if (isThereOneDown) {
			str = str + "d";
		}
		str = str + ".png";
		answer = answer + str;
	}
	else if (terrain.getTypeOfTerrain() == STREET) { //Camino
		answer = "./resources/Images/terrain/";
		bool isThereOneUp, isThereOneDown, isThereOneLeft, isThereOneRight;
		isThereOneUp = false;
		isThereOneDown = false;
		isThereOneLeft = false;
		isThereOneRight = false;
		for (unsigned int i = 0; i < list.size(); i++) {
			if (list[i].getPosition().x == terrain.getPosition().x && (list[i].getPosition().y) == terrain.getPosition().y - 1 &&
				list[i].getTypeOfTerrain() == terrain.getTypeOfTerrain()) {
				isThereOneUp = true;
			}
			else if (list[i].getPosition().x == terrain.getPosition().x && (list[i].getPosition().y) == terrain.getPosition().y + 1 &&
				list[i].getTypeOfTerrain() == terrain.getTypeOfTerrain()) {
				isThereOneDown = true;
			}
			else if ((list[i].getPosition().x) == terrain.getPosition().x - 1 && (list[i].getPosition().y) == terrain.getPosition().y &&
				list[i].getTypeOfTerrain() == terrain.getTypeOfTerrain()) {
				isThereOneLeft = true;
			}
			else if ((list[i].getPosition().x) == terrain.getPosition().x + 1 && (list[i].getPosition().y) == terrain.getPosition().y &&
				list[i].getTypeOfTerrain() == terrain.getTypeOfTerrain()) {
				isThereOneRight = true;
			}
		}
		answer = answer + "c_";
		string str;
		if (isThereOneUp) {
			str = "u";
		}
		if (isThereOneLeft) {
			str = str + "l";
		}
		if (isThereOneRight) {
			str = str + "r";
		}
		if (isThereOneDown) {
			str = str + "d";
		}
		str = str + ".png";
		answer = answer + str;
	}
	return answer;
}

void Graphics::reDrawSide() {
	string str = "./resources/pop-up.png";
	ALLEGRO_BITMAP *bmp = al_load_bitmap(str.c_str());
	al_draw_scaled_bitmap(bmp, 0, 0, 575, 600, TILE_SIDE * 16, -24, TILE_SIDE * 6.6, TILE_SIDE *13.5, 0);
	al_destroy_bitmap(bmp);
	return;
}

void Graphics::introduction() {
	if (graphicsError == G_NO_ERROR) {
		ALLEGRO_BITMAP * bmp = al_load_bitmap("./resources/banner.png");
		if (bmp != NULL) {
			//timerMiliseconds(1000);
			for (int i = DISPLAY_HEIGHT; i > 0; i--) {
				al_clear_to_color(al_map_rgb(255, 255, 255));
				al_draw_scaled_bitmap(bmp, 0, 0, 1000, 500, 0, i, DISPLAY_WIDTH,DISPLAY_HEIGHT +i, 0);
				if (graphicsError == G_NO_ERROR) {
					al_flip_display();
				}
				timerMiliseconds(10);
			}
			al_destroy_bitmap(bmp);
		}
		else {
			graphicsError = G_LOAD_BITMAP_ERROR;
		}
		bmp = al_load_bitmap("./resources/pressstart.png");
		if (bmp != NULL && graphicsError == G_NO_ERROR) {
			al_draw_bitmap(bmp, TILE_SIDE * 5, TILE_SIDE * 8,0);
			if (graphicsError == G_NO_ERROR) {
				al_flip_display();
			}
			al_destroy_bitmap(bmp);
		}
		else {
			graphicsError = G_LOAD_BITMAP_ERROR;
		}
		ALLEGRO_EVENT ev;
		bool tmp = false;
		while (!tmp) {
			al_wait_for_event(evQueue, &ev);
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || ev.type == ALLEGRO_EVENT_KEY_DOWN
				|| ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				tmp = true;
			}
		}
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_text(fontLarge, al_map_rgb(0, 0, 0), TILE_SIDE * 9, TILE_SIDE * 5, 0,"Please Wait");
		al_flip_display();
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			graphicsError = G_GAME_CLOSED;
		}
	}
	return;
}