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
    parent->setGeometry(QRect(0,0,800,600));
    this->setGeo(800,600);
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
    const int numGrass = 100, numGroupCow = 10, numCowPerG = 10, numTiger = 10;
    const double energyGrass = 1e2, energyCow = 1e3, energyTiger = 1e4;
    srand(0);
    for (int i = 0; i < numGrass; ++i)
        grasslist.push_back(new Grass(0.0, energyGrass,   // 构造函数还有很多要改
                            rand()/double(RAND_MAX)*this->width(),
                            rand()/double(RAND_MAX)*this->height(),0,0));
    for (int i = 0; i < numGroupCow; ++i) {                  // Cow群落生成
        double centerx = rand()/double(RAND_MAX)*this->width(),
                centery = rand()/double(RAND_MAX)*this->height();
        const double limx = 10, limy = 10;
        for (int j = 0; j < numCowPerG; ++j)
            cowlist.push_back(new Cow(0,0,rand()/double(RAND_MAX)*limx-limx/2+centerx,
                                rand()/double(RAND_MAX)*limy-limy/2+centery,0,0));
    }
    for (int i = 0; i < numTiger; ++i)
        tigerlist.push_back(new Tiger(0,0,rand()/double(RAND_MAX)*this->width(),
                                      rand()/double(RAND_MAX)*this->height(),0,0));
}

void mysystem::drawsystem(QPainter *painter){
    for(Grass* iter:grasslist){
        painter->setBrush(iter->getcolor());
        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),5,5);
    }
    for(Cow* iter:cowlist){
        painter->setBrush(iter->getcolor());
        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),5,5);
    }
    for(Tiger* iter:tigerlist){
        painter->setBrush(iter->getcolor());
        painter->drawEllipse(QPointF(iter->displayx(),iter->displayy()),5,5);
    }
}

void mysystem::updatesystem(){
    for(Cow* iter:cowlist){
        if (rand() % 2==1)
        iter->setcoordinate(iter->displayx()+rand()/double(RAND_MAX)*this->width()/100,iter->displayy()+rand()/double(RAND_MAX)*this->width()/100);
        else
            iter->setcoordinate(iter->displayx()-rand()/double(RAND_MAX)*this->width()/100,iter->displayy()-rand()/double(RAND_MAX)*this->width()/100);
    }
    for(Tiger* iter:tigerlist){
        if (rand() % 2==1)
        iter->setcoordinate(iter->displayx()+rand()/double(RAND_MAX)*this->width()/100,iter->displayy()+rand()/double(RAND_MAX)*this->width()/100);
        else
            iter->setcoordinate(iter->displayx()-rand()/double(RAND_MAX)*this->width()/100,iter->displayy()-rand()/double(RAND_MAX)*this->width()/100);
    }
}

// hunting proccess

#include <queue>
#include <set>
#include <cmath>

struct Node { // Tiger A will hunt cow B
    Tiger* A;
    Cow* B;
    double dis;
    Node(Tiger* A=NULL, Cow* B=NULL, double dis=0): A(A), B(B) {}
    bool operator<(const Node &op) const {
        return dis > op.dis;
    }
};

std::priority_queue<Node> que;
std::set<Tiger*> matchedt;
std::set<Cow*> matchedc;
QList<Node> huntlist;

// help function
double mysystem::dist(Tiger* A, Cow* B) {
    double x = A->displayx()-B->displayx(),
            y = A->displayy()-B->displayy();
    return std::sqrt(x*x+y*y);
}

void mysystem::match() {
    // initialize
    while (!que.empty()) que.pop();
    matchedt.clear(); matchedc.clear();
    huntlist.clear();
    // find out hungry tigers and match the cows
    for (Tiger* it: tigerlist)
        if (it->ishungry()) {
            for (Cow* itcow: cowlist)
                que.push(Node(it, itcow, dist(it, itcow));
        }
    while (!que.empty()) {
        Node tmp = que.top(); que.pop();
        if (!matchedc.count(tmp.B) && ! matchedt.count(tmp.A)) {
            huntlist.push_back(tmp);
            matchedc.insert(tmp.A);
            matchedt.insert(tmp.B);
        }
    }
}

void mysystem::hunt() {

}

void mysystem::escape() {
    
}
