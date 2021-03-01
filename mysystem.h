#ifndef mysystem_H
#define mysystem_H

#include <QWidget>
#include "creature.h"
#include "cow.h"
#include "grass.h"
#include "tiger.h"
using namespace std;

class testcreature{
public:
    testcreature(QColor c,double xx,double yy):owncolor(c),x(xx),y(yy){

    }
    ~testcreature(){

    }
    QColor getcolor(){
        return owncolor;
    }
    double getx(){
        return x;
    }
    double gety(){
        return y;
    }


private:
    QColor owncolor;
    int x,y;
};

class mysystem: public QWidget
{
    Q_OBJECT
public:
    double width(){
        return w;
    }
    double height(){
        return h;
    }
    void setGeo(double x,double y){
        w=x,h=y;
    }
    explicit mysystem(QWidget *parent = nullptr);
    ~mysystem();
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    //intial mysystem,这里写process
    void initSystem();
    //递归绘制
    void drawsystem(QPainter *painter);
    //更新系统，这里写process
    void updatesystem();
    void match();
    void hunt();
    QList<testcreature*> creaturelist;
    QList<Tiger*> tigerlist;
    QList<Cow*> cowlist;
    QList<Grass*> grasslist;
    double w;//窗体宽度
    double h;//窗体高度
};


#endif // mysystem_H
