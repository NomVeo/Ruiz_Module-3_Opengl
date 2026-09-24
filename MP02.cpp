#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut_ext.h>
#include <GL/glut.h>
#endif
#include <cstdio>
#include <cstdlib>
#include <iostream>


using namespace std;

float playerX = 0.0f;
float playerY = -0.6f;

float playerR = 1.0f;
float playerG = 0.0f;
float playerB = 0.0f;

int playerColor = 0;
// 0 = Red
// 1 = Green
// 2 = Blue

// Barrier
float barrierX = 1.0f;
float barrierY = 1.0f;
float barrierSpeed = 0.012f;
bool barrierFromSide = true;

int barrierColor = 0;

int score = 0;
bool gameOver = false;

// Text
void drawText(float x, float y, const char *text) {
  glRasterPos2f(x, y);

  for (const char *c = text; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
  }
}

// Player Bounding Box
void drawPlayer() {
  glColor3f(playerR, playerG, playerB);

  glBegin(GL_QUADS);

  glVertex2f(playerX - 0.12f, playerY - 0.12f);
  glVertex2f(playerX + 0.12f, playerY - 0.12f);
  glVertex2f(playerX + 0.12f, playerY + 0.12f);
  glVertex2f(playerX - 0.12f, playerY + 0.12f);

  glEnd();
}

// BARRIER COLOR
void setBarrierColor() {
  if (barrierColor == 0) {
    glColor3f(1.0f, 0.0f, 0.0f);
  } else if (barrierColor == 1) {
    glColor3f(0.0f, 1.0f, 0.0f);
  } else {
    glColor3f(0.0f, 0.0f, 1.0f);
  }
}

// Barrier
void drawBarrier() {
  setBarrierColor();

  glBegin(GL_QUADS);

  if (barrierFromSide) {
    // Vertical barrier entering from the right side.
    glVertex2f(barrierX - 0.05f, -0.85f);
    glVertex2f(barrierX + 0.05f, -0.85f);
    glVertex2f(barrierX + 0.05f, 0.85f);
    glVertex2f(barrierX - 0.05f, 0.85f);
  } else {
    // Horizontal barrier entering from the top.
    glVertex2f(-0.85f, barrierY - 0.05f);
    glVertex2f(0.85f, barrierY - 0.05f);
    glVertex2f(0.85f, barrierY + 0.05f);
    glVertex2f(-0.85f, barrierY + 0.05f);
  }

  glEnd();
}

// Color
const char *getColorName(int color) {
  if (color == 0)
    return "RED";

  if (color == 1)
    return "GREEN";

  return "BLUE";
}

// Matching Colors
bool colorsMatch() { return playerColor == barrierColor; }

// Collision
bool checkGateCollision() {
  if (barrierFromSide) {
    return barrierX < playerX + 0.12f && barrierX > playerX - 0.12f;
  }

  return barrierY < playerY + 0.12f && barrierY > playerY - 0.12f;
}

// Spawn
void spawnNextBarrier() {
  barrierFromSide = !barrierFromSide;
  barrierX = 1.0f;
  barrierY = 1.0f;

  barrierColor = rand() % 3;

  // Increase speed gradually
  barrierSpeed += 0.001f;

  // Speed Capped
  if (barrierSpeed > 0.035f)
    barrierSpeed = 0.035f;
}

// Restart
void resetGame() {
  playerX = 0.0f;
  playerY = -0.6f;
  playerColor = 0;
  playerR = 1.0f;
  playerG = 0.0f;
  playerB = 0.0f;

  score = 0;
  barrierSpeed = 0.012f;
  barrierColor = rand() % 3;
  barrierFromSide = true;
  barrierX = 1.0f;
  barrierY = 1.0f;
  gameOver = false;

  cout << "Game restarted." << endl;
}

// Dashboard
void drawDashboard() {
  char buffer[100];

  glColor3f(1.0f, 1.0f, 1.0f);

  snprintf(buffer, sizeof(buffer), "Score: %d", score);

  drawText(-0.9f, 0.90f, buffer);

  snprintf(buffer, sizeof(buffer), "Player Color: %s",
           getColorName(playerColor));

  drawText(-0.9f, 0.80f, buffer);

  drawText(-0.9f, 0.68f, "[R] Red   [G] Green   [B] Blue");

  drawText(-0.9f, 0.58f, "Match the barrier color!");

  drawText(-0.9f, 0.48f, "[ESC] Exit");
}

void display() {
  glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  drawDashboard();

  if (gameOver) {
    glColor3f(1.0f, 0.2f, 0.2f);
    drawText(-0.35f, 0.10f, "GAME OVER");
    drawText(-0.55f, -0.05f, "Press R to Restart");
  } else {
    drawPlayer();
    drawBarrier();
  }

  glFlush();
}

// Timer
void updateBarrier(int value) {
  if (!gameOver) {
    if (barrierFromSide)
      barrierX -= barrierSpeed;
    else
      barrierY -= barrierSpeed;

    // Barrier reached player
    if (checkGateCollision()) {
      if (colorsMatch()) {
        score++;

        cout << "Correct match! Score: " << score << endl;

        spawnNextBarrier();
      } else {
        cout << "Wrong color! GAME OVER!" << endl;

        gameOver = true;
      }
    }

    // Barrier passed the player
    if ((barrierFromSide && barrierX < -1.1f) ||
        (!barrierFromSide && barrierY < -1.1f)) {
      spawnNextBarrier();
    }
  }

  glutPostRedisplay();

  glutTimerFunc(16, updateBarrier, 0);
}

void keyboard(unsigned char key, int x, int y) {
  if (key == 27) {
    exit(0);
  }

  if (gameOver && (key == 'r' || key == 'R')) {
    resetGame();
    glutPostRedisplay();
    return;
  }

  if (key == 'r' || key == 'R') {
    playerColor = 0;
    playerR = 1.0f;
    playerG = 0.0f;
    playerB = 0.0f;
  } else if (key == 'g' || key == 'G') {
    playerColor = 1;

    playerR = 0.0f;
    playerG = 1.0f;
    playerB = 0.0f;
  }

  else if (key == 'b' || key == 'B') {
    playerColor = 2;
    playerR = 0.0f;
    playerG = 0.0f;
    playerB = 1.0f;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  srand(12345);
  glutInit(&argc, argv);
  glutInitWindowSize(800, 700);
  glutCreateWindow("Machine Problem 2 - Chroma-Shift");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  resetGame();

  glutTimerFunc(16, updateBarrier, 0);
  glutMainLoop();
  return 0;
}
