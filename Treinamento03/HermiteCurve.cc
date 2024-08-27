#include <GL/glut.h>

#include <cmath>
#include <vector>

int numSegments = 5;

struct HermitePoint {
  double x{}, y{};
};

HermitePoint calculate(double u) {
  return {u * u * u + 8 * u * u - 2 * u + 5,
          -5 * u * u * u - u * u + 15 * u - 11};
}

void drawCurve(int numSegments) {
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i <= numSegments; i++) {
    double u = static_cast<double>(i) / numSegments;
    HermitePoint p = calculate(u);
    glVertex2d(p.x, p.y);
  }
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);

  drawCurve(numSegments);

  glFlush();
}

void special(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      if (numSegments == 100) {
        break;
      } else
        numSegments++;
      break;
    case GLUT_KEY_DOWN:
      if (numSegments == 5) {
        break;
      } else
        numSegments--;
      break;
  }
  glutPostRedisplay();
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  gluOrtho2D(0, 15, -15, 5);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 400);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Curva de Hermite");
  init();
  glutDisplayFunc(display);
  glutSpecialFunc(special);
  glutMainLoop();
  return 0;
}
