#include"cow.h"
using namespace std;
Cow::Cow(double speed_, double energy_, double x, double y, double matingage_, double energy_threshhold_)
    :matingage(matingage_), energy_threshhold(energy_threshhold_) {
        speed = speed_;
        energy = energy_;
        coordinatex = x;
        coordinatey = y;
        hungry = false;
        time_t t;
		t=time(NULL); 
		birth = t;
}

double Cow::getspeed() { return speed; }
void Cow::energyloss(double cost) { energy -= cost; if(energy < energy_threshhold) hungry = true; }
bool Cow::ishungry() { return hungry; }
bool Cow::isadult() { return returnage()-matingage > 0; }
double Cow::getenergy() { return energy; }
void Cow::prey(double energyget) { energy += energyget; }
double Cow::returnage() { time_t t; t=time(NULL); return difftime(birth,t); } 
double Cow::displayx() { return coordinatex; }
double Cow::displayy() { return coordinatey; }
QColor Cow::getcolor(){
    return owncolor;
}
double Tiger::getprobability(){
	return probability; 
} 
void Cow::setcoordinate(double x, double y){
    coordinatex=x,coordinatey=y;
}
