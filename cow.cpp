#include"cow.h"
using namespace std;
Cow::Cow(double speed_, double energy_, double x, double y, double matingage_, double energy_threshhold_)
    :matingage(matingage_), energy_threshhold(energy_threshhold_) {
        speed = speed_;
        energy = energy_;
        coordinatex = x;
        coordinatey = y;
        hungry = false;
}

double Cow::getspeed() { return speed; }
void Cow::energyloss(double cost) { energy -= cost; if(energy < energy_threshhold) hungry = true; }
bool Cow::ishungry() { return hungry; }
double Cow::getenergy() { return energy; }
double Cow::displayx() { return coordinatex; }
double Cow::displayy() { return coordinatey; }
QColor Cow::getcolor(){
    return owncolor;
}
void Cow::setcoordinate(double x, double y){
    coordinatex=x,coordinatey=y;
}
