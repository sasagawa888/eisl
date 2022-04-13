;; test formula library for compiler


(import "formula")

(defun fib (n)
    (cond ((= n 1) 1)
          ((= n 2) 1)
          (t (+ (fib (- n 1)) (fib (- n 2)))) ))

(defun fib1 (n)
    (cond ((= n 1) 1)
          ((= n 2) 1)
          (t (formula (fib1 (n - 1)) + (fib1 (n - 2)))) ))











