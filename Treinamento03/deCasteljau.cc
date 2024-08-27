#include <GL/glut.h>

#include <vector>

int numSegments = 5;

struct point {
  double x{}, y{};
};

struct deCasteljau {
  double b[4]{};
  deCasteljau(double u) {
    double m = 1.0 - u;
    b[0] = m * m * m;
    b[1] = 3.0 * u * m * m;
    b[2] = 3.0 * u * u * m;
    b[3] = u * u * u;
  }
};

point calculateBezier(double u, const std::vector<point>& controlPoints) {
  point P;
  deCasteljau dC(u);
  for (int i = 0; i < controlPoints.size(); i++) {
    double blend = dC.b[i];
    point p = controlPoints[i];
    P.x += p.x * blend;
    P.y += p.y * blend;
  }
  return {P.x, P.y};
}

void drawCurve(const std::vector<point>& controlPoints, int numSegments) {
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i <= numSegments; i++) {
    double u = static_cast<double>(i) / numSegments;
    point p = calculateBezier(u, controlPoints);
    glVertex2d(p.x, p.y);
  }
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
  std::vector<point> controlPoints = {{3, 4}, {7, 9}, {16, 12}, {23, 8}};

  drawCurve(controlPoints, numSegments);

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
  gluOrtho2D(0, 30, 0, 10);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 400);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Curva de Bézier");
  init();
  glutDisplayFunc(display);
  glutSpecialFunc(special);
  glutMainLoop();
  return 0;
}
