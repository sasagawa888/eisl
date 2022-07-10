;; test tcltk library

(import "tcltk")

(defun main ()
  (tk::init)
  (tk::label 'hello '-text "hello world" '-width 50 '-height 15)
  (tk::button 'bt1 '-text "button1")
  (tk::button 'bt2 '-text "button2")
  (tk::radiobutton 'rbt1 '-text '(one 1))
  (tk::radiobutton 'rbt2 '-text '(two 2))
  (tk::pack 'hello 'bt1 'bt2 'rbt1 'rbt2)
  (tk::mainloop)
  T)


(defun canvas ()
  (tk::init)
  (tk::canvas 'c0)
  (for ((i 10 (+ i 10)))
       ((> i 200) t)
       (tk::create 'c0 (rectangle i i (+ i 10) (+ i 10)) '-fill 'red))
  (tk::pack 'c0)
  (tk::mainloop))


(defglobal area (create-array '(100 100) 0))

(defun init-area ()
    (for ((i 0 (+ i 1)))
         ((> i 500) t)
         (set-aref 1 area (random 100) (random 100))))



(defun life ()
    (init-area)
    (tk::init)
    (tk::canvas 'c0)
    (for ((i 0 (+ i 1)))
         ((>= i 100) t)
         (for ((j 0 (+ j 1)))
              ((>= j 100) t)
              (if (= (aref area i j) 1)
                  (tk::create 'c0 (rectangle (* 3 i) (* 3 j) (+ (* 3 i) 3) (+ (* 3 j) 3)) '-fill 'red))))
    (tk::pack 'c0)
    (tk::mainloop))

(defun flag ()
    (tk::init)
    (tk::canvas 'c0)
    (tk::create 'c0 (rectangle 0 0 300 100) '-fill 'blue)
    (tk::create 'c0 (rectangle 0 100 300 200) '-fill 'yellow)
    (tk::create 'c0 (text 20 210) '-text "Love and Peace!" '-anchor 'nw)
    (tk::pack 'c0)
    (tk::mainloop))
