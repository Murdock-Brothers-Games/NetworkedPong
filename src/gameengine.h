#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QElapsedTimer>
#include <QTimer>

#include "gamestate.h"

class GameEngine : public QWidget
{
    Q_OBJECT
public:
    GameEngine(GameState* game, QWidget *parent = 0);

    ~GameEngine();



    void handleInput();

    void update(float dt);
    
signals:
    
public slots:

    void slotRun();

    void slotExit();

private:

    void setupUi();

    void makeConnections();


    QTimer* _loopControl;
    QElapsedTimer _timer;
    qint64 _interval_usec;
    int _interval_msec;

    QVBoxLayout* _mainLayout;

    GameState* _gamestate;

    bool _exit;
    
};

#endif // GAMEENGINE_H
