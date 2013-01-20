#ifndef COLLISIONTYPES_H
#define COLLISIONTYPES_H

#include "gameprimitives.h"

//Collision codes

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


#endif // COLLISIONTYPES_H
