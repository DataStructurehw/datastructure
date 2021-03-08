#include "mammal.h"

mammal::mammal(double energy_, double x, double y,bool sexx,int born_datee)
{
    energy = energy_;
    coordinatex = x;
    coordinatey = y;
    sex= sexx;//新加的
    born_date=born_datee;//新加的
    matingage=40;
    energy_threshhold=400;
    energy_threshhold2=800;
}
double mammal::getspeed() {
    return 0;
}
bool mammal::ishungry(){
    if (getenergy()>energy_threshhold) return 0;
    else return 1;
}

void mammal::energyloss(double cost) {
    energy -= cost;
}
double mammal::getenergy() {
    return energy;
}
double mammal::displayx() {
    return coordinatex;
}
double mammal::displayy() {
    return coordinatey;
}
int mammal::getage(){
    return born_date;
}//加了
void mammal::setcoordinate(double x, double y){
    coordinatex=x,coordinatey=y;
}
