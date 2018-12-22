#include "./dummys.h"


void MartusUnidades::setUnit(units_d type, position_s pos, int team, bool fog) {
	typeOfUnit = type;
	position = pos;
	this->team = team;
	this->fog = fog;
	return;
}

position_s MartusUnidades::getPosition() {
	return position;
}

units_d MartusUnidades::getTypeOfUnit() {
	return typeOfUnit;
}

/*string MartusUnidades::getImagePath() {
	string answer;
	if (team == TEAM_3) {
		switch (typeOfUnit) {
		case UNIDAD_1:
			answer = "./resources/Images/units/antiair_3.png";
			break;
		case UNIDAD_2:
			answer = "./resources/Images/units/apc_3.png";
			break;
		case UNIDAD_3:
			answer = "./resources/Images/units/artillery_3.png";
			break;
		case UNIDAD_4:
			answer = "./resources/Images/units/infantry_3.png";
			break;
		case UNIDAD_5:
			answer = "./resources/Images/units/mech_3.png";
			break;
		case UNIDAD_6:
			answer = "./resources/Images/units/medtank_3.png";
			break;
		case UNIDAD_7:
			answer = "./resources/Images/units/recon_3.png";
			break;
		case UNIDAD_8:
			answer = "./resources/Images/units/rocket_3.png";
			break;
		case UNIDAD_9:
			answer = "./resources/Images/units/tank_3.png";
			break;
		default:
			break;
		}
	}
	else if (team == TEAM_1) {
		switch (typeOfUnit) {
		case UNIDAD_1:
			answer = "./resources/Images/units/antiair_1.png";
			break;
		case UNIDAD_2:
			answer = "./resources/Images/units/apc_1.png";
			break;
		case UNIDAD_3:
			answer = "./resources/Images/units/artillery_1.png";
			break;
		case UNIDAD_4:
			answer = "./resources/Images/units/infantry_1.png";
			break;
		case UNIDAD_5:
			answer = "./resources/Images/units/mech_1.png";
			break;
		case UNIDAD_6:
			answer = "./resources/Images/units/medtank_1.png";
			break;
		case UNIDAD_7:
			answer = "./resources/Images/units/recon_1.png";
			break;
		case UNIDAD_8:
			answer = "./resources/Images/units/rocket_1.png";
			break;
		case UNIDAD_9:
			answer = "./resources/Images/units/tank_1.png";
			break;
		default:
			break;
		}
	}
	else if (team == TEAM_2) {
		switch (typeOfUnit) {
		case UNIDAD_1:
			answer = "./resources/Images/units/antiair_2.png";
			break;
		case UNIDAD_2:
			answer = "./resources/Images/units/apc_2.png";
			break;
		case UNIDAD_3:
			answer = "./resources/Images/units/artillery_2.png";
			break;
		case UNIDAD_4:
			answer = "./resources/Images/units/infantry_2.png";
			break;
		case UNIDAD_5:
			answer = "./resources/Images/units/mech_2.png";
			break;
		case UNIDAD_6:
			answer = "./resources/Images/units/medtank_2.png";
			break;
		case UNIDAD_7:
			answer = "./resources/Images/units/recon_2.png";
			break;
		case UNIDAD_8:
			answer = "./resources/Images/units/rocket_2.png";
			break;
		case UNIDAD_9:
			answer = "./resources/Images/units/tank_2.png";
			break;
		default:
			break;
		}
	}
	else if (team == TEAM_4) {
		switch (typeOfUnit) {
		case UNIDAD_1:
			answer = "./resources/Images/units/antiair_4.png";
			break;
		case UNIDAD_2:
			answer = "./resources/Images/units/apc_4.png";
			break;
		case UNIDAD_3:
			answer = "./resources/Images/units/artillery_4.png";
			break;
		case UNIDAD_4:
			answer = "./resources/Images/units/infantry_4.png";
			break;
		case UNIDAD_5:
			answer = "./resources/Images/units/mech_4.png";
			break;
		case UNIDAD_6:
			answer = "./resources/Images/units/medtank_4.png";
			break;
		case UNIDAD_7:
			answer = "./resources/Images/units/recon_4.png";
			break;
		case UNIDAD_8:
			answer = "./resources/Images/units/rocket_4.png";
			break;
		case UNIDAD_9:
			answer = "./resources/Images/units/tank_4.png";
			break;
		default:
			break;
		}
	}
	return answer;
}*/

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

void MartusTerrains::setTerrain(terrains_d type, position_s pos, bool fog) {
	this->typeOfTerrain = type;
	this->position = pos;
	this->fog = fog;
	return;
}

position_s MartusTerrains::getPosition() {
	return position;
}

terrains_d MartusTerrains::getTypeOfTerrain() {
	return typeOfTerrain;
}

/*string MartusTerrains::getImagePath() {
	string answer;
	switch (typeOfTerrain) {
	case TERRENO_1:
		answer = "./resources/Images/terrain/forest.png";
		break;
	case TERRENO_2:
		answer = "./resources/Images/terrain/hill.png";
		break;
	case TERRENO_3:
		answer = "./resources/Images/terrain/plain.png";
		break;
	case TERRENO_4:
		answer = "./resources/Images/terrain/river.png";
		break;
	case TERRENO_5:
		answer = "./resources/Images/terrain/road.png";
		break;
	default:
		break;
	}
	return answer;
}*/

bool MartusTerrains::getFog() {
	return fog;
}

void MartusTerrains::setFogOn() {
	fog = true;
	return;
}

void MartusBuildings::setBuilding(buildings_d type, position_s pos, int team, bool fog) {
	this->typeOfBuilding = type;
	this->position = pos;
	this->team = team;
	this->fog = fog;
}

position_s MartusBuildings::getPosition() {
	return position;
}

buildings_d MartusBuildings::getTypeOfBuilding() {
	return typeOfBuilding;
}

/*string MartusBuildings::getImagePath() {
	string answer;
	if (buildingIsFree) {
		if (team == TEAM_3) {
			switch (typeOfBuilding) {
			case EDIFICIO_1:
				answer = "./resources/Images/building/city_3.png";
				break;
			case EDIFICIO_2:
				answer = "./resources/Images/building/factory_3.png";
				break;
			case EDIFICIO_3:
				answer = "./resources/Images/building/hq_3.png";
				break;
			default:
				break;
			}
		}
		else if (team == TEAM_1) {
			switch (typeOfBuilding) {
			case EDIFICIO_1:
				answer = "./resources/Images/building/city_1.png";
				break;
			case EDIFICIO_2:
				answer = "./resources/Images/building/factory_1.png";
				break;
			case EDIFICIO_3:
				answer = "./resources/Images/building/hq_1.png";
				break;
			default:
				break;
			}
		}
		else if (team == TEAM_2) {
			switch (typeOfBuilding) {
			case EDIFICIO_1:
				answer = "./resources/Images/building/city_2.png";
				break;
			case EDIFICIO_2:
				answer = "./resources/Images/building/factory_2.png";
				break;
			case EDIFICIO_3:
				answer = "./resources/Images/building/hq_2.png";
				break;
			default:
				break;
			}
		}
		else if (team == TEAM_4) {
			switch (typeOfBuilding) {
			case EDIFICIO_1:
				answer = "./resources/Images/building/city_4.png";
				break;
			case EDIFICIO_2:
				answer = "./resources/Images/building/factory_4.png";
				break;
			case EDIFICIO_3:
				answer = "./resources/Images/building/hq_4.png";
				break;
			default:
				break;
			}
		}
	}
	else {
		switch (typeOfBuilding) {
		case EDIFICIO_1:
			answer = "./resources/Images/building/city_0.png";
			break;
		case EDIFICIO_2:
			answer = "./resources/Images/building/factory_0.png";
			break;
		default:
			break;
		}
	}
	return answer;
}*/

int MartusBuildings::getTeam() {
	return team;
}

bool MartusBuildings::getFog() {
	return fog;
}

void MartusBuildings::setFogOn() {
	fog = true;
	return;
}

std::vector<MartusBuildings> MartusMap::getBuildings() {
	return buildings;
}

std::vector<MartusTerrains>	MartusMap::getTerrains() {
	return terrains;
}

std::vector<MartusUnidades> MartusMap::getUnits() {
	return units;
}

bool MartusMap::isThereAUnitThere(int x, int y) {
	bool answer = false;
	for (unsigned int i = 0; i <= units.size(); i++) {
		if (units[i].getPosition().x == x && units[i].getPosition().y == y) {
			answer = true;
		}
	}
	return answer;
}

bool MartusMap::isThereABuildingThere(int x, int y) {
	bool answer = false;
	for (unsigned int i = 0; i <= buildings.size(); i++) {
		if (buildings[i].getPosition().x == x && buildings[i].getPosition().y == y) {
			answer = true;
		}
	}
	return answer;
}

options_s MartusMap::getOptions(int x, int y) {
	options_s tmp;
	tmp.attackDownAvailable = false;
	tmp.attackLeftAvailable = false;
	tmp.attackRightAvailable = false;
	tmp.attackUpAvailable = false;
	tmp.buyAvailable = false;
	tmp.moveDownAvailable = false;
	tmp.moveLeftAvailable = false;
	tmp.moveRightAvailable = false;
	tmp.moveUpAvailable = false;
	tmp.passAvailable = true;
	if (isThereAFriendUnitThere(x, y)) {
		if (isThereAnEnemyThere(x, y-1, getEnemyTeam())) {
			tmp.attackUpAvailable = true;
			tmp.moveUpAvailable = false;
		}
		else {
			tmp.attackUpAvailable = false;
			tmp.moveUpAvailable = true;
		}
		if (isThereAnEnemyThere(x, y + 1, getEnemyTeam())) {
			tmp.attackDownAvailable = true;
			tmp.moveDownAvailable = false;
		}
		else {
			tmp.attackDownAvailable = false;
			tmp.moveDownAvailable = true;
		}
		if (isThereAnEnemyThere(x-1, y, getEnemyTeam())) {
			tmp.attackLeftAvailable = true;
			tmp.moveLeftAvailable = false;
		}
		else {
			tmp.attackLeftAvailable = false;
			tmp.moveLeftAvailable = true;
		}
		if (isThereAnEnemyThere(x+1, y , getEnemyTeam())) {
			tmp.attackRightAvailable = true;
			tmp.moveRightAvailable = false;
		}
		else {
			tmp.attackRightAvailable = false;
			tmp.moveRightAvailable = true;
		}
	}
	else if (isThereAFriendBuildingThere(x, y)) {
		tmp.buyAvailable = true;
	}
	return tmp;
}

bool MartusMap::isThereAnEnemyThere(int x, int y, int enemyTeam) {
	bool exit = false;

	for (unsigned int i = 0; i < units.size(); i++) {
		if (units[i].getPosition().x == x && units[i].getPosition().y == y) {
			if (units[i].getTeam() == enemyTeam) {
				exit = true;
			}
		}
	}
	for (unsigned int i = 0; i < buildings.size(); i++) {
		if (buildings[i].getPosition().x == x && buildings[i].getPosition().y == y) {
			if (buildings[i].getTeam() == enemyTeam) {
				exit = true;
			}
		}
	}
	return exit;
}

bool MartusMap::isThereAFriendUnitThere(int x, int y) {
	bool answer = false;
	for (unsigned int i = 0; i < units.size(); i++) {
		if (units[i].getPosition().x == x && units[i].getPosition().y == y) {
			if (units[i].getTeam() == this->getTeam()) {
				answer = true;
			}
		}
	}
	return answer;
}

bool MartusMap::isThereAFriendBuildingThere(int x, int y) {
	bool answer = false;
	for (unsigned int i = 0; i < buildings.size(); i++) {
		if (buildings[i].getPosition().x == x && buildings[i].getPosition().y == y) {
			if (buildings[i].getTeam() == this->getTeam()) {
				answer = true;
			}
		}
	}
	return answer;
}

int MartusMap::getTeam() {
	return this->team;
}

int MartusMap::getEnemyTeam() {
	return this->enemyTeam;
}

void MartusMap::setTeam(int tmp) {
	this->team = tmp;
	return;
}

void MartusMap::setEnemyTeam(int tmp) {
	this->enemyTeam = tmp;
	return;
}

void MartusMap::addTerrain(MartusTerrains newTerrain) {
	this->terrains.push_back(newTerrain);
	return;
}

void MartusMap::addBuilding(MartusBuildings newBuilding) {
	this->buildings.push_back(newBuilding);
	return;
}

void MartusMap::addUnit(MartusUnidades newUnit) {
	this->units.push_back(newUnit);
	return;
}