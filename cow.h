#ifndef COW_H
#define COW_H
#include "mammal.h"
#include <QWidget>
class Cow:public mammal{
public:
        Cow(double, double, double,bool,int);//新加了参数
<<<<<<< Updated upstream

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
=======
        QColor owncolor=Qt::blue;
>>>>>>> Stashed changes
};



#endif // COW_H
