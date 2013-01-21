#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QWidget>
#include <QVBoxLayout>

#include "gamestate.h"

class GameEngine : public QWidget
{
    Q_OBJECT
public:
    GameEngine(GameState* game, QWidget *parent = 0);

    ~GameEngine();

    void run();

    void handleInput();

    void update(float dt);
    
signals:
    
public slots:

    void slotExit();

private:

    void setupUi();

    void makeConnections();


    QVBoxLayout* _mainLayout;

    GameState* _gamestate;

    bool _exit;
    
};

#endif // GAMEENGINE_H
