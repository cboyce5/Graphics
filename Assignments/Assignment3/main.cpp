//Assignment 3
//Made By: Cliff Boyce
//Description: Draws a car with a snowman on it and allows the car to move using wasd keys.

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

static size_t windowWidth  = 700;
static size_t windowHeight = 700;
static float aspectRatio;

GLint leftMouseButton; 		   	    // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse
float carX, carY, carZ;
float carTheta;
float carDirX, carDirY, carDirZ;
float cameraX, cameraY, cameraZ;           // camera position in cartesian coordinates
float cameraTheta, cameraPhi;               // camera DIRECTION in spherical coordinates
float zoom = 75;
float bodyAngle = 0;
float wheelAngle = 0;

GLuint environmentDL;                       // display list for the 'city'

float speed = 1.5;

float getRand() {
   	return rand() / (float)RAND_MAX;
}

//drawing the surrounding fence to give the bounds a little more realism
void drawFences() {
	glColor3f(0.4,0.2,0);
	
	//each fence is a series of cubes that are streched and translated
	glPushMatrix(); {
		glTranslatef(100,15,0);
		glScalef(1,1,133);
		glutSolidCube(1.5);
		glTranslatef(0,-5,0);
		glutSolidCube(1.5);
		glTranslatef(0,-5,0);
		glutSolidCube(1.5);
	} glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0,15,100);
		glScalef(133,1,1);
		glutSolidCube(1.5);
		glTranslatef(0,-5,0);
		glutSolidCube(1.5);
		glTranslatef(0,-5,0);
		glutSolidCube(1.5);
	} glPopMatrix();
	glPushMatrix(); {
		glTranslatef(-100,15,0);
		glScalef(1,1,133);
		glutSolidCube(1.5);
		glTranslatef(0,-5,0);
		glutSolidCube(1.5);
		glTranslatef(0,-5,0);
		glutSolidCube(1.5);
	} glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0,15,-100);
		glScalef(133,1,1);
		glutSolidCube(1.5);
		glTranslatef(0,-5,0);
		glutSolidCube(1.5);
		glTranslatef(0,-5,0);
		glutSolidCube(1.5);
	} glPopMatrix();
}

//drawing several bits of scenery for our world, i.e torches
void drawScenery() {
	for (int i = -100; i <= 100; i+= 5) {
		for (int j = -100; j <= 100; j += 5) {
			if (i % 50 == 0 && j % 50 == 0) {
				glColor3f(0.4,0.2,0);
				glPushMatrix(); {
					glTranslatef(i,10,j);
					glScalef(1,10,1);
					glutSolidCube(2);
				} glPopMatrix();
				glColor3f(1,1,0.4);
				glPushMatrix(); {
					glTranslatef(i,20,j);
					glutSolidSphere(2.5,25,25);
				} glPopMatrix();
			}
		}
	}
	drawFences();
}

//draws the base grid on the ground
void drawGrid() {
    glDisable( GL_LIGHTING );

	for (int i = -100; i <= 100; i+= 5) {
		for (int j = -100; j <= 100; j += 5) {
			glLineWidth(1);
			glColor3f(1,1,1);
			glBegin(GL_LINES);
				glVertex3f(i,0,j);
				glVertex3f(i,0,abs(j));
				
				glVertex3f(i,0,j);
				glVertex3f(abs(i),0,j);
			glEnd();
		}
	}
    glEnable( GL_LIGHTING );
}

//individual wheel function
void drawWheel() {
	glPushMatrix(); {
		glColor3f(0.1,0.1,0.1);
		glutSolidTorus(1,2,10,10);
		glColor3f(0.2,0.2,0.2);
		glutWireTorus(1,2,10,10);
	} glPopMatrix();
}

//individual axel function
void drawAxel() {
	glPushMatrix(); {
		glColor3f(1,0,0);
		glutSolidCone(1,3,30,30);
	} glPopMatrix();
}

//drawing the face of the snowman
void drawFace() {
	glPushMatrix(); {
		glTranslatef(0.35,0.1,1.55);
		glColor3f(0.1,0.1,0.1);
		glutSolidSphere(0.2,25,25);
		glTranslatef(-0.7,0,0);
		glutSolidSphere(0.2,25,25);
		glTranslatef(0.35,-0.2,0);
		glColor3f(1,0.4,0);
		glutSolidCone(0.1,1,30,30);
	} glPopMatrix();
}

//drawing the body of the snowman
void drawBody() {
	glPushMatrix(); {
		glColor3f(1,1,1);
		glutSolidSphere(3,50,50);
		glTranslatef(0,4,0);
		glutSolidSphere(2,50,50);
		glTranslatef(0,3.2,0);
		glutSolidSphere(1.5,50,50);
		
		//rotate 90 degrees then draw the face to show the direction of the car (i.e. which was is forward)
		glRotatef(90,0,1,0);
		drawFace();
	} glPopMatrix();
}

void drawCar() {
	glPushMatrix(); {
		
		//base coordinates for the care, make it a tad bigger, apply rotation accoding to amount car has turned
		glTranslatef(carX,2,carZ);
		glScalef(1.5,1.5,1.5);
		glRotatef(-carTheta*180/M_PI,0,1,0);
		
		//bed of the car
		glPushMatrix(); {
			glColor3f(0,0,1);
			glScalef(9,1,6);
			glutSolidCube(1);
		} glPopMatrix();
		
		//snowman body
		glPushMatrix(); {
			glTranslatef(0,3,0);
			glRotatef(bodyAngle,0,1,0);
			drawBody();
		} glPopMatrix();
		
		//4 wheels
		glPushMatrix(); {
			glTranslatef(2,0,4);
			glRotatef(-wheelAngle,0,0,1);
			glScalef(0.5,0.5,0.5);
			drawWheel();
		} glPopMatrix();
		glPushMatrix(); {
			glTranslatef(2,0,-4);
			glScalef(0.5,0.5,0.5);
			glRotatef(-wheelAngle,0,0,1);
			drawWheel();
		} glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-2,0,4);
			glScalef(0.5,0.5,0.5);
			glRotatef(-wheelAngle,0,0,1);
			drawWheel();
		} glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-2,0,-4);
			glScalef(0.5,0.5,0.5);
			glRotatef(-wheelAngle,0,0,1);
			drawWheel();
		} glPopMatrix();
		
		//4 axels
		glPushMatrix(); {
			glTranslatef(2,0,3);
			drawAxel();
		} glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-2,0,3);
			drawAxel();
		} glPopMatrix();
		glPushMatrix(); {
			glTranslatef(2,0,-3);
			glScalef(1,1,-1);
			drawAxel();
		} glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-2,0,-3);
			glScalef(1,1,-1);
			drawAxel();
		} glPopMatrix();
		
	} glPopMatrix();
}

//list of things to draw (from lab02)
void generateEnvironmentDL() {
	environmentDL = glGenLists( 1 );
	glNewList( environmentDL, GL_COMPILE );
		drawGrid();
		drawScenery();
	glEndList();
    
}

//arcball calculations
//	only need to change the camera position based on the car position and the 2 angles
//	of the arcball camera, changed when mouse1 is held down and dragged
void recomputeOrientation() {	
	cameraX = carX + zoom*sin(cameraPhi)*sin(cameraTheta);
	cameraY = carY + zoom*(-1*cos(cameraPhi));
	cameraZ = carZ + zoom*(-1*cos(cameraTheta)*sin(cameraPhi));
}

//resize window function
void resizeWindow(int w, int h) {
    aspectRatio = w / (float)h;

    windowWidth = w;
    windowHeight = h;

    //update the viewport to fill the window
    glViewport(0, 0, w, h);

    //update the projection matrix with the new window properties
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100000);
}

//mouse callbacks
void mouseCallback(int button, int state, int thisX, int thisY) {
    // update the left mouse button states, if applicable
    if(button == GLUT_LEFT_BUTTON) {
        leftMouseButton = state;
		if(leftMouseButton == GLUT_DOWN) {
			mouseX = thisX;
			mouseY = thisY;
		}

	}
}

//active motion if mouse1 is held down
void mouseMotion(int x, int y) {
	if (leftMouseButton == GLUT_DOWN && (glutGetModifiers() & GLUT_ACTIVE_CTRL)) {
		float diffY = mouseY - y;
		zoom += diffY*0.25;
		if (zoom < 0) {
			zoom = 0;
		}
		recomputeOrientation();
		glutPostRedisplay();
	}
    else if(leftMouseButton == GLUT_DOWN) {
        float diffX = x - mouseX;
		cameraTheta += (diffX*0.005);
		float diffY = mouseY - y;
		cameraPhi += (diffY*0.005);
		if (cameraPhi <= 0) {
			cameraPhi = 0.001;
		}
		else if (cameraPhi >= M_PI){
			cameraPhi = M_PI - 0.001;
		}
        recomputeOrientation();     // update camera (x,y,z) based on (radius,theta,phi)
		glutPostRedisplay();	    // redraw our scene from our new camera POV
    }
	mouseX = x;
	mouseY = y;
}

//nothing changed from lab02
void initScene()  {
    glEnable(GL_DEPTH_TEST);

    //******************************************************************
    // this is some code to enable a default light for the scene;
    // feel free to play around with this, but we won't talk about
    // lighting in OpenGL for another couple of weeks yet.
    float lightCol[4] = { 1, 1, 1, 1};
    float ambientCol[4] = { 0.0, 0.0, 0.0, 1.0 };
    float lPosition[4] = { 10, 10, 10, 1 };
    glLightfv( GL_LIGHT0, GL_POSITION,lPosition );
    glLightfv( GL_LIGHT0, GL_DIFFUSE,lightCol );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
	
    // tell OpenGL not to use the material system; just use whatever we 
    // pass with glColor*()
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    //******************************************************************

    glShadeModel(GL_FLAT);

    srand( time(NULL) );	// seed our random number generator
    generateEnvironmentDL();
}

//renderscene function
//	gluLookAt() now is located at the camera positon, and always looks at the car
void renderScene(void)  {
    //clear the render buffer
    glDrawBuffer( GL_BACK );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //update the modelview matrix based on the camera's position
    glMatrixMode(GL_MODELVIEW);              //make sure we aren't changing the projection matrix!
    glLoadIdentity();
    gluLookAt( cameraX, cameraY, cameraZ,					//located at
                carX,  carY,  carZ,								//looking at
                0,  1,  0);     								// up vector is (0,1,0) (positive Y)

    glCallList( environmentDL );
	drawCar();
    //push the back buffer to the screen
    glutSwapBuffers();
}

//keys held down check
//	w and s move forward and back, check for bounds so the car doesnt move outside the pen things
//	a and d change angle the car is rotated at, recalculates car direction so it moves in the correct direction
void normalKeysDown(unsigned char key, int x, int y) {
	switch (key) {
		//w pressed
		case 119:
			wheelAngle += 5;
			if (carX >= -100 && carX <= 100 && carZ >= -100 && carZ <= 100) {
				carX += carDirX*speed;
				carZ += carDirZ*speed;
				cameraX += carDirX*speed;
				cameraZ += carDirZ*speed;
			}
			if (carX < -100) {
				carX = -99.99;
				
			}
			else if(carX > 100) {
				carX = 99.99;
			}
			if (carZ < -100) {
				carZ = -99.99;
			}
			else if(carZ > 100) {
				carZ = 99.99;
			}
			//calling recomputeOrientation because if we reset the car position when it moves outside bounds, the camera wont keep going
			recomputeOrientation();
			break;
		//s pressed
		case 115:
			wheelAngle -= 5;
			if (carX >= -100 && carX <= 100 && carZ >= -100 && carZ <= 100) {
				carX -= carDirX*speed;
				carZ -= carDirZ*speed;
				cameraX -= carDirX*speed;
				cameraZ -= carDirZ*speed;
			}
			if (carX < -100) {
				carX = -99.99;
			}
			else if(carX > 100) {
				carX = 99.99;
			}
			if (carZ < -100) {
				carZ = -99.99;
			}
			else if(carZ > 100) {
				carZ = 99.99;
			}
			recomputeOrientation();
			break;
		//a pressed
		case 97:
			carTheta -= 0.15;
			carDirX = cos(carTheta);
			carDirZ = sin(carTheta);
			break;
		//d pressed
		case 100:
			carTheta += 0.15;
			carDirX = cos(carTheta);
			carDirZ = sin(carTheta);
			break;
			
	}
	
	//quit
    if(key == 'q' || key == 'Q' || key == 27)
        exit(0);

    glutPostRedisplay();		// redraw our scene from our new camera POV
}

int main(int argc, char **argv) {
    // create a double-buffered GLUT window at (50,50) with predefined windowsize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Assignment 3");

    // give the camera a scenic starting point.
	carX = 0;
	carY = 2;
	carZ = 0;
	carTheta = 0;
	carDirX = cos(carTheta);
	carDirZ = sin(carTheta);
    cameraTheta = 3*M_PI / 2.0;
    cameraPhi = M_PI / 1.5;
    recomputeOrientation();

    // register callback functions...
    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glutKeyboardFunc(normalKeysDown);
    glutDisplayFunc(renderScene);
    glutReshapeFunc(resizeWindow);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(mouseMotion);
	

    // do some basic OpenGL setup
    initScene();

    // and enter the GLUT loop, never to exit.
    glutMainLoop();

    return(0);
}
