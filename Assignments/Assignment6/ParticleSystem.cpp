#include "ParticleSystem.h"
#include "Point.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

ParticleSystem::ParticleSystem() {
	
}

ParticleSystem::ParticleSystem(char* c, GLuint handle) {
	//read in file setting variables for system
	ifstream input;
	input.open(c);
	if (input.is_open()) {
		float d,e,f;
		float a,b,c,g,h;
		input >> a >> b >> c >> d >> e >> g >> h >> f;
		posX = a;
		posY = b;
		posZ = c;
		width = d;
		depth = e;
		minVel = g;
		maxVel = h;
		rate = f;
	}
	input.close();
	
	//create all particles
	for (int i = 0; i < rate; i++) {
		Particle p(handle, posX, posY, posZ, width, depth, minVel);
		particles.push_back(p);
	}
}

void ParticleSystem::draw(Camera camera, GLuint particleAge, GLuint shaderProgramHandle) {
	
	//sort all
	Point XZcamera = Point(camera.getX(),0.,camera.getZ());
	Point origin = Point(0,0,0);
	Vector viewVector = origin - XZcamera;
	std::vector< float > distances;
	
	std::vector< Point > particlePoints;
	
	
	for (unsigned int i = 0; i < particles.size(); i++) {
		Point p(particles[i].getPosX(), particles[i].getPosY(), particles[i].getPosZ());
		particlePoints.push_back(p);
	}

	
	//build distances vector
	for (int i = 0; i < particlePoints.size(); i++) {
		Vector spriteVector = particlePoints.at(i) - XZcamera;
		distances.push_back(dot(viewVector,spriteVector));
	}

	
	//sort treeSpritePositions using distances vector
	std::vector< Particle > t;
	
	while(distances.size() != 0 ) {
		double min = distances.at(0);
		int index = 0;
		for (unsigned int j = 1; j < distances.size(); j++) {
			if (distances.at(j) > min) {
				min = distances.at(j);
				index = j;
			}
		}
		t.push_back(particles.at(index));
		particles.erase(particles.begin()+index);
		distances.erase(distances.begin()+index);
	}

	
	particles = t;
	
	//draw each
	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw(camera, particleAge ,shaderProgramHandle);	// may need to pass in camera for rotation to face camera
	}
}

//updates each individual particle in the system
void ParticleSystem::update() {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].update();
	}
}