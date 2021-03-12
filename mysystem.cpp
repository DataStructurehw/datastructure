#include "mysystem.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QTimer>
#include <stdlib.h>
#include<queue>
#include <time.h>
#include<complex>

int cnt=0,tigernumber=0;
mysystem::mysystem(QWidget *parent)
    :QWidget(parent)
{
    srand(time(NULL));
    this->setGeo(800,600);
    initSystem();
    QTimer *timer= new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=]{
        updatesystem();
        update();
    });
    timer->start(1000/60);
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
    const int numGrass = 300, numGroupCow = 6, numCowPerG = 5, numTiger = 5;//
    for (int i = 0; i < numGrass; ++i)
        grasslist.insert(new Grass(1000,
                            rand()/double(RAND_MAX)*this->width(),
                            rand()/double(RAND_MAX)*this->height(),10,10,cnt));
    for (int i = 0; i < numGroupCow; ++i) {
        double centerx = rand()/double(RAND_MAX)*this->width(),
                centery = rand()/double(RAND_MAX)*this->height();
        const double limx = 10, limy = 10;
        for (int j = 0; j < rand()%numCowPerG; ++j)
            cowlist.insert(new Cow(2000,rand()/double(RAND_MAX)*limx-limx/2+centerx,
                                rand()/double(RAND_MAX)*limy-limy/2+centery,rand()%2,cnt));//
    }
    for (int i = 0; i < numTiger; ++i){
        int tmp = rand()%2;
        tigerlist.insert(new Tiger(2000,rand()/double(RAND_MAX)*this->width(),
                                      rand()/double(RAND_MAX)*this->height(),tmp,cnt));//匹配新的构造函数
    }
}

void mysystem::drawsystem(QPainter *painter){
    for(Grass* iter:grasslist){
        painter->setBrush(iter->owncolor);
        painter->drawEllipse(QPointF(iter->getLoc().real(), iter->getLoc().imag()),2,2);
    }
    for(Cow* iter:cowlist){
        if (!iter->ishungry())
        painter->setBrush(iter->owncolor);
        else painter->setBrush(Qt::darkBlue);
        if(cnt-iter->getage()>iter->matingage)
        {
            if(cnt-iter->lastgen>100)
            painter->drawEllipse(QPointF(iter->getLoc().real(), iter->getLoc().imag()),5,5);
            else
                painter->drawEllipse(QPointF(iter->getLoc().real(), iter->getLoc().imag()),10,10);
        }
        else
        painter->drawEllipse(QPointF(iter->getLoc().real(), iter->getLoc().imag()),2,2);
    }
    for(auto iter:tigerlist){
        if (!iter->ishungry())
        painter->setBrush(iter->sex?Qt::red : Qt::yellow);
        else painter->setBrush(Qt::darkGray);
        if(cnt-iter->getage()>iter->matingage)
        {
            if(cnt-iter->lastgen>100)
            painter->drawEllipse(QPointF(iter->getLoc().real(), iter->getLoc().imag()),5,5);
            else
                painter->drawEllipse(QPointF(iter->getLoc().real(), iter->getLoc().imag()),10,10);
        }
        else
        painter->drawEllipse(QPointF(iter->getLoc().real(), iter->getLoc().imag()),2,2);
    }
}

struct Node { // Tiger A will hunt cow B
    Tiger* A;
    Cow* B;
    double dis;
    Node(Tiger* A=NULL, Cow* B=NULL): A(A), B(B) { dis = abs(A->getLoc()-B->getLoc()); }
    bool operator<(const Node &op) const {
        return dis > op.dis;
    }
};

struct NodeCG { // Cow eats  Grass
    Cow* C;
    Grass* G;
    double dis;
    NodeCG(Cow* C=NULL, Grass* G=NULL): C(C), G(G) { dis = abs(C->getLoc()-G->getLoc()); }
    bool operator<(const NodeCG &op) const {
        return dis > op.dis;
    }
};

struct NodeGT {
    Tiger* T;
    Grass* G;
    double dis;
    NodeGT(Grass* G=NULL, Tiger* T=NULL):T(T), G(G) { dis = abs(G->getLoc()-T->getLoc()); }
    bool operator<(const NodeGT &op) const {
        return dis > op.dis;
    }
};


const double pred_rad = 100, prey_rad = 100, eps = 2.4, RunTime = 1.0, Theta = M_PI_2 / 5;
const double tA = 0.2, tSpedMax = 2.5, tB = 0.18, cSpedMax = 2.0, engThresh = 0;
const complex<double> I(0, 1);


std::priority_queue<Node> que;
std::priority_queue<NodeGT> gtque;
std::priority_queue<NodeCG> pque;
std::set<Tiger*> matchedt;
std::set<Cow*> matchedc;
QList<Node> huntlist;
QList<pair<Cow*, std::complex<double> > > esclist;
std::set<Cow*> matchedC;
std::set<Grass*> matchedG;
QList<NodeCG> eatList;
std::set<Cow*> escC;
std::set<Grass*> matchG;


void mysystem::matchGT() {
    while (!gtque.empty()) gtque.pop();
    matchG.clear();
    for (Grass* g : grasslist)
        for (Tiger* t : tigerlist)
            if (abs(t->getLoc()-g->getLoc()) < 100) gtque.push(NodeGT(g, t));
    while (!gtque.empty()) {
        NodeGT tmp = gtque.top(); gtque.pop();
        matchG.insert(tmp.G);
    }
}


void mysystem::matchCG() {
    while (!pque.empty()) pque.pop();
    matchedC.clear(); matchedG.clear();
    eatList.clear();
    int cnt1=0;
    for (Cow* it: cowlist)
        if (it->ishungry()) {// condition hungry and condition safe  (it->ishungry())
            cnt1++;
            for (Grass* itG: grasslist)
                if (!matchG.count(itG)) pque.push(NodeCG(it, itG));
        }
    while (!pque.empty()) {
        NodeCG tmp = pque.top(); pque.pop();
        if (!matchedC.count(tmp.C) && !matchedG.count(tmp.G)) {
            eatList.push_back(tmp);
            cnt1--;
            matchedC.insert(tmp.C);
            matchedG.insert(tmp.G);
        }
    }
    if(cnt1>0) qDebug()<<1;
}

void eatGrass(Cow* C, Grass* G) {
    complex<double> cLoc = C->getLoc(), gLoc = G->getLoc(), cTg = gLoc-cLoc, speed = abs(C->getVel());
    if (abs(cTg) < eps) { C->setVel(0,0); return; } // Cow has eaten the grass
    C->setVel(cTg/abs(cTg)*speed);
    C->setLoc(cLoc+C->getVel());
}

void updateFreeWalk(Creature *it) {
    it->setVel(it->getVel()*exp((Theta*rand()/RAND_MAX*2-Theta)*I));
    it->setLoc(it->getLoc()+it->getVel()*RunTime);
}

void mysystem::freeWalk() { // cow and tiger would like free walking if they are not hunting or escaping.
    for (Cow *it: cowlist) if (it->getenergy() > engThresh) {
        bool flag = true;
        for (Tiger *pred: tigerlist)
            if (std::abs(it->getLoc()-pred->getLoc()) < prey_rad) {
                flag = false;
                break;
            }
        if (flag) updateFreeWalk(it);
    }
}

void hunt(Tiger *T, Cow *C) {
    std::complex<double> tLoc = T->getLoc(), cLoc = C->getLoc(), tVel = T->getVel(), TtoC = cLoc-tLoc;
    double dist = abs(TtoC), tSped = abs(tVel);
    if (dist < eps || T->getenergy() < engThresh) return; // hunt will end if T got the C or T has no energy
    if (dist > pred_rad) T->setLoc(tLoc+tVel*RunTime);
    else {
        T->setVel(TtoC/dist*min(tSped+tA*RunTime, tSpedMax));
        T->setLoc(tLoc+tVel*RunTime);
    }
}

void escape() { // update the cows in esclist
    for (auto it: esclist) {
        if (it.first->getenergy() < engThresh) continue;
        double speed = abs(it.first->getVel());
        complex<double> dir = it.second/abs(it.second);
        it.first->setVel(speed*dir);
        it.first->setLoc(it.first->getLoc()+dir*min(cSpedMax, speed+tB*RunTime)*RunTime);
    }
}


double Cross(complex<double> A, complex<double> B) {
    return A.real()*B.imag() - A.imag()*B.real();
}


void mysystem::match() { // clarify the relationship between the creature
    // initialize
    while (!que.empty()) que.pop();
    matchedt.clear(); matchedc.clear();
    huntlist.clear();
    // find out hungry tigers and match the cows
    for (Tiger* it: tigerlist)
        if (it->ishungry()) {  // condition hungry
            for (Cow* itcow: cowlist)
                que.push(Node(it, itcow));
        }
    while (!que.empty()) {
        Node tmp = que.top(); que.pop();
        if (!matchedc.count(tmp.B) && !matchedt.count(tmp.A)) {
            huntlist.push_back(tmp);
            matchedc.insert(tmp.B);
            matchedt.insert(tmp.A);
            tmp.A->setstate(1);
        }
    }
    esclist.clear();          // check which cows will escape
    for (Cow *it: cowlist) {
        bool flag = true;
        complex<double> tmp(0, 0);
        for (Tiger *pred: tigerlist) {
            double dis = std::abs(it->getLoc()-pred->getLoc());
            if (dis < eps) {
                flag = true;
                break;
            }
            if (dis < prey_rad) {
                flag = false;
                tmp += (it->getLoc()-pred->getLoc())/dis/dis;
            }
        }
        if (flag) continue;
        it->setstate(1);
        // the cow may choose a "vague" direction to run
        esclist.push_back(make_pair(it, tmp*exp(I*(Theta*rand()/RAND_MAX*2-Theta))));
    }
}

double calEnergy(Creature *it, double k, double t) {
    double v = abs(it->getVel());
    return k*v*v + t;
}

void mysystem::updateEnergy() {
    for (Cow *it: cowlist)
        it->energyloss(calEnergy(it, 2, 1));
    for (Tiger *it: tigerlist) {
        it->energyloss(calEnergy(it, 1, 1));

    }
    for (Grass *it: grasslist)
        it->energyloss(0.1);
}

void mysystem::takeFood() {
    for (auto it: eatList)
        if (abs(it.C->getLoc()-it.G->getLoc()) < 10) {
            it.C->energyloss(-it.G->getenergy()*0.9);
            grasslist.erase(it.G);
            delete it.G;
        }
    for (auto it: huntlist)
        if (abs(it.A->getLoc()-it.B->getLoc()) < eps) {
            it.A->energyloss(-it.B->getenergy()*0.8);
            cowlist.erase(it.B);
            delete it.B;
        }
}

template<class T>
void helpclear(std::set<T*> &s) {
    QList<T*> tmp;
    tmp.clear();
    for (auto it: s)
        if (it->getenergy() < 0) tmp.push_back(it);
    for (auto it: tmp) {
        s.erase(it);
        delete it;
    }
}

void mysystem::clearDeath() {
    helpclear(cowlist);
    helpclear(grasslist);
    helpclear(tigerlist);
}

void mysystem::Hang_out(Creature* x){

    if(typeid(*x).name()==typeid(Tiger).name()){
        Tiger* xx=dynamic_cast<Tiger*>(x);
        double vecx=0,vecy=0,svecx=0,svecy=0;
        for(auto iter:tigerlist){
            if(xx->sex==0) xx->territoryr=20;
            vecx=iter->getLoc().real() - xx->getLoc().real();
            vecy=iter->getLoc().imag() - xx->getLoc().imag();
            if(vecx>-20&&vecx<=20 && -20<=vecy && vecy<=20){
                if(rand()%15<2 && xx->getenergy()>=xx->energy_threshhold && iter->getenergy()>=iter->energy_threshhold && xx->sex^iter->sex && cnt-xx->getage()>xx->matingage && cnt-iter->getage()>iter->matingage){
                    if(iter->sex==0) iter->ispregnant=1;
                    else xx->ispregnant=1;
                    tigerlist.insert(new Tiger(xx->getenergy()/3,iter->getLoc().real(),iter->getLoc().imag(),rand()%2,cnt));
                    tigernumber++;
                    iter->lastgen=xx->lastgen=cnt;
                    xx->energyloss(xx->getenergy()/3);
                    iter->energyloss(iter->getenergy()/3);
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
                double x_dif=x_next-xx->getLoc().real();
                double y_dif=y_next-xx->getLoc().imag();
                double dis=sqrt(x_dif*x_dif+y_dif*y_dif);
                dis_sum[i+1]=dis_sum[i]+dis;
            }
            int pos=upper_bound(dis_sum,dis_sum+37,rand()/double(RAND_MAX)*dis_sum[36])-dis_sum;
            double angle_pos=10*pos+fir;
            double x_next=xx->territoryx+xx->territoryr*cos(angle_pos*3.14159/180);
            double y_next=xx->territoryy+xx->territoryr*sin(angle_pos*3.14159/180);

            svecx=x_next-xx->getLoc().real();
            svecy=y_next-xx->getLoc().imag();
            normalize(svecx,svecy);
            xx->now_vecx=svecx;
            xx->now_vecy=svecy;
            if(xx->sex==1)
            xx->change_time=75+rand()%10;
            else xx->change_time=30+rand()%10;
        }
        else xx->change_time--;
        xx->setLoc(xx->getLoc().real()+xx->now_vecx,xx->getLoc().imag()+xx->now_vecy);

    }
    else if(typeid(*x).name()==typeid(Cow).name()){
        double vecx=0,vecy=0,svecx=0,svecy=0;
        Cow* xx=dynamic_cast<Cow*>(x);
        for(auto iter:cowlist){
            vecx=iter->getLoc().real() - xx->getLoc().real();
            vecy=iter->getLoc().imag() - xx->getLoc().imag();
            if(vecx>-20&&vecx<=20 && -20<=vecy && vecy<=20){
                if(rand()%15<2 && xx->getenergy()>=xx->energy_threshhold
                        && iter->getenergy()>=iter->energy_threshhold && xx->sex^iter->sex &&
                        cnt-xx->getage()>xx->matingage && cnt-iter->getage()>iter->matingage){
                    cowlist.insert(new Cow(xx->getenergy()/3,iter->getLoc().real(),iter->getLoc().imag(),rand()%2,cnt));
                    iter->lastgen=xx->lastgen=cnt;
                    xx->energyloss(xx->getenergy()/3);
                    iter->energyloss(iter->getenergy()/3);
                }
                continue;
            }
            double weight=1;
            if (xx->sex^iter->sex) weight=2;
            svecx+=weight*vecx/sqrt(vecx*vecx+vecy*vecy);
            svecy+=weight*vecy/sqrt(vecx*vecx+vecy*vecy);
        }
    }
}
void mysystem::normalize(double &x, double &y){
    double tmp=x/sqrt(x*x+y*y);
    y=y/sqrt(x*x+y*y);
    x=tmp;
}
void mysystem::updatesystem(){
    cnt++;
    match();
    for (auto it: huntlist) hunt(it.A, it.B);
    escape();
    matchGT();
    matchCG();
    for (auto it: eatList) eatGrass(it.C, it.G);
    takeFood();
    clearDeath();
    for(auto iter:tigerlist){
        if (iter->getenergy()>iter->energy_threshhold || cnt-iter->getage()<iter->matingage)Hang_out(iter);
    }
    for(auto iter:cowlist){
        if (iter->getenergy()>iter->energy_threshhold || cnt-iter->getage()<iter->matingage)Hang_out(iter);
    }
    freeWalk();
    updateEnergy();
}
