#include "mygldraw.h"

MyGLDraw::MyGLDraw(QWidget* parent):
QGLWidget(parent)
{
    srand(time(NULL));
    resizeGL(480,480);
    _width = 480;
    _height = 480;
    buildColorMap();

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
    glDeleteTextures(1, &_fireTexture);
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
    _particles->update(30);
    updateGL();
}
