;;; test paralell

(defun fib (n)
    (plet ((a (fib1 (- n 1)))
           (b (fib1 (- n 2)))) (+ a b)))

(defun fib1 (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib1 (- n 1)) (fib1 (- n 2))))))

(defun foo (x y z)
    (plet ((a (tarai x y z))
           (b (tarai x y z))) b))

(defun bar (x y z)
    (progn (tarai x y z)
           (tarai x y z)))

(defun tarai (x y z)
    (if (<= x y)
        y
        (tarai (tarai (- x 1) y z)
               (tarai (- y 1) z x)
               (tarai (- z 1) x y))))
