#include "mysystem.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QTimer>
#include <stdlib.h>
#include <time.h>

mysystem::mysystem(QWidget *parent)
    :QWidget(parent)
{
    parent->setGeometry(QRect(0,0,1280, 720));
    this->setGeo(1280, 720);
    qDebug()<<this->width();
    initSystem();
    QTimer *timer= new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=]{
        updatesystem();
        update();
    });
    timer->start(100);
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
    // testcreature *a1= new testcreature(Qt::blue,this->width()/2,this->height());
    // creaturelist.push_back(a1);
    // qDebug()<<this->width()<<this->height();
    // testcreature *a2=new testcreature(Qt::red,this->width(),this->height()/2);
    // creaturelist.push_back(a2);
    // testcreature *a3 =new testcreature(Qt::green,400,300);
    // creaturelist.push_back(a3);
    // initialize ramdom seed
    srand((unsigned)time(NULL));
    const int numGrass = 500, numGroupCow = 50, numCowPerG = 10, numTiger = 100;
    const double energyGrass = 1e2, energyCow = 1e5, energyTiger = 1e4;
    for (int i = 0; i < numGrass; ++i)
        grasslist.insert(new Grass(energyGrass,
                            rand()/double(RAND_MAX)*this->width(),
                            rand()/double(RAND_MAX)*this->height(),0,energyGrass/3));
    for (int i = 0; i < numGroupCow; ++i) {                  // Cow群落生成
        double centerx = rand()/double(RAND_MAX)*this->width(),
                centery = rand()/double(RAND_MAX)*this->height();
        const double limx = 10, limy = 10;
        for (int j = 0; j < numCowPerG; ++j)
            cowlist.insert(new Cow(1,energyCow,rand()/double(RAND_MAX)*limx-limx/2+centerx,
                                rand()/double(RAND_MAX)*limy-limy/2+centery,0,energyCow/3));
    }
    for (int i = 0; i < numTiger; ++i)
        tigerlist.insert(new Tiger(2,energyTiger,rand()/double(RAND_MAX)*this->width(),
                                      rand()/double(RAND_MAX)*this->height(),0,energyTiger/3));
}

void mysystem::drawsystem(QPainter *painter){
    for(Grass* iter:grasslist){
        painter->setBrush(iter->getcolor());
        painter->drawEllipse(QPointF(iter->getLoc().real(),iter->getLoc().imag()),5,5);
    }
    for(Cow* iter:cowlist){
        painter->setBrush(iter->getcolor());
        painter->drawEllipse(QPointF(iter->getLoc().real(),iter->getLoc().imag()),5,5);
    }
    for(Tiger* iter:tigerlist){
        painter->setBrush(iter->getcolor());
        painter->drawEllipse(QPointF(iter->getLoc().real(),iter->getLoc().imag()),5,5);
    }
}


/**************************************************************
 *  main updating system program is updatesystem(), when other*
 * functions are the parts of it.                             *
***************************************************************/

#include <iostream>
#define DebugP(x) std::cout << "Line" << __LINE__ << " " << #x << "=" << x << endl



#include <queue>
#include <cmath>

// help function

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


const double pred_rad = 100, prey_rad = 100, limit = 1e-1, eps = 2.4, RunTime = 1.0, Theta = M_PI_2 / 5;
const double tA = 0.2, tSpedMax = 2.5, tB = 0.18, cSpedMax = 2.0, engThresh = 10;
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
    for (Cow* it: cowlist)
        if (!escC.count(it) && it->ishungry()) {// condition hungry and condition safe  (it->ishungry())
            for (Grass* itG: grasslist)
                if (!matchG.count(itG)) pque.push(NodeCG(it, itG));
        }
    while (!pque.empty()) {
        NodeCG tmp = pque.top(); pque.pop();
        if (!matchedC.count(tmp.C) && !matchedG.count(tmp.G)) {
            eatList.push_back(tmp);
            matchedC.insert(tmp.C);
            matchedG.insert(tmp.G);
        }
    }
}

void eatGrass(Cow* C, Grass* G) {
    complex<double> cLoc = C->getLoc(), gLoc = G->getLoc(), cTg = gLoc-cLoc, speed = abs(C->getVel());
    if (abs(cTg) < eps) { C->setVel(0,0); return; } // Cow has eaten the grass
    C->setVel(cTg/abs(cTg)*speed);
    C->setLoc(cLoc+C->getVel());
}

// help function to update the object in free walking state.
void updateFreeWalk(Creature *it) {
    it->setVel(it->getVel()*exp((Theta*rand()/RAND_MAX*2-Theta)*I));
    it->setLoc(it->getLoc()+it->getVel()*RunTime);
}

void mysystem::freeWalk() { // cow and tiger would like free walking if they are not hunting or escaping.
    for (Tiger *it: tigerlist)
            if (it->getState() == 0 && it->getenergy() > engThresh)
                updateFreeWalk(it);
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
            tmp.A->setState(1);
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
        it->setState(1);
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
        it->energyloss(calEnergy(it, 20, 1));
    for (Tiger *it: tigerlist) {
        it->energyloss(calEnergy(it, 10, 10));
        DebugP(it->getenergy());
    }
    for (Grass *it: grasslist)
        it->energyloss(0.1);
}

void mysystem::takeFood() {
    for (auto it: eatList)
        if (abs(it.C->getLoc()-it.G->getLoc()) < eps) {
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

void mysystem::updatesystem(){
//    for(Cow* iter:cowlist){
//        if (rand() % 2==1)
//        iter->setcoordinate(iter->getLoc().real()+rand()/double(RAND_MAX)*this->width()/100,iter->getLoc().imag()+rand()/double(RAND_MAX)*this->width()/100);
//        else
//            iter->setcoordinate(iter->getLoc().real()-rand()/double(RAND_MAX)*this->width()/100,iter->getLoc().imag()-rand()/double(RAND_MAX)*this->width()/100);
//    }
//    for(Tiger* iter:tigerlist){
//        if (rand() % 2==1)
//        iter->setcoordinate(iter->getLoc().real()+rand()/double(RAND_MAX)*this->width()/100,iter->getLoc().imag()+rand()/double(RAND_MAX)*this->width()/100);
//        else
//            iter->setcoordinate(iter->getLoc().real()-rand()/double(RAND_MAX)*this->width()/100,iter->getLoc().imag()-rand()/double(RAND_MAX)*this->width()/100);
//    }
    match();
    for (auto it: huntlist) hunt(it.A, it.B);
    escape();
    freeWalk();
    matchGT();
    matchCG();
    for (auto it: eatList) eatGrass(it.C, it.G);
    takeFood();
    clearDeath();
    updateEnergy();
}


