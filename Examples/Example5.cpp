#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

float playerX = 0.0f;
float playerY = 0.0f;

float targetX = 0.6f;
float targetY = 0.5f;

int score = 0;

void drawBitmapString(void* font, const char* str)

{
    for (const char* c = str; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void drawPlayer()
{
    glColor3f(0.0f, 0.6f, 1.0f);

    glBegin(GL_QUADS);
        glVertex2f(playerX - 0.08f, playerY - 0.08f);
        glVertex2f(playerX + 0.08f, playerY - 0.08f);
        glVertex2f(playerX + 0.08f, playerY + 0.08f);
        glVertex2f(playerX - 0.08f, playerY + 0.08f);
    glEnd();
}

void drawTarget()
{
    glColor3f(1.0f, 0.8f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(targetX - 0.07f, targetY - 0.07f);
        glVertex2f(targetX + 0.07f, targetY - 0.07f);
        glVertex2f(targetX + 0.07f, targetY + 0.07f);
        glVertex2f(targetX - 0.07f, targetY + 0.07f);
    glEnd();
}

void drawHUD()
{
    char buffer[50];

    // Draw Score
    snprintf(buffer, sizeof(buffer), "Score: %d", score);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.9f, 0.9f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    // Draw On-Screen Instructions Panel
    glColor3f(0.8f, 0.8f, 0.8f); // Slightly softer white for instructions
    glRasterPos2f(-0.9f, 0.76f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "=== CONTROLS ===");
    glRasterPos2f(-0.9f, 0.66f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "[W][A][S][D] - Move Player");
    glRasterPos2f(-0.9f, 0.56f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "[R]          - Restart Game");
    glRasterPos2f(-0.9f, 0.46f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "[ESC]        - Exit Program");
}

bool collision()
{
    float distanceX = playerX - targetX;
    float distanceY = playerY - targetY;

    if (distanceX < 0)
        distanceX = -distanceX;

    if (distanceY < 0)
        distanceY = -distanceY;

    return distanceX < 0.15f &&
           distanceY < 0.15f;
}

void moveTarget()
{
    int position = score % 6;

    switch (position)
    {
        case 0:
            targetX = 0.6f;
            targetY = 0.5f;
            break;

        case 1:
            targetX = -0.6f;
            targetY = 0.5f;
            break;

        case 2:
            targetX = 0.6f;
            targetY = -0.5f;
            break;

        case 3:
            targetX = -0.6f;
            targetY = -0.5f;
            break;

        case 4:
            targetX = 0.0f;
            targetY = 0.7f;
            break;

        case 5:
            targetX = 0.0f;
            targetY = -0.7f;
            break;
    }
}

void display()
{
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawPlayer();
    drawTarget();
    drawHUD();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            playerY += 0.08f;
            break;

        case 's':
        case 'S':
            playerY -= 0.08f;
            break;

        case 'a':
        case 'A':
            playerX -= 0.08f;
            break;

        case 'd':
        case 'D':
            playerX += 0.08f;
            break;

        case 'r':
        case 'R':

                playerX = 0.0f;
            playerY = 0.0f;
            score = 0;
            targetX = 0.6f;
            targetY = 0.5f;
            cout << "Game restarted." << endl;
            break;

        case 27:
            exit(0);
    }

    // Boundary checking
    if (playerX > 0.9f)
        playerX = 0.9f;

    if (playerX < -0.9f)
        playerX = -0.9f;

    if (playerY > 0.85f)
        playerY = 0.85f;

    if (playerY < -0.85f)
        playerY = -0.85f;

    // Collision detection
    if (collision())
    {
        score++;
        cout << "Target collected! Score: " << score << endl;
        moveTarget();
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("Program 5 - Collect the Target with Text Instructions");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
