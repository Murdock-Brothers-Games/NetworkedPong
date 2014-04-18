#-------------------------------------------------
#
# Project created by QtCreator 2013-01-12T23:53:29
#
#-------------------------------------------------

QT       += core gui opengl phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkedPong
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mygldraw.cpp \
    gameobject.cpp \
    collisionsystem.cpp \
    gameengine.cpp \
    gamestate.cpp \
    pongstate.cpp \
    sleepthread.cpp \
    soundmanager.cpp

HEADERS  += mainwindow.h \
    mygldraw.h \
    gameobject.h \
    collisiontypes.h \
    gameprimitives.h \
    collisionsystem.h \
    collision.h \
    gameengine.h \
    gamestate.h \
    pongstate.h \
    sleepthread.h \
    soundmanager.h

LIBS += -lglut -lGL -lGLU -lGLEW
OTHER_FILES +=

RESOURCES += \
    PongResources.qrc
