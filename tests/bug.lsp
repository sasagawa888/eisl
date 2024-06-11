;;----------- multi-thread-----------------

(import "unistd")

(defun foo (n)
    (mt-let ((a (sleep n))
             (b (sleep n)))
        (print 'end)))

(defun pfib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (mt-call #'+ (fib (- n 1)) (fib (- n 2))))))


(defun fib1 (n)
    (mt-let ((a (fib (- n 1)))
             (b (fib (- n 2))))
        (+ a b)))

(defun fib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib (- n 1)) (fib (- n 2))))))



