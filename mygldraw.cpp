#include "mygldraw.h"
#include <QDebug>

MyGLDraw::MyGLDraw(int screenWidth, int screenHeight, QWidget* parent):
 QGLWidget(parent),
  _width(screenWidth),
  _height(screenHeight)
{
    srand(time(NULL));
    resizeGL(_width,_height);



    //30 millisecond timer
    //_timer.setInterval(30);
    //_timer = new QTimer(this);
    //_simulationTime = new QTime();
    //_simulationTime->start();
    //connect(_timer, SIGNAL(timeout()), this, SLOT(myUpdate()));
    //_timer->start(15);

}

MyGLDraw::~MyGLDraw()
{
    glDeleteTextures(1, &_quadTexture);
}

QList<GameObject*> MyGLDraw::getGameObjects()
{
    return _screenObjects;
}

void MyGLDraw::setGameObjects(QList<GameObject*> gObjs)
{
    _screenObjects = gObjs;
}

int MyGLDraw::getNumGameObjects()
{
    return _screenObjects.size();
}

void MyGLDraw::clearGameObjects()
{
    //May not want to do this here.
    //The game engine should be the only
    //one creating or deleting game
    //objects.
    //*Edit* - It looks like clear() doesn't
    //         call the destructors, it just
    //         removes them from the list.
    //         As long as that's true this
    //         should be fine, but if anything
    //         goes wrong check this function.
    _screenObjects.clear();
}

void MyGLDraw::addGameObject(GameObject* gObj)
{
    _screenObjects.append(gObj);
}

bool MyGLDraw::removeGameObject(QString name)
{
    int index = 0;
    bool found = false;
    for(index = 0; index < _screenObjects.size(); ++index){
        if( _screenObjects[index]->getName() == name ){
            found = true;
            break;
        }
    }
    if( found ){
        _screenObjects.removeAt(index);
    }else{
        qDebug() << QString("MyGLDraw::removeGameObject(): Error: GameObject '%1' not found.").arg(name);
    }
    return found;
}

int MyGLDraw::getScreenWidth()
{
    return _width;
}

void MyGLDraw::setScreenWidth(int width)
{
    _width = width;
}

int MyGLDraw::getScreenHeight()
{
    return _height;
}

void MyGLDraw::setScreenHeight(int height)
{
    _height = height;
}

void MyGLDraw::myGLRender()
{
    //Elapse 30 milliseconds
    updateGL();
}

QSize MyGLDraw::size() const
{
    return QSize(_width,_height);
}

QSize MyGLDraw::minimumSizeHint() const
{
    return QSize(_width,_height);
}

QSize MyGLDraw::sizeHint() const
{
    return minimumSizeHint();
}

void MyGLDraw::initializeGL()
{
    makeCurrent();
    //wglMakeCurrent();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Let OpenGL clear to black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glClearColor(0.63f, 0.32f, 0.18f, 0.0f);
    //we want smooth shading...
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    //Alpha blending (transparency)
    //Only draw pixels with alpha levels of .5 or
    //greater.
    //glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenTextures(1, &_quadTexture);

}

void MyGLDraw::resizeGL(int w, int h)
{
    makeCurrent();
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, (GLint)w, 0.0f, (GLint)h);
    glMatrixMode(GL_MODELVIEW);

}

void MyGLDraw::paintGL()
{
    makeCurrent();
    //GL painting code goes here
    glClear( GL_COLOR_BUFFER_BIT );
    //do this for 2D painting only!
    glDisable(GL_DEPTH_TEST);

    //Setup texture


//    glBegin(GL_QUADS);
//    glColor3f(1.0f, 1.0f, 1.0f);
//    float wPoint = (_width / 4.0f);
//    float hPoint = (_height / 4.0f);
//    glVertex2f(wPoint, hPoint);
//    glVertex2f(wPoint, hPoint*2.0f);
//    glVertex2f(wPoint*2.0f, hPoint*2.0f);
//    glVertex2f(wPoint*2.0f, hPoint);
//    glEnd();
//    qDebug() << "MyGLDraw::paintGL(): screenObjects.size = " <<
//                _screenObjects.size();
    for(int i = 0; i < _screenObjects.size(); ++i){
        GameObject* gObj = _screenObjects[i];
        Position pos = gObj->getPosition();
        Volume vol = gObj->getVolume();
        Appearance app = gObj->getAppearance();
        if( app.textured ){
            //Handle the texture stuff
            int texWidth = (app.texEndX - app.texStartX);
            int texHeight = (app.texEndY - app.texStartY);

            //First, ensure we make the regions of the image
            //transparent that should be.  Replace any part of
            //the texture that matches this color with transparency.
            QRgb alphaColor = qRgb(1.0f, 0.0f, 1.0f);
            QImage texAlpha = app.texture.createMaskFromColor(alphaColor);
            QImage textureOGL = QGLWidget::convertToGLFormat((const QImage&)texAlpha);
            glBindTexture(GL_TEXTURE_2D, _quadTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth,
                         texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         textureOGL.bits());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBegin(GL_QUADS);
            //2D, don't care about 3rd dimension for now.
            //glColor3f(1.0f, 1.0f, 1.0f);

            //Bottom left
            glTexCoord2f(app.texStartX, app.texStartY);
            glVertex2f(pos.x, pos.y);

            //Top left
            glTexCoord2f(app.texStartX, app.texEndY);
            glVertex2f(pos.x, pos.y+vol.height);

            //Top right
            glTexCoord2f(app.texEndX, app.texEndY);
            glVertex2f(pos.x+vol.width, pos.y+vol.height);

            //Bottom right
            glTexCoord2f(app.texEndX, app.texStartY);
            glVertex2f(pos.x+vol.width, pos.y);
            glEnd();
        }else{
            glBegin(GL_QUADS);
            glColor4f(app.r, app.g, app.b, app.alpha);
            glVertex2f(pos.x, pos.y);
            glVertex2f(pos.x, pos.y+vol.height);
            glVertex2f(pos.x+vol.width, pos.y+vol.height);
            glVertex2f(pos.x+vol.width, pos.y);
            glEnd();
        }
    }

    //Draw HUD elements here at some point.
}
