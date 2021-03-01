#include "creature.h"

double Creature::getspeed() { return speed; }
double Creature::getenergy() { return energy; }
double Creature::displayx() { return coordinatex; }
double Creature::displayy() { return coordinatey; }
double Creature::displaytx() { return tx; }
double Creature::displayty() { return ty; }
void Creature::setcoordinate(double x, double y) { coordinatex = x; coordinatey = y; }
void Creature::setdirection(double Tx, double Ty) { tx = Tx; ty = Ty; }
void Creature::setspeed(double s) { speed = s; }
double Creature::getprobability() { return probability; }
