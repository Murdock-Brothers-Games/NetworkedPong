#-------------------------------------------------
#
# Project created by QtCreator 2013-01-12T23:53:29
#
#-------------------------------------------------

QT       += core gui opengl phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkedPong
TEMPLATE = app


SOURCES += ./src/*.cpp

HEADERS  += ./src/*.h

LIBS += -lglut -lGL -lGLU -lGLEW
OTHER_FILES +=

RESOURCES += \
    ./res/PongResources.qrc
