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

int shape = 1;

float red = 0.0f;
float green = 0.7f;
float blue = 1.0f;

// Function to draw bitmap text on the screen
void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawTriangle()
{
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(-0.4f, -0.3f);
        glVertex2f(0.4f, -0.3f);
    glEnd();
}

void drawSquare()
{
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, -0.3f);
        glVertex2f(0.3f, -0.3f);
        glVertex2f(0.3f, 0.3f);
        glVertex2f(-0.3f, 0.3f);
    glEnd();
}

void drawDiamond()
{
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.4f, 0.0f);
        glVertex2f(0.0f, -0.4f);
        glVertex2f(-0.4f, 0.0f);
    glEnd();
}

void display()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set text color to white for contrast against dark background
    glColor3f(1.0f, 1.0f, 1.0f);

    // Display instruction text panel
    drawText(-0.9f, 0.82f, "=== SHAPE & COLOR SELECTOR ===");
    drawText(-0.9f, 0.72f, "[1] - Triangle  |  [R] - Red Color");
    drawText(-0.9f, 0.62f, "[2] - Square    |  [G] - Green Color");
    drawText(-0.9f, 0.52f, "[3] - Diamond   |  [B] - Blue Color");
    drawText(-0.9f, 0.42f, "[ESC] - Exit Program");

    // Set shape color based on user selection
    glColor3f(red, green, blue);

    if (shape == 1)
        drawTriangle();
    else if (shape == 2)
        drawSquare();
    else if (shape == 3)
        drawDiamond();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
            shape = 1;
            cout << "Triangle selected" << endl;
            break;

        case '2':
            shape = 2;
            cout << "Square selected" << endl;
            break;

        case '3':
            shape = 3;
            cout << "Diamond selected" << endl;
            break;

        case 'r':
        case 'R':
            red = 1.0f;
            green = 0.0f;
            blue = 0.0f;
            cout << "Color: RED" << endl;
            break;

        case 'g':
        case 'G':
            red = 0.0f;
            green = 1.0f;
            blue = 0.0f;
            cout << "Color: GREEN" << endl;
            break;

        case 'b':
        case 'B':
            red = 0.0f;
            green = 0.0f;
            blue = 1.0f;
            cout << "Color: BLUE" << endl;
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(700, 600);

    glutCreateWindow("Program 3 - Interactive Shape Selector with Text");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
