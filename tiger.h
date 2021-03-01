#ifndef TIGER_H
#define TIGER_H
#include "creature.h"
#include <QWidget>
#include <time.h>

class Tiger:public Creature {
public:
        void energyloss(double);//how we define the energy loss, using speed or else?
        bool ishungry();
        bool isadult();//whether can mate
//        double getenergy();
        void prey(double);//get energy from other creatures
        double returnage();//return the age
        QColor getcolor();
        Tiger(double, double, double, double, double, double);

private:
        double matingage;//the age whether the tigers can mating
        double energy_threshhold;//when tiger is hungry
        double birth;//unit is seconds
        QColor owncolor=Qt::red;
};



#endif // TIGER_H
