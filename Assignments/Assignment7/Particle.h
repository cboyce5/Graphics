#pragma once
#include <GL/glew.h>
#include "Camera.h"
#include "Vector.h"

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

class Particle {
	private:
	float posX;
	float posY;
	float posZ;
	
	float angle;
	float down;
	bool fall;
	
	public:
	int health;
	Vector heading;
	Vector toHero;
	Particle();
	Particle(float x, float y, float z);
	void draw();
	void update(float x, float z);
	void moveForward();
	void moveBackward();
	float getPosX();
	float getPosY();
	float getPosZ();
};