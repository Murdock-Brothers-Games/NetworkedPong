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
    MyGLDraw(int screenWidth, int screenHeight, QWidget *parent=0);

    ~MyGLDraw();

    QList<GameObject*> getGameObjects();

    void setGameObjects(QList<GameObject*> gObjs);

    int getNumGameObjects();

    void clearGameObjects();

    void addGameObject(GameObject* gObj);

    bool removeGameObject(QString name);

    int getScreenWidth();

    void setScreenWidth(int width);

    int getScreenHeight();

    void setScreenHeight(int height);

    void myGLRender();

    QSize size() const;

    QSize minimumSizeHint() const;

    QSize sizeHint() const;

public slots:


protected:
    //Overridden QT Functions
    void initializeGL();

    void resizeGL(int w, int h);

    void paintGL();

private:

    GLuint _quadTexture;
    QTimer* _timer;

    QTime* _simulationTime;

    QList<GameObject*> _screenObjects;

    float _width;
    float _height;

};

#endif // MYGLDRAW_H
