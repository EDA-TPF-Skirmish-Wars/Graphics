#include <iostream>
#include "./Graphics.h"
#include "./dummys/dummys.h"

int main (void){
    std::list<terrains_d> hola1;
    std::list<units_d>  hola2;
    std::list<buildings_d> hola3;
    Graphics chau(hola1,hola2,hola3);
    return 0;
}