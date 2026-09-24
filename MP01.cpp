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
#include <cmath>

using namespace std;

const int ASTEROID_COUNT = 2;
const float PLAYER_HALF_WIDTH = 0.10f;
const float PLAYER_HALF_HEIGHT = 0.13f;

struct Asteroid
{
    float x;
    float y;
    float size;
    float speed;
};

float playerX = 0.0f;
float playerY = -0.65f;
Asteroid asteroids[ASTEROID_COUNT];

int score = 0;
int lives = 3;
int resetCount = 0;
bool gameRunning = true;

void drawBitmapString(void* font, const char* str)
{
    for (const char* c = str; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void drawShip()
{
    //Hull
    glColor3f(0.10f, 0.70f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(playerX, playerY + 0.13f);
        glVertex2f(playerX - 0.07f, playerY - 0.08f);
        glVertex2f(playerX + 0.07f, playerY - 0.08f);
    glEnd();

    // Cockpit
    glColor3f(0.20f, 0.90f, 1.0f);
    glBegin(GL_TRIANGLES); 
        glVertex2f(playerX, playerY + 0.08f);
        glVertex2f(playerX - 0.04f, playerY - 0.08f);
        glVertex2f(playerX + 0.04f, playerY - 0.08f);
    glEnd();
    
    // Thrusters
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(playerX - 0.07f, playerY - 0.08f);
        glVertex2f(playerX - 0.04f, playerY - 0.08f);
        glVertex2f(playerX - 0.055f, playerY - 0.13f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(playerX + 0.07f, playerY - 0.08f);
        glVertex2f(playerX + 0.04f, playerY - 0.08f);
        glVertex2f(playerX + 0.055f, playerY - 0.13f);
    glEnd();
    
}

void drawAsteroid(const Asteroid& asteroid)
{
    glColor3f(0.55f, 0.48f, 0.42f);
    glBegin(GL_POLYGON);
        glVertex2f(asteroid.x - asteroid.size, asteroid.y);
        glVertex2f(asteroid.x - asteroid.size * 0.55f,
                   asteroid.y + asteroid.size * 0.90f);
        glVertex2f(asteroid.x + asteroid.size * 0.35f,
                   asteroid.y + asteroid.size);
        glVertex2f(asteroid.x + asteroid.size,
                   asteroid.y + asteroid.size * 0.30f);
        glVertex2f(asteroid.x + asteroid.size * 0.75f,
                   asteroid.y - asteroid.size * 0.70f);
        glVertex2f(asteroid.x - asteroid.size * 0.20f,
                   asteroid.y - asteroid.size);
    glEnd();

    glColor3f(0.30f, 0.26f, 0.24f);
    glPointSize(8.0f);
}


void drawHUD()
{
    char buffer[64];

    // Draw Score
    glColor3f(1.0f, 1.0f, 1.0f);
    snprintf(buffer, sizeof(buffer), "Score: %d", score);
    glRasterPos2f(-0.92f, 0.91f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    // Draw Lives
    snprintf(buffer, sizeof(buffer), "Lives: %d", lives);
    glRasterPos2f(0.65f, 0.91f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    // Instructions
    glColor3f(0.70f, 0.78f, 0.90f);
    glRasterPos2f(-0.92f, -0.94f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "W/A/S/D: Move     R: Restart     ESC: Exit");
}

bool checkCollision(const Asteroid& asteroid)
{
    return fabs(playerX - asteroid.x) < PLAYER_HALF_WIDTH + asteroid.size &&
           fabs(playerY - asteroid.y) < PLAYER_HALF_HEIGHT + asteroid.size;
}

void resetAsteroid(int index)
{
    const float lanes[] = {-0.72f, -0.38f, 0.0f, 0.38f, 0.72f};
    asteroids[index].x = lanes[(resetCount + index * 2) % 5];
    asteroids[index].y = 1.05f + index * 0.32f;
    resetCount++;
}

void resetGame()
{
    playerX = 0.0f;
    playerY = -0.65f;
    score = 0;
    lives = 3;
    resetCount = 0;
    gameRunning = true;

    asteroids[0].size = 0.09f;
    asteroids[0].speed = 0.010f;
    asteroids[1].size = 0.12f;
    asteroids[1].speed = 0.018f;

    resetAsteroid(0);
    resetAsteroid(1);
}

void updateGame(int value)
{
    if (gameRunning)
    {
        for (int i = 0; i < ASTEROID_COUNT; i++)
        {
            asteroids[i].y -= asteroids[i].speed;

            if (checkCollision(asteroids[i]))
            {
                lives--;
                cout << "Asteroid hit! Lives remaining: " << lives << endl;
                resetAsteroid(i);

                if (lives <= 0)
                {
                    lives = 0;
                    gameRunning = false;
                    cout << "Game over! Final score: " << score << endl;
                    break;
                }
            }
            else if (asteroids[i].y + asteroids[i].size < -1.0f)
            {
                score++;
                resetAsteroid(i);
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateGame, 0);
}

void display()
{
    glClearColor(0.025f, 0.025f, 0.09f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    if (gameRunning)
    {
        drawShip();
        for (int i = 0; i < ASTEROID_COUNT; i++)
        {
            drawAsteroid(asteroids[i]);
        }
        drawHUD();
    }
    else
    {
        char finalScore[64];
        glColor3f(1.0f, 0.35f, 0.25f);
        glRasterPos2f(-0.40f, 0.05f);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "GAME OVER - Press R to Restart");

        snprintf(finalScore, sizeof(finalScore), "Final Score: %d", score);
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(-0.15f, -0.08f);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, finalScore);
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        exit(0);
    }

    if (key == 'r' || key == 'R')
    {
        resetGame();
        cout << "Game restarted." << endl;
        glutPostRedisplay();
        return;
    }

    if (!gameRunning)
    {
        return;
    }

    switch (key)
    {
        case 'w':
        case 'W':
            playerY += 0.07f;
            break;
        case 's':
        case 'S':
            playerY -= 0.07f;
            break;
        case 'a':
        case 'A':
            playerX -= 0.07f;
            break;
        case 'd':
        case 'D':
            playerX += 0.07f;
            break;
    }

    // Boundary checking
    if (playerX > 0.86f)
        playerX = 0.86f;
    if (playerX < -0.86f)
        playerX = -0.86f;
    if (playerY > 0.70f)
        playerY = 0.70f;
    if (playerY < -0.78f)
        playerY = -0.78f;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("The Cosmic Dodger");

    resetGame();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateGame, 0);

    glutMainLoop();
    return 0;
}
