# Manual of OpenGL

# Install
install OpenGL on linux and compile library/opengl.lsp with Easy-ISLisp

# Functions
(glut::init)

(glut::init-display-mode x)

(glut::init-window-size hight width)

(glut::init-window-position hight width)

(glut::create-window x)

(gl::clear-color x1 y1 x2 y2)

(glut::display-func x)

(glut::keyboard-func x)

(glut::mouse-func x)

(glut::main-loop)

(gl::clear x)


(gl::color3d r g b)


(defun gl::begin x)
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
          

(gl::vertex2d x y)
    
(gl::vertex3d x y z)
    
(gl::vertex4d x1 x2 x3 x4)

(glut::solid-cube x)
    
(glut::solid-sphere x y z)
    
(glut::solid-torus x1 x2 x3 x4)

(glut::solid-icosahedron)

(glut::solid-octahedron)
    
(glut::solid-tetrahedron)

(glut::solid-dodecahedron)

(glut::solid-cone x1 x2 x3 x4)    

(glut::solid-teapot x)
    
(gl::end)
    
(gl::flush)
    
(gl::finish)
