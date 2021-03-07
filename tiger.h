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
        void prey(double);//get energy from other creatures
        double returnage();//return the age
        int getState();
        void setState(int);
        QColor getcolor();
        Tiger(double, double, double, double, double, double);

private:
        double matingage;//the age whether the tigers can mating
        double energy_threshhold;//when tiger is hungry
        double birth;//unit is seconds
        int state; // state 0: free walking; 1: hunt;
        QColor owncolor=Qt::red;
};



#endif // TIGER_H
