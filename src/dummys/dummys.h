#ifndef DUMMYS_H
#define DUMMYS_H
#include <iostream>
#include <string>
#include <vector>


using namespace std;

typedef enum{ANTIAIR,APC,ARTILLERY,INFANTRY,MECH,MEDTANK,RECON,ROCKET,TANK}units_d;
typedef enum{FOREST,HILL,PLAIN,RIVER,STREET}terrains_d;
typedef enum{CITY,FACTORY,HQ}buildings_d;
typedef enum{TEAM_RED,TEAM_BLUE,TEAM_GREEN,TEAM_YELLOW,NO_TEAM}teams_d;

typedef struct{
    int x;
    int y;
}position_s;

typedef struct{
    bool attackUpAvailable;
    bool attackDownAvailable;
    bool attackRightAvailable;
    bool attackLeftAvailable;
    bool buyAvailable;
    bool moveUpAvailable;
    bool moveDownAvailable;
    bool moveLeftAvailable;
    bool moveRightAvailable;
    bool passAvailable;
}options_s;

class Unit
{
public:
	void setUnit(int type, position_s pos, int team, bool fog);
    position_s getPosition();
    int getTypeOfUnit();
    int getTeam();
    bool getFog();
    void setFogOn();
protected:
    position_s position;
    string imagePath;
    int team;
    bool fog;
private:
    int typeOfUnit;
};

class Terrain
{
public:
	void setTerrain(terrains_d type, position_s pos, bool fog);
    position_s getPosition();
    int getTypeOfTerrain();
    bool getFog();
    void setFogOn();
protected:
    position_s position;
    string imagePath;
    bool fog;
private:
    int typeOfTerrain;
};

class Building
{
public:
	void setBuilding(int type, position_s pos, int team, bool fog);
    position_s getPosition();
    int getTypeOfBuilding();
    int getTeam();
    bool getFog();
    void setFogOn();
protected:
    position_s position;
    string imagePath;
    int team;
    bool fog;
	bool buildingIsFree;
private:
	int typeOfBuilding;
};

class Map
{
public:
    std::vector<Building> getBuildings();
    std::vector<Terrain> getTerrains();
    std::vector<Unit> getUnits();
	void setTerrains(std::vector<Terrain> newTerr);
	void setBuildings(std::vector<Building> newBuild);
	void setUnits(std::vector<Unit> newUnits);
	void addTerrain(Terrain newTerrain);
	void addBuilding(Building newBuilding);
	void addUnit(Unit newUnit);
    bool isThereAUnitThere(int x, int y);
    bool isThereABuildingThere(int x, int y);
    options_s getOptions(int x , int y);
	int getTeam();
	int getEnemyTeam();
	void setTeam(int team);
	void setEnemyTeam(int enemyTeam);
protected:
	bool isThereAnEnemyThere(int x,int y, int enemyTeam);
	bool isThereAFriendUnitThere(int x, int y);
	bool isThereAFriendBuildingThere(int x, int y);
    std::vector<Building> buildings;
    std::vector<Terrain> terrains;
    std::vector<Unit> units;
private:
	int team;
	int enemyTeam;
};

#endif