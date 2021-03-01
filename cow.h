#ifndef COW_H
#define COW_H
#include "creature.h"
#include <QWidget>
class Cow:public Creature {
public:
        double getspeed();//every species has its own random speed
        void energyloss(double);//how we define the energy loss, using speed or else?
        bool ishungry();
        double getenergy();
        double displayx();
        void setcoordinate(double,double);
        double displayy();
        bool faith();//return death
        void die();//set death
        bool survival();//decide whther energy is bigger than 0
        QColor getcolor();
        Cow(double, double, double, double, double, double);
private:
        double matingage;//the age whether the Cows can mating
        double energy_threshhold;//when Cow is hungry
        QColor owncolor=Qt::blue;
        bool death;//decide whther it alive or die
};



#endif // COW_H
