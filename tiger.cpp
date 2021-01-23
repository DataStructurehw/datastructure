#include"tiger.h"
using namespace std;
Tiger::Tiger(double speed_, double energy_, double x, double y, double matingage_, double energy_threshhold_):
    matingage(matingage_), energy_threshhold(energy_threshhold_) {
        speed = speed_;
        energy = energy_;
        coordinatex = x;
        coordinatey = y;
        hungry = false;
}

double Tiger::getspeed() { return speed; }
void Tiger::energyloss(double cost) { energy -= cost; if(energy < energy_threshhold) hungry = true; }
bool Tiger::ishungry() { return hungry; }
double Tiger::getenergy() { return energy; }
double Tiger::displayx() { return coordinatex; }
double Tiger::displayy() { return coordinatey; }
QColor Tiger::getcolor(){
    return owncolor;
}
void Tiger::setcoordinate(double x, double y){
    coordinatex=x,coordinatey=y;
}

