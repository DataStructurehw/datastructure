#include"cow.h"
using namespace std;
Cow::Cow(double speed, double energy_, double x, double y, double matingage_, double energy_threshhold_)
    :matingage(matingage_), energy_threshhold(energy_threshhold_) {
        setVel(speed*exp(std::complex<double>(0, (double)rand()/RAND_MAX*M_PI*2)));
        energy = energy_;
        setLoc(x, y);
        hungry = false;
        time_t t;
		t=time(NULL); 
		birth = t;
        setState(0);
}


void Cow::energyloss(double cost) { energy -= cost; energy = min(energy, energy_threshhold*3); if(energy < energy_threshhold) hungry = true; else hungry = false; }
bool Cow::ishungry() { return hungry; }
bool Cow::isadult() { return returnage()-matingage > 0; }
void Cow::prey(double energyget) { energy += energyget; }
double Cow::returnage() { time_t t; t=time(NULL); return difftime(birth,t); } 
QColor Cow::getcolor(){
    return owncolor;
}
int Cow::getState() { return state; }
void Cow::setState(int _state) { state = _state; }
