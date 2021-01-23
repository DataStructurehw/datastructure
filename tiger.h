#ifndef TIGER_H
#define TIGER_H
#include "creature.h"
#include <QWidget>
class Tiger:public Creature {
public:
        double getspeed();//every species has its own random speed
        void energyloss(double);//how we define the energy loss, using speed or else?
        bool ishungry();
        double getenergy();
        double displayx();
        double displayy();
        void setcoordinate(double,double);
        QColor getcolor();
        Tiger(double, double, double, double, double, double);

private:
        double matingage;//the age whether the tigers can mating
        double energy_threshhold;//when tiger is hungry
        QColor owncolor=Qt::red;
};



#endif // TIGER_H
