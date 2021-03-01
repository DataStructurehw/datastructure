#ifndef TIGER_H
#define TIGER_H
#include "creature.h"
#include <QWidget>
#include <time.h>

class Tiger:public Creature {
public:
        double getspeed();//every species has its own random speed
        double getprobability();//calculate probability of dying
        void energyloss(double);//how we define the energy loss, using speed or else?
        bool ishungry();
        bool isadult();//whether can mate
        double getenergy();
        void prey();//get energy from other creatures
        double returnage();//return the age
        double displayx();
        double displayy();
        void setcoordinate(double,double);
        QColor getcolor();
        Tiger(double, double, double, double, double, double);

private:
        double matingage;//the age whether the tigers can mating
        double energy_threshhold;//when tiger is hungry
        double probability;//probability of dying
        double birth;//unit is seconds
        QColor owncolor=Qt::red;
};



#endif // TIGER_H
