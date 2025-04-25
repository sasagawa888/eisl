(import "opengl")


(defun main ()
  (glut:init)
  (glut:init-display-mode 'glut-single)
  (glut:init-window-size 400 300)
  (glut:init-window-position 200 300)

  (glut:create-window "GLUT test")
  (glut:init-display-mode 'glut-rgba)
  (gl:clear-color 1.0 1.0 1.0 1.0)

  (glut:display-func 'show)
  (glut:main-loop)
)

(defun show ()
  (gl:clear 'gl-color-buffer-bit)
  (gl:color3d 1.0 0.0 0.0)
  (gl:begin 'gl-line-loop)

  (gl:vertex2d -0.5 -0.5)
  (gl:vertex2d -0.5 0.5)
  (gl:vertex2d 0.5 0.5)
  (gl:vertex2d 0.5 -0.5)
  
  (gl:end)
  (glut:solid-teapot 0.5)
  (gl:flush)
)
