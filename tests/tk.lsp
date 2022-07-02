(import "tcltk")


(defun main ()
  (tk::init)
  (tk::label 'hello '-text "hello world" '-width 22 '-hight 5)
  (tk::pack 'hello)
  (tk::mainloop)
  T
)

