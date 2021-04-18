#ifndef COW_H
#define COW_H
#include "mammal.h"
#include <QWidget>
class Cow:public mammal{
public:
        Cow(double, double, double,bool,int);
        QColor owncolor=Qt::blue;
};



#endif // COW_H
