
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "MyMesh.h"

#include <iostream>
#include <time.h>
using namespace std;

MyMesh::MyMesh()
{
	vertNum = triNum = 0;
	vertices = NULL;
	indices = NULL;
	vertColors = NULL;
	vbo_id = ibo_id = cbo_id = 0;
}

MyMesh::~MyMesh()
{
	//Don't forget to deallocate the buffer objects from the GPU when your program is shut down!
	glDeleteBuffers(1, &vbo_id);
	glDeleteBuffers(1, &cbo_id);
	glDeleteBuffers(1, &ibo_id);
}

void MyMesh::prepareBufferObjects()
{
	// prepare VBO
	// generate a new VBO and get the associated ID
	glGenBuffers(1, &vbo_id);

	// bind VBO in order to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

	// upload data to VBO - data went to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertNum * 2, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // clean up

	// it is safe to delete after copying data to VBO
	// for example, if vertices array was dynamically created, it is saft to call "delete [ ] vertices;"
	delete[] vertices;

	// repeat for colors and indices

	glGenBuffers(1, &cbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, cbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertNum * 3, vertColors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // clean up
	delete[] vertColors;

	glGenBuffers(1, &ibo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triNum * 3, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // clean up
	delete[] indices;

	// by now, we moved the position and index data to GPU. There will be no redundant data copy at drawing time
}

void MyMesh::load(char* fileName)
{

}

void MyMesh::load(const unsigned int p_vertNum, const unsigned int p_triNum, const float* p_vertices, const unsigned int* p_indices)
{
	vertNum = p_vertNum;
	triNum = p_triNum;

	vertices = new float[vertNum*2];
	indices = new unsigned int[triNum*3];
	vertColors = new float[vertNum * 3]; 

	for (unsigned int i = 0; i < vertNum*2; i++) {
		vertices[i] = p_vertices[i];
	}

	for (unsigned int i = 0; i < triNum * 3; i++) {
		indices[i] = p_indices[i];
	}

	// generate random vertex colors

	time_t t;
	srand((unsigned)time(&t));
	for (unsigned int i = 0; i < vertNum; i++) {
		vertColors[i * 3 + 0] = float(rand()) / (RAND_MAX + 1); 
		vertColors[i * 3 + 1] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 2] = float(rand()) / (RAND_MAX + 1);
	}

	prepareBufferObjects();
}

void MyMesh::update()
{
	// we will use this for transformations later.... 
}

void MyMesh::draw()
{
		glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, cbo_id);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
		glDrawElements(GL_TRIANGLES, triNum*3, GL_UNSIGNED_INT, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}