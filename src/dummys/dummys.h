#ifndef DUMMYS_H
#define DUMMYS_H
#include <iostream>
#include <string>
#include <vector>


using namespace std;

typedef enum{UNIDAD_1,UNIDAD_2,UNIDAD_3,UNIDAD_4,UNIDAD_5,UNIDAD_6,UNIDAD_7,UNIDAD_8,UNIDAD_9}units_d;
typedef enum{TERRENO_1,TERRENO_2,TERRENO_3,TERRENO_4,TERRENO_5,TERRENO_6}terrains_d;
typedef enum{EDIFICIO_1,EDIFICIO_2,EDIFICIO_3,EDIFICIO_4,EDIFICIO_5}buildings_d;
typedef enum{TEAM_1,TEAM_2,TEAM_3,TEAM_4,NO_TEAM}teams_d;

typedef struct{
    unsigned int x;
    unsigned int y;
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

class MartusUnidades
{
public:
	void setUnit(units_d type, position_s pos, int team, bool fog);
    position_s getPosition();
    units_d getTypeOfUnit();
    string getImagePath();
    int getTeam();
    bool getFog();
    void setFogOn();
protected:
    position_s position;
    string imagePath;
    int team;
    bool fog;
private:
    units_d typeOfUnit;
};

class MartusTerrains
{
public:
	void setTerrain(terrains_d type, position_s pos, bool fog);
    position_s getPosition();
    terrains_d getTypeOfTerrain();
    string getImagePath();
    bool getFog();
    void setFogOn();
protected:
    position_s position;
    string imagePath;
    bool fog;
private:
    terrains_d typeOfTerrain;
};

class MartusBuildings
{
public:
	void setBuilding(buildings_d type, position_s pos, int team, bool fog);
    position_s getPosition();
    buildings_d getTypeOfBuilding();
    string getImagePath();
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
    buildings_d typeOfBuilding;
};

class MartusMap
{
public:
    //void updateFog();
    std::vector<MartusBuildings> getBuildings();
    std::vector<MartusTerrains> getTerrains();
    std::vector<MartusUnidades> getUnits();
	void addTerrain(MartusTerrains newTerrain);
	void addBuilding(MartusBuildings newBuilding);
	void addUnit(MartusUnidades newUnit);
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
    std::vector<MartusBuildings> buildings;
    std::vector<MartusTerrains> terrains;
    std::vector<MartusUnidades> units;
private:
	int team;
	int enemyTeam;
};

#endif