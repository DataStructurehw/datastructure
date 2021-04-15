#include"grass.h"
using namespace std;
Grass::Grass(double energy_, double x, double y,double growth_,double Eloss,int born_datee):
    growth_time(growth_), Eloss_speed(Eloss) {
    energy = energy_;
    coordinatex = x;
    coordinatey = y;
    setLoc(x, y);
    born_date=born_datee;
}

double Grass::getspeed() {
    if (growth_time+Eloss_speed>0) return 1;
        return 0;
}
void Grass::energyloss(double x) {
    energy -= x;
}//待补充
bool Grass::ishungry() {
    return 0;
}//待补充
double Grass::getenergy() {
    return energy;
}
double Grass::displayx() {
    return coordinatex;
}
double Grass::displayy() {
    return coordinatey;
}
void Grass::setcoordinate(double x, double y){
    coordinatex=x,coordinatey=y;
}
int Grass::getage(){
    return born_date;
}
