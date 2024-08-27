#include <GL/glut.h>

#include <cmath>
#include <iostream>

int width = 800;
int height = 600;
float angleX = 0.0f;
float angleY = 0.0f;
float zoom = 1.0f;
float distance = 32.0f;
bool mousePressed = false;
int lastX = 0;
int lastY = 0;
unsigned long long int state = 0, objColor = 0;

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

void drawPyramid(int arg) {
  double P[5][3] = {{0, 1, 0}, {1, 0, 0}, {0, 0, -1}, {-1, 0, 0}, {0, 0, 1}};

  float color = 0.2f;
  float iteration = 0.2f;

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glBegin(GL_TRIANGLES);
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[0][0], P[0][1], P[0][2]);

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glVertex3f(P[0][0], P[0][1], P[0][2]);

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glVertex3f(P[0][0], P[0][1], P[0][2]);

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[0][0], P[0][1], P[0][2]);
  glEnd();

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  glBegin(GL_POLYGON);
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[4][0], P[4][1], P[4][2]);

  glEnd();
}

void drawOctahedron(int arg) {
  double P[6][3] = {{0, 1, 0},  {1, 0, 0}, {0, 0, -1},
                    {-1, 0, 0}, {0, 0, 1}, {0, -1, 0}};

  glBegin(GL_TRIANGLES);
  float color = 0.125f;
  float iteration = 0.125f;

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[0][0], P[0][1], P[0][2]);

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glVertex3f(P[0][0], P[0][1], P[0][2]);

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glVertex3f(P[0][0], P[0][1], P[0][2]);

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[0][0], P[0][1], P[0][2]);

  // parte de baixo

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[5][0], P[5][1], P[5][2]);

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glVertex3f(P[5][0], P[5][1], P[5][2]);

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glVertex3f(P[5][0], P[5][1], P[5][2]);

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[5][0], P[5][1], P[5][2]);
  glEnd();
}

void drawCube(int arg) {
  double P[8][3] = {{1, -1, 1}, {1, -1, -1}, {-1, -1, -1}, {-1, -1, 1},
                    {1, 1, 1},  {1, 1, -1},  {-1, 1, -1},  {-1, 1, 1}};

  float color = 0.16f;
  float iteration = 0.16f;

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  // Face 1
  glBegin(GL_POLYGON);
  glVertex3f(P[0][0], P[0][1], P[0][2]);
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glEnd();

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  // Face 2
  glBegin(GL_POLYGON);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glVertex3f(P[5][0], P[5][1], P[5][2]);
  glVertex3f(P[6][0], P[6][1], P[6][2]);
  glVertex3f(P[7][0], P[7][1], P[7][2]);
  glEnd();

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  // Face 3
  glBegin(GL_POLYGON);
  glVertex3f(P[0][0], P[0][1], P[0][2]);
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[7][0], P[7][1], P[7][2]);
  glVertex3f(P[4][0], P[4][1], P[4][2]);
  glEnd();

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  // Face 4
  glBegin(GL_POLYGON);
  glVertex3f(P[3][0], P[3][1], P[3][2]);
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[6][0], P[6][1], P[6][2]);
  glVertex3f(P[7][0], P[7][1], P[7][2]);
  glEnd();

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
  color += iteration;
  // Face 5
  glBegin(GL_POLYGON);
  glVertex3f(P[1][0], P[1][1], P[1][2]);
  glVertex3f(P[2][0], P[2][1], P[2][2]);
  glVertex3f(P[6][0], P[6][1], P[6][2]);
  glVertex3f(P[5][0], P[5][1], P[5][2]);
  glEnd();

  if (arg == 0) {
    glColor3f(color, 0.0f, 0.0f);
  } else if (arg == 1) {
    glColor3f(0.0f, color, 0.0f);
  } else if (arg == 2) {
    glColor3f(0.0f, 0.0f, color);
  } else {
    glColor3f(color, color, color);
  }
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

  float eyeX = distance * zoom * cos(angleX) * cos(angleY);
  float eyeY = distance * zoom * sin(angleY);
  float eyeZ = distance * zoom * sin(angleX) * cos(angleY);

  gluLookAt(eyeX, eyeY, eyeZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  drawCoordinateSystem();

  switch (state) {
    case 0:
      drawPyramid(objColor);
      break;
    case 1:
      drawOctahedron(objColor);
      break;
    case 2:
      drawCube(objColor);
      break;
  }

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
  if (button == 3) {  // Scroll wheel up
    zoom -= 0.1f;
  } else if (button == 4) {  // Scroll wheel down
    zoom += 0.1f;
  }

  // Ensure zoom stays within a reasonable range
  if (zoom < 0.1f) {
    zoom = 0.1f;
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
  if (key == 'q' || key == 'Q') {
    exit(0);
  }
}

void specialHandle(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      if (state == 2) {
        state = 0;
      } else
        state++;
      break;
    case GLUT_KEY_DOWN:
      if (state == 0) {
        state = 2;
      } else
        state--;
      break;
    case GLUT_KEY_LEFT:
      if (objColor == 3) {
        objColor = 0;
      } else
        objColor++;
      break;
    case GLUT_KEY_RIGHT:
      if (objColor == 0) {
        objColor = 3;
      } else
        objColor--;
      break;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("Questao 6 - 3dObjects");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);

  glutMotionFunc(motion);
  glutSpecialFunc(specialHandle);

  std::cout
      << "Aperte Q para fechar a janela--------------------------------------"
      << std::endl
      << "-------------------------------------------------------------------"
      << std::endl
      << "--Aperte a seta para cima ou baixo no teclado para mudar o objeto--"
      << std::endl
      << "Aperte a seta para esquerda ou direita no teclado para mudar a cor-"
      << std::endl
      << "-------------------------------------------------------------------"
      << std::endl;

  glEnable(GL_DEPTH_TEST);

  glutMainLoop();

  return 0;
}