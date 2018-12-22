

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
			pos.x = u;
			pos.y = i;
			tstTerr.setTerrain(TERRENO_3, pos, true);
			tstMap.addTerrain(tstTerr);
		}
	}
	tstMap.setTeam(TEAM_2);

	pos.x = 0;
	pos.y = 0;
	tstUnit.setUnit(UNIDAD_4, pos, TEAM_1, true);
	tstMap.addUnit(tstUnit);
	pos.x = 5;
	pos.y = 4;
	tstUnit.setUnit(UNIDAD_4, pos, TEAM_2, true);
	tstMap.addUnit(tstUnit);
	pos.x = 0;
	pos.y = 11;
	tstBuil.setBuilding(EDIFICIO_1, pos, TEAM_3, true);
	tstMap.addBuilding(tstBuil);

	Graphics tstGr(tstMap.getTerrains(), tstMap.getUnits(), tstMap.getBuildings());
	tstGr.getUserAction();
	tstGr.displayActionInvalid();
	pos.x = 7;
	pos.y = 9;
	tstUnit.setUnit(UNIDAD_2, pos, TEAM_4, true);
	tstMap.addUnit(tstUnit);
	tstGr.updateGraphics(tstMap.getUnits(),tstMap.getBuildings());
	tstGr.getUserAction();
	tstGr.showDices(13, 5);
	return 0;
}