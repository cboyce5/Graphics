/*
 *  CSCI 441, Computer Graphics, Fall 2016
 *
 *  Project: Assignment 1
 *  File: main.cpp
 *
 *	Author: Cliff Boyce
 *
 *  Description:
 *      Hero Banner
 *
 */

#ifdef __APPLE__				// if compiling on Mac OS
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else							// if compiling on Linux or Windows OS
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif

// global variables to keep track of window width and height.
// set to initial values for convenience, but we need variables
// for later on in case the window gets resized.
int windowWidth = 700, windowHeight = 150;

// global variable to keep track of the window id
int windowId;

//
//  void changeSize(int w, int h)
//
//      We will register this function as GLUT's reshape callback.
//   When the window is resized, the OS will tell GLUT and GLUT will tell
//   us by calling this function - GLUT will give us the new window width
//   and height as 'w' and 'h,' respectively - so save those to our global vars.
//
void changeSize( int w, int h ) {
    //save the new window width / height that GLUT informs us about
    windowWidth = w;
    windowHeight = h;

    // update the projection matrix based on the window size
    // the GL_PROJECTION matrix governs properties of the view;
    // i.e. what gets seen - use an Orthographic projection that ranges
    // from [0, windowWidth] in X and [0, windowHeight] in Y. (0,0) is the lower left.
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, windowWidth, 0, windowHeight );
    
    // update the viewport as well - tell OpenGL we want to render the whole window
    glViewport( 0, 0, windowWidth, windowHeight );

    // just as good practice, switch back to GL_MODELVIEW mode; that's the matrix
    // that we want to be changing with glTranslatef(), glScalef(), etc., so
    // just in case we forget to explicitly set it later...
    glMatrixMode( GL_MODELVIEW );
}

//Draws the letter V consisting of 2 triangles
void drawLetterV() {
	
	glPushMatrix();
	glBegin( GL_TRIANGLES );
	
	//triangle 1
	glColor3f(0.07,0.65,0.08);
	glVertex2f( 0, 100 );
	glColor3f(0.88,0.88,0.61);
	glVertex2f( 50, 0 );
	glVertex2f( 50, 40 );
	
	//triangle 2
	glVertex2f( 50, 0 );
	glVertex2f( 50, 40 );
	glColor3f(0.07,0.65,0.08);
	glVertex2f( 100, 100 );
	
	glEnd();
	glPopMatrix();
}

//Draws the letter O using 3 different squares, all on top of each other
void drawLetterO() {
	
	glPushMatrix();
	glBegin(GL_QUADS);
	
	//square 1
	glColor3f(0.07,0.65,0.08);
	glVertex2f( 0, 0 );
	glColor3f(0.88,0.88,0.61);
	glVertex2f( 100, 0 );
	glColor3f(0.07,0.65,0.08);
	glVertex2f( 100, 100 );
	glColor3f(0.88,0.88,0.61);
	glVertex2f( 0, 100);
	
	//square 2
	glColor3f(0.266,0.25,0.450);
	glVertex2f( 10, 10 );
	glVertex2f( 90, 10 );
	glVertex2f( 90, 90 );
	glVertex2f( 10, 90);
	
	//square 3
	glColor3f(0.266,0.25,0.450);
	glVertex2f( 20, 20 );
	glColor3f(0.88,0.88,0.61);
	glVertex2f( 80, 20 );
	glColor3f(0.266,0.25,0.450);
	glVertex2f( 80, 80 );
	glColor3f(0.88,0.88,0.61);
	glVertex2f( 20, 80);
	
	glEnd();
	glPopMatrix();
}

//Draws the letter R using a rectangle and a couple triangles
void drawLetterR() {
	
	glPushMatrix();
	glBegin( GL_QUADS );
	
	//square
	glColor3f(0.88,0.88,0.61);
	glVertex2f( 0, 0 );
	glVertex2f( 0, 100 );
	glVertex2f( 10, 100 );
	glVertex2f( 10, 0 );
	glEnd();
	
	//triangle 1
	glBegin(GL_TRIANGLES);
	glVertex2f(10,100);
	glColor3f(0.266,0.25,0.450);
	glVertex2f(75,75);
	glColor3f(0.88,0.88,0.61);
	glVertex2f(10,50);
	
	//triangle 2
	glVertex2f(10,50);
	glColor3f(0.07,0.65,0.08);
	glVertex2f(75,0);
	glColor3f(0.88,0.88,0.61);
	glVertex2f(20,55);
	
	glEnd();
	glPopMatrix();
}

//Draws the letter A using one triagnle and one rectangle
void drawLetterA() {
	
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	
	//triangle
	glColor3f(0.88,0.88,0.61);
	glColor3f(0.07,0.65,0.08);
	glVertex2f(50,100);
	glColor3f(0.88,0.88,0.61);
	glVertex2f(25,60);
	glVertex2f(75,60);
	glEnd();
	
	//rectangle
	glBegin(GL_QUADS);
	glColor3f(0.266,0.25,0.450);
	glVertex2f(0,0);
	glColor3f(0.88,0.88,0.61);
	glVertex2f(25,60);
	glVertex2f(75,60);
	glColor3f(0.266,0.25,0.450);
	glVertex2f(100,0);
	
	glEnd();
	glPopMatrix();
}

//Draws the letter G using several triangles
void drawLetterG() {
	
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	
	//triangle 1
	glColor3f(0.88,0.88,0.61);
	glVertex2f(0,0);
	glColor3f(0.266,0.25,0.450);
	glVertex2f(0,50);
	glColor3f(0.88,0.88,0.61);
	glVertex2f(60,0);
	
	//triangle 2
	glColor3f(0.266,0.25,0.450);
	glVertex2f(0,50);
	glColor3f(0.88,0.88,0.61);
	glVertex2f(0,100);
	glVertex2f(60,100);
	
	//triangle 3
	glVertex2f(60,0);
	glVertex2f(100,40);
	glVertex2f(20,0);
	
	//triangle 4
	glVertex2f(100,40);
	glVertex2f(60,40);
	glVertex2f(80,20);
	
	//triangle 5
	glVertex2f(0,100);
	glVertex2f(0,80);
	glVertex2f(100,100);
	
	//triangle 6
	glColor3f(0.07,0.65,0.08);
	glVertex2f(100,80);
	glColor3f(0.88,0.88,0.61);
	glVertex2f(80,100);
	glVertex2f(100,100);
	
	glEnd();
	glPopMatrix();
	
}

//Draws the crest of my character Vorago using one rectangle and 4 triangles
void drawCrest() {
	
	glPushMatrix();
	glBegin(GL_QUADS);
	
	//rectangle
	glColor3f(0.88,0.88,0.61);
	glVertex2f(25,25);
	glColor3f(0.266,0.25,0.450);
	glVertex2f(25,75);
	glColor3f(0.88,0.88,0.61);
	glVertex2f(75,75);
	glColor3f(0.266,0.25,0.450);
	glVertex2f(75,25);
	glEnd();
	
	//triangle 1
	glBegin(GL_TRIANGLES);
	glColor3f(0.88,0.88,0.61);
	glVertex2f(25,25);
	glColor3f(0.266,0.25,0.450);
	glVertex2f(25,75);
	glColor3f(0.07,0.65,0.08);
	glVertex2f(0,0);
	
	//triangle 2
	glColor3f(0.88,0.88,0.61);
	glVertex2f(25,25);
	glColor3f(0.266,0.25,0.450);
	glVertex2f(75,25);
	glColor3f(0.07,0.65,0.08);
	glVertex2f(0,0);
	
	//triangle 3
	glColor3f(0.88,0.88,0.61);
	glVertex2f(75,75);
	glColor3f(0.266,0.25,0.450);
	glVertex2f(25,75);
	glColor3f(0.07,0.65,0.08);
	glVertex2f(100,100);
	
	//triangle 4
	glColor3f(0.88,0.88,0.61);
	glVertex2f(75,75);
	glColor3f(0.266,0.25,0.450);
	glVertex2f(75,25);
	glColor3f(0.07,0.65,0.08);
	glVertex2f(100,100);
	
	glEnd();
	glPopMatrix();
}

//
//  void renderScene()
//
//      We will register this function as GLUT's display callback.
//  This is where the magic happens - all rendering is done here.
//
void renderScene() {
    // clear whatever was drawn to the screen last time - 
    // set the clear color to black and then signal to clear the RGB buffer.
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

    // switch to GL_MODELVIEW, for when we start using glTranslatef(), glScalef(), etc..
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	//*******************************************//
	//***                                     ***//
	//***   YOUR CODE WILL GO HERE            ***//
	//***                                     ***//
	//*******************************************//
	
	//background color
	glColor3f(0.266,0.25,0.450);
	glBegin(GL_QUADS);
	glVertex2f( 0, 0 );
	glVertex2f( 0, 150 );
	glVertex2f( 700, 150 );
	glVertex2f( 700, 0 );
	glEnd();
	
	//V, translation and scaling
	glPushMatrix();
	glTranslatef(0,5,0);
	glScalef(0.9, 1.3, 1);
	drawLetterV();
	glPopMatrix();
	
	//First O, translation and scaling
	glPushMatrix();
	glTranslatef(95,5, 0);
	glScalef(0.9, 1.3, 1);
	drawLetterO();
	glPopMatrix();
	
	//R, translation and scaling
	glPushMatrix();
	glTranslatef(190,5,0);
	glScalef(0.9, 1.3, 1);
	drawLetterR();
	glPopMatrix();
	
	//A, translation and scaling
	glPushMatrix();
	glTranslatef(260,5,0);
	glScalef(0.9, 1.3, 1);
	drawLetterA();
	glPopMatrix();
	
	//G, translation and scaling
	glPushMatrix();
	glTranslatef(355,5,0);
	glScalef(0.9, 1.3, 1);
	drawLetterG();
	glPopMatrix();
	
	//Second O using rotation, translation and scaling
	glPushMatrix();
	glTranslatef(515,5,0);
	glScalef(0.9, 0.9, 1);
	glRotatef(45,0,0,1);
	drawLetterO();
	glPopMatrix();
	
	//crest using Rotation, translation and scaling
	glPushMatrix();
	glTranslatef(650,5,0);
	glScalef(0.9, 0.9, 1);
	glRotatef(45,0,0,1);
	drawCrest();
	glPopMatrix();

    // flush the OpenGL commands and make sure they get rendered!
    glFlush();
}

// you should know what main does...
int main( int argc, char *argv[] ) {
	
	// initialize GLUT... always need this call.
	glutInit( &argc, argv );
	
	// request a window with just an RGB frame buffer, nothing fancy...
	// place it at (50,50) on the screen and set its size to our constants from earlier
	glutInitDisplayMode( GLUT_RGB );
	glutInitWindowPosition( 50, 50 );
	glutInitWindowSize( windowWidth, windowHeight );
	
	// this actually creates our window giving it title "Lab 00B"
	windowId = glutCreateWindow( "Banner of Vorago" );
	
	// register our reshape and display callbacks with GLUT - these functions are above
	glutDisplayFunc( renderScene );
	glutReshapeFunc( changeSize );
	
	// begin GLUT loop
	glutMainLoop();
	
	return 0;
}
