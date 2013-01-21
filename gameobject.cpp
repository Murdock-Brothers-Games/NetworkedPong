#include "gameobject.h"
#include <QDebug>
#include <QFile> //For loading texture image

GameObject::GameObject(QString name, Position pos, QObject *parent):
    QObject(parent)
{
}

GameObject::~GameObject()
{
}

QString GameObject::getName()
{
    return _myName;
}

void GameObject::setName(QString name)
{
    _myName = name;
}

Volume GameObject::getVolume()
{
    return _myVolume;
}

void GameObject::setVolume(Volume vol)
{
    _myVolume = vol;
}

BoundingBox2D GameObject::getHitBox()
{
    return _myHitBox;
}

void GameObject::setHitBox(BoundingBox2D hBox)
{
    _myHitBox = hBox;
}

CollisionBehavior GameObject::getHitAction()
{
    return _myHitAction;
}

void GameObject::setHitAction(CollisionBehavior act)
{
    _myHitAction = act;
}

Position GameObject::getPosition()
{
    return _curPosition;
}

void GameObject::setPosition(Position pos)
{
    _curPosition = pos;
    //Don't let hitbox get out of sync
    //with position
    _myHitBox.startX = _curPosition.x;
    _myHitBox.startY = _curPosition.y;
}

Velocity GameObject::getVelocity()
{
    return _curVelocity;
}

void GameObject::setVelocity(Velocity vel)
{
    _curVelocity = vel;
}

Acceleration GameObject::getAcceleration()
{
    return _curAcceleration;
}

void GameObject::setAcceleration(Acceleration acc)
{
    _curAcceleration = acc;
}

Appearance GameObject::getAppearance()
{
    return _myAppearance;
}

void GameObject::setAppearance(Appearance app)
{
    _myAppearance = app;
}

QList<Force> GameObject::getForces()
{
    return _forces;
}

void GameObject::clearForces()
{
    _forces.clear();
}

int GameObject::findForce(QString name)
{
    int thePosition = -1;
    bool found = false;
     int index;
    for(index = 0; index < _forces.size(); ++index){
        if( _forces[index].name == name ){
            found = true;
            break;
        }
    }

    if( found ){
        //Note: If the _forces list ever exceeds
        //      the maximum possible signed 32 bit
        //      integer amount, this will fail.
        thePosition = (int)index;
    }else{
        qDebug() <<
          QString("GameObject::findForce(): Error: force '%1' not found. (GameObject '%2').").arg(
                   name).arg(_myName);
    }
    return thePosition;
}

bool GameObject::hasForce(QString name)
{
    bool found = false;
     int index;
    for(index = 0; index < _forces.size(); ++index){
        if( _forces[index].name == name ){
            found = true;
            break;
        }
    }
    return found;
}

Force GameObject::getForce(QString name)
{
    Force retForce;
    int index = findForce(name);
    bool found = (index != -1);

    if( found ){
        retForce = _forces[index];
    }else{
        qDebug() <<
          QString("GameObject::getForce(): Error: force '%1' not found. (GameObject '%2').").arg(
                   name).arg(_myName);
    }
    return retForce;
}

void GameObject::addForce(Force theForce)
{
    _forces.append(theForce);
}

void GameObject::removeForce(QString name)
{

    int index = findForce(name);
    bool found = (index != -1);

    if( found ){
        _forces.removeAt(index);
    }else{
        qDebug() <<
          QString("GameObject::removeForce(): Error: force '%1' not found. (GameObject '%2').").arg(
                   name).arg(_myName);
    }
}

void GameObject::modifyForce(QString name, Acceleration acc, float lifespan)
{
    int index = findForce(name);
    bool found = (index != -1);

    if( found ){
        _forces[index].acc = acc;
        _forces[index].lifespan = (lifespan == -1 ?
                                       _forces[index].lifespan :
                                       lifespan );
    }else{
        qDebug() <<
          QString("GameObject::modifyForce(): Error: force '%1' not found. (GameObject '%2').").arg(
                   name).arg(_myName);
    }
}

bool GameObject::isCollidable()
{
    return _collidable;
}

void GameObject::setCollidable(bool collidable)
{
    _collidable = collidable;
}

bool GameObject::isSolid()
{
    return _solid;
}

void GameObject::setSolid(bool solid)
{
    _solid = solid;
}

bool GameObject::isMobile()
{
    return _mobile;
}

void GameObject::setMobile(bool mobile)
{
    _mobile = mobile;
}

bool GameObject::isInteractive()
{
    return _interactive;
}

void GameObject::setInteractive(bool interactive)
{
    _interactive = interactive;
}

bool GameObject::isPlayable()
{
    return _playable;
}

void GameObject::setPlayable(bool playable)
{
    _playable = playable;
}

void GameObject::update(float dt)
{
    updateMovement(dt);
}

void GameObject::loadTexture(QString filename)
{
    //Create the QImage from the filename.
    QFile theFile(filename);
    if( !theFile.exists()){
        qDebug() <<
          QString("GameObject::loadTexture(): Error: texture file '%1' not found. (GameObject '%2').").arg(
                   filename).arg(_myName);
        return;
    }
    //Texture should be loaded in now.
    _myAppearance.texture.load(filename);
}

void GameObject::updateMovement(float dt)
{
    //Update position
    //_newPosition.x = _curPosition.x + (_curVelocity.x*dt);
    _curPosition.x = _curPosition.x + (_curVelocity.x*dt);
    //_newPosition.y = _curPosition.y + (_curVelocity.y*dt);
    _curPosition.y = _curPosition.y + (_curVelocity.y*dt);
    //_newPosition.z = _curPosition.z + (_curVelocity.z*dt);
    _curPosition.z = _curPosition.z + (_curVelocity.z*dt);
    //Don't let hitbox get out of sync
    //with position
    //_myHitBox.startX = _newPosition.x;
    _myHitBox.startX = _curPosition.x;
    //_myHitBox.startY = _newPosition.y;
    _myHitBox.startY = _curPosition.y;

    //Update velocity
    //_newVelocity.x = _curVelocity.x + (_curAcceleration.x*dt);
    _curVelocity.x = _curVelocity.x + (_curAcceleration.x*dt);
    //_newVelocity.y = _curVelocity.y + (_curAcceleration.y*dt);
    _curVelocity.y = _curVelocity.y + (_curAcceleration.y*dt);
    //_newVelocity.z = _curVelocity.z + (_curAcceleration.z*dt);
    _curVelocity.z = _curVelocity.z + (_curAcceleration.z*dt);
}

//void GameObject::commitMoveUpdate()
//{
//    _curPosition = _newPosition;
//    _curVelocity = _newVelocity;
//}

void GameObject::updateForces(float dt)
{
    for(int i = 0; i < _forces.size(); ++i){
        if( _forces[i].active ){
            if( _forces[i].lifespan > 0.0f){
                _forces[i].lifespan -= dt;
            }else{
                _forces[i].active = false;
            }
        }
    }
}

