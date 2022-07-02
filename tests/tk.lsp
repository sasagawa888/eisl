;; test tcltk library

(compile-file "library/tcltk.lsp") ;; re compile
(import "tcltk")

(defun main ()
  (tk::init)
  (tk::label 'hello '-text "hello world" '-width 22 '-height 5)
  (tk::button 'bt1 '-text "button1")
  (tk::button 'bt2 '-text "button2")
  (tk::pack 'hello 'bt1 'bt2)
  (tk::mainloop)
  T)
