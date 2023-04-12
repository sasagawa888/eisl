(import "formula")
(import "test")

(defun fib (n)
    (the <fixnum> n)
    (cond ((= n 1) 1)
          ((= n 2) 1)
          (t (+ (fib (- n 1)) (fib (- n 2)))) ))

(defun fib1 (n)
    (the <fixnum> n)
    (cond ((= n 1) 1)
          ((= n 2) 1)
          (t (formula (fib1 (n - 1)) + (fib1 (n - 2)))) ))

($test (fib 10) 55)
($test (fib1 10) 55)
($test (let ((a 1)(b 2)(c 3)(x 4)) (formulas "a*x^2+b*x+c")) 27)

