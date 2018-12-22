//////////////////////////////////////////////////////////
//Libreria Graphics                                     //
//Encargada de manejar toda la parte grafica del juego  //
//skirmich Wars. TP FINAL EDA, 1er Cuatrimestre 2017    //
//Trabajo Hecho por:                                    //
//  -Ian Diaz                                           //
//  -Martina Maspero                                    //
//                                          26/08/2018  //
//////////////////////////////////////////////////////////
/*Definiciones:
-   Las posiciones son discretas y estan horizontalmente de 0 a 15 y verticalmente de 0-11.
    La posicion (0,0) se encuentra en la esquina superior izquierda del mapa y la posicion
    (15,11) en la esquina inferior derecha.

-   Las clases "terrenos", "edificios" y "unidades" deben tener, aparte de las que se necesite,
    los metodos que poseen las clases de 'dummy.h'
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define DEBUG
//#define FOW

#include <iostream>
#include <vector>

#ifdef  DEBUG
    #include "./dummys/dummys.h"
#endif


#ifdef __linux__
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#elif _WIN32
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#endif





typedef enum {A_NO_ACTION, A_ATTACK, A_MOVE , A_PURCHASE, A_PASS ,A_CLOSE_GAME}act_s;

typedef enum {G_LOAD_GRAPHICS_ERROR, G_NO_ERROR,G_LOAD_BITMAP_ERROR, G_DISPLAY_ERROR, G_LOAD_FONT_ERROR}errors_s;

typedef struct{
    position_s positionFrom;
    position_s positionTo;
    MartusUnidades unitType;
}movement_s;

typedef struct {
	act_s act;
	position_s positionFrom;
	position_s positionTo;
}action_s;



class Graphics
{
public:
    Graphics(std::vector<MartusTerrains> newTerrainList, 
                std::vector<MartusUnidades> newUnitList, 
                std::vector<MartusBuildings> newBuildingList);
/*Funcion de inicializacion de la clase, se le debe pasar 3 vectores uno con Terrenos, otro con unidades y
el tercero con edificios.
NO devuelve nada.
*/
    ~Graphics();
    
    void setTeam(int team);
/*Funcion de seteo del team del correspondiente jugador, se le debe pasar TEAM_1, TEAM_2, TEAM_3 o TEAM_4 como parametro y no devuelve nada.
Sirve para ver el color de tus propias unidades.
*/
    //introduction(); //poner algun presentacion al juego para hacerlo mas copado

    errors_s updateGraphics(std::vector<MartusUnidades> unitList,
                            std::vector<MartusBuildings> buildingList);
/*  Esta funcion se la utiliza para actualizar los vectores de unidades y de edificios que fueron modificados por el
jugador oponente. Se le pasa el nuevo vector de unidades, y el nuevo vector de edificios que actualiza el vector contenido
dentro de esta clase. Y una vez actualizado grafica todas las lineas del mapa para que se vean en pantalla.
Devuelve: un errors_s que estan especificados al principio de este archivo
*/
    action_s getUserAction();
/*Funcion encargada de obtener los movimientos que haga el usuario. Recibe como parametro un callback
al que se le pasara una accion y respondera true si esa accion es valida, o false si no lo es.
Devuelve: una action_s
*/

	errors_s getError();

protected:
    std::vector<MartusUnidades> unitList;
    std::vector<MartusBuildings> buildingList;
    std::vector<MartusTerrains> terrainList;
    MartusMap map;
    int team;
private:
    void showLine(unsigned int i); //partially done
    //
    //Funcion encargada de dibujar en el display la linea numero i contando de arriba hacia abajo, es decir la linea
    // numero 0 es la linea horizontal superior y la linea numero 11  es la linea horizontal inferior.
    //
    void drawTerrain(MartusTerrains terrainToDraw);//partially done
    void drawBuilding(MartusBuildings buildingToDraw);//partially done
    void drawUnit(MartusUnidades unitToDraw);//partially done
    void showTransition();//not done
    action_s getMouseAction(void);//partially done
    action_s getKeyboardAction(int xTile, int yTile);//partially done
    action_s showPopUp(options_s opt, int xTile, int yTile); //partially done
	void drawMap();//done
	void drawMessage();



    std::vector<MartusUnidades> newUnitList;
    std::vector<MartusBuildings> newBuildingList;
    std::vector<MartusTerrains> newTerrainList;
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * evQueue = NULL;
    ALLEGRO_FONT *font = NULL;
	ALLEGRO_FONT *fontLarge = NULL;
	errors_s graphicsError;
};

#endif