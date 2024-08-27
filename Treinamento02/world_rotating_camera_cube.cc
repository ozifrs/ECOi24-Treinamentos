#include <GL/glut.h>

#include <cmath>
#include <iostream>

#define PI 3.14159265358979323846

int width = 800;
int height = 600;
float angleX = PI / 4.0f;
float angleY = PI / 4.0f;
float zoom = 1.0f;
float distance = 20.0f;

float eyeX(0.0f), centerX(10.0f);
float eyeY(0.0f), centerY(6.0f);
float eyeZ(0.0f), centerZ(3.0f);

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

double cube[8][4] = {{13, 3, 6, 1}, {13, 3, 0, 1}, {7, 3, 0, 1}, {7, 3, 6, 1},
                     {13, 9, 6, 1}, {13, 9, 0, 1}, {7, 9, 0, 1}, {7, 9, 6, 1}};

void drawCube(double P[8][4]) {
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

  drawCube(cube);

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

void rotateCube(double (&P)[8][4], double angle) {
  double result[8][4] = {0}, aux_result[8][4] = {0}, aux0_result[8][4] = {0};
  double T1[4][4] = {
      {1, 0, 0, -10}, {0, 1, 0, -6}, {0, 0, 1, -3}, {0, 0, 0, 1}};

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++) result[i][j] += T1[j][k] * P[i][k];

  double T2[4][4] = {{cosf(angle * 0.5), 0, sinf(angle * 0.5), 0},
                     {0, cosf(angle), -sinf(angle), 0},
                     {-sinf(angle * 0.5), sinf(angle), cosf(angle * 0.5), 0},
                     {0, 0, 0, 1}};

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++) aux_result[i][j] += T2[j][k] * result[i][k];

  double T3[4][4] = {
      {1, 0, 0, 10},
      {0, 1, 0, 6},
      {0, 0, 1, 3},
      {0, 0, 0, 1},
  };

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++)
        aux0_result[i][j] += T3[j][k] * aux_result[i][k];

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 3; j++) P[i][j] = aux0_result[i][j];
}

void timer(int value) {
  rotateCube(cube, PI / 360.0);
  glutPostRedisplay();
  glutTimerFunc(33, timer, 1);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':
    case 'Q':
      exit(0);
      break;

    case 'w':
    case 'W':
      zoom -= 0.1f;
      if (zoom < 1.0f) {
        zoom = 1.0f;
      }
      break;

    case 's':
    case 'S':
      zoom += 0.1f;
      if (zoom > 5.0f) {
        zoom = 5.0f;
      }
      break;

    case 'a':
    case 'A':
      angleX += PI / 360.0;
      break;

    case 'd':
    case 'D':
      angleX -= PI / 360.0;
      break;

    default:
      break;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("Questao 8 - Cubo girando com zoom e rotacao na camera");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(33, timer, 1);

  std::cout << "Pressione Q para fechar a janela----------------" << std::endl
            << "Pressione W para Zoom In------------------------" << std::endl
            << "Pressione S para Zoom Out-----------------------" << std::endl
            << "Pressione A para giro no sentido antihorario----" << std::endl
            << "Pressione D para giro no sentido horario--------" << std::endl;

  glEnable(GL_DEPTH_TEST);

  glutMainLoop();

  return 0;
}