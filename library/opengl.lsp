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
    (c-lang "displayfunc = Fcons(X,NIL);")
    (c-lang "glutDisplayFunc(display_callback);"))

(defun glut::keyboard-func (x)
    (c-lang "keyboardfunc = Fcons(X,NIL);")
    (c-lang "glutKeyboardFunc(keyboard_callback);"))

(defun glut::mouse-func (x)
    (c-lang "mousefunc = Fcons(X,NIL);")
    (c-lang "glutMouseFunc(mouse_callback);")) 

(defun glut::main-loop ()
    (c-lang "glutMainLoop();"))

(defun gl::clear (x)
    (cond ((eq x 'gl_color_buffer_bit) (c-lang "glClear(GL_COLOR_BUFFER_BIT);"))))

(defun gl::color3d (r g b)
    (c-lang "glColor3d(Fgetflt(R),Fgetflt(G),Fgetflt(B));"))

(defun gl::begin (x)
    (cond ((eq x 'gl-line-loop) (c-lang "glBegin(GL_LINE_LOOP);"))
          ((eq x 'gl-points) (c-lang "glBegin(GL_POINTS);"))
          ((eq x 'gl-lines) (c-lang "glBegin(GL_LINES);"))
          ((eq x 'gl-line-strip) (c-lang "glBegin(GL_LINE_STRIP);"))
          ((eq x 'gl-triangles) (c-lang "glBegin(GL_TRIANGLES);"))
          ((eq x 'gl-quads) (c-lang "glBegin(GL_QUADS);"))
          ((eq x 'gl-triangle-strip) (c-lang "glBegin(GL_TRIANGLE_STRIP);"))
          ((eq x 'gl-quad-strip) (c-lang "glBegin(GL_QUAD_STRIP);"))
          ((eq x 'gl-triangle-fan) (c-lang "glBegin(GL_TRIANGLE_FAN);"))
          ((eq x 'gl-polygon) (c-lang "glBegin(GL_POLYGON);"))
          (t (error "gl::begin" x))))

  

(defun gl::vertex2d (x y)
    (c-lang "glVertex2d(Fgetflt(X),Fgetflt(Y));"))

(defun gl::vertex3d (x y z)
    (c-lang "glVertex3d(Fgetflt(X),Fgetflt(Y),Fgetflt(Z));"))

(defun gl::vertex4d (x1 x2 x3 x4)
    (c-lang "glVertex4d(Fgetflt(X1),Fgetflt(X2),Fgetflt(X3),Fgetflt(X4));"))

(defun glut::solid-cube (x)
    (c-lang "glutSolidCube(Fgetflt(X));")) 

(defun glut::solid-sphere (x y z)
    (c-lang "glutSolidSphere(Fgetflt(X),Fgetflt(Y),Fgetflt(Z));"))

(defun glut::solid-torus (x1 x2 x3 x4)
    (c-lang "glutSolidTorus(Fgetflt(X1),Fgetflt(X2),Fgetflt(X3),Fgetflt(X4));")) 

(defun glut::solid-icosahedron ()
    (c-lang "glutSolidIcosahedron();"))

(defun glut::solid-octahedron ()
    (c-lang "glutSolidOctahedron();"))

(defun glut::solid-tetrahedron ()
    (c-lang "glutSolidTetrahedron();"))

(defun glut::solid-dodecahedron ()
    (c-lang "glutSolidDodecahedron();"))

(defun glut::solid-cone (x1 x2 x3 x4)    
    (c-lang "glutSolidCone(Fgetflt(X1),Fgetflt(X2),Fgetflt(X3),Fgetflt(X4));"))

(defun glut::solid-teapot (x)
    (c-lang "glutSolidTeapot(Fgetflt(X));")) 

(defun gl::end ()
    (c-lang "glEnd();"))

(defun gl::flush ()
    (c-lang "glFlush();"))

(defun gl::finish ()
    (c-lang "glFinish();"))
