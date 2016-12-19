#include "Particle.h"
#include <cstdlib>
#include "Point.h"
#include "Vector.h"
#include <math.h>
#include <iostream>
#include "Matrix.h"
using namespace std;

Particle::Particle() {
	
}

Particle::Particle(float x, float y, float z) {
	posX = x;
	posY = y;
	posZ = z;
	heading = Vector(1,0,0);
	angle = 0;
	down = 0;
	fall = false;
	health = 3;
}

void Particle::draw() {
	// draw the sphere
		//cout << posX << " " << posY << " " << posZ << endl;
	glPushMatrix(); {
		glColor3f(0.5,(float)health/2,0.9);
		glTranslatef(posX, posY, posZ);
		glRotatef(180-angle,0,1,0);
		
		// glBegin(GL_LINES);
		// glColor3f(0,0,1);
			// glVertex3f(0,0,0);
			// glVertex3f(heading.at(0)*50,heading.at(1)*50,heading.at(2)*50);
			
			// glVertex3f(0,0,0);
			// glVertex3f(toHero.at(0)*50,toHero.at(1)*50,toHero.at(2)*50);
			
		// glEnd();
		glutSolidCube(5);
	} glPopMatrix();
}

void Particle::update(float x, float z) {
	
	if (fall) {
		down += 0.05;
		posY -= down;
	}
	
	Point a(posX, posY, posZ);
	Point b(x,0.0,z);
	toHero = (a-b);
	
	toHero.normalize();
	heading.normalize();
	
	
	angle = (180.0/M_PI)*acos( dot(heading,toHero) );
	
	// if (tempAngle > 0.5)  {
		// angle = tempAngle;
		// Vector axis = cross(heading,toHero);
		// Matrix r;
		// r.makeRotation(tempAngle,axis.at(0),axis.at(1),axis.at(2);
		// heading = r*heading;
		// heading.normalize();
	
	// }
	
	moveForward();
	
	
	
	if (posX < -100) {
		fall = true;
	}
	else if(posX > 100) {
		fall = true;
	}
	if (posZ < -100) {
		fall = true;
	}
	else if(posZ > 100) {
		fall = true;
	}
	
}

void Particle::moveForward() {
	posX -= 0.20*toHero.at(0);
	posY -= 0.20*toHero.at(1);
	posZ -= 0.20*toHero.at(2);
}

void Particle::moveBackward() {
	posX += 0.35*toHero.at(0);
	posY += 0.35*toHero.at(1);
	posZ += 0.35*toHero.at(2);
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