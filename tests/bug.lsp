
#|
(defun fib1 (n)
    (mp-let ((a (fib (- n 1)))
             (b (fib (- n 2))))
        (+ a b)))
|#


(defun test-lambda-mix1 (n)
  ((lambda (x)
     (let ((a x))
       (setq a (+ a 10))
       ((lambda (y)
          (+ a y))
        5)))
   n))


(defun test-lambda-shadow1 (n)
  ;; variable shadowing
  ((lambda (x)
     (let ((x (+ x 10)))
       (+ x 1)))
   n))

(defun test-lambda-shadow2 (n)
  ;; deeper shadow
  ((lambda (x)
     (let ((x (+ x 10)))
       (let ((x (+ x 20)))
         (+ x 1))))
   n))
