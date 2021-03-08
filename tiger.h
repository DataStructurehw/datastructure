#ifndef TIGER_H
#define TIGER_H
#include "mammal.h"
#include <QWidget>
class Tiger:public mammal {
public:
        Tiger(double, double, double,bool,int);//新加了参数
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

        QColor owncolor=Qt::red;
private:

        int born_date;//加了出生日期
=======
        double territoryx;//
        double territoryy;//
        double territoryr;//
        double now_vecx;//
        double now_vecy;//
        double change_time=0;//
        QColor owncolor=Qt::red;
>>>>>>> Stashed changes
};



#endif // TIGER_H
