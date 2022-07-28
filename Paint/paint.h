#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>
#include<QList>
class scribblearea;
QT_BEGIN_NAMESPACE
namespace Ui { class Paint; }
QT_END_NAMESPACE

class Paint : public QMainWindow
{
    Q_OBJECT

public:
    Paint(QWidget *parent = nullptr);
    ~Paint();
protected :
    void closeEvent(QCloseEvent *event)override;
private:
    Ui::Paint *ui;
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormate);
    scribblearea *scribbleArea;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QList <QAction*>saveActs;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

};
#endif // PAINT_H
