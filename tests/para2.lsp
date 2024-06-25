;;; test for destributed parallel

(defun fib1 (n)
    (dp-let ((a (fib (- n 1)))
             (b (fib (- n 2))))
        (+ a b)))

