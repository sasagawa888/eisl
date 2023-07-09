;;; test paralell

(defun fib (n)
    (plet ((a (fib1 (- n 1)))
           (b (fib1 (- n 2)))) (+ a b)))

(defun fib1 (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib1 (- n 1)) (fib1 (- n 2))))))

