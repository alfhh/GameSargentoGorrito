//
//  Object.cpp
//  GameSargentoGorrito
//
//  Created by Francisco Canseco on 01/11/15.
//  Copyright (c) 2015 Francisco Canseco. All rights reserved.
//

#include "Object.h"
Object::Object(int x,int y, int w, int h){
    posX = x;
    posY = y;
    width = w;
    height = h;
}

int Object::getPosX(){
    return posX;
}

int Object::getPosY(){
    return posY;
}

int Object::getWidth(){
    return width;
}

int Object::getHeight(){
    return height;
}

void Object::setPosX(int x){
    posX = x;
}

void Object::setPosY(int y){
    posY = y;
}

void Object::setWidth(int w){
    width = w;
}

void Object::setHeight(int h){
    height = h;
}

bool Object::checkColision(Object o){
    if (o.getPosX()+o.getWidth()>posX||posX+width>o.getPosX()){
        if (o.getPosY()+o.getHeight()>posY||posY+o.getHeight()>o.getPosY()){
            return true;
        }
    }
    return false;
}