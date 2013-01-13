#ifndef MYGLDRAW_H
#define MYGLDRAW_H

#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QImage>
#include <QFile>
#include <QFileDialog>
#include <QString>

#include "GL/GLU.h"

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

    float _width;
    float _height;

};

#endif // MYGLDRAW_H
