#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QDebug>

// global variables
double calcVal=0.0;
bool divTrig=false;
bool multTrig=false;
bool addTrig=false;
bool subTrig=false;


// constrcutor
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    // generate window
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0;i<10;i++){
        // iterate on each button and casting with a certain one
        QString butName="pushButton"+QString::number(i);
        numButtons[i]=MainWindow :: findChild<QPushButton  *>(butName);
        connect(numButtons[i],SIGNAL(released()),this,SLOT(numPressed()));
    }


    // operations
    connect(ui->add,SIGNAL(released()),this,SLOT(mathButtuonsPressed()));
    connect(ui->subtract,SIGNAL(released()),this,SLOT(mathButtuonsPressed()));
    connect(ui->multiply,SIGNAL(released()),this,SLOT(mathButtuonsPressed()));
    connect(ui->div,SIGNAL(released()),this,SLOT(mathButtuonsPressed()));

    // equals
    connect(ui->Equals,SIGNAL(released()),this,SLOT(equalButton()));

    // change sign
    connect(ui->changeSign,SIGNAL(released()),this,SLOT(changeNumberSign()));

}

void MainWindow:: numPressed(){
    QPushButton *button=(QPushButton*)sender();
    QString butVal= button->text();
    QString displayVal=ui->Display->text();
    if(displayVal.toDouble()==0.0 || displayVal.toDouble()==0)
        ui->Display->setText(butVal);
    else
    {
        QString newVal=displayVal+butVal;
        double  dbnewVal=newVal.toDouble();
        ui->Display->setText(QString::number(dbnewVal,'g',16));
    }
}
void MainWindow::mathButtuonsPressed(){

    divTrig=false;
    multTrig=false;
    addTrig=false;
    subTrig=false;


    QString displayVal=ui->Display->text();
    calcVal=displayVal.toDouble();
    QPushButton *button=(QPushButton  *)sender();
    QString butVal=button->text();
    if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0)
        divTrig=true;
    else    if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0)
        multTrig=true;
    else   if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0)
        addTrig=true;
    else
        subTrig=true;
    ui->Display->setText("");
}
void MainWindow::equalButton(){
    double sol=0.0;
    QString displayVal=ui->Display->text();
    double dbDisplayVal=displayVal.toDouble();
    if(addTrig || subTrig || multTrig || divTrig){
        if(addTrig)
            sol=calcVal+dbDisplayVal;
        else if(subTrig)
            sol=calcVal-dbDisplayVal;
        else if(multTrig)
            sol=calcVal*dbDisplayVal;
        else
            sol=calcVal/dbDisplayVal;
    }
    ui->Display->setText(QString::number(sol));
}
void MainWindow::changeNumberSign(){

    QString dispVal=ui->Display->text();
    QRegExp reg("[-]?[0-9.]");
    if(reg.exactMatch(dispVal)){
        double dbDispVal=dispVal.toDouble();
        double dbDisplaySign=-1*dbDispVal;
        ui->Display->setText(QString::number(dbDisplaySign));
    }
}

// destructor
MainWindow::~MainWindow()
{
    delete ui;
}

