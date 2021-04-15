#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
extern QTimer *timer;
extern int cnt;
extern set<Tiger*> tigerlist;
extern set<Cow*> cowlist;
extern set<Grass*> grasslist;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Enclosed System");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startbutton_clicked()
{
    timer->start();
}

void MainWindow::on_stopbutton_clicked()
{
    timer->stop();
}

void MainWindow::on_speedslide_valueChanged(int value)
{
    timer->stop();
    timer->start(1000/(60*value));
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(tigeradd==1)
    tigerlist.insert(new Tiger(2000,e->x(),e->y(),rand()%2,cnt));
    else if(grassadd==1)
        grasslist.insert(new Grass(1000,e->x(),e->y(),10,10,cnt));
    else if(cowadd==1)
        cowlist.insert(new Cow(2000,e->x(),e->y(),rand()%2,cnt));
    else return;
}

void MainWindow::on_tigeradd_clicked()
{
    if(tigeradd==0) tigeradd = 1;
    else tigeradd = 0;
}

void MainWindow::on_cowadd_clicked()
{
    if(cowadd==0) cowadd = 1;
    else cowadd = 0;
}

void MainWindow::on_grassadd_clicked()
{
    if(grassadd==0) grassadd = 1;
    else grassadd = 0;
}
