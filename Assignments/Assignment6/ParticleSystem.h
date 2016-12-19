#pragma once
#include <vector>
#include "Particle.h"
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

class ParticleSystem {
	private:
	float posX;
	float posY;
	float posZ;
	int width;
	int depth;
	float minVel;
	float maxVel;
	int rate;
	std::vector< Particle > particles;
	
	public:
	ParticleSystem();
	ParticleSystem(char* c, GLuint handle);
	void draw(Camera cam, GLuint particleAge, GLuint shaderProgramHandle);
	void update();
};