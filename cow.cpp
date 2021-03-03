#include"cow.h"
using namespace std;
Cow::Cow(double speed, double energy_, double x, double y, double matingage_, double energy_threshhold_)
    :matingage(matingage_), energy_threshhold(energy_threshhold_) {
        setVel(speed, 0);
        energy = energy_;
        setLoc(x, y);
        hungry = false;
        time_t t;
		t=time(NULL); 
		birth = t;
}


void Cow::energyloss(double cost) { energy -= cost; if(energy < energy_threshhold) hungry = true; }
bool Cow::ishungry() { return hungry; }
bool Cow::isadult() { return returnage()-matingage > 0; }
void Cow::prey(double energyget) { energy += energyget; }
double Cow::returnage() { time_t t; t=time(NULL); return difftime(birth,t); } 
QColor Cow::getcolor(){
    return owncolor;
}
