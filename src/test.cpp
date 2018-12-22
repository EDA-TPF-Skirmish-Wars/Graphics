

#include <iostream>
#include "./Graphics.h"
#include "./dummys/dummys.h"
#include <allegro5/allegro.h>

int main(void) {
	if (!al_init()) {
		printf("Could Not Init Alegro\n");
		return -1;
	}
	MartusMap tstMap;
	MartusTerrains tstTerr;
	MartusUnidades tstUnit;
	MartusBuildings tstBuil;
	position_s pos;
	for (int i = 0; i < 12; i++) {
		for (int u = 0; u < 16; u++) {
			pos.x = i;
			pos.y = u;
			tstTerr.setTerrain(TERRENO_3, pos, true);
			tstMap.addTerrain(tstTerr);
		}
	}
	pos.x = 5;
	pos.y = 5;
	tstUnit.setUnit(UNIDAD_4, pos, TEAM_1, true);
	tstMap.addUnit(tstUnit);
	pos.x = 5;
	pos.y = 4;
	tstUnit.setUnit(UNIDAD_4, pos, TEAM_2, true);
	tstMap.addUnit(tstUnit);
	pos.x = 7;
	pos.y = 7;
	tstBuil.setBuilding(EDIFICIO_1, pos, TEAM_3, true);
	tstMap.addBuilding(tstBuil);

	Graphics tstGr(tstMap.getTerrains(), tstMap.getUnits(), tstMap.getBuildings());

	getchar();
	return 0;
}