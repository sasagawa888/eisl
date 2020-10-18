(defun fib* (n)
  (cond ((= n 1.0) 1.0)
        ((= n 2.0) 1.0)
        (t (+ (fib* (- n 1.0)) (fib* (- n 2.0))))))