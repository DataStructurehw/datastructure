#include "creature.h"

Creature::~Creature(){

}
double Creature::getenergy() { return energy; }
std::complex<double> Creature::getLoc() { return loc; }
std::complex<double> Creature::getVel() { return vel; }
void Creature::setLoc(double x, double y) { setLoc(std::complex<double>(x, y)); }
void Creature::setLoc(std::complex<double> newloc) { loc = newloc; }
void Creature::setVel(double x, double y) { setVel(std::complex<double>(x, y)); }
void Creature::setVel(std::complex<double> newvel) { vel = newvel; }
double Creature::getprobability() { return probability; }
