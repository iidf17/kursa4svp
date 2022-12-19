#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QGroupBox>
#include <math.h>
#include <iostream>

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    double hgt;
    double wgt;
    double IMT;
    double wst;
    double ift = 0;
    double sd = 0.00375;
    double mean = 0.07725;
    double absi = 0;

    QWidget *widget = new QWidget;


    QLabel *absiz = new QLabel(tr("Your ABSI = " "%1").arg(absi));;
    QLabel *res = new QLabel;

    QDoubleSpinBox *spBox1 = new QDoubleSpinBox();
    QDoubleSpinBox *spBox2 = new QDoubleSpinBox();
    QDoubleSpinBox *spBox3 = new QDoubleSpinBox();

    QPushButton *clear = new QPushButton("Clear");

    QGroupBox *GrSpBox1 = new QGroupBox;
    QGroupBox *GrSpBox2 = new QGroupBox;
    QGroupBox *GrSpBox3 = new QGroupBox;
    QGroupBox *GrSpBox4 = new QGroupBox;
    QGroupBox *GrBox1 = new QGroupBox;
    QGroupBox *GrBox2 = new QGroupBox;


    QVBoxLayout *V_Layout1 = new QVBoxLayout;
    QVBoxLayout *V_Layout2 = new QVBoxLayout;
    QVBoxLayout *V_Layout3 = new QVBoxLayout;
    QVBoxLayout *V_Layout4 = new QVBoxLayout;
    QHBoxLayout *H_Layout1 = new QHBoxLayout;
    QVBoxLayout *Res_L = new QVBoxLayout;
    QGridLayout *Fin_L = new QGridLayout;

private:
    Ui::MainWindow *ui;



public slots:
    void AcceptButClicked();
    //void ClearButClicked();
};

#endif // MAINWINDOW_H
