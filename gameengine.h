#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QWidget>
#include <QVBoxLayout>

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
    
signals:
    
public slots:

    void slotExit();

private:

    void setupUi();


    QVBoxLayout* _mainLayout;

    MyGLDraw* _screen;

    bool _exit;
    
};

#endif // GAMEENGINE_H
