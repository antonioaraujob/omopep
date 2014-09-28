#-------------------------------------------------
#
# Project created by QtCreator 2014-09-15T10:46:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = omopep
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lsqlite3

SOURCES += main.cpp\
        mainwindow.cpp \
    simulation.cpp \
    particle.cpp \
    globalrepository.cpp \
    particlerepository.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    simulation.h \
    particle.h \
    globalrepository.h \
    particlerepository.h \
    qcustomplot.h

FORMS    += mainwindow.ui
