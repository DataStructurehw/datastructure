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
double dist(Tiger* A, Cow* B) {
    double x = A->displayx()-B->displayx(),
            y = A->displayy()-B->displayy();
    return std::sqrt(x*x+y*y);
}

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
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
                que.push(Node(it, itcow, dist(it, itcow)));
        }
    while (!que.empty()) {
        Node tmp = que.top(); que.pop();
        if (!matchedc.count(tmp.B) && ! matchedt.count(tmp.A)) {
            huntlist.push_back(tmp);
            matchedc.insert(tmp.B);
            matchedt.insert(tmp.A);
        }
    }
}

bool def_cd() {
    return rand()/double(RAND_MAX) > 0.7;
}

// help function Cow(x1, y1) is chased by Tiger(x2, y2) with original direction vector(d1, d2)
bool prey_pred(Tiger *A, Cow *B) {
    double x1 = B->displayx(), y1 = B->displayy(), x2 = A->displayx(), y2 = A->displayy(),
            d1 = B->displayd1(), d2 = B->displayd2(), D1 = A->displayd1(), D2 = A->displayd2();

    double pred_rad = 6, prey_rad = 4, pred_speed = A->getspeed(), prey_speed = B->getspeed(),
            pred_speed_max = 1.5, prey_speed_max = 1.2, pred_a = 0.4, prey_a = 0.3, dis=dist(x1, y1, x2, y2);

    const double eps = 1e-1, limit = 1e-1;
    // Base Case
    if (fabs(dist(A, B)) < eps) return true;
    if (A->getenergy() < limit) return false;

    double tx = (x1-x2)/dis, ty = (y1-y2)/dis;
    A->setd1(tx); B->setd2(ty);
    if (dis > pred_rad) { x2 += tx*pred_speed; y2 += ty*pred_speed; x1 += d1*prey_speed; y1 += d2*prey_speed; }
    else {
        pred_speed = min(pred_a+pred_speed, pred_speed_max);
        x2 += tx*pred_speed; y2 += ty*pred_speed;
        if (dist(x1, y1, x2, y2) < prey_rad && B->getenergy() > limit) {       // if the distance between them is smaller than pred_rad, Cow B would accelerate
            prey_speed = min(prey_a+prey_speed, prey_speed_max);
            if (def_cd()) { double ptx = tx, pty = -ty, a = rand()%4-2; tx += a*ptx; ty += a*pty; tx /= diss; ty /= diss; }
            x1 += tx*prey_speed; y1 += ty*prey_speed;
            B->setd1(tx); B->setd2(ty);
        }
    }
    // here would decrease their energy
    B->setx(x1); B->sety(y1); B->setspeed(prey_speed);
    A->setx(x2); A->Sety(y2); A->setspeed(pred_speed);
    return false;
}

void mysystem::hunt() {
    for (Node it: huntlist) // update the nodes in huntlist
        if (prey_pred(it.A, it.B)) eat(it.A, it.B);
}

// Test program
//int main() {
//    double x1=0, y1=0, x2=18, y2=6, d1=0, d2=0;
//    prey_pred(x1, y1, x2, y2, d1, d2);
//    return 0;
//}


