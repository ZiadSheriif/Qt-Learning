#include "paint.h"
#include<QtWidgets>
#include<QByteArray>
#include<QByteRef>
#include<ScribbleArea.h>
#include "./ui_paint.h"

Paint::Paint(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Paint)
{
    ui->setupUi(this);
    scribbleArea =new scribblearea();
    setCentralWidget(scribbleArea);
    createActions();
    createMenus();
    setWindowTitle(tr("Scribble"));
    resize(500,500);
}
void Paint::closeEvent(QCloseEvent *event){
    if(maybeSave())
        event->accept();
    else
        event->accept();
}
void Paint::open(){
    if(maybeSave()){
        QString fileName=QFileDialog::getOpenFileName(this,tr("Open file"),QDir::currentPath());
        if(!fileName.isEmpty())
            scribbleArea->openImage(fileName);
    }
}
void Paint::save(){
    QAction *action=qobject_cast<QAction *>(sender());
    QByte fileFormat=action->data().toBitArray();
    saveFile(fileFormat);
}
void Paint::penColor(){
    QColor newColor=QColorDialog::getColor(scribbleArea->penColor());
    if(newColor.isValid())
        scribbleArea->setPenColor(newColor);
}
void Paint::penWidth(){
    bool test;
    int newWidth=QInputDialog::getInt(this,tr("Scribb;e"),tr("Select pen width"),scribbleArea->penWidth(),1,50,1,&test);
    if(test)
        scribbleArea->setPenWidth(newWidth);

}
void Paint::about(){
//    QMessageBox::about(this,tr("About Scrrible"),try)
}
Paint::~Paint()
{
    delete ui;
}

