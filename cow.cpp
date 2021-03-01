#include"cow.h"
using namespace std;
Cow::Cow(double energy_, double x, double y,bool sexx,int born_datee){//
    energy = energy_;
    coordinatex = x;
    coordinatey = y;
    sex= sexx;//新加的
    born_date=born_datee;//新加的
    matingage=40;
    energy_threshhold=400;
    energy_threshhold2=800;
}

double Cow::getspeed() {
     return 0;
}
void Cow::energyloss(double cost) {
    energy -= cost;
}
bool Cow::ishungry() {
    return 0;
}
double Cow::getenergy() {
    return energy;
}
double Cow::displayx() {
    return coordinatex;
}
double Cow::displayy() {
    return coordinatey;
}
int Cow::getage(){
    return born_date;
}
void Cow::setcoordinate(double x, double y){
    coordinatex=x,coordinatey=y;
}
