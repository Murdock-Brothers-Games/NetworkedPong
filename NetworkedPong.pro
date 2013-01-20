#-------------------------------------------------
#
# Project created by QtCreator 2013-01-12T23:53:29
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkedPong
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mygldraw.cpp \
    gameobject.cpp \
    collisionsystem.cpp

HEADERS  += mainwindow.h \
    mygldraw.h \
    gameobject.h \
    collisiontypes.h \
    gameprimitives.h \
    collisionsystem.h \
    collision.h
