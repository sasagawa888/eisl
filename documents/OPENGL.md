# OpenGL

# Installation

Install OpenGL on linux and compile *library/opengl.lsp* with Easy-ISLisp.

# Example

```lisp
(import "opengl")
;; Compile library/opengl.lsp before import

(defun main ()
  (glut:init)
  (glut:init-display-mode 'glut-single)
  (glut:init-window-size 400 300)
  (glut:init-window-position 200 300)

  (glut:create-window "GLUT test")
  (glut:init-display-mode "GLUT_RGBA")
  (gl:clear-color 1.0 1.0 1.0 1.0)

  (glut:display-func 'show)
  (glut:main-loop)
)

(defun show ()
  (gl:clear 'gl_color_buffer_bit)
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

(main)
```

![screen5.png](teapot)

# Functions

(glut:init)

(glut:init-display-mode x)

(glut:init-window-size hight width)

(glut:init-window-position hight width)

(glut:create-window x)

(gl:clear-color x1 y1 x2 y2)

(glut:display-func x)

(glut:keyboard-func x)
callback function can get parameters as the following variables:
gl:key
gl:x
gl:y

(glut:mouse-func x)
callback function can get parameter as the following variables:
gl:button
gl:state
gl:x
gl:y

(glut:main-loop)

(gl:clear x)

(gl:color3d r g b)

(gl:begin x)
  x is a symbol, one of
    'gl-line-loop
    'gl-points
    'gl-lines
    'gl-line-strip
    'gl-triangles
    'gl-quads
    'gl-triangle-strip
    'gl-quad-strip
    'gl-triangle-fan
    'gl-polygon

(gl:vertex2d x y)
    
(gl:vertex3d x y z)
    
(gl:vertex4d x1 x2 x3 x4)

(glut:solid-cube x)
    
(glut:solid-sphere x y z)
    
(glut:solid-torus x1 x2 x3 x4)

(glut:solid-icosahedron)

(glut:solid-octahedron)
    
(glut:solid-tetrahedron)

(glut:solid-dodecahedron)

(glut:solid-cone x1 x2 x3 x4)    

(glut:solid-teapot x)
    
(gl:end)
    
(gl:flush)
    
(gl:finish)
