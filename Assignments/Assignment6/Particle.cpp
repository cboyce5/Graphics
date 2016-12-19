#include "Particle.h"
#include <cstdlib>
#include "Point.h"
#include "Vector.h"
#include <math.h>
#include <iostream>
using namespace std;

Particle::Particle(GLuint h, float x, float y, float z, float w, float d, float v) {
	//set variables
	handle = h;
	maxDepth = d;
	vel = v;
	width = w;
	age = 0;
	//determine random size around xyz within d, set pos accordingly
	startX = x;
	startY = y;
	startZ = z;
	posY = y;
	posX = ((rand() % (int)w) - ((float)w / 2.))+x;
	posZ = ((rand() % (int)w) - ((float)w / 2.))+z;
}

void Particle::drawSprite(float spriteXWidth, float spriteYWidth) {
	//hard coded sprite sizes
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, handle );
	glBegin( GL_QUADS ); {
        glTexCoord2f( 0, 0.01 );
        glVertex3f( -(spriteXWidth/2.0f), spriteYWidth, 0 );
        
        glTexCoord2f( 0, 1 );
        glVertex3f( -(spriteXWidth/2.0f),         0.0f, 0 );
        
        glTexCoord2f( 1, 1 );
        glVertex3f( (spriteXWidth/2.0f),         0.0f, 0 );
        
        glTexCoord2f( 1, 0.01 );
        glVertex3f( (spriteXWidth/2.0f), spriteYWidth, 0 );
    }; glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Particle::draw(Camera c, GLuint particleAge, GLuint shaderProgramHandle) {
	
	glUseProgram(shaderProgramHandle);
	glUniform1f(particleAge,age);
	//rotate to face camera
	Vector a = Vector(0,0,1);
	Vector b = Vector(-c.getX(),0.,-c.getZ());
	b.normalize();
	double angle;
	glPushMatrix(); {
		// TODO #2: Draw our sprite!
		glTranslatef(posX,posY,posZ);
		glColor3f(1,1,1);
		if (c.getX() > 0) {
			angle = (acos(dot(a,b)))*(180.0/M_PI) + (2*(180. - (acos(dot(a,b)))*(180.0/M_PI)));
		}
		else {
			angle = (acos(dot(a,b)))*(180.0/M_PI);
		}

		glRotatef(angle,0,1,0);
		
		drawSprite(5,5);
		
		
	}; glPopMatrix();
	
	glUseProgram(0);
  
}

void Particle::update() {
	//decrease y value corresponding to velocity, occurs every passive timer step
	if (rand() % 2 == 1) {
		posY -= vel;
	}
	posY -= vel;
	
	age = (startY-posY)/(float)maxDepth;
	//cout << age << endl;
	
	//if 'lifetime' has expired, i.e. below depth, renew y and recompute x and z to make it appear as if a new particle is being created
	if (posY < (float)startY-(float)maxDepth) {
		posY = startY;
		posX = ((rand() % (int)width) - (width / 2.))+startX;
		posZ = ((rand() % (int)width) - (width / 2.))+startZ;
	}
}

float Particle::getPosX() {
	return posX;
}

float Particle::getPosY() {
	return posY;
}

float Particle::getPosZ() {
	return posZ;
}