#include <GL/glut.h>

#include <cmath>
#include <iostream>

#define PI 3.14159265358979323846

int width = 800;
int height = 600;
float angleX = PI / 4.0f;
float angleY = PI / 4.0f;
float zoom = 1.0f;
float distance = 32.0f;
bool mousePressed = false;
int lastX = 0;
int lastY = 0;

float eyeX(0), centerX(0);
float eyeY(0), centerY(0);
float eyeZ(0), centerZ(0);

void drawCoordinateSystem() {
  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);

  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);

  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glEnd();
}

void drawCube() {
  double P[8][3] = {{13, 3, 6}, {13, 3, 0}, {7, 3, 0}, {7, 3, 6},
                    {13, 9, 6}, {13, 9, 0}, {7, 9, 0}, {7, 9, 6}};

  float color = 0.16f;
  float iteration = 0.16f;

  glColor3f(1.0f, 0.0f, 0.0f);
  // Face 1
  glBegin(GL_POLYGON);
  glVertex3f(P[0][0], P[0][1], P[0][2]);
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glEnd();

  // Face 2
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_POLYGON);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glVertex3f(P[5][0], P[5][1], P[5][2]);
  glVertex3f(P[6][0], P[6][1], P[6][2]);
  glVertex3f(P[7][0], P[7][1], P[7][2]);
  glEnd();

  // Face 3
  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_POLYGON);
  glVertex3f(P[0][0], P[0][1], P[0][2]);
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[7][0], P[7][1], P[7][2]);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glEnd();

  // Face 4
  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_POLYGON);
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[6][0], P[6][1], P[6][2]);
  glVertex3f(P[7][0], P[7][1], P[7][2]);
  glEnd();

  // Face 5
  glColor3f(1.0f, 0.0f, 1.0f);
  glBegin(GL_POLYGON);
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[6][0], P[6][1], P[6][2]);
  glVertex3f(P[5][0], P[5][1], P[5][2]);
  glEnd();

  glColor3f(0.0f, 1.0f, 1.0f);
  // Face 6
  glBegin(GL_POLYGON);
  glVertex3f(P[0][0], P[0][1], P[0][2]);
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[5][0], P[5][1], P[5][2]);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  eyeX = distance * zoom * cos(angleX) * cos(angleY) + centerX;
  eyeY = distance * zoom * sin(angleY) + centerY;
  eyeZ = distance * zoom * sin(angleX) * cos(angleY) + centerZ;

  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);
  drawCoordinateSystem();

  drawCube();

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
  if (button == 3) {
    zoom -= 0.1f;
  } else if (button == 4) {
    zoom += 0.1f;
  }

  if (zoom < 0.5f) {
    zoom = 0.5f;
  }

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

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':
    case 'Q':
      exit(0);
      break;

    case 'a':
    case 'A':
      centerX = 10.0f;
      centerY = 6.0f;
      centerZ = 3.0f;
      break;

    case 's':
    case 'S':
      centerX = 10.0f;
      centerY = 6.0f;
      centerZ = 3.0f;
      angleX = 0.0;
      angleY = 0.0;
      break;

    case 'd':
    case 'D':
      centerX = 10.0f;
      centerY = 6.0f;
      centerZ = 3.0f;
      angleX = PI / 2.0;
      angleY = 0.0;
      break;

    case 'f':
    case 'F':
      centerX = 10.0f;
      centerY = 6.0f;
      centerZ = 3.0f;
      angleX = PI;
      angleY = 0.0;
      break;

    case 'x':
    case 'X':
      centerX = 10.0f;
      centerY = 6.0f;
      centerZ = 3.0f;
      angleX = -PI / 2.0;
      angleY = 0.0;
      break;

    case 'c':
    case 'C':
      centerX = 10.0f;
      centerY = 6.0f;
      centerZ = 3.0f;
      angleX = 0.0;
      angleY = PI / 2.0;
      break;

    case 'v':
    case 'V':
      centerX = 10.0f;
      centerY = 6.0f;
      centerZ = 3.0f;
      angleX = 0.0;
      angleY = -PI / 2.0;
      break;

    case 'r':
    case 'R':
      centerX = 0.0f;
      centerY = 0.0f;
      centerZ = 0.0f;
      break;

    default:
      break;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("Questao 6 - Cubo");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);

  std::cout << "Pressione Q para fechar a janela----------------" << std::endl
            << "Pressione A para centralizar a camera no Cubo---" << std::endl
            << "Pressione R para centralizar a camera no Centro-" << std::endl
            << "Pressione S para a face Ciano do Cubo-----------" << std::endl
            << "Pressione D para a face Amarela do Cubo---------" << std::endl
            << "Pressione F para a face Azul do Cubo------------" << std::endl
            << "Pressione X para a face Magenta do Cubo---------" << std::endl
            << "Pressione C para a face Verde do Cubo-----------" << std::endl
            << "Pressione V para a face Vermelha do Cubo--------" << std::endl;

  glEnable(GL_DEPTH_TEST);

  glutMainLoop();

  return 0;
}