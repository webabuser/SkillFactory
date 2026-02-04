#include "mainwindow.h"
#include <QApplication>
#include "usermanager.h"
#include <QDebug>
#include <QFile>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QFile styleFile(":/styles/style.qss");
    if(styleFile.open(QFile::ReadOnly)){
        a.setStyleSheet(styleFile.readAll());
    }


    MainWindow w;
    w.show();




    return a.exec();
}
