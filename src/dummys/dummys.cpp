#include "./dummys.h"


void MartusUnidades::setUnit(int type, position_s pos, int team, bool fog) {
	typeOfUnit = type;
	position = pos;
	this->team = team;
	this->fog = fog;
	return;
}

position_s MartusUnidades::getPosition() {
	return position;
}

int MartusUnidades::getTypeOfUnit() {
	return typeOfUnit;
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




void MartusTerrains::setTerrain(terrains_d type, position_s pos, bool fog) {
	this->typeOfTerrain = type;
	this->position = pos;
	this->fog = fog;
	return;
}

position_s MartusTerrains::getPosition() {
	return position;
}

int MartusTerrains::getTypeOfTerrain() {
	return typeOfTerrain;
}

bool MartusTerrains::getFog() {
	return fog;
}

void MartusTerrains::setFogOn() {
	fog = true;
	return;
}




void MartusBuildings::setBuilding(int type, position_s pos, int team, bool fog) {
	this->typeOfBuilding = type;
	this->position = pos;
	this->team = team;
	this->fog = fog;
}

position_s MartusBuildings::getPosition() {
	return position;
}

int MartusBuildings::getTypeOfBuilding() {
	return typeOfBuilding;
}

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

void MartusMap::setTerrains(std::vector<MartusTerrains> newTerr) {
	this->terrains.clear();
	this->terrains = newTerr;
	return;
}

void MartusMap::setBuildings(std::vector<MartusBuildings> newBuild) {
	this->buildings.clear();
	this->buildings = newBuild;
	return;
}

void MartusMap::setUnits(std::vector<MartusUnidades> newUnits) {
	this->units.clear();
	this->units = newUnits;
	return;
}
