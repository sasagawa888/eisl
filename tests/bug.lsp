

(defun fib1 (n)
    (mp-let ((a (fib (- n 1)))
             (b (fib (- n 2))))
        (+ a b)))