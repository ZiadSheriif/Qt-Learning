#include<QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include<QPrinter>
#include<QPrinterDialog>
#endif
#endif
#include "scribblearea.h"
scribblearea::scribblearea(scribblearea *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified=false;
    scribbling=false;
    myPenWidth=1;
    myPenColor=Qt::blue;
}
bool scribblearea::openImage(const QString &fileName){
    QImage loadedImage;
    if(!loadedImage.load(fileName)){
        return false;
    }
    QSize newsz=loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage,newsz);
    image=loadedImage;
    modified=false;
    update();
    return true;
}
bool scribblearea::saveImage(const QString &fileName,const char *fileFormat){
    QImage visibleImage=image;
    resizeImage(&visibleImage,size());
    if(visibleImage.save(fileName,fileFormat)){
        modified=false;
        return true;
    }
    else
        return false;
}
void scribblearea::setPenColor(const QColor &newColor){
    myPenColor=newColor;
}
void scribblearea::setPenWidth(int newWidth){
    myPenWidth=newWidth;
}
void scribblearea::clearImage(){
    image.fill(qRgb(255,255,255));
    modified=true;
    update();
}
void scribblearea::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        lastPoint=event->pos();
        scribbling=true;
    }
}
void scribblearea::mouseMoveEvent(QMouseEvent *event){
    if((event->buttons()&Qt::LeftButton)&&scribbling){
        drawlineTo(event->pos());
    }
}

