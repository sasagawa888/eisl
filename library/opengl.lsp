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
    (cond ((eq x 'glut_single) (c-lang "glutInitDisplayMode(GLUT_SINGLE);"))))

(defun glut::init-window-size (hight width)
    (c-lang "glutInitWindowSize((INT_MASK & HIGHT), (INT_MASK & WIDTH));"))

(defun glut::init-window-position (hight width)
    (c-lang "glutInitWindowPosition((INT_MASK & HIGHT), (INT_MASK & WIDTH));"))

(defun glut::create-window (x)
    (c-lang "glutCreateWindow(Fgetname(X));"))

(defun gl::clear-color (x1 y1 x2 y2)
    (c-lang "glClearColor(Fgetflt(X1),Fgetflt(Y1),Fgetflt(X2),Fgetflt(Y2));"))

(defun glut::display-func (x)
    (c-lang "callbackfunc = Fcons(X,NIL);")
    (c-lang "glutDisplayFunc(callback);"))

(defun glut::main-loop ()
    (c-lang "glutMainLoop();"))

(defun gl::clear (x)
    (c-lang "glClear(GL_COLOR_BUFFER_BIT);"))

(defun gl::color3d (r g b)
    (c-lang "glColor3d(Fgetflt(R),Fgetflt(G),Fgetflt(B));"))

(defun gl::begin ()
    (c-lang "glBegin(GL_LINE_LOOP);"))

(defun gl::vertex2d (x y)
    (c-lang "glVertex2d(Fgetflt(X),Fgetflt(Y));"))

(defun gl::end ()
    (c-lang "glEnd();"))

(defun gl::flush ()
    (c-lang "glFlush();"))