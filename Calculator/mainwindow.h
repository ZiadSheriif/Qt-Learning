#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QStack>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStack<double>Memory;

private slots:
    void numPressed();
    void mathButtuonsPressed();
    void equalButton();
    void changeNumberSign();
    void clearFunc();
    void popMemory();
    void pushMemory();
    void getMemory();

};
#endif // MAINWINDOW_H
