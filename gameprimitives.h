#ifndef GAMEPRIMITIVES_H
#define GAMEPRIMITIVES_H

#include <QImage>
#include <QString>

typedef struct Volume{
    float width;
    float height;
    float depth; //Maybe?
    bool threeD; //Maybe?
    Volume(float theWidth, float theHeight, float theDepth, bool isThreeD=false){
        width = theWidth;
        height = theHeight;
        depth = theDepth;
        threeD = isThreeD;
    };
    Volume(){
        width = 0.0f;
        height = 0.0f;
        depth = 0.0f;
        threeD = false;
    };
} Volume;

typedef struct Position{
    float x;
    float y;
    float z;     //Maybe?
    Position(float theX, float theY, float theZ){
        x = theX;
        y = theY;
        z = theZ;
    };
    Position(){
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    };
    bool operator==(const Position& other){
        return (x == other.x &&
                y == other.y &&
                z == other.z);
    };
    bool operator!=(const Position& other){
        return !(*this == other);
    };
    Position operator+(const Position& other){
        Position ret;
        ret.x = x + other.x;
        ret.y = y + other.y;
        ret.z = z + other.z;
        return ret;
    };
    Position& operator+=(const Position& other){
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    };
    Position operator-(const Position& other){
        Position ret;
        ret.x = x - other.x;
        ret.y = y - other.y;
        ret.z = z - other.z;
        return ret;
    };
    Position& operator-=(const Position& other){
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    };
    Position operator*(const Position& other){
        Position ret;
        ret.x = x * other.x;
        ret.y = y * other.y;
        ret.z = z * other.z;
        return ret;
    };
    Position& operator*=(const Position& other){
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    };
    Position operator/(const Position& other){
        Position ret;
        ret.x = x / other.x;
        ret.y = y / other.y;
        ret.z = z / other.z;
        return ret;
    };
    Position& operator/=(const Position& other){
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    };
} Position;

typedef struct Velocity{
   float x;
   float y;
   float z;
   Velocity(float theX, float theY, float theZ){
       x = theX;
       y = theY;
       z = theZ;
   };
   Velocity(){
       x = 0.0f;
       y = 0.0f;
       z = 0.0f;
   };
   bool operator==(const Velocity& other){
       return (x == other.x &&
               y == other.y &&
               z == other.z);
   };
   bool operator!=(const Velocity& other){
       return !(*this == other);
   };
   Velocity operator+(const Velocity& other){
       Velocity ret;
       ret.x = x + other.x;
       ret.y = y + other.y;
       ret.z = z + other.z;
       return ret;
   };
   Velocity& operator+=(const Velocity& other){
       x += other.x;
       y += other.y;
       z += other.z;
       return *this;
   };
   Velocity operator-(const Velocity& other){
       Velocity ret;
       ret.x = x - other.x;
       ret.y = y - other.y;
       ret.z = z - other.z;
       return ret;
   };
   Velocity& operator-=(const Velocity& other){
       x -= other.x;
       y -= other.y;
       z -= other.z;
       return *this;
   };
   Velocity operator*(const Velocity& other){
       Velocity ret;
       ret.x = x * other.x;
       ret.y = y * other.y;
       ret.z = z * other.z;
       return ret;
   };
   Velocity& operator*=(const Velocity& other){
       x *= other.x;
       y *= other.y;
       z *= other.z;
       return *this;
   };
   Velocity operator/(const Velocity& other){
       Velocity ret;
       ret.x = x / other.x;
       ret.y = y / other.y;
       ret.z = z / other.z;
       return ret;
   };
   Velocity& operator/=(const Velocity& other){
       x /= other.x;
       y /= other.y;
       z /= other.z;
       return *this;
   };
} Velocity;

typedef struct Acceleration{
    float x;
    float y;
    float z;
    Acceleration(float theX, float theY, float theZ){
        x = theX;
        y = theY;
        z = theZ;
    };
    Acceleration(){
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    };
    bool operator==(const Acceleration& other){
        return (x == other.x &&
                y == other.y &&
                z == other.z);
    };
    bool operator!=(const Acceleration& other){
        return !(*this == other);
    };
    Acceleration operator+(const Acceleration& other){
        Acceleration ret;
        ret.x = x + other.x;
        ret.y = y + other.y;
        ret.z = z + other.z;
        return ret;
    };
    Acceleration& operator+=(const Acceleration& other){
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    };
    Acceleration operator-(const Acceleration& other){
        Acceleration ret;
        ret.x = x - other.x;
        ret.y = y - other.y;
        ret.z = z - other.z;
        return ret;
    };
    Acceleration& operator-=(const Acceleration& other){
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    };
    Acceleration operator*(const Acceleration& other){
        Acceleration ret;
        ret.x = x * other.x;
        ret.y = y * other.y;
        ret.z = z * other.z;
        return ret;
    };
    Acceleration& operator*=(const Acceleration& other){
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    };
    Acceleration operator/(const Acceleration& other){
        Acceleration ret;
        ret.x = x / other.x;
        ret.y = y / other.y;
        ret.z = z / other.z;
        return ret;
    };
    Acceleration& operator/=(const Acceleration& other){
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    };
} Acceleration;

typedef struct Force{
    QString name;
    Acceleration acc;
    float lifespan;
    bool active;
    Force(){
        name = QString("");
        lifespan = 0.0f;
        active = false;
    };
} Force;

typedef struct Appearance{
    bool visible;
    //Color
    float r;
    float g;
    float b;
    float alpha;
    //Texture
    bool textured;   //Maybe
    QImage texture;  //Maybe
    int texStartX; //Maybe
    int texStartY; //Maybe
    int texEndX;
    int texEndY;
    //int texWidth;   //Maybe
    //int texHeight;   //Maybe
    Appearance(){
      visible = false;
      r = 0.0f;
      g = 0.0f;
      b = 0.0f;
      alpha = 0.0f;
      textured = false;
      texStartX = 0;
      texStartY = 0;
      texEndX = 0;
      texEndY = 0;
      //texWidth = 0;
      //texHeight = 0;
    };
} Appearance;

#endif // GAMEPRIMITIVES_H
