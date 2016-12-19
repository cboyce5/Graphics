/*
 *  CSCI 441, Computer Graphics, Fall 2016
 *
 *  Project: lab00b
 *  File: main.cpp
 *
 *	Author: Dr. Jeffrey Paone - Fall 2016
 *
 *  Description:
 *      Contains the code for a simple 2D OpenGL / GLUT example.
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
int windowWidth = 512, windowHeight = 512;

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

//Draws a tringle that is the typical rock shape and color according tot he environment
void drawRockTriangle() {
	
	glPushMatrix();
	
	//rock color
	glColor3f(0.78,0.78,0.61);
	
	//base coordinates
	glBegin( GL_TRIANGLES );
	glVertex2f( 0, 0 );
	glVertex2f( 20, 0 );
	glVertex2f( 10, 25 );
	
	glEnd();
	
	glPopMatrix();
}

void drawCornerTriangle() {
	glPushMatrix();
	
	//rock color
	glColor3f(0.88,0.88,0.61);
	
	//base coordinates
	glBegin( GL_TRIANGLES );
	glVertex2f( 0, 0 );
	glVertex2f( 150, 0 );
	glVertex2f( 0, 150 );
	
	glEnd();
	
	glPopMatrix();
	
	glPushMatrix();
	
	//rock color
	glColor3f(0.88,0.88,0.61);
	
	//base coordinates
	glBegin( GL_TRIANGLES );
	glVertex2f( 511, 511 );
	glVertex2f( 361, 511 );
	glVertex2f( 511, 361 );
	
	glEnd();
	
	glPopMatrix();
	
	glPushMatrix();
	
	//rock color
	glColor3f(0.88,0.88,0.61);
	
	//base coordinates
	glBegin( GL_TRIANGLES );
	glVertex2f( 511, 0 );
	glVertex2f( 511, 150 );
	glVertex2f( 361, 0 );
	
	glEnd();
	
	glPopMatrix();
	
	glPushMatrix();
	
	//rock color
	glColor3f(0.88,0.88,0.61);
	
	//base coordinates
	glBegin( GL_TRIANGLES );
	glVertex2f( 0, 511 );
	glVertex2f( 0, 361 );
	glVertex2f( 150, 511 );
	
	glEnd();
	
	glPopMatrix();
}

//Draws a series of rock formations using the original triangle shape
//and also applying different transformations to it
void drawRockFormations() {
	
	//scaling and translation
	glPushMatrix();
	glTranslatef( 350, 350, 0 );
	glScalef(1.5,1.5,1.5);
	drawRockTriangle();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef( 175, 145, 0 );
	glScalef(2,2,1.5);
	drawRockTriangle();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef( 275, 225, 0 );
	glScalef(1,3,1);
	drawRockTriangle();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef( 125, 300, 0 );
	glScalef(2,3,1);
	drawRockTriangle();
	glPopMatrix();
	
	//translations
	glPushMatrix();
	glTranslatef( 300, 300, 0 );
	drawRockTriangle();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef( 210, 210, 0 );
	drawRockTriangle();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef( 350, 125, 0 );
	drawRockTriangle();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef( 210, 300, 0 );
	drawRockTriangle();
	glPopMatrix();
	
	//rotations
	glPushMatrix();
	glTranslatef(255, 255, 0);
	glRotatef(20, 1, 1, 0);
	drawRockTriangle();
	glPopMatrix();
	
	//rotations
	glPushMatrix();
	glTranslatef(210, 210, 0);
	glRotatef(50, 1, 1, 0);
	drawRockTriangle();
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
	
	//Sky Box including the color
	glColor3f(0.266,0.25,0.450);
	
	glBegin( GL_QUADS );
	glVertex2f( 0, 0 );
	glVertex2f( 0, 511 );
	glVertex2f( 511, 511 );
	glVertex2f( 511, 0 );
	
	glEnd();
	
	//bottom left rock
	glColor3f(0.98,0.98,0.71);
	
	glBegin( GL_TRIANGLES );
	glVertex2f( 0, 0 );
	glVertex2f( 0, 200 );
	glVertex2f( 200, 0 );
	
	glEnd();
	
	//bottom right rock
	glColor3f(0.98,0.98,0.71);
	
	glBegin( GL_TRIANGLES );
	glVertex2f( 511, 0 );
	glVertex2f( 311, 0 );
	glVertex2f( 511, 200 );
	
	glEnd();
	
	//top left rock
	glColor3f(0.98,0.98,0.71);
	
	glBegin( GL_TRIANGLES );
	glVertex2f( 0, 511 );
	glVertex2f( 0, 311 );
	glVertex2f( 200, 511 );
	
	glEnd();
	
	//top right rock
	glColor3f(0.98,0.98,0.71);
	
	glBegin( GL_TRIANGLES );
	glVertex2f( 511, 511 );
	glVertex2f( 511, 311 );
	glVertex2f( 311, 511 );
	
	glEnd();
	
	//main island
	glColor3f(0.98,0.98,0.71);
	
	glBegin( GL_QUADS );
	glVertex2f( 256, 0 );
	glVertex2f( 511, 256 );
	glVertex2f( 256, 511 );
	glVertex2f( 0 , 256 );
	
	glEnd();
	
	//corner triagnles with different color
	drawCornerTriangle();
	
	//draw the rock formations, uses all 3 transformations
	drawRockFormations();

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
	windowId = glutCreateWindow( "Lab 00B" );
	
	// register our reshape and display callbacks with GLUT - these functions are above
	glutDisplayFunc( renderScene );
	glutReshapeFunc( changeSize );
	
	// begin GLUT loop
	glutMainLoop();
	
	return 0;
}
