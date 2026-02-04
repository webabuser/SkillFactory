#-------------------------------------------------
#
# Project created by QtCreator 2025-11-06T14:38:28
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui_server
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_CXXFLAGS += -std=c++17
LIBS += -lmysqlclient

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        usermanager.cpp \
        config.cpp

HEADERS += \
        mainwindow.h \
        usermanager.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc

CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += -O0  # Отключаем оптимизации
}
