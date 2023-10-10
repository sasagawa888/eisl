;; test tcltk library

(import "tcltk")

(defun foo ()
  (tk:init)
  (tk:command "eisl_eval + %x %y"))

(defun hello ()
  (tk:init)
  (tk:label 'hello '-text "hello world" '-width 50 '-height 15)
  (tk:pack 'hello)  
  (tk:mainloop))

(defun main ()
  (tk:init)
  (tk:label 'hello '-text "hello world" '-width 50 '-height 15)
  (tk:button 'bt1 '-text "button1")
  (tk:button 'bt2 '-text "button2")
  (tk:radiobutton 'rbt1 '-text '(one 1))
  (tk:radiobutton 'rbt2 '-text '(two 2))
  (tk:scrollbar 's)
  (tk:command "set first last")
  (tk:listbox 'lb1 '-xscrollcommand ".s set")
  (tk:configure 'root '-menu 'm1)
  (tk:menu 'm1)
  (tk:add 'm1 "cascade" '-label "Games" '-underline 0 '-menu '(m1 game))
  (tk:add 'm1 "cascade" '-label "Level" '-underline 0 '-menu '(m1 level))
  (tk:pack 'hello 'bt1 'bt2 'rbt1 'rbt1 's 'lb1)
  (tk:mainloop)
  T)


(defun canvas ()
  (tk:init)
  (tk:canvas 'c0)
  (for ((i 10 (+ i 10)))
       ((> i 200) t)
       (tk:create 'c0 (rectangle i i (+ i 10) (+ i 10)) '-fill 'red))
  (tk:pack 'c0)
  (tk:bind 'c0 "<Button-1>" `(bar %x %y))
  (tk:bind 'c0 "<KeyPress>" `(tk:deleteinterp))
  (tk:mainloop))


(defglobal area (create-array '(100 100) 0))

(defun init-area ()
    (for ((i 0 (+ i 1)))
         ((> i 500) t)
         (set-aref 1 area (random 100) (random 100))))



(defun life ()
    (init-area)
    (tk:init)
    (tk:canvas 'c0)
    (for ((i 0 (+ i 1)))
         ((>= i 100) t)
         (for ((j 0 (+ j 1)))
              ((>= j 100) t)
              (if (= (aref area i j) 1)
                  (tk:create 'c0 (rectangle (* 3 i) (* 3 j) (+ (* 3 i) 3) (+ (* 3 j) 3)) '-fill 'red))))
    (tk:pack 'c0)
    (tk:mainloop))

(defun flag ()
    (tk:init)
    (tk:canvas 'c0)
    (tk:create 'c0 (rectangle 0 0 300 100) '-fill 'blue)
    (tk:create 'c0 (rectangle 0 100 300 200) '-fill 'yellow)
    (tk:create 'c0 (text 20 210) '-text "Love and Peace!" '-anchor 'nw)
    (tk:pack 'c0)
    (tk:mainloop))

(defun flag1 ()
    (tk:init)
    (tk:canvas 'c0)
    (tk:create 'c0 (rectangle 0 0 300 50) '-fill 'blue)
    (tk:create 'c0 (rectangle 0 150 300 200) '-fill 'blue)
    (draw-star #(100 60) #(100 140) #(200 60) #(200 140))
    (tk:create 'c0 (text 20 210) '-text "Love and Peace!" '-anchor 'nw)
    (tk:pack 'c0)
    (tk:mainloop))

(defun draw-star (a b c d)
  (draw-star1 (midpoint a c) (up-point b 20) (up-point d 20))
  (draw-star1 (midpoint b d) (down-point a 20) (down-point c 20)))

(defun up-point (x y)
  (vector (elt x 0) (- (elt x 1) y)))

(defun down-point (x y)
  (vector (elt x 0) (+ (elt x 1) y)))

(defun draw-star1 (a b c)
   (let ((a0 (elt a 0))
         (a1 (elt a 1))
         (b0 (elt b 0))
         (b1 (elt b 1))
         (c0 (elt c 0))
         (c1 (elt c 1)))
      (tk:create 'c0 (line a0 a1 b0 b1 c0 c1 a0 a1) '-fill 'blue)))

(defun precur ()
    (tk:init)
    (tk:canvas 'c0 '-width 600 '-height 600)
    (pgasket #(300 0) #(0 600) #(600 600) 6)
    (tk:pack 'c0)
    (tk:mainloop))

(defun recur ()
    (tk:init)
    (tk:canvas 'c0 '-width 600 '-height 600)
    (gasket #(300 0) #(0 600) #(600 600) 6)
    (tk:pack 'c0)
    (tk:mainloop))

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
      (tk:create 'c0 (line a0 a1 b0 b1 c0 c1 a0 a1) '-fill 'green)))

(defun pgasket (a b c n)
    (cond ((= n 0) t)
          (t
            (plock
            (draw-triang a b c)
            (draw-triang (midpoint a b) (midpoint b c) (midpoint c a))
            (tk:pack 'c0)(tk:update))
            (pexec (pgasket a (midpoint a b) (midpoint a c) (- n 1))
                   (pgasket (midpoint a b) b (midpoint b c) (- n 1))
                   (pgasket (midpoint a c) (midpoint b c) c (- n 1)) ))))

(defun gasket (a b c n)
    (cond ((= n 0) t)
          (t
            (plock
            (draw-triang a b c)
            (draw-triang (midpoint a b) (midpoint b c) (midpoint c a))
            (tk:pack 'c0)(tk:update))
            (gasket a (midpoint a b) (midpoint a c) (- n 1))
            (gasket (midpoint a b) b (midpoint b c) (- n 1))
            (gasket (midpoint a c) (midpoint b c) c (- n 1)) )))

