#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    spBox1->setRange(0,3);
    spBox1->setSingleStep(0.1);
    spBox1->setValue(1.50);

    spBox2->setRange(0.0,100.0);
    spBox2->setValue(50.0);

    spBox3->setRange(0,200);
    spBox3->setValue(70);

    QPushButton *but1 = new QPushButton("Accept");

    QLabel *heightLabel = new QLabel("Enter your height (m)");
    QLabel *weightLabel = new QLabel("Enter your weight (kg)");
    QLabel *waistLabel = new QLabel("Enter your waist (cm)");

    V_Layout1->addWidget(heightLabel);
    V_Layout1->addWidget(spBox1);
    V_Layout2->addWidget(weightLabel);
    V_Layout2->addWidget(spBox2);
    V_Layout3->addWidget(waistLabel);
    V_Layout3->addWidget(spBox3);
    V_Layout4->addWidget(but1);

    GrSpBox1->setLayout(V_Layout1);
    GrSpBox2->setLayout(V_Layout2);
    GrSpBox3->setLayout(V_Layout3);
    GrSpBox4->setLayout(V_Layout4);

    H_Layout1->addWidget(GrSpBox1);
    H_Layout1->addWidget(GrSpBox2);
    H_Layout1->addWidget(GrSpBox3);
    H_Layout1->addWidget(GrSpBox4);

    GrBox1->setLayout(H_Layout1);

    Fin_L->addWidget(GrBox1);

    connect(but1, &QPushButton::clicked,this, &MainWindow::AcceptButClicked);

    widget->setLayout(Fin_L);
    widget->setWindowTitle("ABSI Calculating");
    widget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::AcceptButClicked(){

    hgt = MainWindow::spBox1->value();
    wgt = MainWindow::spBox2->value();
    IMT = wgt/pow(hgt,2);
    wst = MainWindow::spBox3->value();
    double tmp = 2./3;
    ift = wst/(pow(IMT,tmp)*sqrt(hgt)*100);
    absi = (ift-mean)/sd;
    //QLabel *imt;
    //imt = new QLabel(tr("Your IFT = " "%1").arg(ift));
    absiz->setText(tr("Your ABSI = " "%1").arg(absi));
    if (absi<-0.868){res->setText("Death risk is very low"); res->setStyleSheet("QLabel { color : green }"); }
    else if((absi>-0.868)&&(absi<-0.272)){ res->setText("Death risk is low"); res->setStyleSheet("QLabel { color : green }"); }
    else if((absi>-0.272)&&(absi<0.229)){ res->setText("Death risk is average"); res->setStyleSheet("QLabel { color : orange }"); }
    else if((absi>0.229)&&(absi<0.798)){ res->setText("Death risk is high"); res->setStyleSheet("QLabel { color : orange }"); }
    else {res->setText("Death risk is very high"); res->setStyleSheet("QLabel { color : red }"); }

    Res_L->addWidget(absiz);
    Res_L->addWidget(res);

    GrBox2->setLayout(Res_L);

    Fin_L->addWidget(GrBox2);

}

