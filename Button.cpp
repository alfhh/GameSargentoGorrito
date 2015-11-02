//
//  Button.cpp
//  GameSargentoGorrito
//
//  Created by Francisco Canseco on 01/11/15.
//  Copyright (c) 2015 Francisco Canseco. All rights reserved.
//

#include "Button.h"
Button::Button(int x,int y, int w, int h, string s, int t):Object(x,y,w,h){
    title = s;
    target = t;
}
string Button::getTitle(){
    return title;
}
void Button::setTitle(string s){
    title = s;
}

int Button::getTarget(Object o){
    if (checkColision(o)){
        return target;
    }
    return -1;
}

void Button::draw(){
    int strW=Object::getWidth()*.8;
    
    glPushMatrix();
        glTranslated(Object::getPosX()+Object::getWidth()/2, Object::getPosY()+Object::getHeight()/2, 0);
        glPushMatrix();
            glRotatef(10, 1, -1, 0);
            glScalef(.972, 1.00-((Object::getWidth()/Object::getHeight())*.028), 1.00-((Object::getWidth()/Object::getHeight())*.028));
            glScaled(Object::getWidth(), Object::getHeight(), Object::getHeight());
            glColor3f(0, .3, .6);
            glutSolidCube(1);
            glColor3f(0, 0, 1);
            glutWireCube(1);
            glTranslatef(0, 0, 300);
        glPopMatrix();
        glPushMatrix();
            glLineWidth(3);
            glTranslated(-Object::getWidth()/2.4, -Object::getHeight()/3, 1);
            glScalef((1.0/80.0)*(Object::getWidth()/title.size()),(1.0/80.0)*Object::getHeight()*.5,0);
            //glScaled(Object::getWidth(), Object::getHeight(),0);
            glColor3f(0, 0, 0);
            for (int k=0;k<title.size(); k++)
                glutStrokeCharacter(GLUT_STROKE_ROMAN, title[k]);
        glPopMatrix();
    glPopMatrix();
}