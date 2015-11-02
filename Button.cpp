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