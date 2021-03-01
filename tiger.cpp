#include"tiger.h"
using namespace std;
Tiger::Tiger(double speed_, double energy_, double x, double y, double matingage_, double energy_threshhold_):
    matingage(matingage_), energy_threshhold(energy_threshhold_) {
        speed = speed_;
        energy = energy_;
        coordinatex = x;
        coordinatey = y;
        hungry = false;
        time_t t;
		t=time(NULL); 
		birth = t;
}

double Tiger::getspeed() { return speed; }
void Tiger::energyloss(double cost) { energy -= cost; if(energy < energy_threshhold) hungry = true; }
bool Tiger::ishungry() { return hungry; }
bool Tiger::isadult() { return returnage()-matingage > 0; }
void Tiger::prey(double energyget) { energy += energyget; }
double Tiger::returnage() { time_t t; t=time(NULL); return difftime(birth,t); } 
double Tiger::getenergy() { return energy; }
double Tiger::displayx() { return coordinatex; }
double Tiger::displayy() { return coordinatey; }
QColor Tiger::getcolor(){
    return owncolor;
}
double Tiger::getprobability(){
	return probability; 
} 
void Tiger::setcoordinate(double x, double y){
    coordinatex=x,coordinatey=y;
}

