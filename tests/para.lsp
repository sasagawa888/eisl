;;; test paralell

(defun fib (n)
    (plet ((a (fib1 (- n 1)))
           (b (fib1 (- n 2)))) (+ a b)))

(defun fib1 (n)
    (the <fixnum> n) 
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib1 (- n 1)) (fib1 (- n 2))))))


(defun tarai (x y z)
    ;(the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
        (plet ((x1 (tarai1 (- x 1) y z))) x1))

(defun tarai1 (x y z)
    (print x)
    ;(the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (tarai1 (tarai1 (- x 1) y z)
                (tarai1 (- y 1) z x)
                (tarai1 (- z 1) x y))))