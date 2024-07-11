(defun fib1 (n)
    (dp-let ((a (fib (- n 1)))
             (b (fib (- n 2))))
        (+ a b)))


(defun pfib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (dp-call #'+ (fib (- n 1)) (fib (- n 2))))))

(defun fib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib (- n 1)) (fib (- n 2))))))



(import "unistd")

(defun bar (x)
    (dp-exec (uoo x)))

(defun uoo (x) 
        (dp-report "asdf1")
        (sleep 1)
        (dp-report "asdf2")
        (sleep 1)
        t)
