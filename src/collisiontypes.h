#ifndef COLLISIONTYPES_H
#define COLLISIONTYPES_H

#include "gameprimitives.h"

//Collision codes

#define     NOCOLLISION                     0x00
//collision occured on left or right sides of subjects
#define		COLLISIONAXIS_X					0x01
//collision occured on top or bottom sides of subjects
#define		COLLISIONAXIS_Y					0x02
//collision occured from unknown direction (neither object moving)
#define		COLLISIONAXIS_UNKNOWN			0x04
//collision restricts movement of object on given direction
#define		COLLISIONRESTRICTION_MIN		0x08
#define		COLLISIONRESTRICTION_MAX		0x10


typedef struct CollisionDesc{
    //The type of collision that occurred
    unsigned char code;
    //Position in space where collision occurred
    Position pos;
} CollisionDesc;

enum CollisionBehavior{
    STOP,     //Stops the object that collided with this one
    REFLECT,  //Reflects the velocity of the object
              //that collided with this one in
              //in the axis of collision
    TRIGGER,  //Triggers an event
    PASSIVE   //Does nothing
};


#endif // COLLISIONTYPES_H
