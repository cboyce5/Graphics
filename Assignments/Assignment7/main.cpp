//Assignment 5
//Made By: Cliff Boyce

#include <GL/glew.h>

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <SOIL/soil.h>

#include "include/Shader_Utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>			// we'll use ifstream	
#include <string>			// for, well strings!
#include <vector>			// and vectors (the storage container, not directional)
using namespace std;

//class file
#include "Point.h"
#include "Camera.h"
#include "Material.h"
#include "ParticleSystem.h"

// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

static size_t windowWidth  = 700;
static size_t windowHeight = 700;
static float aspectRatio;

GLint leftMouseButton; 		   	    // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse
float carX, carY, carZ;
float carTheta;
float carDirX, carDirY, carDirZ;
float bodyAngle = 0;
float wheelAngle = 0;

bool drawControlCage = true;
bool drawCurve = true;

GLuint environmentDL;

float speed = 1.5;

//create camera using zoom value of 75
Camera camera(75);

GLuint shaderProgramHandle = 0;             // handle to our shader program

//skybox handles
GLuint up;
GLuint down;
GLuint leftPanel;
GLuint rightPanel;
GLuint front;
GLuint back;
GLuint ground;

int imageWidth;
int imageHeight;
unsigned char* data;

ParticleSystem ps;
GLuint particleHandle;
GLuint particleAge = 0;

bool carFall = false;
float carRate = 0;

int health = 2;

bool completed[4] = {false, false, false, false};

//passive time function for moving the present along the curve
void myTimer(int value) {
	if (carFall) {
		carRate += 0.05;
		carY -= carRate;
		camera.recomputeOrientation(carX, carY, carZ);
	}
	if (completed[0] == true && completed[1] == true && completed[2] == true && completed[3] == true ) {
		//do something for win
		cout << "Congratulations, you win!" << endl;
		exit(0);
	}
	if ( ps.update(carX, carZ) ) {
		health--;
	}
	if (health == 0) {
		//do something for the loss
		cout << "The enemies got to you. Game Over." << endl;
		exit(0);
	}
	
	glutPostRedisplay();
	glutTimerFunc( 25, myTimer, 0);
}

//generate random variable
float getRand() {
   	return rand() / (float)RAND_MAX;
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

//drawing the car for the snowman
void drawCar() {
	glPushMatrix(); {
		
		//base coordinates for the care, make it a tad bigger, apply rotation accoding to amount car has turned
		glTranslatef(carX,carY,carZ);
		
		glRotatef(-carTheta*180/M_PI,0,1,0);
		
		
		//draw the curve and points inside car as it needs to be always related to hero location
		
			
		
		glScalef(1.5,1.5,1.5);
		
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

//draw the rings for playing the actual game
void drawRings() {
	glPushMatrix(); {
		if (completed[0] == true) {
			glColor3f(0.9,1.0,0);
		}
		else {
			glColor3f(1,0,0);
		}
		glTranslatef(50,15,50);
		glutSolidTorus(2.5,15,10,20);
	} glPopMatrix();
	
	glPushMatrix(); {
		if (completed[1] == true) {
			glColor3f(0.9,1.0,0);
		}
		else {
			glColor3f(1,0,0);
		}
		glTranslatef(-50,15,-50);
		glutSolidTorus(2.5,15,10,20);
	} glPopMatrix();
	
	glPushMatrix(); {
		if (completed[2] == true) {
			glColor3f(0.9,1.0,0);
		}
		else {
			glColor3f(1,0,0);
		}
		glTranslatef(50,15,-50);
		glutSolidTorus(2.5,15,20,20);
	} glPopMatrix();
	
	glPushMatrix(); {
		if (completed[3] == true) {
			glColor3f(0.9,1.0,0);
		}
		else {
			glColor3f(1,0,0);
		}
		glTranslatef(-50,15,50);
		glutSolidTorus(2.5,15,20,20);
	} glPopMatrix();
}

//list of things to draw (from lab02)
void generateEnvironmentDL() {
	environmentDL = glGenLists( 1 );
	glNewList( environmentDL, GL_COMPILE );
		//drawRings();
	glEndList();
    
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
		camera.setZoom(camera.getZoom()+diffY*0.25);
		camera.recomputeOrientation(carX, carY, carZ);
		glutPostRedisplay();
	}
    else if(leftMouseButton == GLUT_DOWN) {
        float diffX = x - mouseX;
		camera.setTheta(camera.getTheta()+diffX*0.005);
		float diffY = mouseY - y;
		camera.setPhi(camera.getPhi()+diffY*0.005);
        camera.recomputeOrientation(carX, carY, carZ);     // update camera (x,y,z) based on (radius,theta,phi)
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

	glDisable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
	
    glShadeModel(GL_SMOOTH);
	
	generateEnvironmentDL();
	
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//renderscene function
void renderScene(void)  {
	
    //clear the render buffer
	glClearColor(0,0,0,1);
    glDrawBuffer( GL_BACK );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //update the modelview matrix based on the camera's position
    glMatrixMode(GL_MODELVIEW);              //make sure we aren't changing the projection matrix!
    glLoadIdentity();
    gluLookAt( camera.getX(), camera.getY(), camera.getZ(),		//uses camera object
                carX,  carY,  carZ,								//looking at
                0,  1,  0);     								// up vector is (0,1,0) (positive Y)
			
	Material *test = new Material(GOL_MATERIAL_CYANRUBBER);
	setCurrentMaterial(test);

	drawCar();
	glCallList( environmentDL );
	
	glDisable(GL_LIGHTING);
	
	glEnable(GL_TEXTURE_2D);
	
	//skyboxes
	{
	//COMPLETE
	glBindTexture(GL_TEXTURE_2D,up);
	glColor3f(1,1,1);
	glPushMatrix(); {
		if (!carFall) {
			glTranslatef(carX,carY,carZ);
		}
		else {
			glTranslatef(carX,0,carZ);
		}
		glBegin(GL_QUADS); {
			
			glTexCoord2f(1,1);
			glVertex3f(-200,200,-200);
			
			glTexCoord2f(0,1);
			glVertex3f(200,200,-200);
			
			glTexCoord2f(0,0);
			glVertex3f(200,200,200);
			
			glTexCoord2f(1,0);
			glVertex3f(-200,200,200);
					
		} glEnd();
	} glPopMatrix();
	
	//COMPLETE
	glBindTexture(GL_TEXTURE_2D,down);
	glColor3f(1,1,1);
	glPushMatrix(); {
		if (!carFall) {
			glTranslatef(carX,carY,carZ);
		}
		else {
			glTranslatef(carX,0,carZ);
		}
		glRotatef(180,1,0,1);
		glBegin(GL_QUADS); {
			glTexCoord2f(1,0);
			glVertex3f(-200,200,-200);
			
			glTexCoord2f(1,1);
			glVertex3f(200,200,-200);
			
			glTexCoord2f(0,1);
			glVertex3f(200,200,200);
			
			glTexCoord2f(0,0);
			glVertex3f(-200,200,200);
			
			
		} glEnd();
	} glPopMatrix();
	
	//COMPLETE
	glBindTexture(GL_TEXTURE_2D,rightPanel);
	glColor3f(1,1,1);
	glPushMatrix(); {
		if (!carFall) {
			glTranslatef(carX,carY,carZ);
		}
		else {
			glTranslatef(carX,0,carZ);
		}
		glRotatef(180,0,1,0);
		glBegin(GL_QUADS); {
			glTexCoord2f(0,0);
			glVertex3f(-200,-200,-200);
			
			glTexCoord2f(1,0);
			glVertex3f(200,-200,-200);
			
			glTexCoord2f(1,1);
			glVertex3f(200,200,-200);
			
			glTexCoord2f(0,1);
			glVertex3f(-200,200,-200);
			
			
		} glEnd();
	} glPopMatrix();
	
	//COMPLETE
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,leftPanel);
	glColor3f(1,1,1);
	glPushMatrix(); {
		if (!carFall) {
			glTranslatef(carX,carY,carZ);
		}
		else {
			glTranslatef(carX,0,carZ);
		}
		glBegin(GL_QUADS); {
			glTexCoord2f(0,0);
			glVertex3f(-200,-200,-200);
			
			glTexCoord2f(1,0);
			glVertex3f(200,-200,-200);
			
			glTexCoord2f(1,1);
			glVertex3f(200,200,-200);
			
			glTexCoord2f(0,1);
			glVertex3f(-200,200,-200);
			
			
		} glEnd();
	} glPopMatrix();
	
	// COMPLETE
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,back);
	glColor3f(1,1,1);
	glPushMatrix(); {
		if (!carFall) {
			glTranslatef(carX,carY,carZ);
		}
		else {
			glTranslatef(carX,0,carZ);
		}
		glBegin(GL_QUADS); {
			glTexCoord2f(0,0);
			glVertex3f(200,-200,-200);
			
			glTexCoord2f(1,0);
			glVertex3f(200,-200,200);
			
			glTexCoord2f(1,1);
			glVertex3f(200,200,200);
			
			glTexCoord2f(0,1);
			glVertex3f(200,200,-200);
			
			
		} glEnd();
	} glPopMatrix();
	
	//COMPLETE
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,front);
	glColor3f(1,1,1);
	glPushMatrix(); {
		if (!carFall) {
			glTranslatef(carX,carY,carZ);
		}
		else {
			glTranslatef(carX,0,carZ);
		}
		glRotatef(180,0,1,0);
		glBegin(GL_QUADS); {
			glTexCoord2f(0,0);
			glVertex3f(200,-200,-200);
			
			glTexCoord2f(1,0);
			glVertex3f(200,-200,200);
			
			glTexCoord2f(1,1);
			glVertex3f(200,200,200);
			
			glTexCoord2f(0,1);
			glVertex3f(200,200,-200);
			
			
		} glEnd();
		
	} glPopMatrix();
	
	//ground
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,ground);
	glColor3f(1,1,1);
	glPushMatrix(); {
		glBegin(GL_QUADS); {
			glTexCoord2f(8,0);
			glVertex3f(100,0,100);
			
			glTexCoord2f(8,8);
			glVertex3f(100,0,-100);
			
			glTexCoord2f(0,8);
			glVertex3f(-100,0,-100);
			
			glTexCoord2f(0,0);
			glVertex3f(-100,0,100);
			
			
		} glEnd();
	} glPopMatrix();
	}

	//somehow gives everything materials, idk how tho
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPushMatrix(); {
		//glUseProgram(shaderProgramHandle);
		glTranslatef(50,25,50);
		glScalef(5,5,5);
		glUseProgram(0);
    }; glPopMatrix();

	//glUseProgram(shaderProgramHandle);
	ps.draw();
	//glUseProgram(0);
	
	//cout << carX << " " << carZ << endl;
	//check if car is within each ring
	if ( carX > 40 && carX < 60  && carZ > 40 && carZ < 60 ) {
		completed[0] = true;
	}
	if ( carX < -40 && carX > -60  && carZ < -40 && carZ > -60 ) {
		completed[1] = true;
	}
	if ( carX > 40 && carX < 60  && carZ < -40 && carZ > -60 ) {
		completed[2] = true;
	}
	if ( carX < -40 && carX > -60  && carZ > 40 && carZ < 60 ) {
		completed[3] = true;
	}
	
	drawRings();
	
	
    //push the back buffer to the screen
    glutSwapBuffers();
}

//fall off the world
void fall() {
	carFall = true;
	
}

//keys held down check
void normalKeysDown(unsigned char key, int x, int y) {
	switch (key) {
		//w pressed
		case 119:
			wheelAngle += 5;
			
			carX += carDirX*speed;
			carZ += carDirZ*speed;
			//camera object used to change values
			camera.setX(camera.getX()+(carDirX*speed));
			camera.setZ(camera.getZ()+(carDirZ*speed));
			
			if (carX < -100) {
				//carX = -99.99;
				fall();
			}
			else if(carX > 100) {
				//carX = 99.99;
				fall();
			}
			if (carZ < -100) {
				//carZ = -99.99;
				fall();
			}
			else if(carZ > 100) {
				//carZ = 99.99;
				fall();
			}
			//calling recomputeOrientation because if we reset the car position when it moves outside bounds, the camera wont keep going
			camera.recomputeOrientation(carX, carY, carZ);
			break;
		//s pressed
		case 115:
			wheelAngle -= 5;
			
			carX -= carDirX*speed;
			carZ -= carDirZ*speed;
			camera.setX(camera.getX()-(carDirX*speed));
			camera.setZ(camera.getZ()-(carDirZ*speed));
			
			if (carX < -100) {
				//carX = -99.99;
				fall();
			}
			else if(carX > 100) {
				//carX = 99.99;
				fall();
			}
			if (carZ < -100) {
				fall();
			}
			else if(carZ > 100) {
				//carZ = 99.99;
				fall();
			}
			camera.recomputeOrientation(carX, carY, carZ);
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

//set up the shaders
void setupShaders() {

	// TODO #7: compile shader program
	shaderProgramHandle = createShaderProgram("shaders/customShader.v.glsl","shaders/customShader.f.glsl");
	
	particleAge = glGetUniformLocation(shaderProgramHandle,"age");
}

bool readPPM(string filename, int &imageWidth, int &imageHeight, unsigned char* &imageData)
{
    FILE *fp = fopen(filename.c_str(), "r");
    int temp, maxValue;
    fscanf(fp, "P%d", &temp);
    if(temp != 3)
    {
        fprintf(stderr, "Error: PPM file is not of correct format! (Must be P3, is P%d.)\n", temp);
        fclose(fp);
        return false;
    }
    
    //got the file header right...
    fscanf(fp, "%d", &imageWidth);
    fscanf(fp, "%d", &imageHeight);
    fscanf(fp, "%d", &maxValue);
    
    //now that we know how big it is, allocate the buffer...
    imageData = new unsigned char[imageWidth*imageHeight*3];
    if(!imageData)
    {
        fprintf(stderr, "Error: couldn't allocate image memory. Dimensions: %d x %d.\n", imageWidth, imageHeight);
        fclose(fp);
        return false;
    }
    
    //and read the data in.
    for(int j = 0; j < imageHeight; j++)
    {
        for(int i = 0; i < imageWidth; i++)
        {
            int r, g, b;
            fscanf(fp, "%d", &r);
            fscanf(fp, "%d", &g);
            fscanf(fp, "%d", &b);
            
            imageData[(j*imageWidth+i)*3+0] = r;
            imageData[(j*imageWidth+i)*3+1] = g;
            imageData[(j*imageWidth+i)*3+2] = b;
        }
    }
    
    fclose(fp);
    return true;
}


bool registerOpenGLTexture(unsigned char *textureData,
                           unsigned int texWidth, unsigned int texHeight,
                           GLuint &textureHandle) {
    // TODO #2b: Fill this in
    glEnable(GL_TEXTURE_2D);
	glGenTextures(1,&textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texWidth,texHeight,0,GL_RGB,GL_UNSIGNED_BYTE,textureData);
	
    return true;
}

//register transparent tezture, called to generate texture in main but passed to particle system for particle.draw();
bool registerTransparentOpenGLTexture(unsigned char *imageData, unsigned char *imageMask, int texWidth, int texHeight, GLuint &texHandle) {
    // combine the 'mask' array with the image data array into an RGBA array.
    unsigned char *fullData = new unsigned char[texWidth*texHeight*4];
    for(int j = 0; j < texHeight; j++) {
        for(int i = 0; i < texWidth; i++) {
            fullData[(j*texWidth+i)*4+0] = imageData[(j*texWidth+i)*3+0];	// R
            fullData[(j*texWidth+i)*4+1] = imageData[(j*texWidth+i)*3+1];	// G
            fullData[(j*texWidth+i)*4+2] = imageData[(j*texWidth+i)*3+2];	// B
            fullData[(j*texWidth+i)*4+3] = imageMask[(j*texWidth+i)*3+0];	// A
        }
    }
    
    // first off, get a real texture handle.
    glGenTextures(1, &texHandle);
    
    // make sure that future texture functions affect this handle
    glBindTexture(GL_TEXTURE_2D, texHandle);
    
    // set this texture's color to be multiplied by the surface colors --
    //  GL_MODULATE instead of GL_REPLACE allows us to take advantage of OpenGL lighting
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // set the minification and magnification functions to be linear; not perfect
    //  but much better than nearest-texel (GL_NEAREST).
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Set the texture to repeat in S and T -- though it doesn't matter here
    //  because our texture coordinates are always in [0,0] to [1,1].
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // actually transfer the texture to the GPU and use MipMaps!!
    /*    gluBuild2DMipMaps(
     GL_TEXTURE_2D,              //still working with 2D textures, obv.
     GL_RGBA,                    //we're going to provide OpenGL with R, G, B, and A components...
     texWidth,                   //...of this width...
     texHeight,                  //...and this height.
     GL_RGBA,                    //and store it, internally, as RGBA (OpenGL will convert to floats between 0.0 and 1.0f)
     GL_UNSIGNED_BYTE,           //this is the format our data is in, and finally,
     fullData);                  //there's the data!
     */
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, fullData );
    
    // clean up our memory on the CPU side since it's already been transfered to the GPU
    delete fullData;
    
    // whoops! i guess this function can't fail. in an ideal world, there would
    // be checks with glGetError() that we could use to determine if this failed.
    return true;
}

//main
int main(int argc, char **argv) {
    // create a double-buffered GLUT window at (50,50) with predefined windowsize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Assignment 7");
	
	/* initialize GLEW */
    // LOOKHERE #1
    GLenum glewResult = glewInit();
    /* check for an error */
    if( glewResult != GLEW_OK ) {
        printf( "[ERROR]: Error initalizing GLEW\n");
        return 0;
    }
	
    // give the camera a scenic starting point.
	carX = 0;
	carY = 2;
	carZ = 0;
	carTheta = 0;
	carDirX = cos(carTheta);
	carDirZ = sin(carTheta);
	
	GLint maxVertexAttribs = 0;
    glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs );
    
    GLint maxLights = 0;
    glGetIntegerv( GL_MAX_LIGHTS, &maxLights );
    
    GLint maxTextures = 0;
    glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures );
    
    fprintf( stdout, "[INFO]: /--------------------------------------------------------\\\n");
    fprintf( stdout, "[INFO]: | OpenGL Information                                     |\n");
    fprintf( stdout, "[INFO]: |--------------------------------------------------------|\n");
    fprintf( stdout, "[INFO]: |   OpenGL Version:  %35s |\n", glGetString(GL_VERSION) );
    fprintf( stdout, "[INFO]: |   OpenGL Renderer: %35s |\n", glGetString(GL_RENDERER) );
    fprintf( stdout, "[INFO]: |   OpenGL Vendor:   %35s |\n", glGetString(GL_VENDOR) );
    fprintf( stdout, "[INFO]: |   Shading Version: %35s |\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );
    fprintf( stdout, "[INFO]: >--------------------------------------------------------<\n");
    fprintf( stdout, "[INFO]: |   Max # Vertex Attributes:  %26d |\n", maxVertexAttribs );
    fprintf( stdout, "[INFO]: |   Max # Lights:    %35d |\n", maxLights );
    fprintf( stdout, "[INFO]: |   Max # Textures:  %35d |\n", maxTextures );
    fprintf( stdout, "[INFO]: \\--------------------------------------------------------/\n\n");
    
    /* make sure OpenGL 2.0 is supported */
    if( !glewIsSupported( "GL_VERSION_2_0" ) ) {
        printf( "[ERROR]: System does not support OpenGL 2.0 and GLSL\n" );
        return 0;
    }
    
    printf( "[INFO]: System supports OpenGL2.0 and GLSL!\n\n" );

    //do some basic OpenGL setup
    initScene();
    printf( "[INFO]: OpenGL Scene set up\n" );
    
    // set up our shaders (the files are hardcoded in)
    printf( "[INFO]: Shader compilation complete.\n" );
	

    // register callback functions...
    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glutKeyboardFunc(normalKeysDown);
    glutDisplayFunc(renderScene);
    glutReshapeFunc(resizeWindow);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(mouseMotion);
	glutTimerFunc( 5, myTimer, 0);		//timer callback added just for this assignment
	
	//register all textures
	{
	up =
		SOIL_load_OGL_texture(
		"textures/ss_up.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
			| SOIL_FLAG_INVERT_Y
			| SOIL_FLAG_COMPRESS_TO_DXT
	);
    // TODO #6: Register non-PPM
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	down =
		SOIL_load_OGL_texture(
		"textures/ss_dn.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
			| SOIL_FLAG_INVERT_Y
			| SOIL_FLAG_COMPRESS_TO_DXT
	);
    // TODO #6: Register non-PPM
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	leftPanel =
		SOIL_load_OGL_texture(
		"textures/ss_lf.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
			| SOIL_FLAG_INVERT_Y
			| SOIL_FLAG_COMPRESS_TO_DXT
	);
    // TODO #6: Register non-PPM
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	rightPanel =
		SOIL_load_OGL_texture(
		"textures/ss_rt.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
			| SOIL_FLAG_INVERT_Y
			| SOIL_FLAG_COMPRESS_TO_DXT
	);
    // TODO #6: Register non-PPM
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	front =
		SOIL_load_OGL_texture(
		"textures/ss_ft.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
			| SOIL_FLAG_INVERT_Y
			| SOIL_FLAG_COMPRESS_TO_DXT
	);
    // TODO #6: Register non-PPM
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	back =
		SOIL_load_OGL_texture(
		"textures/ss_bk.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
			| SOIL_FLAG_INVERT_Y
			| SOIL_FLAG_COMPRESS_TO_DXT
	);
    // TODO #6: Register non-PPM
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	ground =
		SOIL_load_OGL_texture(
		"textures/metal.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
			| SOIL_FLAG_INVERT_Y
			| SOIL_FLAG_COMPRESS_TO_DXT
	);
    // TODO #6: Register non-PPM
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	particleHandle =
		SOIL_load_OGL_texture(
		"textures/wood.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
			| SOIL_FLAG_INVERT_Y
			| SOIL_FLAG_COMPRESS_TO_DXT
	);
    // TODO #6: Register non-PPM
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	}
	
	
	setupShaders();
	ps = ParticleSystem("control.txt");
	
	
    // do some basic OpenGL setup
    initScene();
	
    // and enter the GLUT loop, never to exit.
    glutMainLoop();

    return(0);
}
