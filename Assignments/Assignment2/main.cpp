/*
 *  CSCI 441 / 598B Computer Graphics, Fall 2016
 *
 *  Project: a2
 *  File: main.cpp
 *
 *  Author: Cliff Boyce
 *
 *  Description:
 *		This program demonstrates event functionality as used in lab01, in conjunction with our hero.
 */

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else						// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

// include everything necessary to make our world map work
#include "WorldMap.h"


// global variables to keep track of window width and height.
// set to initial values for convenience, but we need variables
// for later on in case the window gets resized.
int windowWidth = 512, windowHeight = 512;
int x = 250;
int y = 250;
int staffAngle = 0;
int quadrant = 0;
bool gaze = false;


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

//changes the color of one ear depending on the quadrant of the cursor
void myMotion (int mouseX, int mouseY) {
	if (mouseX > 0 && mouseX < 255 && mouseY > 0 && mouseY < 255) {
		quadrant = 0;
	}
	else if (mouseX > 255 && mouseX < 511 && mouseY > 0 && mouseY < 255) {
		quadrant = 1;
	}
	else if (mouseX > 0 && mouseX < 255 && mouseY > 255 && mouseY < 511) {
		quadrant = 2;
	}
	else {
		quadrant = 3;
	}
}

//changes the color of the eyes depending on if mouse1 is pressed
void myMouse( int button, int state, int mouseX, int mouseY) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			gaze = true;
		}
		else {
			gaze = false;
		}
	}
}

//moves the character using the numpad number 2,4,6,8, also allows ESC for quitting
void myKeyboard( unsigned char key, int mouseX, int mouseY) {
	switch(key) {
		case 50:
			if (y < 0) {
				moveDown();
				y = 511;
			}
			y -= 3;
			break;
		case 52:
			if (x < 0) {
				x = 511;
				moveLeft();
			}
			x -= 3;
			break;
		case 54:
			if (x > 511) {
				x = 0;
				moveRight();
			}
			x += 3;
			break;
		case 56:
			if (y > 511)  {
				y = 0;
				moveUp();
			}
			y += 3;
			break;
		case 27:
			exit(0);
			break;
	}
}

//passively rotates the staff/cane thing
void myTimer(int value) {
	staffAngle += 5;
	glutPostRedisplay();
	glutTimerFunc( 50, myTimer, 0);
}


//The following functions draw the specific body parts of my hero
void drawEyes() {
	glPushMatrix();
	if (gaze) {
		glColor3f(0,0,0);
	}
	else {
		glColor3f(1,1,1);
	}
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(10,0);
		glVertex2f(10,10);
		glVertex2f(0,10);
	glEnd();
	glPopMatrix();
}

void drawMouth() {
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		glVertex2f(0,0);
		glVertex2f(30,0);
		glVertex2f(15,15);
	glEnd();
	glPopMatrix();
}

void drawNose() {
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		glVertex2f(0,0);
		glVertex2f(16,0);
		glVertex2f(8,8);
	glEnd();
	glPopMatrix();
}

void drawHead() {
	
	//drawing the head outline, including some extra shapes to give detail
	glColor3f(0.88,0.88,0.61);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		//base head
		glVertex2f(0,100);
		glVertex2f(100,100);
		glVertex2f(50,-20);
		
		//ear thing 1
		glColor3f(0.78,0.78,0.51);
		glVertex2f(20,100);
		glVertex2f(40,100);
		switch(quadrant) {
			case 0:
				glColor3f(0,1,0);
				break;
			case 1:
				glColor3f(1,0,0);
				break;
			default:
				break;
		}
		glVertex2f(30,115);
		
		//ear thing 2
		glColor3f(0.78,0.78,0.51);
		glVertex2f(80,100);
		glVertex2f(60,100);
		switch (quadrant) {
			case 2:
				glColor3f(0,0,1);
				break;
			case 3:
				glColor3f(0,0,0);
				break;
			default:
				break;
		}
		glVertex2f(70,115);
	glEnd();
	glPopMatrix();
	
	//drawing the left eye
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(30,70,0);
	drawEyes();
	glPopMatrix();
	
	//drawing the right eye
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(60,70,0);
	drawEyes();
	glPopMatrix();
	
	//drawing the mouth
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(35,25,0);
	drawMouth();
	glPopMatrix();
	
	//drawing the nose
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(42,45,0);
	drawNose();
	glPopMatrix();
}

void drawCape() {
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	
		//triangle 1
		glVertex2f(0,50);
		glVertex2f(100,100);
		glVertex2f(100,0);
		
		//2
		glVertex2f(100,0);
		glVertex2f(100,100);
		glVertex2f(200,50);
		
		//3
		glVertex2f(0,50);
		glVertex2f(100,0);
		glVertex2f(50,-35);
		
		//4
		glVertex2f(200,50);
		glVertex2f(100,00);
		glVertex2f(150,-35);
	glEnd();
	glPopMatrix();
}

void drawStaff() {
	glPushMatrix();
	glColor3f(0.68,0.68,0.41);
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(0,-100);
		glVertex2f(10,-100);
		glVertex2f(10,0);
	glEnd();
	glPopMatrix();
}

void drawLeg1() {
	glPushMatrix();
	glColor3f(0.58,0.58,0.31);
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(20,100);
		glVertex2f(30,100);
		glVertex2f(10,0);
	glEnd();
	glPopMatrix();
}

void drawLeg2() {
	glPushMatrix();
	glColor3f(0.58,0.58,0.31);
	glBegin(GL_QUADS);
		glVertex2f(0,100);
		glVertex2f(10,100);
		glVertex2f(20,0);
		glVertex2f(10,0);
	glEnd();
	glPopMatrix();
}

void drawTorso() {
	glPushMatrix();
	glColor3f(0.83,0.83,0.58);
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(100,0);
		glVertex2f(80,100);
		glVertex2f(20,100);
	glEnd();
	glPopMatrix();
}

void drawArm() {
	glPushMatrix();
	glColor3f(0.83,0.83,0.58);
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(100,0);
		glVertex2f(100,10);
		glVertex2f(0,10);
	glEnd();
	glPopMatrix();
}


void drawBody() {
	
	//drawing the torso of the hero
	glPushMatrix();
	glColor3f(0.78,0.78,0.51);
	drawCape();
	glPopMatrix();
	
	//drawing the legs
	glPushMatrix();
	glTranslatef(50,-50,0);
	drawLeg1();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(120,-50,0);
	drawLeg2();
	glPopMatrix();
	
	//draw the torso
	glPushMatrix();
	glTranslatef(50,-20,0);
	drawTorso();
	glPopMatrix();
	
	//drawing the arms
	glPushMatrix();
	glTranslatef(0,45,0);
	drawArm();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(100,45,0);
	drawArm();
	glPopMatrix();
	
	//drawing the staff
	glPushMatrix();
	glTranslatef(200,50,0);
	glRotatef(staffAngle,0,0,1);
	drawStaff();
	glPopMatrix();
	
	
}

//calling the following function in turns calls all others and draws the hero
void drawHero() {
	
	//draw the torso first
	glPushMatrix();
	glTranslatef(-50,-50,0);
	drawBody();
	glPopMatrix();
	
	
	//then draw the head
	glPushMatrix();
	drawHead();
	glPopMatrix();
	
}

//
//  void renderScene()
//
//      We will register this function as GLUT's display callback.
//  This is where the magic happens - all rendering is done here.
//
void renderScene() {
	// ensure we are drawing to the back buffer
	glDrawBuffer( GL_BACK );

    // clear whatever was drawn to the screen last time - 
    // set the clear color to black and then signal to clear the RGB buffer.
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

    // switch to GL_MODELVIEW, for when we start using glTranslatef(), glScalef(), etc..
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // draw our World Map to the screen.  this MUST be your first drawing call
    drawMap( windowWidth, windowHeight );	// DO NOT REMOVE THIS LINE

    //////////////////////////////////////////////////////////
    /////			Add Your Drawing Here				 /////
    //////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef( x, y, 0 );
	drawHero();
	glPopMatrix(); // we pushed the matrix earlier, pop it to prevent overflows
	
    // flush the OpenGL commands and make sure they get rendered!
    glutSwapBuffers();
}

//
//  int main( int argc, char* argv[] )
//
int main( int argc, char* argv[] ) {
    // initialize GLUT... always need this call.
    glutInit( &argc, argv );

    // request a window with just an RGB frame buffer, nothing fancy...
    // place it at (50,50) on the screen and set its size to our constants from earlier
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( windowWidth, windowHeight );
    
    // this actually creates our window. 
    // bet you thought the title was going to be a zelda reference, eh? #sworcery
    glutCreateWindow( "A2" );

    // register our reshape and display callbacks with GLUT - these functions are above
    glutDisplayFunc( renderScene );
    glutReshapeFunc( changeSize );
	
	//callbacks that are required for assignment functionality
	glutKeyboardFunc( myKeyboard );
	glutTimerFunc( 5, myTimer, 0);
	glutMouseFunc( myMouse );
	glutPassiveMotionFunc(myMotion);

    // initialize our map
	initMap();

    // begin GLUT loop
    glutMainLoop();

    return 0;
}
