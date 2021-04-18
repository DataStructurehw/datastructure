#ifndef mysystem_H
#define mysystem_H

#include <QWidget>
#include "creature.h"
#include "cow.h"
#include "grass.h"
#include "tiger.h"
#include <set>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <stdlib.h>
#include<queue>
#include <time.h>
#include<complex>
#include<cmath>
using namespace std;
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
    QTimer *timer;
    int cnt=0;
    int daylong=1200;
    void normalize(double &, double &);
    complex<double> normalize(complex<double>);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initSystem();
    void drawsystem(QPainter *painter);
    void updatesystem();
    void sleep_energy();
    void Hang_out(Creature*);
    void match();
    void matchCG();
    void freeWalk();
    void takeFood();
    void clearDeath();
    double ld_delay(double);
    void updateEnergy();
    void motherCheck();
    void motherFetch();
    set<Tiger*> tigerlist;
    set<Cow*> cowlist;
    set<Grass*> grasslist;
    double w;
    double h;

    bool day_or_night;
signals:
    void go_to_sleep();
public slots:
    void get_sleep();
};


#endif // mysystem_H
