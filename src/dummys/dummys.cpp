#include "./dummys.h"


void Unit::setUnit(int type, position_s pos, int team, bool fog) {
	typeOfUnit = type;
	position = pos;
	this->team = team;
	this->fog = fog;
	return;
}

position_s Unit::getPosition() {
	return position;
}

int Unit::getTypeOfUnit() {
	return typeOfUnit;
}

int Unit::getTeam() {
	return team;
}

bool Unit::getFog() {
	return fog;
}

void Unit::setFogOn() {
	fog = true;
	return;
}

void Terrain::setTerrain(terrains_d type, position_s pos, bool fog) {
	this->typeOfTerrain = type;
	this->position = pos;
	this->fog = fog;
	return;
}

position_s Terrain::getPosition() {
	return position;
}

int Terrain::getTypeOfTerrain() {
	return typeOfTerrain;
}

bool Terrain::getFog() {
	return fog;
}

void Terrain::setFogOn() {
	fog = true;
	return;
}

void Building::setBuilding(int type, position_s pos, int team, bool fog) {
	this->typeOfBuilding = type;
	this->position = pos;
	this->team = team;
	this->fog = fog;
}

position_s Building::getPosition() {
	return position;
}

int Building::getTypeOfBuilding() {
	return typeOfBuilding;
}

int Building::getTeam() {
	return team;
}

bool Building::getFog() {
	return fog;
}

void Building::setFogOn() {
	fog = true;
	return;
}

std::vector<Building> Map::getBuildings() {
	return buildings;
}

std::vector<Terrain> Map::getTerrains() {
	return terrains;
}

std::vector<Unit> Map::getUnits() {
	return units;
}

bool Map::isThereAUnitThere(int x, int y) {
	bool answer = false;
	for (unsigned int i = 0; i <= units.size(); i++) {
		if (units[i].getPosition().x == x && units[i].getPosition().y == y) {
			answer = true;
		}
	}
	return answer;
}

bool Map::isThereABuildingThere(int x, int y) {
	bool answer = false;
	for (unsigned int i = 0; i <= buildings.size(); i++) {
		if (buildings[i].getPosition().x == x && buildings[i].getPosition().y == y) {
			answer = true;
		}
	}
	return answer;
}

options_s Map::getOptions(int x, int y) {
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

bool Map::isThereAnEnemyThere(int x, int y, int enemyTeam) {
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

bool Map::isThereAFriendUnitThere(int x, int y) {
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

bool Map::isThereAFriendBuildingThere(int x, int y) {
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

int Map::getTeam() {
	return this->team;
}

int Map::getEnemyTeam() {
	return this->enemyTeam;
}

void Map::setTeam(int tmp) {
	this->team = tmp;
	return;
}

void Map::setEnemyTeam(int tmp) {
	this->enemyTeam = tmp;
	return;
}

void Map::addTerrain(Terrain newTerrain) {
	this->terrains.push_back(newTerrain);
	return;
}

void Map::addBuilding(Building newBuilding) {
	this->buildings.push_back(newBuilding);
	return;
}

void Map::addUnit(Unit newUnit) {
	this->units.push_back(newUnit);
	return;
}

void Map::setTerrains(std::vector<Terrain> newTerr) {
	this->terrains.clear();
	this->terrains = newTerr;
	return;
}

void Map::setBuildings(std::vector<Building> newBuild) {
	this->buildings.clear();
	this->buildings = newBuild;
	return;
}

void Map::setUnits(std::vector<Unit> newUnits) {
	this->units.clear();
	this->units = newUnits;
	return;
}