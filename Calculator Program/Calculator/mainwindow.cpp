#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QDebug>
#include<QStack>

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
    // creating array to iterate from 0->9 and check if button 's number pressed or not
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

    // clear calc
    connect(ui->Clear,SIGNAL(released()),this,SLOT(clearFunc()));

    // memories
    connect(ui->MemAdd,SIGNAL(released()),this,SLOT(pushMemory()));
    connect(ui->MemClear,SIGNAL(released()),this,SLOT(popMemory()));
    connect(ui->MemGet,SIGNAL(released()),this,SLOT(getMemory()));

}
// function when user enters any button except 0->9
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

    if(addTrig)
        sol=calcVal+dbDisplayVal;
    else if(subTrig)
        sol=calcVal-dbDisplayVal;
    else if(multTrig)
        sol=calcVal*dbDisplayVal;
    else
        sol=calcVal/dbDisplayVal;

    ui->Display->setText(QString::number(sol));
}
void MainWindow::changeNumberSign(){

    QString dispVal=ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(dispVal)){
        double dbDispVal=dispVal.toDouble();
        double dbDisplaySign=-1*dbDispVal;
        ui->Display->setText(QString::number(dbDisplaySign));
    }
}
void MainWindow::clearFunc(){
    calcVal=0.0;
    ui->Display->setText("0");
}

// Memories
void MainWindow::popMemory(){
    if(!Memory.empty())
        Memory.pop();
}
void MainWindow::pushMemory(){
    double val=ui->Display->text().toDouble();
    Memory.push(val);
}
void MainWindow::getMemory(){
    if(!Memory.empty()){
        calcVal=Memory.top();
        ui->Display->setText(QString::number(calcVal));
    }
    else
        ui->Display->setText("0");
}

// destructor
MainWindow::~MainWindow()
{
    delete ui;
}

