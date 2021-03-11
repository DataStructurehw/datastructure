#ifndef mysystem_H
#define mysystem_H

#include <QWidget>
#include "creature.h"
#include "cow.h"
#include "grass.h"
#include "tiger.h"
#include <set>
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

    void normalize(double&,double&);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initSystem();
    void drawsystem(QPainter *painter);
    void updatesystem();
    void Hang_out(Creature*);
    void match();
    void matchGT();
    void matchCG();
    void freeWalk();
    void takeFood();
    void clearDeath();
    void updateEnergy();
    set<Tiger*> tigerlist;
    set<Cow*> cowlist;
    set<Grass*> grasslist;

    double w;//窗体宽度
    double h;//窗体高度
};


#endif // mysystem_H
