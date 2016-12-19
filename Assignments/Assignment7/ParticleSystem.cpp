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

ParticleSystem::ParticleSystem(char* c) {
	//read in file setting variables for system
	ifstream input;
	input.open(c);
	if (input.is_open()) {
		int n;
		input >> n;
		for (int i = 0; i < n; i++) {
			float x,z;
			input >> x >> z;
			Particle p(x,5.0,z);
			particles.push_back(p);
		}
	}
	input.close();
}

void ParticleSystem::draw() {
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
}

//updates each individual particle in the system
bool ParticleSystem::update(float x, float z) {
	
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i].update(x,z);
		Point hero(x,0.0,z);
		Point l1(particles[i].getPosX(),particles[i].getPosY(),particles[i].getPosZ());
		if ( (l1-hero).mag() < 5 ) {
			
			return true;
		}
	}
	
	//collision between enemies
	for (unsigned int i = 0; i < particles.size(); i++) {
		for (unsigned int j = 0; j < particles.size(); j++) {
			if (i != j) {	
				Point l1(particles[i].getPosX(),particles[i].getPosY(),particles[i].getPosZ());
				Point l2(particles[j].getPosX(),particles[j].getPosY(),particles[j].getPosZ());
				if ( (l1-l2).mag() < 5.0 ) {
					
					particles[i].health--;
					particles[j].health--;
					
					if (particles[i].health == 0) {
						particles.erase(particles.begin()+i);
					}
					if (particles[j].health == 0) {
						particles.erase(particles.begin()+j);
					}
					
					particles[i].moveBackward();
					particles[j].moveBackward();
					
					Vector normalI = (l2 - l1);	
					Vector normalJ = (l1 - l2);	//compute normal vectors using location of each ball
					
					Vector dI = particles[i].toHero;
					Vector dJ = particles[j].toHero;	//temp direction variables to make direction calculation more readable
					
					particles[i].toHero = dI - (2*dot(dI,normalI)*normalI);
					particles[j].toHero = dJ - (2*dot(dJ,normalJ)*normalJ);	//using same equation for recalculating direction using normal vectors
					
					particles[i].moveForward();
					particles[j].moveForward();
				}
			}
		}
	}
	
	return false;
	
}