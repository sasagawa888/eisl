;; test tcltk library

(import "tcltk")

(defun foo ()
  (tk::init)
  (tk::command "eval + %x %y"))

(defun hello ()
  (tk::init)
  (tk::label 'hello '-text "hello world" '-width 50 '-height 15)
  (tk::pack 'hello)  
  (tk::mainloop))

(defun main ()
  (tk::init)
  (tk::label 'hello '-text "hello world" '-width 50 '-height 15)
  (tk::button 'bt1 '-text "button1")
  (tk::button 'bt2 '-text "button2")
  (tk::radiobutton 'rbt1 '-text '(one 1))
  (tk::radiobutton 'rbt2 '-text '(two 2))
  (tk::scrollbar 's)
  (tk::command "set first last")
  (tk::listbox 'lb1 '-xscrollcommand ".s set")
  (tk::menu '(m m1) '-tearoff 'no)
  (tk::pack 'hello 'bt1 'bt2 'rbt1 'rbt2 'lb1 's)
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

(defun recur ()
    (tk::init)
    (tk::canvas 'c0 '-width 600 '-height 600)
    (gasket #(300 0) #(0 600) #(600 600) 10)
    (tk::pack 'c0)
    (tk::mainloop))

(defun midpoint (a b)
   (let ((a0 (elt a 0))
         (a1 (elt a 1))
         (b0 (elt b 0))
         (b1 (elt b 1)))
      (vector (+ (min a0 b0) (abs (quotient (- a0 b0) 2)))
              (+ (min a1 b1) (abs (quotient (- a1 b1) 2))))))
      

(defun draw-triang (a b c)
   (let ((a0 (elt a 0))
         (a1 (elt a 1))
         (b0 (elt b 0))
         (b1 (elt b 1))
         (c0 (elt c 0))
         (c1 (elt c 1)))
      (tk::create 'c0 (line a0 a1 b0 b1 c0 c1 a0 a1) '-fill 'green)))

(defun gasket (a b c n)
    (cond ((= n 0) t)
          (t
            (draw-triang a b c)
            (draw-triang (midpoint a b) (midpoint b c) (midpoint c a))
            (gasket a (midpoint a b) (midpoint a c) (- n 1))
            (gasket (midpoint a b) b (midpoint b c) (- n 1))
            (gasket (midpoint a c) (midpoint b c) c (- n 1)) )))

