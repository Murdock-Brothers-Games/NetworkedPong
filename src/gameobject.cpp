#include "gameobject.h"
#include <QDebug>
#include <QFile> //For loading texture image

GameObject::GameObject(QString name, Position pos, QObject *parent):
    QObject(parent),
    _myName(name)
{
}

GameObject::~GameObject()
{
//    if(_myAppearance.texture != NULL){
//        delete [] _myAppearance.texture;
//        _myAppearance.texture = NULL;
//    }
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
    //Don't let hitbox get out of sync
    //with volume
    _myHitBox.endX = _myHitBox.startX + vol.width;
    _myHitBox.endY = _myHitBox.startY + vol.height;
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
    //First, determine what offset (if any)
    //exists between the position and the hitbox
    float hBoxOffX = _myHitBox.startX - _curPosition.x;
    float hBoxWidth = _myHitBox.endX - _myHitBox.startX;
    float hBoxOffY = _myHitBox.startY - _curPosition.y;
    float hBoxHeight = _myHitBox.endY - _myHitBox.startY;
    _curPosition = pos;
    //Don't let hitbox get out of sync
    //with position
    _myHitBox.startX = _curPosition.x + hBoxOffX;
    _myHitBox.startY = _curPosition.y + hBoxOffY;
    //_myHitBox.endX = _curPosition.x + _myVolume.width;
    _myHitBox.endX = _myHitBox.startX + hBoxWidth;
    //_myHitBox.endY = _curPosition.y + _myVolume.height;
    _myHitBox.endY = _myHitBox.startY + hBoxHeight;
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
    //qDebug() << "GameObject::updateMovement...";
    //this->print();
    //Update position
    //_newPosition.x = _curPosition.x + (_curVelocity.x*dt);
    _curPosition.x = _curPosition.x + (_curVelocity.x*dt);
    //_newPosition.y = _curPosition.y + (_curVelocity.y*dt);
    _curPosition.y = _curPosition.y + (_curVelocity.y*dt);
    //_newPosition.z = _curPosition.z + (_curVelocity.z*dt);
    _curPosition.z = _curPosition.z + (_curVelocity.z*dt);
    //Don't let hitbox get out of sync
    //with position
    float hBoxWidth = _myHitBox.endX - _myHitBox.startX;
    float hBoxHeight = _myHitBox.endY - _myHitBox.startY;
    //_myHitBox.startX = _curPosition.x;
    _myHitBox.startX = _myHitBox.startX + (_curVelocity.x*dt);
    //_myHitBox.startY = _curPosition.y;
    _myHitBox.startY = _myHitBox.startY + (_curVelocity.y*dt);
    //_myHitBox.endX = _myHitBox.startX + _myVolume.width;
    _myHitBox.endX = _myHitBox.startX + hBoxWidth;
    //_myHitBox.endY = _myHitBox.startY + _myVolume.height;
    _myHitBox.endY = _myHitBox.startY + hBoxHeight;

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

void GameObject::print()
{
    qDebug() << QString("GameObject::print(): Printing GameObject...");
    qDebug() << QString("GameObject::print(): Name = %1").arg(_myName);
    qDebug() << QString("GameObject::print(): Position = %1").arg(_curPosition.getPrint());
    qDebug() << QString("GameObject::print(): Volume = %1").arg(_myVolume.getPrint());
    qDebug() << QString("GameObject::print(): HitBox = %1").arg(_myHitBox.getPrint());
    qDebug() << QString("GameObject::print(): Velocity = %1").arg(_curVelocity.getPrint());
    qDebug() << QString("GameObject::print(): Acceleration = %1").arg(_curAcceleration.getPrint());
    qDebug() << QString("GameObject::print(): Appearance = %1").arg(_myAppearance.getPrint());
    qDebug() << QString("GameObject::print(): collidable? = %1").arg(_collidable);
    qDebug() << QString("GameObject::print(): solid? = %1").arg(_solid);
    qDebug() << QString("GameObject::print(): mobile? = %1").arg(_mobile);
    qDebug() << QString("GameObject::print(): interactive? = %1").arg(_interactive);
    qDebug() << QString("GameObject::print(): playable? = %1").arg(_playable);
    qDebug() << "";
}

