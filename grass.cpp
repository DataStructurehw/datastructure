#include"grass.h"
using namespace std;
Grass::Grass(double energy_, double x, double y, double growth_, double Eloss)
    :growth_time(growth_), Eloss_speed(Eloss) {
        energy = energy_;
        setLoc(x, y);
        hungry = false;
        time_t t;
		t=time(NULL); 
		birth = t;
        setVel(0, 0);
}

void Grass::energyloss(double x) { energy -= x; }//待补充
bool Grass::ishungry() {return 0;}//待补充
double Grass::returnage() { time_t t; t=time(NULL); return difftime(birth,t); } 
QColor Grass::getcolor(){
    return owncolor;
}
