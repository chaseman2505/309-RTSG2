// Course: IGME 309
// Student Name: YOUR NAME
// Friday Exercise: 05
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif
#include "MyMesh.h"
#include <iostream>
using namespace std;

MyMesh g_mesh;
const char* meshFile = "data2.obj"; // you can change the path, but please use relative path
bool useVBO = true;                // Set false for the loader checkpoint.

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (useVBO) g_mesh.draw();
    else g_mesh.drawImmediate();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    // Keep the 0..10 canvas square when the window is resized.
    int side = w < h ? w : h;
    glViewport((w - side) / 2, (h - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 10.0, 0.0, 10.0);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int, int)
{
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutCreateWindow("E05 - Connecting Code Pieces - 2D Mesh");
    
// For using VBO, glewInit() is needed in Windows. 
#ifndef __APPLE__
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        std::cerr << "GLEW initialization failed." << std::endl;
        return 1;
    }
#endif
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    if (!g_mesh.loadFromOBJ(meshFile)) {
        cerr << "Mesh loading failed." << endl;
        return 1;
    }
    cout << meshFile << ": " << g_mesh.getVertNum() << " vertices, " << g_mesh.getTriNum() << " triangles" << endl;
    if (useVBO) g_mesh.prepareBufferObjects();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
