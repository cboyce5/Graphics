#pragma once
#include <GL/glew.h>
#include "Camera.h"

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
	float vel;
	float maxDepth;
	float startX;
	float startY;
	float startZ;
	GLuint handle;
	float width;
	float age;
	
	public:
	Particle(GLuint h, float x, float y, float z, float w, float d, float v);
	void draw(Camera c, GLuint particleAge, GLuint shaderProgramHandle);
	void drawSprite(float a, float b);
	void update();
	float getPosX();
	float getPosY();
	float getPosZ();
};