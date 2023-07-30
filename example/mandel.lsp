(import "tcltk")

(defun mandelbrot ()
    (tk:init)
    (tk:canvas 'c0 '-width 600 '-height 600)
    (mandelbrot-draw)
    (tk:pack 'c0)
    (tk:mainloop))



(defun mandelbrot-draw ()
    (progn (mandelbrot-part -1.0 1.0 1.0 0.0)
            (mandelbrot-part -1.0 -1.0 1.0 0.0)))

(defun mandelbrot-part (r1 i1 r2 i2)
    (for ((r r1 (+ r 0.1)))
         ((> r r2) nil)
         (for ((i i1 (+ i 0.1)))
              ((> i i2) nil)
              (format (standard-output) "~A+i~A " r i)
              (if (mandelbrotp r i)
                  (plock (plot r i)(tk:pack 'c0)(tk:update))))))


(defun plot (r i)
     (tk:create 'c0 (oval (+ (* 300 r) +3) 
                          (+ (* 300 i) +3) 
                          (+ (* 300 r) -3) 
                          (+ (* 300 i) -3)) '-fill 'blue))

(defun mandelbrotp (a b)
    (mandelbrotp1 0 0 a b 0))

(defun mandelbrotp1 (r i a b j)
    (cond ((> j 30) t)
          ((> (cabs r i) 2) nil)
          (t (mandelbrotp1 (+ (- (* r r) (* i i)) a)
                           (+ (* 2 r i) b)
                           a
                           b 
                           (+ j 1)))))


(defun cabs (r i)
    (sqrt (+ (* r r) (* i i))))
             

