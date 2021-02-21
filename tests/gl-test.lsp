(import "opengl")

(defun main ()
  (glut::init)
  (glut::init-display-mode 'glut-single)
  (glut::init-window-size 400 300)
  (glut::init-window-position 200 300)

  (glut::create-window "GLUT test")
  (glut::init-display-mode "GLUT_RGBA")
  (gl::clear-color 1.0 1.0 1.0 1.0)

  (glut::display-func 'show)
  (glut::main-loop)
)

(defun show ()
  (gl::clear 'gl_color_buffer_bit)
  (gl::color3d 1.0 0.0 0.0)
  (gl::begin)

  (gl::vertex2d -0.5 -0.5)
  (gl::vertex2d -0.5 0.5)
  (gl::vertex2d 0.5 0.5)
  (gl::vertex2d 0.5 -0.5)

  (gl::end)
  (gl::flush)
)
