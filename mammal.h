#ifndef MAMMAL_H
#define MAMMAL_H

#include "creature.h"
#include <QWidget>
class mammal:public Creature
{
public:
    mammal(double, double, double,bool,int);
    double getspeed();
    double getenergy();
    double displayx();
    double displayy();
    double energy_threshhold;
    double energy_threshhold2;

    int getage();
    int matingage;
    int delaytime;

    bool sex;//new
    bool ishungry();
    bool ispregnant;

    void energyloss(double);
    void setcoordinate(double,double);

    mammal* mate;
    QList<mammal*> childlist;
private:

        int born_date;//加了出生日期
};

#endif // MAMMAL_H
