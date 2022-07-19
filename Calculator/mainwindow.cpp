#include "mainwindow.h"
#include "./ui_mainwindow.h"

double calcVal=0;
bool divTrig=false;
bool multTrig=false;
bool addTrig=false;
bool subTrig=false;
// constrcutor
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0;i<10;i++){
        QString butName="Button"+QString::number(i);
        numButtons[i]=MainWindow :: findChild<QPushButton*>(butName);
        connect(numButtons[i],SIGNAL(relesed()),this,SLOT(numPressed()));
    }
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
        ui->Display->setText(QString::number(dbnewVal));
    }
}
void MainWindow::mathButtuonsPressed(){

}
void MainWindow::equalButton(){

}
void MainWindow::changeNumberSign(){

}

// destructor
MainWindow::~MainWindow()
{
    delete ui;
}

