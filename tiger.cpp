#include"tiger.h"
using namespace std;
Tiger::Tiger(double energy_, double x, double y,bool sexx,int born_datee):mammal(energy_,x,y,sexx,born_datee){
    matingage = 40;
    energy_threshhold = 400;
    energy_threshhold2 = 800;
    territoryx = x;
    territoryy=y;
    territoryr=100;
}


