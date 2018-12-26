

#include <iostream>
#include "./Graphics.h"
#include "./dummys/dummys.h"
#include <allegro5/allegro.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

int main(void) {
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // _WIN32
	srand(time(NULL));
	if (!al_init()) {
		printf("Could Not Init Alegro\n");
		return -1;
	}
	Map tstMap;
	Terrain tstTerr;
	Unit tstUnit;
	Building tstBuil;
	position_s pos;
	for (int i = 0; i < 12; i++) {
		for (int u = 0; u < 16; u++) {
			pos.x = u;
			pos.y = i;
			int a = rand() % 5;
			switch (a) {
			case 0:
				tstTerr.setTerrain(FOREST, pos, true);
				break;
			case 1:
				tstTerr.setTerrain(HILL, pos, true);
				break;
			case 2:
				tstTerr.setTerrain(PLAIN, pos, true);
				break;
			case 3:
				tstTerr.setTerrain(RIVER, pos, true);
				break;
			case 4:
				tstTerr.setTerrain(STREET, pos, true);
				break;
			default: 
				tstTerr.setTerrain(STREET, pos, true);
				break;
			}
			tstMap.addTerrain(tstTerr);
		}
	}
	tstMap.setTeam(TEAM_BLUE);

	for (int i = 0; i < rand() % 30; i++) {
		pos.x = rand() % 16;
		pos.y = rand() % 12;
		int a = rand() % 9;
		int b = rand() % 4;
		tstUnit.setUnit(a, pos, b, true);
		tstMap.addUnit(tstUnit);
	}

	for (int u = 0; u < rand() % 15; u++) {
		pos.x = rand() % 16;
		pos.y = rand() % 12;
		int a = rand() % 3;
		int b = rand() % 5;
		tstBuil.setBuilding(a, pos, TEAM_GREEN, true);
		tstMap.addBuilding(tstBuil);
	}
	Graphics tstGr(tstMap);
	action_s act = tstGr.getUserAction();
	pos.x = 7;
	pos.y = 9;
	tstUnit.setUnit(ARTILLERY, pos, TEAM_YELLOW, true);
	tstMap.addUnit(tstUnit);
	tstGr.updateGraphics(tstMap);
	act = tstGr.getUserAction();
	tstGr.showDices((rand()%6)+1, (rand()%6)+1);
	return 0;
}