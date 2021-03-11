#ifndef COW_H
#define COW_H
#include "mammal.h"
#include <QWidget>
class Cow:public mammal{
public:
        Cow(double, double, double,bool,int);//新加了参数
        QColor owncolor=Qt::blue;
};



#endif // COW_H
