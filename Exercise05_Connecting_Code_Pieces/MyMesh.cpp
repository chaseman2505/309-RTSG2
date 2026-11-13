// Course: IGME 309
// Student Name: Chase Martoccia
// Friday Exercise: 05
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif
#include "MyMesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

MyMesh::MyMesh()
{
    vertNum = triNum = 0;
    vertices = NULL;
    indices = NULL;
    vertColors = NULL;
    vbo_id = cbo_id = ibo_id = 0;
}

MyMesh::~MyMesh()
{
    if (vertices != NULL)
        delete[] vertices;
    if (indices != NULL)
        delete[] indices;
    if (vertColors != NULL)
        delete[] vertColors;
}


bool MyMesh::loadFromOBJ(const char* fileName)
{
    ifstream fs(fileName);
    if (!fs.is_open()) {
        cerr << "Cannot open " << fileName
             << ". Check the working directory / OBJ file location." << endl;
        return false;
    }
    vector<vec2> temp_verts;
    vector<uvec3> temp_tris;

    // BEGIN TASK A: adapt the lecture's line-by-line OBJ loader.

    // TODO A: use getline and istringstream. Read v into vec2,
    // and f into uvec3 after converting from 1-based indices.
    // Store results in temp_verts and temp_tris. Skip other rows.

    char c;
    vec2 pos;
    int index[3];
    int vid = 0;

    std::string line;
    while (std::getline(fs, line)) {
        std::istringstream iss(line);

        iss >> c;

        switch (c) {
        case 'v':
        {
            // read a vertex
            iss >> pos.x;
            iss >> pos.y;
            temp_verts.push_back(pos);
            break;
        }
        case 'f':
        {
            // read a triangle's vertex indices
            iss >> index[0];
            iss >> index[1];
            iss >> index[2];
            // NOTE: index in obj files starts from 1
            temp_tris.push_back(uvec3(index[0] - 1, index[1] - 1, index[2] - 1));
            break;
        }
        default:
            // skip the line
            break;
        }
    }
    fs.close();

    // END TASK A

    delete[] vertices;
    delete[] indices;
    delete[] vertColors;
    
    vertNum = static_cast<unsigned int>(temp_verts.size());
    triNum = static_cast<unsigned int>(temp_tris.size());
    vertices = new float[vertNum * 2];
    indices = new unsigned int[triNum * 3];
    vertColors = new float[vertNum * 3];
    
    for (unsigned int i = 0; i < vertNum; ++i) {
        vertices[i * 2] = temp_verts[i].x;
        vertices[i * 2 + 1] = temp_verts[i].y;
        for (unsigned int c = 0; c < 3; ++c)
            vertColors[i * 3 + c] = static_cast<float>(rand()) / RAND_MAX;
    }
    for (unsigned int i = 0; i < triNum; ++i) {
        indices[i * 3] = temp_tris[i].x;
        indices[i * 3 + 1] = temp_tris[i].y;
        indices[i * 3 + 2] = temp_tris[i].z;
    }
    return true;
}

void MyMesh::prepareBufferObjects()
{
    if (vertNum == 0 || triNum == 0) return;

    // BEGIN TASK B: upload positions and triangle indices.
    
    // TODO B: generate, bind, and upload the position VBO (vbo_id)
    // and index buffer (ibo_id). Use two floats per vertex and
    // three unsigned indices per triangle. Unbind each buffer.
    
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertNum * 2, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete[] vertices;

    glGenBuffers(1, &ibo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triNum * 3, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // clean up
    delete[] indices;

    // END TASK B

    // Provided: colors have three components even though positions have two.
    glGenBuffers(1, &cbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, cbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertNum * 3,
                 vertColors, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Retain CPU arrays for the immediate-mode checkpoint.
}

void MyMesh::draw()
{
    if (vertNum == 0 || triNum == 0 || vbo_id == 0 || ibo_id == 0) return;

    // Provided: color-array configuration.
    glBindBuffer(GL_ARRAY_BUFFER, cbo_id);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, NULL);

    // BEGIN TASK C: configure 2D positions and draw the indexed triangles.
    
    // TODO C: bind vbo_id, enable GL_VERTEX_ARRAY, and configure
    // two floats per position. Bind ibo_id and draw the triangles
    // with glDrawElements. NULL is offset zero in a bound buffer.
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
    glDrawElements(GL_TRIANGLES, triNum * 3, GL_UNSIGNED_INT, NULL);

    // END TASK C

    // Provided: leave OpenGL state ready for the next draw.
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MyMesh::drawImmediate()
{
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < triNum * 3; ++i) {
        glColor3fv(vertColors + indices[i] * 3);
        glVertex2fv(vertices + indices[i] * 2);
    }
    glEnd();
}
