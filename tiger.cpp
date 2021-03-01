#include"tiger.h"
using namespace std;
Tiger::Tiger(double energy_, double x, double y,bool sexx,int born_datee){
        energy = energy_;
        coordinatex = x;
        coordinatey = y;
        sex= sexx;//新加的
        born_date=born_datee;//新加的
        matingage=40;
        energy_threshhold=400;
        energy_threshhold2=800;
}

double Tiger::getspeed() {
    return 0;
}
bool Tiger::ishungry(){
    if (getenergy()>energy_threshhold) return 0;
    else return 1;
}

void Tiger::energyloss(double cost) {
    energy -= cost;
}
double Tiger::getenergy() {
    return energy;
}
double Tiger::displayx() {
    return coordinatex;
}
double Tiger::displayy() {
    return coordinatey;
}
int Tiger::getage(){
    return born_date;
}//加了
void Tiger::setcoordinate(double x, double y){
    coordinatex=x,coordinatey=y;
}

