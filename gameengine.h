#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "mygldraw.h"

class GameEngine : public QWidget
{
    Q_OBJECT
public:
    GameEngine(QWidget *parent = 0);

    ~GameEngine();

    void run();

    void handleInput();

    void update(float dt);

    void keyPressEvent(QKeyEvent *k);

    void keyReleaseEvent(QKeyEvent *k);
    
signals:
    
public slots:

    void slotExit();

private:

    void setupUi();


    QVBoxLayout* _mainLayout;

    MyGLDraw* _screen;

    bool _exit;
    bool p1PaddleUp, p1PaddleDown, p2PaddleUp, p2PaddleDown;
    
};

#endif // GAMEENGINE_H
