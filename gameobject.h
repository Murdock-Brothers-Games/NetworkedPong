#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QString>
#include <QList>

#include "gameprimitives.h"
#include "collisiontypes.h"
#include "collision.h"

class GameObject : public QObject
{
    Q_OBJECT
public:

    GameObject(QString name, Position pos, QObject *parent = 0);

    virtual ~GameObject();

    QString getName();

    void setName(QString name);

    Volume getVolume();

    void setVolume(Volume vol);

    BoundingBox2D getHitBox();

    void setHitBox(BoundingBox2D hBox);

    Position getPosition();

    void setPosition(Position pos);

    Velocity getVelocity();

    void setVelocity(Velocity vel);

    Acceleration getAcceleration();

    void setAcceleration(Acceleration acc);

    Appearance getAppearance();

    void setAppearance(Appearance app);

    QList<Force> getForces();
	
	void clearForces();

	int findForce(QString name);
	
    bool hasForce(QString name);

    Force getForce(QString name);

    void addForce(Force theForce);

    void removeForce(QString name);

    void modifyForce(QString name, Acceleration acc, float lifespan=-1.0f);

    bool isCollidable();

    void setCollidable(bool collidable);

    bool isSolid();

    void setSolid(bool solid);

    bool isMobile();

    void setMobile(bool mobile);

    bool isInteractive();

    void setInteractive(bool interactive);

    void loadTexture(QString filename);

    
signals:
    
public slots:

    virtual void update(float dt) = 0;

private:

    void updateMovement(float dt);

    void updateForces(float dt);

    virtual void onCollision(CollisionDesc colType, GameObject* other) = 0;

    virtual void interact(GameObject* other) = 0;

    QString _myName;

    Volume _myVolume;

    BoundingBox2D _myHitBox;

    Position _curPosition;

    Position _newPosition;

    Velocity _curVelocity;

    Velocity _newVelocity;

    Acceleration _curAcceleration;

    Acceleration _newAcceleration;

    Appearance _myAppearance;


    QList<Force> _forces;

    bool _collidable;

    bool _solid;

    bool _mobile;

    bool _interactive;

};

#endif // GAMEOBJECT_H
