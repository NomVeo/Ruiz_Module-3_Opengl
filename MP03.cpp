#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <cmath>
#include <cstdlib>
#include <iostream>


using namespace std;

const int MAX_BURSTS = 30;

struct Burst {
  bool active;

  int type;

  float x;
  float y;

  float size;
  float brightness;

  int age;
};

Burst bursts[MAX_BURSTS];

// TEXT
void drawText(float x, float y, const char *text) {
  glRasterPos2f(x, y);

  for (const char *c = text; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
  }
}

void initializeBursts() {
  for (int i = 0; i < MAX_BURSTS; i++) {
    bursts[i].active = false;
  }
}

// SPAWN
void spawnBurst(int type, float x, float y) {
  for (int i = 0; i < MAX_BURSTS; i++) {
    if (!bursts[i].active) {
      bursts[i].active = true;

      bursts[i].type = type;

      bursts[i].x = x;
      bursts[i].y = y;

      bursts[i].size = 0.02f;
      bursts[i].brightness = 1.0f;

      bursts[i].age = 0;

      cout << "Burst created: " << type << endl;

      return;
    }
  }
}

// DRAW SQUARE BURST
void drawSquareBurst(Burst &b) {
  glColor3f(b.brightness, b.brightness * 0.3f, 0.1f);

  for (int i = 0; i < 3; i++) {
    float s = b.size + i * 0.05f;

    glBegin(GL_LINE_LOOP);

    glVertex2f(b.x - s, b.y - s);
    glVertex2f(b.x + s, b.y - s);
    glVertex2f(b.x + s, b.y + s);
    glVertex2f(b.x - s, b.y + s);

    glEnd();
  }
}

// DRAW DIAMOND BURST
void drawDiamondBurst(Burst &b) {
  glColor3f(0.1f, b.brightness, b.brightness);

  for (int i = 0; i < 4; i++) {
    float s = b.size + i * 0.05f;

    glBegin(GL_LINE_LOOP);

    glVertex2f(b.x, b.y + s);
    glVertex2f(b.x + s, b.y);
    glVertex2f(b.x, b.y - s);
    glVertex2f(b.x - s, b.y);

    glEnd();
  }
}

void drawStarBurst(Burst &b) {
  glColor3f(b.brightness, b.brightness, 0.1f);

  for (int i = 0; i < 8; i++) {
    float angle = i * 3.14159f / 4.0f;

    float x2 = b.x + cos(angle) * b.size;

    float y2 = b.y + sin(angle) * b.size;

    glBegin(GL_LINES);

    glVertex2f(b.x, b.y);
    glVertex2f(x2, y2);

    glEnd();
  }
}

// DRAW BURST
void drawBurst(Burst &b) {
  if (!b.active)
    return;

  if (b.type == 1)
    drawSquareBurst(b);

  else if (b.type == 2)
    drawDiamondBurst(b);

  else if (b.type == 3)
    drawStarBurst(b);
}

// UPDATE
void updateBursts(int value) {
  for (int i = 0; i < MAX_BURSTS; i++) {
    if (bursts[i].active) {
      // Expansion
      bursts[i].size += 0.015f;

      // Fade
      bursts[i].brightness -= 0.02f;

      bursts[i].age++;

      // Expire burst
      if (bursts[i].age > 50 || bursts[i].brightness <= 0.0f) {
        bursts[i].active = false;
      }
    }
  }

  glutPostRedisplay();

  // Reschedule timer
  glutTimerFunc(30, updateBursts, 0);
}

void drawSidebar() {
  int activeCount = 0;

  for (int i = 0; i < MAX_BURSTS; i++) {
    if (bursts[i].active)
      activeCount++;
  }

  glColor3f(1.0f, 1.0f, 1.0f);

  drawText(-0.95f, 0.90f, "=== FIREWORK STUDIO ===");

  drawText(-0.95f, 0.80f, "[1] Square Burst");

  drawText(-0.95f, 0.70f, "[2] Diamond Burst");

  drawText(-0.95f, 0.60f, "[3] Star Burst");

  drawText(-0.95f, 0.50f, "[SPACE] Random Burst");

  drawText(-0.95f, 0.40f, "[ESC] Exit");

  char buffer[100];

  snprintf(buffer, sizeof(buffer), "Active Bursts: %d", activeCount);

  drawText(-0.95f, -0.90f, buffer);
}

void display() {
  glClearColor(0.01f, 0.01f, 0.03f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  drawSidebar();

  for (int i = 0; i < MAX_BURSTS; i++) {
    if (bursts[i].active) {
      drawBurst(bursts[i]);
    }
  }

  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  if (key == 27) {
    exit(0);
  }

  if (key == '1') {
    float randomX = -0.6f + (rand() % 120) / 100.0f;

    float randomY = -0.6f + (rand() % 120) / 100.0f;

    spawnBurst(1, randomX, randomY);
  }

  else if (key == '2') {
    float randomX = -0.6f + (rand() % 120) / 100.0f;

    float randomY = -0.6f + (rand() % 120) / 100.0f;

    spawnBurst(2, randomX, randomY);
  }

  else if (key == '3') {
    float randomX = -0.6f + (rand() % 120) / 100.0f;

    float randomY = -0.6f + (rand() % 120) / 100.0f;

    spawnBurst(3, randomX, randomY);
  }

  else if (key == ' ') {
    int type = 1 + rand() % 3;

    float randomX = -0.6f + (rand() % 120) / 100.0f;

    float randomY = -0.6f + (rand() % 120) / 100.0f;

    spawnBurst(type, randomX, randomY);
  }

  glutPostRedisplay();
}

int main(int argc, char **argv) {
  srand(12345);

  initializeBursts();

  glutInit(&argc, argv);

  glutInitWindowSize(900, 700);

  glutCreateWindow("Machine Problem 3 - Dynamic Fireworks");

  glutDisplayFunc(display);

  glutKeyboardFunc(keyboard);

  glutTimerFunc(30, updateBursts, 0);

  glutMainLoop();

  return 0;
}