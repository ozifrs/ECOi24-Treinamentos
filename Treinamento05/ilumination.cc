#include <GL/glut.h>

#include <cmath>

#define PI 3.14159265358979323846

bool mousePressed = false;

int width = 400, height = 400, lastX{}, lastY{};
double angleX = PI / 2.0, angleY{};
double zoom = 1.0, distance = 16.0f;
double eyeX{}, centerX{}, eyeY{}, centerY{}, eyeZ{}, centerZ{};

void drawCoordinateSystem() {
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(1.0, 0.0, 0.0);

  glColor3f(0.0, 1.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 1.0, 0.0);

  glColor3f(0.0, 0.0, 1.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 1.0);
  glEnd();
}

GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
GLfloat mat_ambient[] = {0.1, 0.1, 0.1, 1.0};
GLfloat mat_ambient_color[] = {0.7, 0.7, 0.7, 1.0};
GLfloat mat_diffuse[] = {0.3, 0.3, 0.3, 1.0};
GLfloat mat_specular[] = {0.75, 0.75, 0.75, 1.0};
GLfloat no_shininess[] = {0.0};
GLfloat low_shininess[] = {1.0};
GLfloat high_shininess[] = {3.0};
GLfloat mat_emission[] = {0.1, 0.1, 0.1, 1.0};

void init(void) {
  GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat diffuse[] = {0.5, 0.5, 0.5, 1.0};
  GLfloat specular[] = {0.2, 0.2, 0.2, 1.0};

  GLfloat position[] = {0.0, 3.9, 0.0, 1.0};
  GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat local_view[] = {float(eyeX), float(eyeY), float(eyeZ), 1.0};

  glClearColor(0.0, 0.1, 0.1, 0.0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void drawRoom() {
  // Paredes
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glColor3f(1.0, 0.0, 0.0);
  glTranslatef(0.0, 0.0, -4.0);
  glScalef(8.0, 8.0, 0.1);
  glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glColor3f(1.0, 1.0, 0.0);
  glTranslatef(-4.0, 0.0, 0.0);
  glScalef(0.1, 8.0, 8.0);
  glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glColor3f(0.0, 1.0, 1.0);
  glTranslatef(4.0, 0.0, 0.0);
  glScalef(0.1, 8.0, 8.0);
  glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glColor3f(0.0, 0.0, 1.0);
  glTranslatef(0.0, 4.0, 0.0);
  glScalef(8.0, 0.1, 8.0);
  glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glColor3f(0.0, 1.0, 0.0);
  glTranslatef(0.0, -4.0, 0.0);
  glScalef(8.0, 0.1, 8.0);
  glutSolidCube(1.0);
  glPopMatrix();

  // Draw Objects
  glColor3f(1.0, 1.0, 1.0);
  // Cubo 1
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glTranslatef(-2.0, -3.0, -2.0);
  glScalef(2.0, 2.0, 2.0);
  glutSolidCube(1.0);
  glPopMatrix();

  // Cubo 2
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glTranslatef(2.0, -2.5, 2.0);
  glScalef(3.0, 3.0, 3.0);
  glutSolidCube(1.0);
  glPopMatrix();

  // Esfera 1
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glTranslatef(2.0, 0.0, -2.0);
  glScalef(1.0, 1.0, 1.0);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  eyeX = distance * zoom * cos(angleX) * cos(angleY) + centerX;
  eyeY = distance * zoom * sin(angleY) + centerY;
  eyeZ = distance * zoom * sin(angleX) * cos(angleY) + centerZ;

  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);

  init();
  drawRoom();

  glutSwapBuffers();
  glutPostRedisplay();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, double(w) / double(h), 1.0, 1024.0);
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
  // Giro no botão três do mouse (para frente)
  if (button == 3) {
    zoom -= 0.1;
  }

  // Giro no botão três do mouse (para trás)
  if (button == 4) {
    zoom += 0.1;
  }

  if (zoom < 0.2) {
    zoom = 0.2;
  }

  if (zoom > 20) {
    zoom = 20;
  }

  // Se botão esquerdo apertado
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
    angleX += (x - lastX) * 0.01;
    angleY += (y - lastY) * 0.01;
    lastX = x;
    lastY = y;
    glutPostRedisplay();
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("Atividade de Iluminacao");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glEnable(GL_DEPTH_TEST);

  glutMainLoop();

  return 0;
}