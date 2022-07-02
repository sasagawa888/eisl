# tcl/tk
library to use GUI of tk.

under construction

# usage
install tcl/tk   sudo apt install tcl-dev tk-dev

compile       eisl -c (compile-file "library/tcltk.lsp")

import       (import "tcltk")

# function

### label 
(label object option)

### pack
(pack object1 object2 ... objectN)


# example


```
(import "tcltk")


(defun main ()
  (tk::init)
  (tk::label 'hello '-text "hello world" '-width 22 '-hight 5)
  (tk::pack 'hello)
  (tk::mainloop)
  T
)


```
