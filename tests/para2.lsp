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


(defun bar (x y)
    (dp-exec (fib x) (fib y)))
    