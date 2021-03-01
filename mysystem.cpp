#include "mysystem.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QTimer>
#include <stdlib.h>
#include <time.h>

int cnt=0,tigernumber=0;
mysystem::mysystem(QWidget *parent)
    :QWidget(parent)
{
    this->setGeo(800,600);
    initSystem();
    QTimer *timer= new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=]{
        updatesystem();
        update();
    });
    timer->start(200);
}
mysystem::~mysystem(){
}

void mysystem::paintEvent(QPaintEvent *event){
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::white);
    drawsystem(&painter);
}

void mysystem::initSystem(){
    const int numGrass = 30, numGroupCow = 5, numCowPerG = 10, numTiger = 10;
    srand(0);
    for (int i = 0; i < numGrass; ++i)
        grasslist.push_back(new Grass(100,
                            rand()/double(RAND_MAX)*this->width(),
                            rand()/double(RAND_MAX)*this->height(),10,10,cnt));
    for (int i = 0; i < numGroupCow; ++i) {
        double centerx = rand()/double(RAND_MAX)*this->width(),
                centery = rand()/double(RAND_MAX)*this->height();
        const double limx = 10, limy = 10;
        for (int j = 0; j < rand()%numCowPerG; ++j)
            cowlist.push_back(new Cow(1000,rand()/double(RAND_MAX)*limx-limx/2+centerx,
                                rand()/double(RAND_MAX)*limy-limy/2+centery,rand()%2,cnt));//
    }
    for (int i = 0; i < numTiger; ++i){
        int tmp = rand()%2;
        tigerlist.push_back(new Tiger(1000,rand()/double(RAND_MAX)*this->width(),
                                      rand()/double(RAND_MAX)*this->height(),tmp,cnt));//匹配新的构造函数
    }
}

void mysystem::drawsystem(QPainter *painter){
    for(Grass* iter:grasslist){
        painter->setBrush(iter->owncolor);
        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),2,2);
    }
    for(Cow* iter:cowlist){
        painter->setBrush(iter->owncolor);
        if(cnt-iter->getage()>iter->matingage)
        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),5,5);
        else
        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),2,2);
    }
    for(Tiger* iter:tigerlist){
        painter->setBrush(iter->sex?Qt::red : Qt::yellow);
        if(cnt-iter->getage()>iter->matingage)
        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),5,5);
        else
        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),2,2);
    }
}

void mysystem::updatesystem(){
    cnt++;
    for(Tiger* iter:tigerlist){
        if (iter->getenergy()>iter->energy_threshhold || cnt-iter->getage()<iter->matingage)Hang_out(iter);
    }
    for(Cow* iter:cowlist){
        if (iter->getenergy()>iter->energy_threshhold || cnt-iter->getage()<iter->matingage)Hang_out(iter);
    }
}

void mysystem::Hang_out(Creature* x){
    if(typeid(*x).name()==typeid(Tiger).name()){
        double vecx=0,vecy=0,svecx=0,svecy=0;
        Tiger* xx=dynamic_cast<Tiger*>(x);
        for(Tiger* iter:tigerlist){
            vecx=iter->displayx() - xx->displayx();
            vecy=iter->displayy() - xx->displayy();
            if(vecx>-20&&vecx<=20 && -20<=vecy && vecy<=20){
                if(rand()%15<2 && xx->getenergy()>=xx->energy_threshhold2 && iter->getenergy()>=iter->energy_threshhold2 && xx->sex^iter->sex && cnt-xx->getage()>xx->matingage && cnt-iter->getage()>iter->matingage){
                    tigerlist.push_back(new Tiger(xx->getenergy()/3,iter->displayx(),iter->displayy(),rand()%2,cnt));
                    tigernumber++;
                    iter->energyloss(iter->getenergy()/3);
                    xx->energyloss(xx->getenergy()/3);
                    qDebug()<<tigernumber;
                }
                continue;
            }
            double weight=1;
            if (xx->sex^iter->sex) weight=2;
            svecx+=weight*vecx/sqrt(vecx*vecx+vecy*vecy);
            svecy+=weight*vecy/sqrt(vecx*vecx+vecy*vecy);

        }
        double tmpx=svecx/sqrt(svecx*svecx+svecy*svecy);
        svecy=svecy/(svecx*svecx+svecy*svecy);
        svecx=tmpx;
        if (rand()%2==0)xx->setcoordinate(xx->displayx()+5*svecx,xx->displayy()+5*svecy);
        else {
            double tmp=rand();
            svecx=cos(tmp);
            svecy=sin(tmp);
            xx->setcoordinate(xx->displayx()+5*svecx,xx->displayy()+5*svecy);
        }
    }
    else if(typeid(*x).name()==typeid(Cow).name()){
        double vecx=0,vecy=0,svecx=0,svecy=0;
        Cow* xx=dynamic_cast<Cow*>(x);
        for(Cow* iter:cowlist){
            vecx=iter->displayx() - xx->displayx();
            vecy=iter->displayy() - xx->displayy();
            if(vecx>-20&&vecx<=20 && -20<=vecy && vecy<=20){
                if(rand()%15<2 && xx->getenergy()>=xx->energy_threshhold2 && iter->getenergy()>=iter->energy_threshhold2 && xx->sex^iter->sex && cnt-xx->getage()>xx->matingage && cnt-iter->getage()>iter->matingage){
                    cowlist.push_back(new Cow(xx->getenergy()/3,iter->displayx(),iter->displayy(),rand()%2,cnt));
                    iter->energyloss(iter->getenergy()/3);
                    xx->energyloss(xx->getenergy()/3);
                }
                continue;
            }
            double weight=1;
            if (xx->sex^iter->sex) weight=2;
            svecx+=weight*vecx/sqrt(vecx*vecx+vecy*vecy);
            svecy+=weight*vecy/sqrt(vecx*vecx+vecy*vecy);
        }
        double tmpx=svecx/sqrt(svecx*svecx+svecy*svecy);
        svecy=svecy/(svecx*svecx+svecy*svecy);
        svecx=tmpx;
        if (rand()%2==0)xx->setcoordinate(xx->displayx()+5*svecx,xx->displayy()+5*svecy);
        else {
            double tmp=rand();
            svecx=cos(tmp);
            svecy=sin(tmp);
            xx->setcoordinate(xx->displayx()+5*svecx,xx->displayy()+5*svecy);
        }
    }
}

