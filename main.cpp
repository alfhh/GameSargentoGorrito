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
#include "imageloader.h" // Used to load textures
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

//-----------------------------------Bottones
vector <Button> arrButtons;
Object mouse(-2,-2,1,1);

// Buttons of room 0 = Menu
Button b(450,460,300,80,"Menu Principal",1);
Button b2(450, 320, 300, 80, "Opciones", 2);
Button b3(450, 180, 300, 80, "Cargar", 3);

// Buttons of room 1 = Game room
Button bEsc(450, 420, 300, 80, "Salir del juego", 0);
Button bEnc(450, 280, 300, 80, "La Enciclopedia", 9);

//-----------------------------------Bottones

//Termina Cosas Nuevas

// Timer
char tiempo[] = {'0',':','0','0','.','0'};
int sec = 0; // used for the timer

// Game info
int score = 0;

// Strings
string mainTitle="Sargento Gorrito";
string labelLife = "100%";
string labelScore = "Puntuacion = 123,456";
string labelPause = "En pausa";

// Textures
GLuint _textureId; //The id of the texture

// Player
int playerxcor;
int playerycor;
int playerSpeed = 10;

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

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void materialRuby(){
    //Asigna los apropiados materiales a las superficies
    GLfloat mat_ambient[] = {0.25, 0.20725, 0.20725, 1.0f}; //gris
    GLfloat mat_diffuse[] = {1, 0.829, 0.829, 1.0f};
    GLfloat mat_specular[] = {0.296648, 0.296648, 0.296648, 1.0f};
    GLfloat mat_shininess[]= {50.0f};
   // glEnable(GL)
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
}

void materialOriginal(){

    //Asigna los apropiados materiales a las superficies
    GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f}; //gris
    GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[]= {50.0f};
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

}

void init(void)
{
    corre=false;
    glClearColor(0,.47,0,1); // Background color
    arrButtons.push_back(b); // Button added to the array
    actualRoom = 0; // Default value 0 = mainMenu

    // Player initial values
    playerxcor = 540;
    playerycor = 320;

    glEnable(GL_DEPTH);

    ///*
    //Material stuff
//glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glShadeModel(GL_SMOOTH);
    //glEnable(GL_DEPTH_TEST); //para eliminar las caras ocultas
    //glEnable(GL_NORMALIZE); //normaliza el vector para ombrear apropiadamente
    // asigna la apropiada fuente de luz
    //GLfloat lightIntensity[] = {1.0f, 1.0f, 1.0f, 1.0f};
    //GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 0.0f};
    //glLightfv(GL_LIGHT0, GL_POSITION,light_position);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE,lightIntensity);
    //*/
}

// MAIN MENU
void room0() {
    // TODO REFACTOR THIS
    // TEXTURE RENDERING


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
    b.draw(); // Button1
    b2.draw(); // Button 2
    b3.draw(); // Button 3



}

// HEALTH MANUAL
void manual(){
    glClearColor(.99,.93,.75,1); // Background color
    glColor3f(1,1,1);

    glPushMatrix();
    glTranslatef(600, 400, 0);
    glutSolidCube(500);
    glPopMatrix();

    glFlush();
}

// Draw the player
void drawPlayer(){
    glColor3f(1, 0,0);
    //materialRuby();
    glRectf(0, 0, 60, 80);
    //materialOriginal();
}

// FIRST LEVEL
void room1() {
    glClearColor(1,1,1,1); // Background color
    score = 0; // Reset the score of the player
    //glDisable(GL_LIGHTING);
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
    glColor3f(0,0,1); // Color white
    glScaled(.3, .3, .3);
    for (int k=0;k<labelLife.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, labelLife[k]);
    glPopMatrix();

    glPopMatrix(); // -------------------------------------------------------- NAVBAR

    // ----------------------------- Player
    glPushMatrix();
    glTranslatef(playerxcor, playerycor, 0);
    drawPlayer();
    glPopMatrix();
    //------------------------------ Player

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
        bEsc.draw();
        bEnc.draw();
    }
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
        case 9:
            manual();
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
        if(actualRoom == 0){
                if (b.getTarget(mouse) > -1){
                val = b.getTarget(mouse);
                cout << "entro" << endl;
                break;
            } else if (b2.getTarget(mouse) > -1){
                val = b2.getTarget(mouse);
                cout << "entro" << endl;
                break;
            } else if (b3.getTarget(mouse) > -1){
                val = b3.getTarget(mouse);
                cout << "entro" << endl;
                break;
            }
        } else if(actualRoom == 1){
            if ((bEsc.getTarget(mouse) > -1) && onPause){
                val = bEsc.getTarget(mouse);
                cout << "entro" << endl;
                break;
            } else if ((bEnc.getTarget(mouse) > -1) && onPause){
                val = bEnc.getTarget(mouse);
                cout << "entro" << endl;
                break;
            }
        }
    }

    switch (val) {
        case -1:
            break;
        case 0:
            cout << "Go to room 0" << endl;
            timerRunning = false;
            onPause = false;
            actualRoom = 0;
            break;
        case 1:
            cout << "Go to room 1" << endl;
            actualRoom = 1;
            timerRunning = true;
            sec = 0;
            break;
        case 2:
            cout << "Go to room Opciones" << endl;
            break;
        case 3:
            cout << "Go to room Cargar" << endl;
            break;
        case 9:
            cout << "Go to room Enciclopedia";
            timerRunning = false;
            actualRoom = 9;
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
    x = (x * 1200) / glutGet(GLUT_WINDOW_WIDTH);
    x = 1200 - x;

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

void myKeyboard(unsigned char theKey, int x, int y)
{
    y = (y * 800) / glutGet(GLUT_WINDOW_HEIGHT);
    y = 800 - y;
    if(actualRoom == 0){ // Main menu
            switch (theKey) {
            case 27:
                exit(-1); //terminate the program
            default:
                break; // do nothing
        }
    } else if(actualRoom == 1){ // Game room
        switch (theKey) {
            case 'w':
            case 'W': // Movement upward
                if(playerycor < 650){
                    playerycor+= playerSpeed;
                }
                break;
            case 's':
            case 'S': // Movement downward
                if(playerycor > 0){
                    playerycor-= playerSpeed;
                }
                break;
            case 'a':
            case 'A': // Go left
                if(playerxcor > 0){
                    playerxcor-= playerSpeed;
                }
                break;
            case 'd':
            case 'D': // Go right
                if(playerxcor < 1140){
                    playerxcor+= playerSpeed;
                }
                break;
            case 27: // Pause game
                onPause = !onPause;
                timerRunning = !timerRunning;
                break;
            default:
                break; // do nothing
        }
    } else if(actualRoom == 9){ // Enciclopedia room
        switch (theKey) {
            case 27:
                actualRoom = 1;
                timerRunning = false;
                onPause = true;
                break;
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
