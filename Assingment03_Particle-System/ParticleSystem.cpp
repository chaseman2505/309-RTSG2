// Course: IGME 309
// Student Name: Chase Martoccia
// Assignment: 03

//Performance Results:
//Particle Count : Average FPS
//500 : 1,600
//5,000 : 1,500
//50,000 : 600
//500,000 : 100
//5,000,000 : 10

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include "ParticleSystem.h"

#include <iostream>
using namespace std;

ParticleSystem::ParticleSystem(int _numParticles)
{
	numParticles = 5000;	// Set the number of particles
	
	// Allocate memory for positions, velocities, colors, and lifetimes.
	positions = new float[numParticles * 3];
	velocities = new float[numParticles * 3];
	colors = new float[numParticles * 4];	
	lifeTimes = new float[numParticles];

	for (int i = 0; i < numParticles; i++) {
		// Initialize the life times
		lifeTimes[i] = maxLifeTime - maxLifeTime * i / numParticles;

		/***************************/
		// Write your code below
		// Please add initializations for other arrays as you see appropriate.
		positions[i * 3] = 0.0f;
		positions[i * 3 + 1] = 0.0f;
		positions[i * 3 + 2] = 0.0f;

		velocities[i * 3] = ParticleSystem::getRandomValue(minSpeedX, maxSpeedX);
		velocities[i * 3 + 1] = ParticleSystem::getRandomValue(minSpeedY, maxSpeedY);
		velocities[i * 3 + 2] = ParticleSystem::getRandomValue(minSpeedZ, maxSpeedZ);

		colors[i * 4] = 1.0f;
		colors[i * 4 + 1] = 0.0f;
		colors[i * 4 + 2] = 0.0f;
		colors[i * 4 + 3] = 1.0f;
		/***************************/
	}
}

void ParticleSystem::update(float deltaTime)
{
	for (int i = 0; i < numParticles; i++) {
		/***************************/
		// Write your code below
		// Update lifetime, velocity, position, and color.
		// Reset particle states (positions, velocities, colors, and lifetimes) when the lifetime reaches the maxLifeTime
		positions[i * 3] += velocities[i * 3] * deltaTime;
		positions[i * 3 + 1] += velocities[i * 3 + 1] * deltaTime;
		positions[i * 3 + 2] += velocities[i * 3 + 2] * deltaTime;

		velocities[i * 3] += acceleration[0] * deltaTime;
		velocities[i * 3 + 1] += acceleration[1] * deltaTime;
		velocities[i * 3 + 2] += acceleration[2] * deltaTime;

		colors[i * 4 + 3] = 1.0f - lifeTimes[i]/maxLifeTime;

		lifeTimes[i] += deltaTime;

		//Resets particle if max lifetime is reached
		if (lifeTimes[i] >= maxLifeTime)
		{
			positions[i * 3] = 0.0f;
			positions[i * 3 + 1] = 0.0f;
			positions[i * 3 + 2] = 0.0f;

			velocities[i * 3] = ParticleSystem::getRandomValue(minSpeedX, maxSpeedX);
			velocities[i * 3 + 1] = ParticleSystem::getRandomValue(minSpeedY, maxSpeedY);
			velocities[i * 3 + 2] = ParticleSystem::getRandomValue(minSpeedZ, maxSpeedZ);

			colors[i * 4 + 3] = 1.0f;

			lifeTimes[i] = 0.0f;
		}
		// Write your code above
		/***************************/
	}
}

void ParticleSystem::draw()
{
	/***************************/
	// Write your code below
	// Use GL_POINTS for rendering
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, positions);

	//Base size of points
	glPointSize(100.0f);

	//Scales point size based on distance from the camera/viewer
	GLfloat attenuation[] = { 0.0f, 0.0f, 1.0f };
	glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuation);

	glMatrixMode(GL_MODELVIEW);

	glDrawArrays(GL_POINTS, 0, numParticles);

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	// Write your code above
	/***************************/
}

float ParticleSystem::getRandomValue(float min_value, float max_value)
{
	return min_value + (std::rand()) / (RAND_MAX / (max_value - min_value));;
}
