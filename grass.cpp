#include"grass.h"
using namespace std;
Grass::Grass(double speed_, double energy_, double x, double y, double growth_, double Eloss)
    :growth_time(growth_), Eloss_speed(Eloss) {
        speed = speed_;
        energy = energy_;
        coordinatex = x;
        coordinatey = y;
        hungry = false;
        time_t t;
		t=time(NULL); 
		birth = t;
}

double Grass::getspeed() { return speed; }
void Grass::energyloss(double x) { energy -= x; }//待补充
bool Grass::ishungry() {return 0;}//待补充
double Grass::getenergy() { return energy; }
double Grass::returnage() { time_t t; t=time(NULL); return difftime(birth,t); } 
double Grass::displayx() { return coordinatex; }
double Grass::displayy() { return coordinatey; }
QColor Grass::getcolor(){
    return owncolor;
}
double Tiger::getprobability(){
	return probability; 
} 