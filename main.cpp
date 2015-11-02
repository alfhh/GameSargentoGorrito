//
//  main.cpp
//  Sargento Gorrito
//  Developed by Francisco Canseco and Alfredo Hinojosa

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

#include "Button.h"
#include "Object.h"
using namespace std;

// Bitmaps
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

//Cosas Nuevas
vector <Button> arrButtons;
Object mouse(-2,-2,1,1);
Button b(450,460,300,80,"Menu Principal",1);
//Termina Cosas Nuevas

// Timer
char tiempo[] = {'0',':','0','0','.','0'};
int sec = 0; // used for the timer

// Player info
int score = 0;

// Strings
string mainTitle="Sargento Gorrito";
string labelLife = "100%";
string labelScore = "Puntuacion = 123,456";
string labelPause = "En pausa";

// Rooms
int actualRoom;

// Flags
bool timerRunning = false;
bool onPause = false; // If true paints pause screen

// Previous stuff
bool corre=false;
int pointsPlayer=0;
int sP = 0; // Score del player
int sD = 0; // Score del dealer
int rotacionCartas = 0;
int rotacionTotal = 0;
int angulo = 0;
bool girando = false;

void formato(int i){
    tiempo[0]=(sec/600)+'0';
    tiempo[2]=((sec%600)/100)+'0';
    tiempo[3]=((sec%100)/10)+'0';
    tiempo[5]=(sec%10)+'0';
}

void myTimer(int i) {
    if (timerRunning){
        sec+=1;
    }

    glutTimerFunc(100,myTimer,i);
    formato(sec);
    glutPostRedisplay();

}

void init(void)
{
    corre=false;
    glClearColor(0,.47,0,1); // Background color
    arrButtons.push_back(b); // Button added to the array
    actualRoom = 1; // Default value 0 = mainMenu
    //glEnable(GL_DEPTH_TEST);
}

// Display buttons
void paintButton(int posX, int posY){

    glPushMatrix(); // Draws the border of the button
    glTranslatef(450 + posX, 400 + posY, 0);
    glColor3f(0,0,0);
    glRectf(0,0,300,80);
    glPushMatrix(); // Draws the inner part of the button
    glColor3f(1,1,1);
    glTranslatef(15, 4, 0);
    glScalef(.9, .9, 1);
    glRectf(0,0,300,80);
    glPopMatrix();
    glPopMatrix();
}

// MAIN MENU
void room0() {
    glClearColor(0,.47,0,1); // Background color
    glColor3f(1,1,1);

    //--------------- Display mainTitle string
    glPushMatrix();
    glTranslatef(1200/(mainTitle.size()), 8.0*800/9.0, 1);
    glScaled(0.6-(mainTitle.size()*.005), 0.6-(mainTitle.size()*.005), 0.6);
    for (int k=0;k<mainTitle.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, mainTitle[k]);
    glPopMatrix();

    //--------------- Display buttons
    // Paint button 1
    paintButton(0, 60);
    b.draw();
    // Paint button 2
    paintButton(0, -60);

    // Paint button 3
    paintButton(0, -180);

}

// FIRST LEVEL
void room1() {
    glClearColor(1,1,1,1); // Background color

    score = 0; // Reset the score of the player

    // Navbar
    glColor3f(0,0,0);
    glRectf(0, 730, 1200, 800); // Draws the black navbar
    glColor3f(1,0,0); // Color red
    glRasterPos2d(20, 750); // Position of the heart
    glBitmap(32, 32, 0,0, 10, 0, Heart); // Draws the heart

    glPushMatrix(); // --------------------Matrix used to have all inside the navbar
    glTranslatef(60, 750, 0);

    glPushMatrix(); // Displays the timer
    glTranslatef(1000, 0, 0);
    glColor3f(1,1,1); // Color white
    glScaled(.3, .3, .3);
    for (int k=0;k<6; k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, tiempo[k]);
    glPopMatrix();

    glPushMatrix(); // Displays the score
    glTranslatef(350, 0, 0);
    glColor3f(1,1,1); // Color white
    glScaled(.3, .3, .3);
    for (int k=0;k<labelScore.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, labelScore[k]);
    glPopMatrix();

    glPushMatrix(); // Diplay percentage of the player's life
    glColor3f(1,1,1); // Color white
    glScaled(.3, .3, .3);
    for (int k=0;k<labelLife.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, labelLife[k]);
    glPopMatrix();

    glPopMatrix(); // -------------------------------------------------------- NAVBAR

    if(onPause) { // Display the pause window

        glColor3f(.92, .92, .92); // Color gray
        glPushMatrix();
        glTranslatef(600, 400, 0);
        glutSolidCube(500); // Background of the panel

        glPushMatrix(); // Pause label
        glTranslatef(-90, 180, 0);
        glColor3f(0,0,0); // Color black
        glScaled(.3, .3, .3);
        for (int k=0;k<labelPause.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, labelPause[k]);
        glPopMatrix();

        glPopMatrix();
    }

    glFlush();

}

void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLineWidth(1.0);

    switch (actualRoom) {
        case 0: // Paints the main menu
            room0();
            break;
        case 1: // Paints the first level
            room1();
            break;
        default:
            break;
    }

    glutSwapBuffers();
}


void reshape (int w, int h)
{   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION); // Projection type
    glLoadIdentity ();

    // The coordiantes of the game
    // X goes from 0 to 1200
    // Y goes from 0 to 800
    // Near and far from -600 to 600
    glOrtho(0, 1200, 0, 800, -600  , 600);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);

}

void checkButtons(){
    int val=-1;
    for(Button b : arrButtons){
        if (b.getTarget(mouse) > -1){
            val = b.getTarget(mouse);
            cout << "entro" << endl;
            break;
        }
    }
    switch (val) {
        case -1:
            break;
        case 1:
            cout << "WORKED" << endl;
            break;
        default:
            break;
    }
}

void myMouse(int button, int state, int x, int y)
{
    // Fix of y
    y = (y * 800) / glutGet(GLUT_WINDOW_HEIGHT);
    y = 800 - y;

    if (state == GLUT_DOWN){

    }
    else
        if (state == GLUT_UP) // Check if button is clicked
        {
            mouse.setPosX(x);
            mouse.setPosY(y);
            cout << "The position of the mouse X: " << mouse.getPosX() <<" and Y: " << mouse.getPosY() << endl;
            //cout << "The position of the button X: " << arrButtons[0].getPosX() <<" and Y: " << arrButtons[0].getPosY() << endl;
            checkButtons();
        }
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    if(actualRoom == 0){
            switch (theKey) {
            case 'j':
                actualRoom = 1;
                break;
            case 'k':
                actualRoom = 0;
                break;
            case 'd':
            case 'D':
                rotacionTotal = 360;
                girando = true;
                break;
            case 'h':
            case 'H':
                rotacionTotal = 360;
                girando = true;
                break;
            case 's':
            case 'S':
                rotacionTotal = 360;
                girando = true;
                break;
            case 27:
                exit(-1); //terminate the program
            default:
                break; // do nothing
        }
    } else if(actualRoom == 1){
        switch (theKey) {
            case 's':
            case 'S':
                timerRunning = true; // Start the timer
                break;
            case 'p':
            case 'P':
                onPause = !onPause;
                timerRunning = !timerRunning;
                break;
            case 'j':
                actualRoom = 1;
                break;
            case 'k':
                actualRoom = 0;
                break;
            case 27:
                exit(-1); //terminate the program
            default:
                break; // do nothing
        }
    }
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 800); // Size of the window, using globals
    glutInitWindowPosition(200,0); // Starting point of the screen
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH ); // Doble buffer for animations
    glutCreateWindow("Sargento Gorrito: El juego");
    init(); // Initialize all the game variables
    glutDisplayFunc(display);
    glutTimerFunc(0, myTimer, 0);
    glutReshapeFunc(reshape);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    glutPostRedisplay();
    return EXIT_SUCCESS;
}
