#ifndef COW_H
#define COW_H
#include "creature.h"
#include <QWidget>
class Cow:public Creature {
public:
        Cow(double, double, double,bool,int);//新加了参数

        double getspeed();
        double getenergy();
        double displayx();
        double displayy();
        double energy_threshhold;
        double energy_threshhold2;

        int getage();
        int matingage;

        bool sex;//new
        bool ishungry();
        bool ispregnant;

        void energyloss(double);
        void setcoordinate(double,double);

        QColor owncolor=Qt::blue;
private:

        int born_date;//加了出生日期
};



#endif // COW_H
