#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include <QFileInfo>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
/*
    QTranslator myappTranslator;
    myappTranslator.load("../translations/my_ru.qm");
    a.installTranslator(&myappTranslator);
/*
    QTranslator qtTranslator;
    qtTranslator.load("../translations/qt_ru.qm");
    a.installTranslator(&qtTranslator);
*/

    QTranslator myappTranslator;
    QString appDir = QCoreApplication::applicationDirPath();
    QString translationPath = appDir + "/translations/my_ru.qm";

    qDebug() << QCoreApplication::applicationDirPath();

    if (myappTranslator.load(translationPath)) {
        a.installTranslator(&myappTranslator);
    } else {
        qDebug() << "Translation file not loaded!";
    }

    qDebug() << "Current language:" << QLocale::system().name();
    qDebug() << "Translation loaded:" << !myappTranslator.isEmpty();


    // Проверка существования файла
    //QString translationPath = "translations/my_ru.qm";
    QFileInfo checkFile(translationPath);
    qDebug() << "Translation file exists:" << checkFile.exists();
    qDebug() << "Absolute path:" << checkFile.absoluteFilePath();


    if (myappTranslator.load(translationPath)) {
        a.installTranslator(&myappTranslator);
        qDebug() << "Translation loaded successfully";
    } else {
        qDebug() << "Translation file not loaded!";
    }








    auto w = MainWindow::createClient();

    if(w)
        w->show();
    else
        return 0;

    return a.exec();
}
