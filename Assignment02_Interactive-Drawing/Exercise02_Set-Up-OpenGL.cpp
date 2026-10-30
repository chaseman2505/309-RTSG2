#ifdef __APPLE__
#include <GLUT/glut.h>      // GLUT for macOS
#else
#include <GL/freeglut.h>    // FreeGLUT for Windows
#endif

#include <stdlib.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>
#include "PolyObject.h"
using namespace glm;
using namespace std;

// ******** Interactive Triangle ********
//
// Left-click:      select triangle vertices.
// Mouse movement:  update cursor position and preview the next edge.
// After 3 clicks:  draw the completed triangle.
// Right-click:     open a menu to change color, clear, or exit.

float canvasSize[] = { 10.0f, 10.0f }; // Logical canvas width, height.
int rasterSize[] = { 600, 600 };       // Window width, height in pixels.

int numOfVertices = 0;               // Number of selected vertices.
// Three 2D vertices: [x0,y0, x1,y1, x2,y2].
float v[2 * 3];
float color[3];                       // Current RGB drawing color.
float mousePos[2];                    // Mouse position in canvas coordinates.

//Dynamic array of polyObjects
vector <PolyObject> polyObjects;


void init(void)
{
    for (int i = 0; i < 6; i++) v[i] = 0.0f;
    mousePos[0] = mousePos[1] = 0.0f;
    color[0] = 1.0f;                  // Start with red.
    color[1] = color[2] = 0.0f;

    //Creates first polyObject
    polyObjects.emplace_back();
}

void drawCursor()
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2fv(mousePos);
    glEnd();
    glPointSize(1.0f);
}

// Display callback: redraws the current program state.
void display(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3fv(color);

    /*if (numOfVertices > 0 && numOfVertices < 3) {
        // Incomplete triangle: selected vertices + mouse position form a preview.
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < numOfVertices; i++) {
            // Each vertex occupies two floats; v+i*2 points to vertex i.
            glVertex2fv(v + i * 2);
        }
        glVertex2fv(mousePos);
        glEnd();
    }
    else if (numOfVertices == 3) {
        // Three vertices selected: draw the filled triangle.
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < numOfVertices; i++)
            glVertex2fv(v + i * 2);
        glEnd();
    }*/

    for (int j = 0; j < std::size(polyObjects); j++)
    {
        if (std::size(polyObjects[j].vertices) > 0 && std::size(polyObjects[j].vertices) < 3) {
            // Incomplete triangle: selected vertices + mouse position form a preview.
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < std::size(polyObjects[i].vertices); i++) {
                glVertex2fv(&polyObjects[j].vertices[i][0]);
                // Each vertex occupies two floats; v+i*2 points to vertex i.
                //glVertex2fv(v + i * 2);
            }
            glVertex2fv(mousePos);
            glEnd();
        }
        else if (numOfVertices == 3) {
            // Three vertices selected: draw the filled triangle.
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < numOfVertices; i++)
                glVertex2fv(v + i * 2);
            glEnd();
        }
    }


    drawCursor();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    rasterSize[0] = w;
    rasterSize[1] = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
    glViewport(0, 0, rasterSize[0], rasterSize[1]);
    glutPostRedisplay();
}

// Convert GLUT raster coordinates to our OpenGL canvas coordinates.
// GLUT mouse coordinates: origin top-left; y increases downward.
// Our canvas:            origin bottom-left; y increases upward.
void rasterToCanvas(int x, int y, float pos[2])
{
    pos[0] = (float)x / rasterSize[0] * canvasSize[0];
    pos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];
}

// Mouse-button callback.
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // A click after a completed triangle starts a new triangle.
        if (numOfVertices >= 3) numOfVertices = 0;

        rasterToCanvas(x, y, mousePos);

        // Store the next vertex as x,y in the flat array.
        v[numOfVertices * 2] = mousePos[0];
        v[numOfVertices * 2 + 1] = mousePos[1];
        numOfVertices++;

        //Adds a vertice to the most recent polyObject
        //polyObjects[std::size(polyObjects) - 1].addVertex(mousePos[0], mousePos[1]);
        polyObjects[0].addVertex(mousePos[0], mousePos[1]);

        glutPostRedisplay();
    }
}

// Passive-motion callback: mouse moves without a button pressed.
void motion(int x, int y)
{
    rasterToCanvas(x, y, mousePos);
    glutPostRedisplay(); // Update cursor and preview edge.
}

// Keyboard callback: ESC exits.
void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) exit(0);
}

// Right-click menu callback.
void menu(int value)
{
    switch (value) {
    case 0: // Clear
        numOfVertices = 0;
        glutPostRedisplay();
        break;
    case 1: // Exit
        exit(0);
        break;
    case 2: // Red
        color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 3: // Green
        color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 4: // Blue
        color[0] = 0.0f; color[1] = 0.0f; color[2] = 1.0f;
        glutPostRedisplay();
        break;
    }
}

void createMenu()
{
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);

    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 0);
    glutAddSubMenu("Colors", colorMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(rasterSize[0], rasterSize[1]);
    glutCreateWindow("Mouse Event - Draw a Triangle");

    // Register callbacks.
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);

    createMenu();
    glutMainLoop();
    return 0;
}