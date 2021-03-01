#ifndef COW_H
#define COW_H
#include "creature.h"
#include <QWidget>
#include <time.h>

class Cow:public Creature {
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
        void setcoordinate(double,double);
        double displayy();
        QColor getcolor();
        Cow(double, double, double, double, double, double);

private:
        double matingage;//the age whether the Cows can mating
        double energy_threshhold;//when Cow is hungry
        double probability;//probability of dying
        double birth;//caluation of age is not solved in this version
        QColor owncolor=Qt::blue;
};



#endif // COW_H
