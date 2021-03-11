#include "mammal.h"

mammal::mammal(double energy_, double x, double y,bool sexx,int born_datee)
{
    energy = energy_;
    coordinatex = x;
    coordinatey = y;
    setLoc(x,y);
    setstate(0);
    double speed=1;
    setVel(speed*exp(std::complex<double>(0, (double)rand()/RAND_MAX*M_PI*2)));
    sex= sexx;//新加的
    born_date=born_datee;//新加的
    matingage=400;
    energy_threshhold=1000;
    energy_threshhold2=1600;
    lastgen=0;
}

mammal::~mammal(){

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
bool mammal::faith() {
    return death;
}
void mammal::die() {
    death = true;
}
bool mammal::survival() {
    if(energy<=0) return false;
    return true;
}
int mammal::getstate() { return state; }
void mammal::setstate(int _state) { state = _state; }
void mammal::prey(double energyget) { energy += energyget; }
bool mammal::isadult() { return returnage()-matingage > 0; }
double mammal::returnage() { time_t t; t=time(NULL); return difftime(birth,t); }
