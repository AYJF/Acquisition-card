#-------------------------------------------------
#
# Project created by QtCreator 2019-02-05T14:07:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TADQTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workerthread.cpp

HEADERS  += mainwindow.h \
    BDaqCL.h \
    workerthread.h

FORMS    += mainwindow.ui
