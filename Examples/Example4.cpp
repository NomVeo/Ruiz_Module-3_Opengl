#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

float carX = 0.0f;

float carR = 0.0f;
float carG = 0.5f;
float carB = 1.0f;

// Function to draw bitmap text on the screen
void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawCar()
{
    // Car body
    glColor3f(carR, carG, carB);
    glBegin(GL_QUADS);
        glVertex2f(carX - 0.4f, -0.2f);
        glVertex2f(carX + 0.4f, -0.2f);
        glVertex2f(carX + 0.4f, 0.1f);
        glVertex2f(carX - 0.4f, 0.1f);
    glEnd();

    // Car roof
    glBegin(GL_POLYGON);
        glVertex2f(carX - 0.25f, 0.1f);
        glVertex2f(carX - 0.1f,  0.35f);
        glVertex2f(carX + 0.2f,  0.35f);
        glVertex2f(carX + 0.3f,  0.1f);
    glEnd();

    // Wheels
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(35.0f);
    glBegin(GL_POINTS);
        glVertex2f(carX - 0.25f, -0.25f);
        glVertex2f(carX + 0.25f, -0.25f);
    glEnd();
}

void display()
{
    glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set text color to dark gray/black for contrast against the light blue background
    glColor3f(0.1f, 0.1f, 0.1f);

    // Display instructions on the screen
    drawText(-0.9f, 0.82f, "=== CAR CONTROLLER INSTRUCTIONS ===");
    drawText(-0.9f, 0.72f, "[A] / [D] - Move Car Left / Right");
    drawText(-0.9f, 0.62f, "[H]       - Home / Center Car");
    drawText(-0.9f, 0.52f, "[R] / [G] / [B] - Change Car Color (Red/Green/Blue)");
    drawText(-0.9f, 0.42f, "[ESC]     - Exit Program");

    // Draw the interactive car
    drawCar();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
            carX -= 0.05f;
            break;

        case 'd':
        case 'D':
            carX += 0.05f;
            break;

        case 'h':
        case 'H':
            carX = 0.0f;
            break;

        case 'r':
        case 'R':
            carR = 1.0f;
            carG = 0.0f;
            carB = 0.0f;
            break;

        case 'g':
        case 'G':
            carR = 0.0f;
            carG = 1.0f;
            carB = 0.0f;
            break;

        case 'b':
        case 'B':
            carR = 0.0f;
            carG = 0.0f;
            carB = 1.0f;
            break;

        case 27:
            exit(0);
    }

    if (carX > 0.55f)
        carX = 0.55f;

    if (carX < -0.55f)
        carX = -0.55f;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(900, 600);

    glutCreateWindow("Program 4 - Keyboard Car Controller with Text");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
