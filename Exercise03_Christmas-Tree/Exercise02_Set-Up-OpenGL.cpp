// Course: 		IGME 309
// Student Name: 	Chase Martoccia
// Friday Exercise: 	03

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

// ******** Event-Driven Graphics Program Pipeline ********
//
// main()
//   |
//   +-- initialize application / GLUT
//   +-- create window
//   +-- register callback functions
//   |
//   +-- glutMainLoop()
//         |
//         +-- window resize --> reshape()
//         |                       |
//         |                       +-- projection
//         |                       +-- viewport
//         |
//         +-- redraw ---------> display()
//                                |
//                                +-- clear buffer
//                                +-- draw primitives
//                                +-- swap buffers


// the window's width and height
int width, height;

// the 3 vertices for the trunk
float trunkv0[2];
float trunkv1[2];
float trunkv2[2];

// the vertices for each leaf
//10 leaves, each leaf has 3 vertices, each vertice has a x and 
int leafCount = 10;
float leaves[10][3][2];


void createTriangle()
{
    // initialize the trunk's vertices
    trunkv0[0] = 4.0f;
    trunkv0[1] = 1.0f;
    trunkv1[0] = 6.0f;
    trunkv1[1] = 1.0f;
    trunkv2[0] = 5.0f;
    trunkv2[1] = 9.0f;


    float spacing = 0.6;
    // initialize each leaf's vertices
    for (int i = 0; i < 10; i++)
    {
        leaves[i][0][0] = 3.0f;
        leaves[i][0][1] = 2.0f + i * spacing;
        leaves[i][1][0] = 7.0f;
        leaves[i][1][1] = 2.0f + i * spacing;
        leaves[i][2][0] = 5.0f;
        leaves[i][2][1] = 4.0f + i * spacing;
    }
}

void init(void)
{
    // initialize the size of the window
    width = 600;
    height = 600;
    createTriangle();
}

// Display callback: called by GLUT when the window needs to be redrawn.
void display(void)
{
    // Set the color used when clearing the color buffer (white).
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Clear the color buffer using the current clear color.
    glClear(GL_COLOR_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // specify the color for drawing
    glColor3f(0.5f, 0.25f, 0.0f);

    // Immediate-mode OpenGL: vertices specified between glBegin() and glEnd()
    // are interpreted according to the primitive type given to glBegin().
    glBegin(GL_TRIANGLES);
    // Three vertices define one triangle.
    glVertex2fv(trunkv0);
    glVertex2fv(trunkv1);
    glVertex2fv(trunkv2);

    glColor3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i < leafCount; i++)
    {
        glVertex2fv(leaves[i][0]);
        glVertex2fv(leaves[i][1]);
        glVertex2fv(leaves[i][2]);
    }

    glEnd();

    // Set the drawing color to blue
    glColor3f(1.0f, 1.0f, 0.0f);

    // Draw a blue point at the origin (0, 0)
    glPointSize(30.0f);
    glBegin(GL_POINTS);
    glVertex2f(5.0f, 9.5f);
    glEnd();
    glPointSize(1.0f);

    // Swap the back buffer with the front buffer.
    // We draw the new frame into the back buffer, then swap it to the screen.
    glutSwapBuffers();
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
    // Update the current window dimensions.
    width = w;
    height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Define a 2D orthographic viewing region.
    // The visible canvas coordinates range from 0 to 10 in both x and y.
    gluOrtho2D(0.0f, 10.0f, 0.0f, 10.0f);
    //gluOrtho2D(-5.0f, 5.0f, -5.0f, 5.0f);

    // Map the rendered image to the entire window.
    // glViewport(x, y, width, height) uses window/pixel coordinates.
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    //glViewport((GLsizei) width/2, (GLsizei) height/2, (GLsizei) width, (GLsizei) height);

    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    // Initialize application data before creating the GLUT window
    init();

    // Initialize GLUT and allow it to process GLUT-specific command-line arguments
    glutInit(&argc, argv);

    // Use double buffering: render into a back buffer and swap it
    // with the front buffer when a frame is complete.
    // Request an RGBA color buffer: Red, Green, Blue, and Alpha.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    //set the initial window size */
    glutInitWindowSize((int)width, (int)height);

    // create the window with a title
    glutCreateWindow("First OpenGL Program");

    // Register reshape() as the callback for window creation/resizing.
    glutReshapeFunc(reshape);

    // Register display() as the callback used when the window needs to be redrawn.
    glutDisplayFunc(display);

    // Enter GLUT's event-processing loop.
    // GLUT now responds to events and calls our registered callback functions.
    glutMainLoop();

    return 0;
}