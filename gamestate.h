#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QWidget>
#include <QList>
#include <QKeyEvent>
#include <QVBoxLayout>

#include "gameobject.h"
#include "gameprimitives.h"
#include "mygldraw.h"

class GameState : public QWidget
{
    Q_OBJECT
public:
    GameState(int screenWidth, int screenHeight,
              QWidget *parent = 0);

    GameState(QWidget *parent = 0);

    virtual ~GameState();

    QString getName();

    void setName(QString name);

    bool hasBackdrop();

    void setBackdrop(bool flag);

    QImage getBackdropImage();

    void setBackdropImage(QImage backdrop);

    void loadBackdrop(QString filename);

    int getScreenWidth();

    void setScreenWidth(int width);

    int getScreenHeight();

    void setScreenHeight(int height);

    virtual void addPlayer(GameObject* player);

    virtual void addNonPlayer(GameObject* npc);

    virtual void addScenery(GameObject* sceneItem);

    virtual QList<GameObject*> getVisibleObjects();

    virtual void buildAssets() = 0;

    virtual void update(float dt) = 0;

    virtual void renderState();

    
signals:
    
public slots:

protected:

    QString _name;

    bool _hasBackdrop;

    QImage _backdrop;

    int _screenWidth;

    int _screenHeight;

    MyGLDraw* _screen;

    QList<GameObject*> _players;

    QList<GameObject*> _nonPlayers;

    QList<GameObject*> _scenery;


private:

    virtual void setupUi();

    //GUI components
    QVBoxLayout* _mainLayout;

    
};

#endif // GAMESTATE_H
