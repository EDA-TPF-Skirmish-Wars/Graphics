#include <iostream>

using namespace std;

typedef enum{UNIDAD1,UNIDAD2,UNIDAD3,UNIDAD4,UNIDAD5,UNIDAD6,UNIDAD7}units_d;
typedef enum{TERRENO1,TERRENO2,TERRENO3,TERRENO4,TERRENO5,TERRENO6}terrains_d;
typedef enum{EDIFICIO1,EDIFICIO2,EDIFICIO3,EDIFICIO4,EDIFICIO5}buildings_d;

typedef struct{
    unsigned int x;
    unsigned int y;
}position_s;

class MartusUnidades
{
public:
    position_s getPosition();
    units_d getTypeOfUnit();
protected:
    position_s position;
private:
    units_d typeOfUnit;
};

class MartusTerrains
{
public:
    position_s getPosition();
    terrains_d getTypeOfTerrain();
protected:
    position_s position;
private:
    terrains_d typeOfTerrain;
};

class MartusBuildings
{
public:
    position_s getPosition();
    buildings_d getTypeOfBuilding();
protected:
    position_s position;
private:
    buildings_d typeOfBuilding;
};
