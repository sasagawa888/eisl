;;distributed parallel

(defun pfib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (dp-call #'+ (fib (- n 1)) (fib (- n 2))))))


(defun fib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib (- n 1)) (fib (- n 2))))))
