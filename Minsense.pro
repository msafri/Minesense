#-------------------------------------------------
#
# Project created by QtCreator 2014-08-23T12:56:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Minsense
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    data.cpp \
    selectableellipse.cpp \
    view.cpp

HEADERS  += mainwindow.h \
    data.h \
    selectableellipse.h \
    view.h

FORMS    += mainwindow.ui
