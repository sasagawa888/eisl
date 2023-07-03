;;; test paralell
(import "unistd")

(defun fib (n)
    (plet ((a (fib1 (- n 1)))
           (b (fib1 (- n 2)))) (+ a b)))

(defun fib1 (n)
    ;(sleep 1)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib1 (- n 1)) (fib1 (- n 2))))))
