#ifndef COLLISION_H
#define COLLISION_H

#include "gameprimitives.h"

typedef struct BoundingBox2D{
    float startX;
    float startY;
    float endX;
    float endY;
    BoundingBox2D(Position pos, Volume vol){
        startX = pos.x;
        startY = pos.y;
        endX = startX + vol.width;
        endY = startY + vol.height;
    }
    BoundingBox2D(){
        startX = 0.0f;
        startY = 0.0f;
        endX = 0.0f;
        endY = 0.0f;
    }
    bool intersectsX(const BoundingBox2D& other){
        if( startX >= other.endX || endX <= other.startX ){
            return false;
        }else{
            return true;
        }
    }
    bool intersectsY(const BoundingBox2D& other){
        if( startY >= other.endY || endY <= other.startY ){
            return false;
        }else{
            return true;
        }
    }
    bool intersects(const BoundingBox2D& other){
        return (intersectsX(other) || intersectsY(other));
    }

} BoundingBox2D;


#endif // COLLISION_H
