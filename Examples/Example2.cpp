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

float squareX = 0.0f;
float squareY = 0.0f;


// Function to draw bitmap text on the screen
void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void display()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set text color to white for contrast against the dark background
    glColor3f(1.0f, 1.0f, 1.0f);

    // Display movement instructions on the screen
    drawText(-0.9f, 0.82f, "=== SQUARE CONTROLLER ===");
    drawText(-0.9f, 0.72f, "[W] / [S] - Move Up / Down");
    drawText(-0.9f, 0.62f, "[A] / [D] - Move Left / Right");
    drawText(-0.9f, 0.52f, "[R]       - Reset Position");
    drawText(-0.9f, 0.42f, "[ESC]     - Exit Program");

    // Draw the movable square
    glColor3f(0.0f, 0.7f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(squareX - 0.1f, squareY - 0.1f);
        glVertex2f(squareX + 0.1f, squareY - 0.1f);
        glVertex2f(squareX + 0.1f, squareY + 0.1f);
        glVertex2f(squareX - 0.1f, squareY + 0.1f);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            squareY += 0.05f;
            break;

        case 's':
        case 'S':
            squareY -= 0.05f;
            break;

        case 'a':
        case 'A':
            squareX -= 0.05f;
            break;

        case 'd':
        case 'D':
            squareX += 0.05f;
            break;

        case 'r':
        case 'R':
            squareX = 0.0f;
            squareY = 0.0f;
            break;

        case 27:
            exit(0);
    }
    // Prevent square from leaving screen
    if (squareX > 0.9f)
        squareX = 0.9f;

    if (squareX < -0.9f)
        squareX = -0.9f;

    if (squareY > 0.9f)
        squareY = 0.9f;

    if (squareY < -0.9f)
        squareY = -0.9f;

    cout << "Position: "
         << squareX << ", "
         << squareY << endl;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(700, 700);

    glutCreateWindow("Program 2 - Keyboard Controlled Square with Text");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
