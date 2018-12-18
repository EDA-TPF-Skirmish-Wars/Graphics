#ifndef DUMMYS_H
#define DUMMYS_H
#include <iostream>
#include <string>

using namespace std;

typedef enum{UNIDAD_1,UNIDAD_2,UNIDAD_3,UNIDAD_4,UNIDAD_5,UNIDAD_6,UNIDAD_7}units_d;
typedef enum{TERRENO_1,TERRENO_2,TERRENO_3,TERRENO_4,TERRENO_5,TERRENO_6}terrains_d;
typedef enum{EDIFICIO_1,EDIFICIO_2,EDIFICIO_3,EDIFICIO_4,EDIFICIO_5}buildings_d;

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
    bool moveAvailable;
    bool passAvailable;
    //etc...
}options_s;

class MartusUnidades
{
public:
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
    position_s getPosition();
    terrains_d getTypeOfTerrain();
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
    terrains_d typeOfTerrain;
};

class MartusBuildings
{
public:
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
private:
    buildings_d typeOfBuilding;
};

class MartusMap
{
public:
    void updateFog();
    std::vector<MartusBuildings> getBuildings();
    std::vector<MartusTerrains> getTerrains();
    std::vector<MartusUnidades> getUnits();
    bool isThereAUnitThere(int x, int y);
    bool isThereABuildingThere(int x, int y);
    options_s getOptions(int x , int y);
protected:
    std::vector<MartusBuildings> buildings;
    std::vector<MartusTerrains> terrains;
    std::vector<MartusUnidades> units;
private:
};

#endif