#|
library for OpenGL
not tested
|#

(c-include "<GL/glut.h>")
(c-option "-lglut -lGLU -lGL")

(defun glut::init ()
    (c-lang "int argc = 0;")
    (c-lang "char *argv;")
    (c-lang "glutInit(&argc, argv);"))

(defun glut::init-display-mode (x)
    (c-lang "glutInitDisplayMode(GLUT_SINGLE);"))

(defun glut::init-window-size (hight width)
    (c-lang "glutInitWindowSize((INT_MASK & HIGHT), (INT_MASK & WIDTH));"))

(defun glut::init-window-position (hight width)
    (c-lang "glutInitWindowPosition((INT_MASK & HIGHT), (INT_MASK & WIDTH));"))

(defun glut::create-window (x)
    (c-lang "glutCreateWindow(Fgetname(X));"))

(defun gl::clear-color (x1 y1 x2 y2)
    (c-lang "glClearColor((INT_MASK & X1),(INT_MASK & Y1),(INT_MASK & X2),(INT_MASK & Y2));"))

(defun glut::display-func (x)
    (c-lang "glutDisplayFunc((void*)Fgetname(X));"))

(defun glut::main-loop ()
    (c-lang "glutMainLoop();"))

(defun gl::clear ()
    (c-lang "glClear(GL_COLOR_BUFFER_BIT);"))

(defun gl::color3d (r g b)
    (c-lang "glColor3d((INT_MASK & R),(INT_MASK & G),(INT_MASK & B));"))

(defun gl::begin ()
    (c-lang "glBegin(GL_LINE_LOOP);"))

(defun gl::vertex2d (x y)
    (c-lang "glVertex2d((INT_MASK & X),(INT_MASK & Y));"))

(defun gl::end ()
    (c-lang "glEnd();"))

(defun gl::flush ()
    (c-lang "glFlush();"))