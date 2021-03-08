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
<<<<<<< Updated upstream
    timer->start(200);
=======
    timer->start(1000/60);
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
    const int numGrass = 30, numGroupCow = 5, numCowPerG = 10, numTiger = 10;
    srand(0);
=======
    const int numGrass = 30, numGroupCow = 1, numCowPerG = 1, numTiger = 10;//
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
        tigerlist.push_back(new Tiger(1000,rand()/double(RAND_MAX)*this->width(),
                                      rand()/double(RAND_MAX)*this->height(),tmp,cnt));//匹配新的构造函数
=======
        tigerlist.push_back(new Tiger(1000,0.5*rand()/double(RAND_MAX)*this->width(),
                                      0.5*rand()/double(RAND_MAX)*this->height(),tmp,cnt));//匹配新的构造函数
>>>>>>> Stashed changes
    }
}

void mysystem::drawsystem(QPainter *painter){
<<<<<<< Updated upstream
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
=======
//    for(Grass* iter:grasslist){
//        painter->setBrush(iter->owncolor);
//        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),2,2);
//    }
//    for(Cow* iter:cowlist){
//        painter->setBrush(iter->owncolor);
//        if(cnt-iter->getage()>iter->matingage)
//        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),5,5);
//        else
//        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),2,2);
//    }
>>>>>>> Stashed changes
    for(Tiger* iter:tigerlist){
        painter->setBrush(iter->sex?Qt::red : Qt::yellow);
        if(cnt-iter->getage()>iter->matingage)
        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),5,5);
        else
        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),2,2);
<<<<<<< Updated upstream
=======
//        for(int i=0;i<360;i+=10){
//            painter->drawEllipse(QPointF(iter->territoryx+iter->territoryr*cos(i*3.14159/180),iter->territoryy+iter->territoryr*sin(i*3.14159/180)),1,1);
//        }
>>>>>>> Stashed changes
    }
}

void mysystem::updatesystem(){
    cnt++;
<<<<<<< Updated upstream
=======
    srand(time(NULL));
>>>>>>> Stashed changes
    for(Tiger* iter:tigerlist){
        if (iter->getenergy()>iter->energy_threshhold || cnt-iter->getage()<iter->matingage)Hang_out(iter);
    }
    for(Cow* iter:cowlist){
        if (iter->getenergy()>iter->energy_threshhold || cnt-iter->getage()<iter->matingage)Hang_out(iter);
    }
}

void mysystem::Hang_out(Creature* x){
<<<<<<< Updated upstream
    if(typeid(*x).name()==typeid(Tiger).name()){
        double vecx=0,vecy=0,svecx=0,svecy=0;
        Tiger* xx=dynamic_cast<Tiger*>(x);
        for(Tiger* iter:tigerlist){
=======

    if(typeid(*x).name()==typeid(Tiger).name()){
        Tiger* xx=dynamic_cast<Tiger*>(x);
        double vecx=0,vecy=0,svecx=0,svecy=0;
        for(Tiger* iter:tigerlist){
            if(xx->sex==0) xx->territoryr=20;

>>>>>>> Stashed changes
            vecx=iter->displayx() - xx->displayx();
            vecy=iter->displayy() - xx->displayy();
            if(vecx>-20&&vecx<=20 && -20<=vecy && vecy<=20){
                if(rand()%15<2 && xx->getenergy()>=xx->energy_threshhold2 && iter->getenergy()>=iter->energy_threshhold2 && xx->sex^iter->sex && cnt-xx->getage()>xx->matingage && cnt-iter->getage()>iter->matingage){
<<<<<<< Updated upstream
=======
                    if(iter->sex==0) iter->ispregnant=1;
                    else xx->ispregnant=1;

>>>>>>> Stashed changes
                    tigerlist.push_back(new Tiger(xx->getenergy()/3,iter->displayx(),iter->displayy(),rand()%2,cnt));
                    tigernumber++;
                    iter->energyloss(iter->getenergy()/3);
                    xx->energyloss(xx->getenergy()/3);
<<<<<<< Updated upstream
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
=======
                }
                continue;
            }
        }
        double fir=rand()%10;
        double dis_sum[37];
        dis_sum[0]=0;
        if (xx->change_time==0){
            for(int i=0;i<36;i++)
            {
                double angle_next=i*10+fir;
                double x_next=xx->territoryx+xx->territoryr*cos(angle_next*3.14159/180);
                double y_next=xx->territoryy+xx->territoryr*sin(angle_next*3.14159/180);
                double x_dif=x_next-xx->displayx();
                double y_dif=y_next-xx->displayy();
                double dis=sqrt(x_dif*x_dif+y_dif*y_dif);
                dis_sum[i+1]=dis_sum[i]+dis;
            }
            int pos=upper_bound(dis_sum,dis_sum+37,rand()/double(RAND_MAX)*dis_sum[36])-dis_sum;
            double angle_pos=10*pos+fir;
            qDebug()<<angle_pos;
            double x_next=xx->territoryx+xx->territoryr*cos(angle_pos*3.14159/180);
            double y_next=xx->territoryy+xx->territoryr*sin(angle_pos*3.14159/180);

            svecx=x_next-xx->displayx();
            svecy=y_next-xx->displayy();
            normalize(svecx,svecy);
            xx->now_vecx=svecx;
            xx->now_vecy=svecy;
            if(xx->sex==1)
            xx->change_time=75+rand()%10;
            else xx->change_time=30+rand()%10;
>>>>>>> Stashed changes
        }
        else xx->change_time--;
        xx->setcoordinate(xx->displayx()+xx->now_vecx,xx->displayy()+xx->now_vecy);

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
<<<<<<< Updated upstream

=======
void mysystem::normalize(double &x, double &y){
    double tmp=x/sqrt(x*x+y*y);
    y=y/sqrt(x*x+y*y);
    x=tmp;
}
>>>>>>> Stashed changes
