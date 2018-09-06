#include <iostream>
#include "./Graphics.h"
#include "./dummys/dummys.h"

int main (void){
    std::vector<terrains_d> hola1;
    std::vector<units_d>  hola2;
    std::vector<buildings_d> hola3;
    Graphics chau(hola1,hola2,hola3);
    return 0;
}