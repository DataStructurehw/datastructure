#ifndef MAMMAL_H
#define MAMMAL_H

#include "creature.h"
#include <QWidget>
#include <math.h>
#include "ctime"
#include "cstdlib"

class mammal:public Creature
{
public:
    mammal(double, double, double,bool,int);
    virtual ~mammal();

    double getspeed();
    double getenergy();
    double displayx();
    double displayy();
    double returnage();
    double birth;
    double probability;
    double energy_threshhold;
    double energy_threshhold2;

    int getage();
    int matingage;
    int delaytime;
    int state;
    int lastgen;
    int getstate();

    bool sex;//new
    bool ishungry();
    bool ispregnant;
    bool death;
    bool hungry;
    bool survival();
    bool faith();
    bool isadult();

    void energyloss(double);
    void setstate(int);
    void prey(double);
    void die();
    void setcoordinate(double,double);

    mammal* mate;
    QList<mammal*> childlist;
private:

        int born_date;//加了出生日期
};

#endif // MAMMAL_H
