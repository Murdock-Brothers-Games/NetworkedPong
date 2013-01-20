#include "mygldraw.h"

MyGLDraw::MyGLDraw(QWidget* parent):
QGLWidget(parent)
{
    srand(time(NULL));
    resizeGL(480,480);
    _width = 480;
    _height = 480;

    //30 millisecond timer
    //_timer.setInterval(30);
    _timer = new QTimer(this);
    _simulationTime = new QTime();
    _simulationTime->start();
    connect(_timer, SIGNAL(timeout()), this, SLOT(myUpdate()));
    _timer->start(15);

}

MyGLDraw::~MyGLDraw()
{
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
    GLuint quadTexture;
    glGenTextures(1, &quadTexture);

    for(int i = 0; i < _screenObjects.size(); ++i){
        GameObject* gObj = _screenObjects[i];
        Position pos = gObj->getPosition();
        Volume vol = gObj->getVolume();
        Appearance app = gObj->getAppearance();
        //Handle the texture stuff
        int texWidth = (app.texEndX - app.texStartX);
        int texHeight = (app.texEndY - app.texStartY);

        //First, ensure we make the regions of the image
        //transparent that should be.  Replace any part of
        //the texture that matches this color with transparency.
        QRgb alphaColor = qRgb(1.0f, 0.0f, 1.0f);
        QImage texAlpha = app.texture.createMaskFromColor(alphaColor);
        QImage textureOGL = QGLWidget::convertToGLFormat((const QImage&)texAlpha);
        glBindTexture(GL_TEXTURE_2D, quadTexture);
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
    }
    glDeleteTextures(1, &quadTexture);

    //Draw HUD elements here at some point.
}

QSize MyGLDraw::size() const
{
    return QSize(480,480);
}

QSize MyGLDraw::minimumSizeHint() const
{
    return QSize(480,480);
}

QSize MyGLDraw::sizeHint() const
{
    return minimumSizeHint();
}

void MyGLDraw::myUpdate()
{
    //Elapse 30 milliseconds
    updateGL();
}
