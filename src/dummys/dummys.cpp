#include "./dummys.h"

position_s MartusUnidades::getPosition() {
	return position;
}

units_d MartusUnidades::getTypeOfUnit() {
	return typeOfUnit;
}

string MartusUnidades::getImagePath() {
	string answer;
	if (team == TEAM_3) {
		switch (typeOfUnit) {
		case UNIDAD_1:
			answer = "../resources/Images/units/antiair_3.png";
			break;
		case UNIDAD_2:
			answer = "../resources/Images/units/apc_3.png";
			break;
		case UNIDAD_3:
			answer = "../resources/Images/units/artillery_3.png";
			break;
		case UNIDAD_4:
			answer = "..resources/Images/units/infantry_3.png";
			break;
		case UNIDAD_5:
			answer = "../resources/Images/units/mech_3.png";
			break;
		case UNIDAD_6:
			answer = "../resources/Images/units/medtank_3.png";
			break;
		case UNIDAD_7:
			answer = "../resources/Images/units/recon_3.png";
			break;
		case UNIDAD_8:
			answer = "../resources/Images/units/rocket_3.png";
			break;
		case UNIDAD_9:
			answer = "../resources/Images/units/tank_3.png";
			break;
		default:
			break;
		}
	}
	else if (team == TEAM_1) {
		switch (typeOfUnit) {
		case UNIDAD_1:
			answer = "../resources/Images/units/antiair_1.png";
			break;
		case UNIDAD_2:
			answer = "../resources/Images/units/apc_1.png";
			break;
		case UNIDAD_3:
			answer = "../resources/Images/units/artillery_1.png";
			break;
		case UNIDAD_4:
			answer = "..resources/Images/units/infantry_1.png";
			break;
		case UNIDAD_5:
			answer = "../resources/Images/units/mech_1.png";
			break;
		case UNIDAD_6:
			answer = "../resources/Images/units/medtank_1.png";
			break;
		case UNIDAD_7:
			answer = "../resources/Images/units/recon_1.png";
			break;
		case UNIDAD_8:
			answer = "../resources/Images/units/rocket_1.png";
			break;
		case UNIDAD_9:
			answer = "../resources/Images/units/tank_1.png";
			break;
		default:
			break;
		}
	}
	else if (team == TEAM_2) {
		switch (typeOfUnit) {
		case UNIDAD_1:
			answer = "../resources/Images/units/antiair_2.png";
			break;
		case UNIDAD_2:
			answer = "../resources/Images/units/apc_2.png";
			break;
		case UNIDAD_3:
			answer = "../resources/Images/units/artillery_2.png";
			break;
		case UNIDAD_4:
			answer = "..resources/Images/units/infantry_2.png";
			break;
		case UNIDAD_5:
			answer = "../resources/Images/units/mech_2.png";
			break;
		case UNIDAD_6:
			answer = "../resources/Images/units/medtank_2.png";
			break;
		case UNIDAD_7:
			answer = "../resources/Images/units/recon_2.png";
			break;
		case UNIDAD_8:
			answer = "../resources/Images/units/rocket_2.png";
			break;
		case UNIDAD_9:
			answer = "../resources/Images/units/tank_2.png";
			break;
		default:
			break;
		}
	}
	else if (team == TEAM_4) {
		switch (typeOfUnit) {
		case UNIDAD_1:
			answer = "../resources/Images/units/antiair_4.png";
			break;
		case UNIDAD_2:
			answer = "../resources/Images/units/apc_4.png";
			break;
		case UNIDAD_3:
			answer = "../resources/Images/units/artillery_4.png";
			break;
		case UNIDAD_4:
			answer = "..resources/Images/units/infantry_4.png";
			break;
		case UNIDAD_5:
			answer = "../resources/Images/units/mech_4.png";
			break;
		case UNIDAD_6:
			answer = "../resources/Images/units/medtank_4.png";
			break;
		case UNIDAD_7:
			answer = "../resources/Images/units/recon_4.png";
			break;
		case UNIDAD_8:
			answer = "../resources/Images/units/rocket_4.png";
			break;
		case UNIDAD_9:
			answer = "../resources/Images/units/tank_4.png";
			break;
		default:
			break;
		}
	}
	return answer;
}

int MartusUnidades::getTeam() {
	return team;
}

bool MartusUnidades::getFog() {
	return fog;
}

void MartusUnidades::setFogOn() {
	fog = true;
	return;
}

position_s MartusTerrains::getPosition() {
	return position;
}

terrains_d MartusTerrains::getTypeOfTerrain() {
	return typeOfTerrain;
}

string MartusTerrains::getImagePath() {
	string answer;
	switch (typeOfTerrain) {
	case TERRENO_1:
		answer = "../resources/Images/terrain/forest.png";
		break;
	case TERRENO_2:
		answer = "../resources/Images/units/hill.png";
		break;
	case TERRENO_3:
		answer = "../resources/Images/units/plain.png";
		break;
	case TERRENO_4:
		answer = "..resources/Images/units/river.png";
		break;
	case TERRENO_5:
		answer = "../resources/Images/units/road.png";
		break;
	default:
		break;
	}
	return answer;
}

bool MartusTerrains::getFog() {
	return fog;
}

void MartusTerrains::setFogOn() {
	fog = true;
	return;
}

position_s MartusBuildings::getPosition() {
	return position;
}

buildings_d MartusBuildings::getTypeOfBuilding() {
	return typeOfBuilding;
}

string MartusBuildings::getImagePath() {
	string answer;
	if (buildingIsFree) {
		if (team == TEAM_3) {
			switch (typeOfBuilding) {
			case EDIFICIO_1:
				answer = "../resources/Images/building/city_3.png";
				break;
			case EDIFICIO_2:
				answer = "../resources/Images/building/factory_3.png";
				break;
			case EDIFICIO_3:
				answer = "../resources/Images/building/hq_3.png";
				break;
			default:
				break;
			}
		}
		else if (team == TEAM_1) {
			switch (typeOfBuilding) {
			case EDIFICIO_1:
				answer = "../resources/Images/building/city_1.png";
				break;
			case EDIFICIO_2:
				answer = "../resources/Images/building/factory_1.png";
				break;
			case EDIFICIO_3:
				answer = "../resources/Images/building/hq_1.png";
				break;
			default:
				break;
			}
		}
		else if (team == TEAM_2) {
			switch (typeOfBuilding) {
			case EDIFICIO_1:
				answer = "../resources/Images/building/city_2.png";
				break;
			case EDIFICIO_2:
				answer = "../resources/Images/building/factory_2.png";
				break;
			case EDIFICIO_3:
				answer = "../resources/Images/building/hq_2.png";
				break;
			default:
				break;
			}
		}
		else if (team == TEAM_4) {
			switch (typeOfBuilding) {
			case EDIFICIO_1:
				answer = "../resources/Images/building/city_4.png";
				break;
			case EDIFICIO_2:
				answer = "../resources/Images/building/factory_4.png";
				break;
			case EDIFICIO_3:
				answer = "../resources/Images/building/hq_4.png";
				break;
			default:
				break;
			}
		}
	}
	else {
		switch (typeOfBuilding) {
		case EDIFICIO_1:
			answer = "../resources/Images/building/city_0.png";
			break;
		case EDIFICIO_2:
			answer = "../resources/Images/building/factory_0.png";
			break;
		default:
			break;
		}
	}
	return answer;
}