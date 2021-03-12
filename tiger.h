#ifndef TIGER_H
#define TIGER_H
#include "mammal.h"
#include <QWidget>
class Tiger:public mammal {
public:
        Tiger(double, double, double,bool,int);//add new parameters
        double territoryx;//
        double territoryy;//
        double territoryr;//
        double now_vecx;//
        double now_vecy;//
        double change_time=0;//
        QColor owncolor=Qt::red;
};



#endif // TIGER_H
