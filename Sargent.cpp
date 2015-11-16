//
//  Sargent.cpp
//  GMG
//
//  Created by Francisco Canseco on 15/11/15.
//  Copyright (c) 2015 Francisco Canseco. All rights reserved.
//

#include "Sargent.h"
#include "Math.h"
#include "cmath"
#define M_PI    3.1415926535897932384626433832795028841971693

Sargent::Sargent (int x, int y, int w , int h, int he,int sX, int sY,int p, int d):Character(x,y,w,h,he,sX,sY,p,d){
}
void Sargent::move(){
    Character::move();
}
double Sargent::getAimX(){
    return aimX;
}
double Sargent::getAimY(){
    return aimY;
}
void Sargent::draw(int mouseX,int mouseY){
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glPushMatrix();
    glTranslated(Object::getPosX()+Object::getWidth()/2, Object::getPosY()+Object::getHeight()/2, Object::getPosY()+Object::getHeight()/2);
    int deg=(int) (atan2(Object::getPosY()-mouseY, Object::getPosX()-mouseX)*(180/M_PI)+90);
    deg%=360;
    glRotatef(deg, 0, 0, 1);
    deg=360-deg;
    aimX=sin(deg*M_PI/180.0);
    aimY=cos(deg*M_PI/180.0);
    glPushMatrix();

    //circulo
    glPushMatrix();
    glScaled(Object::getWidth()*1, Object::getHeight()*1, Object::getHeight());
    glColor4f(1, 1, 1,0.0);
    glutSolidSphere(.5, 100, 100);
    glColor4f(.9, .9, .9,1);
    glutWireSphere(.5, 10, 10);
    glPopMatrix();

    glTranslated(Object::getWidth()*.25,Object::getHeight()*.5,Object::getHeight()*.25);
    glPushMatrix();
    glScaled(Object::getWidth()*.4, Object::getHeight()*.1, Object::getHeight()*.25);
    glColor4f(.1, .1, .1,0.0);
    glutSolidCube(1);
    glPopMatrix();

    glTranslated(-Object::getWidth()*.5,0,0);
    glPushMatrix();
    glScaled(Object::getWidth()*.4, Object::getHeight()*.1, Object::getHeight()*.25);
    glColor4f(.1, .1, .1,0.0);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}
