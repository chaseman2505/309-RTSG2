#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>
using namespace std;

#define MAX_NUM_PARTS 16
#define CIRCLE_RADIUM 2.0

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;


unsigned int currentKey = MAX_NUM_PARTS - 1;
int buttonState;
float colors[3* MAX_NUM_PARTS];
float translations[2* MAX_NUM_PARTS];
float rotations[MAX_NUM_PARTS];

float curMouse[2];
float preMouse[2];

void init(void)
{
    for(int i=0; i< MAX_NUM_PARTS; i++) {
        colors[i*3+0] = 0.0f; // red
        colors[i*3+1] = 0.0f; // green
        colors[i*3+2] = 0.0f; // blue

        rotations[i] = 0.0f;
    }

    buttonState = -1;

    translations[0 * 2 + 0] = 0.0f; // x
    translations[0 * 2 + 1] = 0.0f; // y
    translations[1 * 2 + 0] = 0.0f; // x
    translations[1 * 2 + 1] = 1.75f; // y
    translations[2 * 2 + 0] = 0.0f; // x
    translations[2 * 2 + 1] = 1.5f; // y
    translations[3 * 2 + 0] = 0.0f; // x
    translations[3 * 2 + 1] = 1.25f; // y
    translations[4 * 2 + 0] = -2.125f; // x
    translations[4 * 2 + 1] = 0.5f; // y
    translations[5 * 2 + 0] = -1.5f; // x
    translations[5 * 2 + 1] = 0.0f; // y
    translations[6 * 2 + 0] = -1.25f; // x
    translations[6 * 2 + 1] = 0.0f; // y
    translations[7 * 2 + 0] = 2.125f; // x
    translations[7 * 2 + 1] = 0.5f; // y
    translations[8 * 2 + 0] = 1.5f; // x
    translations[8 * 2 + 1] = 0.0f; // y
    translations[9 * 2 + 0] = 1.25f; // x
    translations[9 * 2 + 1] = 0.0f; // y
    translations[10 * 2 + 0] = -0.75f; // x
    translations[10 * 2 + 1] = -1.5f; // y
    translations[11 * 2 + 0] = 0.0f; // x
    translations[11 * 2 + 1] = -1.5f; // y
    translations[12 * 2 + 0] = -0.25f; // x
    translations[12 * 2 + 1] = -1.25f; // y
    translations[13 * 2 + 0] = 0.75f; // x
    translations[13 * 2 + 1] = -1.5f; // y
    translations[14 * 2 + 0] = 0.0f; // x
    translations[14 * 2 + 1] = -1.5f; // y
    translations[15 * 2 + 0] = 0.25f; // x
    translations[15 * 2 + 1] = -1.25f; // y
    
}

//Draws a box at the origin (before any transformation)
void drawBox(float length, float height, const float* c)
{
    glColor3fv(c);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-length/2, -height/2);
    glVertex2f(length/2, -height/2);
    glVertex2f(length/2, height/2);
    glVertex2f(-length/2, height/2);
    glEnd();
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // the following codes could be written in a for loop.
    // Here I expand them so that you can better trace the changes of cirlce's coordinate system.
    
    int pid = -1; // the index of current part
    // part 0
    pid = 0;
    glTranslatef(translations[pid*2+0], translations[pid*2+1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glPushMatrix();
    drawBox(2, 1.5, colors + pid * 3);
    
    // part 1
    pid = 1;
    glTranslatef(translations[pid*2+0], translations[pid*2+1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glPushMatrix();
    drawBox(2.75, 2, colors + pid * 3);
    
    // part 2
    pid = 2;
    glTranslatef(translations[pid*2+0], translations[pid*2+1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1, 1, colors + pid * 3);
    
    // part 3
    pid = 3;
    glTranslatef(translations[pid*2+0], translations[pid*2+1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(2, 1.5, colors + pid * 3);
    
    // part 4
    glPopMatrix();
    pid = 4;
    glTranslatef(translations[pid*2+0], translations[pid*2+1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1.5, 1, colors + pid * 3);
    
    // part 5
    pid = 5;
    glTranslatef(translations[pid*2+0], translations[pid*2+1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1.5, 1, colors + pid * 3);

    // part 6
    pid = 6;
    glTranslatef(translations[pid * 2 + 0], translations[pid * 2 + 1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1, 1, colors + pid * 3);

    // part 7
    glPopMatrix();
    pid = 7;
    glTranslatef(translations[pid * 2 + 0], translations[pid * 2 + 1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1.5, 1, colors + pid * 3);

    // part 8
    pid = 8;
    glTranslatef(translations[pid * 2 + 0], translations[pid * 2 + 1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1.5, 1, colors + pid * 3);

    // part 9
    pid = 9;
    glTranslatef(translations[pid * 2 + 0], translations[pid * 2 + 1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1, 1, colors + pid * 3);

    // part 10
    glPopMatrix();
    pid = 10;
    glTranslatef(translations[pid * 2 + 0], translations[pid * 2 + 1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1, 1.5, colors + pid * 3);

    // part 11
    pid = 11;
    glTranslatef(translations[pid * 2 + 0], translations[pid * 2 + 1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1, 1.5, colors + pid * 3);

    // part 12
    pid = 12;
    glTranslatef(translations[pid * 2 + 0], translations[pid * 2 + 1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1.5, 1, colors + pid * 3);

    // part 13
    glPopMatrix();
    pid = 13;
    glTranslatef(translations[pid * 2 + 0], translations[pid * 2 + 1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1, 1.5, colors + pid * 3);

    // part 14
    pid = 14;
    glTranslatef(translations[pid * 2 + 0], translations[pid * 2 + 1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1, 1.5, colors + pid * 3);

    // part 15
    pid = 15;
    glTranslatef(translations[pid * 2 + 0], translations[pid * 2 + 1], 0.0f);
    glRotatef(rotations[pid], 0.0f, 0.0f, 1.0f);
    drawBox(1.5, 1, colors + pid * 3);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    win_width =  w;
    win_height = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width/2.0f, canvas_width/2.0f, -canvas_height/2.0f, canvas_height/2.0f);
    glViewport(0, 0, (GLsizei) win_width, (GLsizei) win_height);
    
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) // 'esc' key
        exit(0);
    /*unsigned char asciiOffset = 49; // see an ascii table
    for(unsigned char i = '1'; i<'7'; i++) {
        if(key == i) {
            keyStates[i] = true;
            colors[(i-asciiOffset)*3+0] = 1.0f;
            colors[(i-asciiOffset)*3+1] = 0.0f;
            colors[(i-asciiOffset)*3+2] = 0.0f;
        }
    }*/
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
    //unsigned char asciiOffset = 49; // see an ascii table
    /*for (unsigned char i = '1'; i<'7'; i++) {
        if(key == i) {
            keyStates[i] = false;
            colors[(i-asciiOffset)*3+0] = 0.0f;
            colors[(i-asciiOffset)*3+1] = 0.0f;
            colors[(i-asciiOffset)*3+2] = 0.0f;
        }
    }*/
    if (key == 119) {
        colors[currentKey * 3 + 0] = 0.0f;
        colors[currentKey * 3 + 1] = 0.0f;
        colors[currentKey * 3 + 2] = 0.0f;
        if (currentKey + 1 >= MAX_NUM_PARTS) {
            currentKey = 0;
        }
        else {
            currentKey++;
        }
        colors[currentKey * 3 + 0] = 1.0f;
        colors[currentKey * 3 + 1] = 0.0f;
        colors[currentKey * 3 + 2] = 0.0f;
    }
    if (key == 115) {
        colors[currentKey * 3 + 0] = 0.0f;
        colors[currentKey * 3 + 1] = 0.0f;
        colors[currentKey * 3 + 2] = 0.0f;
        if (currentKey == 0)
        {
            currentKey = MAX_NUM_PARTS - 1;
        }
        else {
            currentKey--;
        }
        colors[currentKey * 3 + 0] = 1.0f;
        colors[currentKey * 3 + 1] = 0.0f;
        colors[currentKey * 3 + 2] = 0.0f;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN) {
        buttonState = button;
        curMouse[0] = ((float)x/win_width - 0.5f)*canvas_width;
        curMouse[1] = ((float)(win_height - y)-0.5f)/win_height*canvas_height;
        preMouse[0] = ((float)x/win_width - 0.5f)*canvas_width;
        preMouse[1] = ((float)(win_height - y)-0.5f)/win_height*canvas_height;
    }
    else if (state == GLUT_UP)
        button = -1;
}

void motion(int x, int y)
{
    unsigned char asciiOffset = 49; // see an ascii table
    
    curMouse[0] = ((float)x/win_width - 0.5f)*canvas_width;
    curMouse[1] = ((float)(win_height - y)-0.5f)/win_height*canvas_height;
    
    if(buttonState == GLUT_RIGHT_BUTTON) {
        translations[currentKey*2+0] += curMouse[0] - preMouse[0];
        translations[currentKey*2+1] += curMouse[1] - preMouse[1];
        glutPostRedisplay();
    }
    
    else if (buttonState == GLUT_LEFT_BUTTON) {
        rotations[currentKey] += (curMouse[0] - preMouse[0]) * 10;
        glutPostRedisplay();
    }
    
    preMouse[0] = curMouse[0];
    preMouse[1] = curMouse[1];
    
}

int main(int argc, char *argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("2D Transformation Tree");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
    
}
