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
    QByteArray fileFormat=action->data().toByteArray();
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
void Paint::createActions(){
    openAct =new QAction(tr("&Open"),this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct,SIGNAL(triggered()),this,SLOT(open()));
    foreach(QByteArray format,QImageWriter::supportedImageFormats()){
        QString text=tr("%1...").arg(QString(format).toUpper());
        QAction *action =new QAction(text,this);
        action->setData(format);
        connect(action,SIGNAL(triggered()),this,SLOT(save()));
        saveAsActs.append(action);
    }
    printAct=new QAction (tr("&Print..."),this);
    connect(printAct,SIGNAL(triggered()),scribbleArea,SLOT(print()));


    exitAct=new QAction (tr("&Exit..."),this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct,SIGNAL(triggered()),scribbleArea,SLOT(close()));


    penColorAct=new QAction (tr("&Pen Color..."),this);
    connect(penColorAct,SIGNAL(triggered()),scribbleArea,SLOT(penColor()));

    penWidthAct=new QAction (tr("&Pen & Width..."),this);
    connect(penWidthAct,SIGNAL(triggered()),scribbleArea,SLOT(penWidth()));

    clearScreenAct=new QAction (tr("&Clear..."),this);
    connect(clearScreenAct,SIGNAL(triggered()),scribbleArea,SLOT(clearImage()));

    aboutAct=new QAction (tr("&About..."),this);
    connect(aboutAct,SIGNAL(triggered()),scribbleArea,SLOT(about()));

    aboutQtAct=new QAction (tr("&About &Qt..."),this);
    connect(aboutQtAct,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
}
void Paint::createMenus(){
    saveAsMenu=new QMenu(tr("& Save As"),this);
    foreach(QAction *action,saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu=new QMenu(tr("&File"),this);
    fileMenu->addAction(openAct);
    //    fileMenu->addAction(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addAction(exitAct);
    optionMenu=new QMenu(tr("&Options"),this);
    optionMenu->addSeparator();
    // TODO: compelte the list of the option and menu lists
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    fileMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    helpMenu=new QMenu(tr("&Help"),this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    helpMenu->addMenu(optionMenu);
    helpMenu->addMenu(helpMenu);
}
bool Paint::maybeSave(){
    if(scribbleArea->isModified()){
        QMessageBox::StandardButton ret;
        ret=QMessageBox::warning(this,tr("Scribble"),tr("The image has been modified.\n"
                                                        "Do you want to save yoru changes?"),QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if(ret==QMessageBox::Save)
            return saveFile("png");
        else if(ret==QMessageBox::Cancel)
            return false;
    }
    return true;
}
bool Paint::saveFile(const QByteArray &fileFormat){
    QString path=QDir::currentPath()+"/unitled"+fileFormat;
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save As"),
                                                  path,tr("%1 Files (*.%2);; All Files(*").arg(QString::fromLatin1(fileFormat.toUpper())).QString::fromLatin1(fileFormat));
    if(fileName.isEmpty()){
        return false;
    }
    else{
        return scribbleArea->saveImage(fileName,fileFormat.constData());
    }
}
Paint::~Paint()
{
    delete ui;
}

