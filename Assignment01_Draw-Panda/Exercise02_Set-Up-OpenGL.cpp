// Course: IGME 309
// Student Name: Chase Martoccia
// Assignment: 01

#ifdef __APPLE__
#include <GLUT/glut.h>      // GLUT for macOS
#else
#include <GL/freeglut.h>    // FreeGLUT for Windows
#endif

#include <math.h>
#include <iostream>

using namespace std;

// Window size
int width, height;

//How many corners/segments every circle has
int segments = 100;

// Initialize application data.
void init(void)
{
    width = 600;
    height = 600;
}

void drawFilledCircle(float red, float green, float blue,
    float center_x, float center_y, float radius)
{
    glColor3f(red, green, blue);

    glBegin(GL_POLYGON);

    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.14159265f * i / segments;

        float x = radius * cos(theta) + center_x;
        float y = radius * sin(theta) + center_y;

        glVertex2f(x, y);
    }

    glEnd();
}

void drawWireframeCircle(float red, float green, float blue,
    float center_x, float center_y, float radius,
    float lineWidth)
{
    glLineWidth(lineWidth);

    glColor3f(red, green, blue);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.14159265f * i / segments;

        float x = radius * cos(theta) + center_x;
        float y = radius * sin(theta) + center_y;

        glVertex2f(x, y);
    }

    glEnd();
}




// Display callback: draw the current program state.
void display(void)
{
    // Clear the color buffer to white.
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //drawFilledCircle(1, 0, 0, 0, 0, 1);
    //drawWireframeCircle(1, 0, 0, 2, 2, 1, 3);
    
    drawFilledCircle(175.0f / 255.0f, 127.0f / 255.0f, 104.0f / 255.0f, -1.25, 1, 0.5);
    drawFilledCircle(175.0f / 255.0f, 127.0f / 255.0f, 104.0f / 255.0f, -1.25, 0.5, 0.5);
    drawFilledCircle(0.0f / 255.0f, 159.0f / 255.0f, 179.0f / 255.0f, -1.25, 1.5, 0.5);

    drawFilledCircle(175.0f / 255.0f, 127.0f / 255.0f, 104.0f / 255.0f, 1.25, 1, 0.5);
    drawFilledCircle(175.0f / 255.0f, 127.0f / 255.0f, 104.0f / 255.0f, 1.25, 0.5, 0.5);
    drawFilledCircle(0.0f / 255.0f, 159.0f / 255.0f, 179.0f / 255.0f, 1.25, 1.5, 0.5);

    drawFilledCircle(107.0f / 255.0f, 107.0f / 255.0f, 109.0f / 255.0f, 0, -1.25, 1);
    drawFilledCircle(71.0f/255.0f, 66.0f/255.0f, 169.0f/255.0f, 0, 0, 1);
    drawFilledCircle(71.0f / 255.0f, 66.0f / 255.0f, 169.0f / 255.0f, 0, -1, 1);
    drawFilledCircle(0.0f / 255.0f, 159.0f / 255.0f, 179.0f / 255.0f, 0, 1, 1);

    drawFilledCircle(175.0f / 255.0f, 127.0f / 255.0f, 104.0f / 255.0f, 0, 2.5, 0.75);
    drawFilledCircle(45.0f / 255.0f, 23.0f / 255.0f, 12.0f / 255.0f, -0.5, 3.25, 0.3);
    drawFilledCircle(45.0f / 255.0f, 23.0f / 255.0f, 12.0f / 255.0f, 0.5, 3.25, 0.3);
    drawFilledCircle(45.0f / 255.0f, 23.0f / 255.0f, 12.0f / 255.0f, 0, 3.25, 0.3);

    drawFilledCircle(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, -0.35, 2.5, 0.1);
    drawFilledCircle(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 0.35, 2.5, 0.1);
    drawFilledCircle(71.0f / 255.0f, 66.0f / 255.0f, 169.0f / 255.0f, -0.25, 2.5, 0.1);
    drawFilledCircle(71.0f / 255.0f, 66.0f / 255.0f, 169.0f / 255.0f, 0.25, 2.5, 0.1);

    glutSwapBuffers();
}


// Idle/update callback.
// We will implement continuous movement and delta time together in class.
void update()
{
    // -------------------------------------------------
    // Update the ball here.
    //
    // We will build this part together in class.
    // -------------------------------------------------


    // Request a new frame.
    glutPostRedisplay();
}


// Reshape callback: update projection and viewport when the window changes.
void reshape(int w, int h)
{
    width = w;
    height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glutPostRedisplay();
}


// Keyboard callback: ESC exits the program.
void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    if(key == 43)//43 is +
    {
        if (segments != 100)
        {
            segments++;
            cout << segments << endl;
        }
    }
    if(key == 45)//45 is -
    {
        if (segments != 3)
        {
            segments--;
            cout << segments << endl;
        }
    }
}


int main(int argc, char* argv[])
{

    // Initialize application data.
    init();
    // Initialize GLUT.
    glutInit(&argc, argv);



    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutCreateWindow("Bouncing Ball - Start");

    // Register callbacks with GLUT.
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(update);

    // Enter GLUT's event-processing loop.
    glutMainLoop();

    return 0;
}