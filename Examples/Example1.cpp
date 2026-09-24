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


float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;

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
    glClearColor(red, green, blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set text color to contrast dynamically with the background color
    glColor3f(1.0f - red, 1.0f - green, 1.0f - blue);

    // Display instructions on the screen
    drawText(-0.8f, 0.6f, "=== RGB BACKGROUND CONTROLLER ===");
    drawText(-0.8f, 0.4f, "[R] - Change to RED");
    drawText(-0.8f, 0.2f, "[G] - Change to GREEN");
    drawText(-0.8f, 0.0f, "[B] - Change to BLUE");
    drawText(-0.8f, -0.2f, "[W] - Change to WHITE");
    drawText(-0.8f, -0.4f, "[K] - Change to BLACK");
    drawText(-0.8f, -0.6f, "[ESC] - Exit Program");

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'r':
        case 'R':
            red = 1.0f;
            green = 0.0f;
            blue = 0.0f;
            cout << "Background: RED" << endl;
            break;

        case 'g':
        case 'G':
            red = 0.0f;
            green = 1.0f;
            blue = 0.0f;
            cout << "Background: GREEN" << endl;
            break;

        case 'b':
        case 'B':
            red = 0.0f;
            green = 0.0f;
            blue = 1.0f;
            cout << "Background: BLUE" << endl;
            break;

        case 'w':
        case 'W':
            red = 1.0f;
            green = 1.0f;
            blue = 1.0f;
            cout << "Background: WHITE" << endl;
            break;

        case 'k':
        case 'K':
            red = 0.0f;
            green = 0.0f;
            blue = 0.0f;
            cout << "Background: BLACK" << endl;
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(700, 500);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("Program 1 - RGB Background Controller with Text");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
