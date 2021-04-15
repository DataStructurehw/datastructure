#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startbutton_clicked();

    void on_stopbutton_clicked();

    void on_speedslide_valueChanged(int value);

    void on_tigeradd_clicked();

    void on_cowadd_clicked();

    void on_grassadd_clicked();

private:
    Ui::MainWindow *ui;
    int tigeradd = 0;
    int cowadd = 0;
    int grassadd = 0;

protected:
    void mousePressEvent(QMouseEvent *e);
};

#endif // MAINWINDOW_H
