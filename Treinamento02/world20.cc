#include <GL/glut.h>

int width = 800;
int height = 600;

float eyeX(20.0), centerX(0);
float eyeY(20.0), centerY(0);
float eyeZ(20.0), centerZ(0);

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

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0f, 0.0f, 1.0f);
  drawCoordinateSystem();

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

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("Questao 5 - Coordenadas");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glEnable(GL_DEPTH_TEST);

  glutMainLoop();

  return 0;
}