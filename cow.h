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
        QColor getcolor();
        Cow(double, double, double, double, double, double);

private:
        double matingage;//the age whether the Cows can mating
        double energy_threshhold;//when Cow is hungry
        QColor owncolor=Qt::blue;
};



#endif // COW_H
