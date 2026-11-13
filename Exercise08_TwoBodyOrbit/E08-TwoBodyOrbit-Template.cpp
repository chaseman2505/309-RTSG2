#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cmath>
#include <cstdlib>

// Course:       IGME 309
// Student Name: Chase Martoccia
// Friday Exercise: 08

// ============================================================
// E08 - Self-Rotation and Revolution
//
// Body A:
//   - stays at the origin
//   - rotates about its own center
//
// Body B:
//   - revolves around Body A
//   - also rotates about its own center
//
// NOTE:
// Body B's orbital rotation also affects its orientation.
// This is expected. You only need to add Body B's
// self-rotation on top of the orbital rotation.
// ============================================================


// Window / canvas
int width = 800;
int height = 800;

const float canvasMin = -4.0f;
const float canvasMax =  4.0f;


// Circle drawing
const float PI = 3.14159265f;
const int circleVertices = 100;


// Body sizes and orbit radius
const float bodyARadius = 0.55f;
const float bodyBRadius = 0.30f;

const float bodyBOrbitRadius = 2.5f;


// Angular speeds in degrees / second
const float bodyASelfSpeed  =  120.0f;  // degree/sec
const float bodyBSelfSpeed  = -180.0f;  // degree/sec, opposite direction
const float bodyBOrbitSpeed =   30.0f;  // degree/sec


// Current rotation angles
float bodyASelfAngle  = 0.0f;
float bodyBSelfAngle  = 0.0f;
float bodyBOrbitAngle = 0.0f;


// Timing
unsigned int previousTime = 0;


// ------------------------------------------------------------
// Draw a solid circle using 100 perimeter vertices.
//
// Two colors are used so the body's orientation and
// self-rotation are easy to see.
// ------------------------------------------------------------
void drawTwoColorCircle( float radius, float r1, float g1, float b1, float r2, float g2, float b2)
{
    glBegin(GL_TRIANGLE_FAN);

    // Center vertex
    glColor3f(r1, g1, b1);
    glVertex2f(0.0f, 0.0f);

    // Circle boundary
    for (int i = 0; i <= circleVertices; i++)
    {
        float theta = 2.0f * PI * i / circleVertices;

        // Use the second color for part of the circle.
        // This makes the orientation visually distinguishable.
        if (i >= 8 && i <= 38)
            glColor3f(r2, g2, b2);
        else
            glColor3f(r1, g1, b1);

        glVertex2f(radius * cos(theta), radius * sin(theta));
    }

    glEnd();
}


// Body A: warm orange / yellow
void drawBodyA()
{
    drawTwoColorCircle(bodyARadius, 1.0f, 0.55f, 0.08f, 1.0f, 0.90f, 0.20f);
}


// Body B: blue / green
void drawBodyB()
{
    drawTwoColorCircle(bodyBRadius, 0.10f, 0.35f, 0.90f, 0.15f, 0.75f, 0.30f);
}


void update()
{
    unsigned int currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    // deltaTime is provided in seconds.
    float deltaTime = (currentTime - previousTime) / 1000.0f;

    previousTime = currentTime;


    // --------------------------------------------------------
    // TODO:
    //
    // Update the three angles using their corresponding
    // angular speeds and deltaTime:
    //
    //   bodyASelfAngle
    //   bodyBSelfAngle
    //   bodyBOrbitAngle
    //
    // Remember:
    //   change in angle = angular speed * deltaTime
    // --------------------------------------------------------
    
    bodyASelfAngle += bodyASelfSpeed * deltaTime;
    bodyBSelfAngle += bodyBSelfSpeed * deltaTime;
    bodyBOrbitAngle += bodyBOrbitSpeed * deltaTime;

    glutPostRedisplay();
}


void display()
{
    glClearColor(0.03f, 0.03f, 0.07f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // --------------------------------------------------------
            // TODO:
            //
            // Complete the transformations so that:
            //
            //   1. Body A stays at the center and rotates about
            //      its own center using bodyASelfAngle.
            //
            //   2. After drawing Body A, restore the coordinate
            //      system before applying Body B's transformations.
            //      You may reverse the transformation or use
            //      glPushMatrix() / glPopMatrix().
            //
            //   3. Body B revolves around Body A using
            //      bodyBOrbitAngle and bodyBOrbitRadius.
            //
            //   4. Body B also rotates about its own center using
            //      bodyBSelfAngle.
            //
            // NOTE:
            // The three statements below are provided only so the
            // starter program displays both bodies and shows their
            // relative distance before you implement the animation.
            //
            // You may add, remove, reorder, or modify transformation
            // statements as needed to complete the requirements.
            // --------------------------------------------------------
    
    glPushMatrix();
    glRotatef(bodyASelfAngle, 0.0f, 0.0f, 1.0f);

    drawBodyA();
    glPopMatrix();
    glRotatef(bodyBOrbitAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(bodyBOrbitRadius, 0.0f, 0.0f);
    glRotatef(bodyBSelfAngle, 0.0f, 0.0f, 1.0f);
    drawBodyB();

    glutSwapBuffers();
}


void reshape(int w, int h)
{
    width = w;
    height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(canvasMin, canvasMax, canvasMin, canvasMax);
    glViewport(0, 0, width, height);

    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) // ESC
        exit(0);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width,height);
    glutCreateWindow("E08 - Self-Rotation and Revolution");

    // Initialize timing before animation begins.
    previousTime = glutGet(GLUT_ELAPSED_TIME);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(update);

    glutMainLoop();

    return 0;
}
