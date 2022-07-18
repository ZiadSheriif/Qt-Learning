#include <QCoreApplication>
#include<qdebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString manga="hello world";
    qDebug()<<manga;

    return a.exec();
}
