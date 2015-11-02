//
//  main.cpp
//  BlackJack
//
//  Created by Francisco Canseco on 18/09/15.
//  Created by Alfredo Hinojosa
//  Copyright (c) 2015 Ma. Guadalupe Roque. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include "Deck.h"
#include "Hand.h"
#include "Card.h"

using namespace std;
Deck *mazo;
Hand *dealer;
Hand *player;
int pointsDealer=0;
string mensaje="Deal?";
string s1="Dealer:";
string s2="Player:";
string s3="D-Deal H-Hit S-Stand Esc-Salir";
string s4="Autor: Francisco Canseco Dominguez Matricula: A01034948";
string sA="Autor: Alfredo Hinojosa Huerta Matricula: A01036053";
string s5="Points Dealer = ";
string s6="Points Player = ";
string s7="Score Dealer = ";
string s8="Score Player = ";
bool corre=false;
int pointsPlayer=0;
int sP = 0; // Score del player
int sD = 0; // Score del dealer

// VARIANBLES DE CARTAS FRANK
int rotacionCartas = 0;
int rotacionTotal = 0;

// ANGULO PARA ROTACION FONDO
int angulo = 0;
bool girando = false;

GLsizei winWidth =1200, winHeight =800;

GLubyte Club[] = {0x00,0x00,0x00,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x03,0x80,0x00,
    0x01,0xF3,0x9F,0x00,
    0x03,0xF9,0x3F,0x80,
    0x07,0xFD,0x7F,0xC0,
    0x0F,0xFE,0xFF,0xE0,
    0x0F,0xFE,0xFF,0xE0,
    0x0F,0xFE,0xFF,0xE0,
    0x0F,0xFE,0xFF,0xE0,
    0x0F,0xFE,0xFF,0xE0,
    0x0F,0xFE,0xFF,0xE0,
    0x07,0xFD,0x7F,0xC0,
    0x03,0xFB,0xBF,0x80,
    0x01,0xF0,0x1F,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x1F,0xF0,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x1F,0xF0,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,};
GLubyte Spade[] = {0x00,0x00,0x00,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x03,0x80,0x00,
    0x01,0xF1,0x1F,0x00,
    0x07,0xF9,0x3F,0xC0,
    0x07,0xFC,0x7F,0xC0,
    0x0F,0xFF,0xFF,0xE0,
    0x0F,0xFF,0xFF,0xE0,
    0x0F,0xFF,0xFF,0xE0,
    0x0F,0xFF,0xFF,0xE0,
    0x0F,0xFF,0xFF,0xE0,
    0x0F,0xFF,0xFF,0xE0,
    0x0F,0xFF,0xFF,0xE0,
    0x07,0xFF,0xFF,0xC0,
    0x07,0xFF,0xFF,0xC0,
    0x07,0xFF,0xFF,0xC0,
    0x03,0xFF,0xFF,0x80,
    0x03,0xFF,0xFF,0x80,
    0x03,0xFF,0xFF,0x80,
    0x01,0xFF,0xFF,0x00,
    0x01,0xFF,0xFF,0x00,
    0x00,0xFF,0xFE,0x00,
    0x00,0x7F,0xFC,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x1F,0xF0,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x03,0x80,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,};
GLubyte Heart[] = {0x00,0x00,0x00,0x00,
    0x00,0x03,0x80,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x1F,0xF0,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x7F,0xFC,0x00,
    0x00,0xFF,0xFE,0x00,
    0x01,0xFF,0xFF,0x00,
    0x03,0xFF,0xFF,0x80,
    0x07,0xFF,0xFF,0xC0,
    0x07,0xFF,0xFF,0xC0,
    0x0F,0xFF,0xFF,0xE0,
    0x0F,0xFF,0xFF,0xE0,
    0x1F,0xFF,0xFF,0xF0,
    0x1F,0xFF,0xFF,0xF0,
    0x3F,0xFF,0xFF,0xF8,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x3F,0xFE,0xFF,0xF8,
    0x3F,0xFE,0xFF,0xF8,
    0x1F,0xFC,0x7F,0xF0,
    0x01,0x37,0xFF,0xFF,
    0x00,0x00,0x00,0x00,};
GLubyte Diamonds[] = {0x00,0x00,0x00,0x00,
    0x00,0x01,0x00,0x00,
    0x00,0x03,0x80,0x00,
    0x00,0x03,0x80,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x1F,0xF0,0x00,
    0x00,0x1F,0xF0,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x7F,0xFC,0x00,
    0x00,0x7F,0xFC,0x00,
    0x00,0xFF,0xFE,0x00,
    0x00,0xFF,0xFE,0x00,
    0x00,0xFF,0xFE,0x00,
    0x00,0xFF,0xFE,0x00,
    0x00,0x7F,0xFC,0x00,
    0x00,0x7F,0xFC,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x1F,0xF0,0x00,
    0x00,0x1F,0xF0,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x03,0x80,0x00,
    0x00,0x03,0x80,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,};

void timer(int value){


    if(girando && angulo <= 360){
        angulo = rotacionCartas;
    } else {
        angulo = 0;
        girando = false;
    }

    if (rotacionTotal>0){
       rotacionCartas+=10;
        rotacionTotal-=10;
    }
    else{
        rotacionCartas=0;
    }
    glutPostRedisplay();
    glutTimerFunc(10, timer, 1);
}


void deal(){
    mazo = new Deck();
    mazo->shuffle();
    dealer = new Hand();
    player = new Hand();
    dealer->addCard(mazo->dealCard());
    player->addCard(mazo->dealCard());
    dealer->addCard(mazo->dealCard());
    player->addCard(mazo->dealCard());
    printf("Dealer: %s\n",dealer->str());
    printf("Player: %s\n",player->str());
    printf("D: %d P: %d\n",dealer->getValue(),player->getValue());
    if (corre){
        printf("You lose. New game. Hit or Stand\n");
        sD++;
        mensaje ="You lose. New game. Hit or Stand";
    }
    else{
        printf("Hit or Stand\n");
        mensaje ="Hit or Stand";
    }
    corre=true;
    glutPostRedisplay();
}
void hit(){
    if (player->getValue()>21||!corre){
        printf("Deal?\n");
        mensaje ="New Deal";
    }
    else{
        mensaje ="Hit or Stand";
        player->addCard(mazo->dealCard());
        printf("Dealer: %s\n",dealer->str());
        printf("Player: %s\n",player->str());
        printf("D: %d P: %d\n",dealer->getValue(),player->getValue());
        if (player->getValue()>21){
            printf("You went over 21. You lose!\n");
            corre = false;
            sD++;
            mensaje ="You went over 21. You lose!";
        }
    }
    glutPostRedisplay();
}
void stand(){
    if (!corre){
        printf("New Deal?\n");
        mensaje ="New Deal?";
    }
    else{

    if (player->getValue()>21){
        printf("You've already lost. Deal?\n");
        sD++;
        mensaje ="You've already lost. Deal?";
    }
    else{
        while (dealer->getValue()<17){
            dealer->addCard(mazo->dealCard());
        }
        if (dealer->getValue()>21){
            printf("Dealer went over 21. You win!\n");
            sP++;
            mensaje ="Dealer went over 21. You win!";
        }
        else{
            if (player->getValue()>dealer->getValue()){
                printf("You got more points. You Win!\n");
                sP++;
                mensaje ="You got more points. You Win!";
            }
            else{
                printf("House wins\n");
                sD++;
                mensaje ="House Wins";
            }
        }
        printf("Dealer: %s\n",dealer->str());
        printf("Player: %s\n",player->str());
        printf("D: %d P: %d\n",dealer->getValue(),player->getValue());
    }
    }
    corre = false;
    glutPostRedisplay();
}

void init(void)
{
    dealer = new Hand();
    player = new Hand();
    corre=false;
    glClearColor(0,.47,0,1); // Color de la ventada, el fondo naranja

}

// Este metodo pinta el numero de una carta que este volteada
void actSize(){
    winWidth =glutGet(GLUT_WINDOW_WIDTH), winHeight =glutGet(GLUT_WINDOW_HEIGHT);
}

// Este metodo dibuja todas las cartas y se encarga de colorealas dependiendo del caso
void dibujaBaraja(){
    //Dibuja Cartas Dealer
    glMatrixMode(GL_MODELVIEW);
    float x =winWidth/20.0;
    glLineWidth(2);
    for (int i = 0 ; i < dealer->getSize(); i++){
        glColor4f(1, 1, 1, 1);
        glPushMatrix();
        glTranslatef(x+(winWidth/18), (5.5*winHeight/7) - winHeight/10, -100);
        glRotatef(10, 1, -1, 0);
        glRotatef(rotacionCartas, 0, 1, 0);
        glScalef(winWidth/10.0, ((4.0*winHeight/7.0)+winHeight/100.0)-((5.5*winHeight/7.0) - winHeight/100.0 ), winWidth/10.0);
        glutSolidCube(1);
        if (dealer->getSuit(i)=='C'||dealer->getSuit(i)=='S'){
            glColor4f(0, 0, 0, 0);

        }
        else{
            glColor4f(1, 0, 0, 1);
        }
        glLineWidth(2);
        glutWireCube(1);
        //glRectf(x, (5.5*winHeight/7.0) - winHeight/100.0 , x+winWidth/10.0, (4.0*winHeight/7.0)+winHeight/100.0);
        glPopMatrix();
        if (dealer->getSuit(i)=='C'||dealer->getSuit(i)=='S'){
            glColor4f(0, 0, 0, 0);
            if (dealer->getSuit(i)=='C'){
                glRasterPos2d(x+(winWidth/20.0)-16, (4.75*winHeight/7.0) -16);
                glBitmap(32, 32, 0,0, 10, 0, Club);
                glFlush();
            }
            else{
                glRasterPos2d(x+(winWidth/20.0)-16, (4.75*winHeight/7.0) -16);
                glBitmap(32, 32, 0,0, 10, 0, Spade);
                glFlush();
            }
        }
        else{
            glColor4f(1, 0, 0, 1);
            if (dealer->getSuit(i)=='H'){
                glRasterPos2d(x+(winWidth/20.0)-16, (4.75*winHeight/7.0) -16);
                glBitmap(32, 32, 0,0, 10, 0, Heart);
                glFlush();
            }
            else{
                glRasterPos2d(x+(winWidth/20.0)-16, (4.75*winHeight/7.0) -16);
                glBitmap(32, 32, 0,0, 10, 0, Diamonds);
                glFlush();
            }
        }

        glPushMatrix();
        glLineWidth(5.5);
        glTranslatef(x+(winWidth/200.0), (5.5*winHeight/7.0) - winHeight/22.5 - 3,1);
        glScaled(0.27, 0.27, 0.25);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, dealer->getValue(i));
        glPopMatrix();

        glPushMatrix();
        glLineWidth(5.5);
        glTranslatef(x+ winWidth/12.8, (4.0*winHeight/7.0)+winHeight/55,1);
        glScaled(0.27, 0.27, 0.25);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, dealer->getValue(i));
        glPopMatrix();

        x+=(winWidth/40.0) + (winWidth/10.0);
    }

    //Dibuja Cartas Player

    x =winWidth/20.0;
    for (int i = 0 ; i < player->getSize(); i++){
        glColor4f(1, 1, 1, 1);
        glPushMatrix();
        glTranslatef(x+(winWidth/18), (3.5*winHeight/7) - winHeight/10, -100);
        glRotatef(10, 1, -1, 0);
        glRotatef(rotacionCartas, 0, 1, 0);
        glScalef(winWidth/10.0, ((4.0*winHeight/7.0)+winHeight/100.0)-((5.5*winHeight/7.0) - winHeight/100.0 ), winWidth/10.0);
        glutSolidCube(1);
        if (dealer->getSuit(i)=='C'||dealer->getSuit(i)=='S'){
            glColor4f(0, 0, 0, 0);

        }
        else{
            glColor4f(1, 0, 0, 1);
        }
        glLineWidth(2);
        glutWireCube(1);
        //glRectf(x, (3.5*winHeight/7.0) - winHeight/100.0 , x+winWidth/10.0, (2.0*winHeight/7.0)+winHeight/100.0);
        glPopMatrix();
        if (player->getSuit(i)=='C'||player->getSuit(i)=='S'){
            glColor4f(0, 0, 0, 0);
            if (player->getSuit(i)=='C'){
                glRasterPos2d(x+(winWidth/20.0)-16, (2.75*winHeight/7.0) -16);
                glBitmap(32, 32, 0,0, 10, 0, Club);
                glFlush();
            }
            else{
                glRasterPos2d(x+(winWidth/20.0)-16, (2.75*winHeight/7.0) -16);
                glBitmap(32, 32, 0,0, 10, 0, Spade);
                glFlush();
            }
        }
        else{
            glColor4f(1, 0, 0, 1);
            if (player->getSuit(i)=='H'){
                glRasterPos2d(x+(winWidth/20.0)-16, (2.75*winHeight/7.0) -16);
                glBitmap(32, 32, 0,0, 10, 0, Heart);
                glFlush();
            }
            else{
                glRasterPos2d(x+(winWidth/20.0)-16, (2.75*winHeight/7.0) -16);
                glBitmap(32, 32, 0,0, 10, 0, Diamonds);
                glFlush();
            }
        }
        glPushMatrix();
        glLineWidth(5.5);
        glTranslatef(x+(winWidth/200.0), (3.5*winHeight/7.0) - winHeight/22.5 - 3,1);
        glScaled(0.27, 0.27, 0.25);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, player->getValue(i));
        glPopMatrix();

        glPushMatrix();
        glLineWidth(5.5);
        glTranslatef(x+ (winWidth/12.95), (2.0*winHeight/7.0)+winHeight/55,1);
        glScaled(0.27, 0.27, 0.25);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, player->getValue(i));
        glPopMatrix();

        x+=winWidth/40.0 + winWidth/10.0;
    }
}

void dibudaTetera(){
    if (mensaje=="Deal?"){
        return;
    }
    if (mensaje=="Hit or Stand"||mensaje=="You lose. New game. Hit or Stand"){
        glPushMatrix();
        glTranslatef(winWidth/1.5, 2.4*winWidth/4, -300);
        glRotatef(rotacionCartas, 0, 1, 0);
        glScalef(winWidth/2, winWidth/4, winWidth/2);
        glColor4f(1, 0, 0, 1);
        glutSolidTeapot(.4);
        glPopMatrix();
    }
    else{
        glPushMatrix();
        glTranslatef(winWidth/3, 2.4*winWidth/4, -300);
        glRotatef(rotacionCartas, 0, 1, 0);
        glScalef(winWidth/2, winWidth/4, winWidth/2);
        glColor4f(0, 0, 1, 1);
        glutSolidTeapot(.4);
        glPopMatrix();
    }
}

void display(){
    //actSize();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Dibuja el cuadro del fondo
    glPushMatrix();
    glColor3f(0.82, 0.62, 0.39); // Color cafe
    glTranslatef(550,  400, 0);
    glRotatef(angulo + 20, 0.0, 0.0, 1.0);
    glutSolidCube(800);
    glPopMatrix();

    dibudaTetera();
    dibujaBaraja();

    /* CARTA QUE TAPA LA PRIMERA DEL DEALER
    if(corre){
        glColor4f(1, 0, 0, 1);
        float x =winWidth/20.0;
        glRectf(x, (5.5*winHeight/7.0) - winHeight/100.0 , x+winWidth/10.0, (4.0*winHeight/7.0)+winHeight/100.0);
    }
    */

    glLineWidth(1.0);
    glColor3f(1,1,1);

    //--------------- Despliega Mensaje
    glPushMatrix();
    glTranslatef(winWidth/(mensaje.size()), 8.0*winHeight/9.0, 1);
    glScaled(0.6-(mensaje.size()*.005), 0.6-(mensaje.size()*.005), 0.6);

    for (int k=0;k<mensaje.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, mensaje[k]);
    glPopMatrix();

    //--------------- Despliega Nombre D
    glLineWidth(3.5);
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(winWidth/20.0, 5.5*winHeight/7.0, 1);
    glScaled(0.5, 0.5, 0.5);
    for (int k=0;k<s1.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s1[k]);
    glPopMatrix();
    glColor3f(0,0,1);
    //--------------- Despliega Nombre P

    glPushMatrix();
    glTranslatef(winWidth/20.0, 3.5*winHeight/7.0, 1);
    glScaled(0.5, 0.5, 0.5);
    for (int k=0;k<s2.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s2[k]);
    glPopMatrix();
    glColor3f(1,1,1);
    //--------------- Despliega Instrucciones
    glLineWidth(1.0);
    glPushMatrix();
    glTranslatef(winWidth/20.0, winHeight/6.0, 1);
    glScaled(0.5, 0.5, 0.5);
    for (int k=0;k<s3.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s3[k]);
    glPopMatrix();
    //--------------- Despliega Nombre Autor

    glPushMatrix();
    glTranslatef(winWidth/40.0, winHeight/10, 1);
    glScaled(0.3, 0.3, 0.3);
    for (int k=0;k<s4.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s4[k]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(winWidth/40.0, winHeight/30, 1);
    glScaled(0.3, 0.3, 0.3);
    for (int k=0;k<sA.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, sA[k]);
    glPopMatrix();

    //Formato de score
    std::stringstream sstm;
    string aux="";
    sstm << dealer->getValue();
    sstm >> aux;
    s5 = "Points Dealer = " + aux;
    std::stringstream sstm2;
    sstm2 << player->getValue();
    sstm2 >> aux;
    s6 = "Points Player = " + aux;
    std::stringstream sstm3;
    sstm3 << sD;
    sstm3 >> aux;
    s7 = "Score Dealer = " + aux;
    std::stringstream sstm4;
    sstm4 << sP;
    sstm4 >> aux;
    s8 = "Score Player = " + aux;

    //--------------- Despliega Puntos D

    if(!corre){
        glPushMatrix();
        glTranslatef(winWidth/1.7, 5.5*winHeight/7.0, 1);
        glScaled(0.3, 0.3, 0.3);
        for (int k=0;k<s5.size(); k++)
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s5[k]);
        glPopMatrix();
    }

    //--------------- Despliega Score D

    glPushMatrix();
    glTranslatef(winWidth/1.7, 4.6*winHeight/7.0, 1);
    glScaled(0.3, 0.3, 0.3);
    for (int k=0;k<s7.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s7[k]);
    glPopMatrix();


    //--------------- Despliega Puntos P

    if(!corre){
        glPushMatrix();
        glTranslatef(winWidth/1.7, 3.5*winHeight/7.0, 1);
        glScaled(0.3, 0.3, 0.3);
        for (int k=0;k<s6.size(); k++)
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s6[k]);
        glPopMatrix();
    }

    //--------------- Despliega Score P

    glPushMatrix();
    glTranslatef(winWidth/1.7, 4.1*winHeight/7.0, 1);
    glScaled(0.3, 0.3, 0.3);
    for (int k=0;k<s8.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s8[k]);
    glPopMatrix();

      glutSwapBuffers();
}


void reshape (int w, int h)
{   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION); // Tipo de proyecion
    glLoadIdentity ();
    glOrtho(0, 1200, 0, 800, -600  , 600);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{    switch (theKey)
    {
        case 'd':
        case 'D':
            rotacionTotal = 360;
            girando = true;
            deal();
            break;
        case 'h':
        case 'H':
            rotacionTotal = 360;
            girando = true;
            hit();
            break;
        case 's':
        case 'S':
            rotacionTotal = 360;
            girando = true;
            stand();
            break;
        case 27:
            exit(-1); //terminate the program
        default:
            break; // do nothing
    }
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(winWidth, winHeight); // Ajusta el ancho y alto de la ventana
    glutInitWindowPosition(200,0); // Posicion en la que aparece la ventana en la pantalla
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH ); // Doble buffer para animacion
    glutCreateWindow("Blackjack");
    init(); // Inicializa todas las variables
    glutDisplayFunc(display);
    glutTimerFunc(5, timer, 1);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    glutPostRedisplay();
    return EXIT_SUCCESS;
}

