#ifndef MYGLDRAW_H
#define MYGLDRAW_H

#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QTime>
#include <QImage>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QList>
#include <ctime>
#include <stdlib.h>
#include <QImage>
#include <QColor>

#include "GL/GLU.h"
#include "gameobject.h"

class MyGLDraw: public QGLWidget
{
    Q_OBJECT


public:
    MyGLDraw(QWidget *parent=0);

    ~MyGLDraw();

    QSize size() const;

    QSize minimumSizeHint() const;

    QSize sizeHint() const;

public slots:
    void myUpdate();

protected:
    //Overridden QT Functions
    void initializeGL();

    void resizeGL(int w, int h);

    void paintGL();

private:

    QTimer* _timer;

    QTime* _simulationTime;

    QList<GameObject*> _screenObjects;



    float _width;
    float _height;


};

#endif // MYGLDRAW_H
