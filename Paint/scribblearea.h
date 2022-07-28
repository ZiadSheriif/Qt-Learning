#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H
#include<QPoint>
#include<QColor>
#include<QWidget>
#include<QImage>
class scribblearea :public QWidget
{
    Q_OBJECT
public:
    scribblearea(QWidget *parent=0);
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName,const char*fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidht);


    bool isModified()const {return modified;}
    QColor penColor()const{return myPenColor;}
    int penWidth()const {return myPenWidth;}



private slots:
    void clearImage();
    void print();
protected:
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void paintEvent(QPaintEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;


private:
    void drawlineTo(const QPoint &endPoint);
    void resizeImage(QImage *image,const QSize &newSize);
    bool modified;
    bool scribbleing;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    int myPenWidth;


};

#endif // SCRIBBLEAREA_H
