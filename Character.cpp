//
//  Character.cpp
//  GMG
//
//  Created by Francisco Canseco on 15/11/15.
//  Copyright (c) 2015 Francisco Canseco. All rights reserved.
//

#include "Character.h"
Character::Character (int x, int y, int w , int h, int he,int sX, int sY,int p, int d):Object(x,y,w,h){
    health=he;
    speedX=sX;
    speedY=sY;
    points=p;
    damage=d;
}
int Character::getHealth(){
    return health;
}
void Character::changeHealth(int h){
    health+=h;
}
int Character::getSpeedX(){
    return speedX;
}
void Character::setSpeedX(int sX){
    speedX=sX;
}
int Character::getSpeedY(){
    return speedY;
}
void Character::setSpeedY(int sY){
    speedY=sY;
}
int Character::getPoints(){
    return points;
}
int Character::getDamage(){
    return damage;
}
void Character::move(){
    Object::setPosX(Object::getPosX()+speedX);
    Object::setPosY(Object::getPosY()+speedY);
}