//
//  Bullet.cpp
//  GMG
//
//  Created by Francisco Canseco on 15/11/15.
//  Copyright (c) 2015 Francisco Canseco. All rights reserved.
//

#include "Bullet.h"
Bullet::Bullet (int x, int y, int w , int h,double sX, double sY):Character(x,y,w,h,1,(int)(sX*5),(int)(sY*5),0,10){
    
}
void Bullet::move(){
    Character::move();
}
void Bullet::draw(){
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glPushMatrix();
    glTranslated(Object::getPosX()+Object::getWidth()/2, Object::getPosY()+Object::getHeight()/2, Object::getPosY()+Object::getHeight()/2);
    
    
    //circulo
    glPushMatrix();
    glScaled(Object::getWidth()*1, Object::getHeight()*1, Object::getHeight());
    glColor4f(0, 0, 0,0.5);
    glutSolidSphere(.5, 100, 100);
    glColor4f(.2, .2, .2,1);
    glutWireSphere(.5, 10, 10);
    glPopMatrix();

    glPopMatrix();
}