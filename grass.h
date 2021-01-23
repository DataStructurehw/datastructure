#ifndef GRASS_H
#define GRASS_H
#include <QWidget>
#include "creature.h"

class Grass: public Creature {
public:
        double getspeed();//the speed of grass should be zero
        void energyloss(double);//if a grass doen't be eaten, how does the energy change
        bool ishungry();//will grass be hungry?
        double getenergy();
        double displayx();
        void setcoordinate(double,double);
        double displayy();
        QColor getcolor();
        Grass(double, double, double, double, double, double);

private:
        double growth_time;//the time a coordinate need to create grass( grass can grow everwhere by the requirements
        double Eloss_speed;//the speed of lossing the energy for grass
        QColor owncolor=Qt::green;
};



#endif // GRASS_H
