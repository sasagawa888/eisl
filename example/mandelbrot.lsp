;;; test of pexec parallel function
;;; usage
;;; invoke eisl with multi-thread  eisl -t 2
;;; (load "./example/mandelbrot.lsp")
;;; (mandelbrot-data)
;;; (mandelbrot-draw)
;;;

(import "plot")

(defun draw ()
    (gbc)
    (mandelbrot-data)
    (open-plot)
    (send-plot "set xrange [-1.5:1.5]")
    (send-plot "set yrange [-1.5:1.5]")
    (send-plot "set xlabel \"Real\"")
    (send-plot "set ylabel \"Imaginary\"")
    (send-plot "plot \"data1.txt\", \"data2.txt\"")
    (close-plot)
    (system "rm -rf data1.txt data2.txt"))



(defun mandelbrot-data ()
    (mp-exec (mandelbrot-part -1.5 -1.6 1.6 0.0 "data1.txt")
             (mandelbrot-part -1.5 0.0 1.5 1.5 "data2.txt")))

(defun mandelbrot-part (r1 i1 r2 i2 file)
    (let ((stream (open-output-file file)))
         (for ((r r1 (+ r 0.01)))
              ((> r r2) t)
              (for ((i i1 (+ i 0.01)))
                   ((> i i2) t)
                   (if (mandelbrot r i)
                       (format stream "~G ~G ~%" r i))))
         (close stream)))


(defun mandelbrot (a b)
    (mandelbrot1 0 0 a b 0))

(defun mandelbrot1 (r i a b n)
    (cond ((> n 30) t)
          ((> (cabs r i) 2) nil)
          (t (mandelbrot1 (+ (- (* r r) (* i i)) a)
                           (+ (* 2 r i) b)
                           a
                           b 
                           (+ n 1)))))


(defun cabs (r i)
    (sqrt (+ (* r r) (* i i))))
             

