#include <GL/glut.h>

#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>
#include <thread>

int width = 800;
int height = 600;
float angleX = 0.0f;
float angleY = 0.0f;
float distance = 192.0f;
bool mousePressed = false;
int lastX = 0;
int lastY = 0;
int state = 0;

void updateState(void) {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (state < 1)
      state++;
    else
      state = 0;
  }
}

void drawCoordinateSystem() {
  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f);  // Vermelho
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);

  glColor3f(0.0f, 1.0f, 0.0f);  // Verde
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);

  glColor3f(0.0f, 0.0f, 1.0f);  // Azul
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glEnd();
}

void drawScrew() {
  double P1[3][3] = {{40, 60, 23}, {45, 60, 23}, {42.5, 55, 23}};
  double P2[3][3] = {{42.5, 60, 25.5}, {42.5, 60, 21.5}, {42.5, 55, 23}};

  // Prafuso 1
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex3f(P1[0][0], P1[0][1], P1[0][2]);
  glVertex3f(P1[1][0], P1[1][1], P1[1][2]);
  glVertex3f(P1[2][0], P1[2][1], P1[2][2]);
  glEnd();

  // Parafuso 2
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex3f(P2[0][0], P2[0][1], P2[0][2]);
  glVertex3f(P2[1][0], P2[1][1], P2[1][2]);
  glVertex3f(P2[2][0], P2[2][1], P2[2][2]);
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(distance * cos(angleX) * cos(angleY), distance * sin(angleY),
            distance * sin(angleX) * cos(angleY), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.0f);

  drawCoordinateSystem();

  if (state == 1) {
    glTranslatef(0.0f, -30.4167f, 0.0f);
    glTranslatef(42.5f, 57.5f, 23.0f);
    glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-42.5f, -57.5f, -23.0f);
    drawScrew();
  } else
    drawScrew();

  glutSwapBuffers();
  glutPostRedisplay();
}

void reshape(int w, int h) {
  width = w;
  height = h;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, static_cast<float>(width) / static_cast<float>(height),
                 1.0f, 1024.0f);
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      mousePressed = true;
      lastX = x;
      lastY = y;
    } else {
      mousePressed = false;
    }
  }
}

void motion(int x, int y) {
  if (mousePressed) {
    angleX += (x - lastX) * 0.01f;
    angleY += (y - lastY) * 0.01f;
    lastX = x;
    lastY = y;
    glutPostRedisplay();
  }
}

int main(int argc, char** argv) {
  std::thread myThread(updateState);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("Questao 8 - Parafuso");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  glEnable(GL_DEPTH_TEST);

  glutMainLoop();

  return 0;
}
