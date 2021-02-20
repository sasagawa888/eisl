#include <GL/glut.h>

void show(void);

int main(int argc, char** argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(400, 300);
  glutInitWindowPosition(200, 200);

  glutCreateWindow("GLUT test");
  glutInitDisplayMode(GLUT_RGBA);
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glutDisplayFunc(show);
  glutMainLoop();

  return 0;
}

void show(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1.0, 0.0, 0.0);
  glBegin(GL_LINE_LOOP);

  glVertex2d(-0.5,-0.5);
  glVertex2d(-0.5, 0.5);
  glVertex2d( 0.5, 0.5);
  glVertex2d( 0.5,-0.5);

  glEnd();
  glFlush();
}