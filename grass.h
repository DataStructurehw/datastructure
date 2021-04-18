#ifndef GRASS_H
#define GRASS_H
#include <QWidget>
#include "creature.h"

class Grass: public Creature {
public:
        bool ishungry();//will grass be hungry?

        double getenergy();
        double getspeed();//the speed of grass should be zero
        double displayx();
        double displayy();

        void setcoordinate(double,double);
        void energyloss(double);//if a grass doen't be eaten, how does the energy change

        int getage();
        Grass(double, double, double, double, double, int);
        QColor owncolor=Qt::green;

private:
        double growth_time;//the time a coordinate need to create grass( grass can grow everwhere by the requirements
        double Eloss_speed;//the speed of lossing the energy for grass
        int born_date;
};



#endif // GRASS_H
