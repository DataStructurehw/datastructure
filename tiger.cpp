#include"tiger.h"
using namespace std;
Tiger::Tiger(double speed, double energy_, double x, double y, double matingage_, double energy_threshhold_):
    matingage(matingage_), energy_threshhold(energy_threshhold_) {
        setVel(speed*exp(std::complex<double>(0, (double)rand()/RAND_MAX*M_PI*2)));
        energy = energy_;
        setLoc(x, y);
        hungry = false;
        time_t t;
		t=time(NULL); 
		birth = t;
}

void Tiger::energyloss(double cost) { energy -= cost; if(energy < energy_threshhold) hungry = true; }
bool Tiger::ishungry() { return hungry; }
bool Tiger::isadult() { return returnage()-matingage > 0; }
void Tiger::prey(double energyget) { energy += energyget; }
double Tiger::returnage() { time_t t; t=time(NULL); return difftime(birth,t); } 
QColor Tiger::getcolor(){
    return owncolor;
}
