;;test
(defun tarai (x y z)
    (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (tarai (tarai (- x 1) y z) (tarai (- y 1) z x) (tarai (- z 1) x y)) ))

(defun tarai* (x y z)
    (if (<= x y)
        y
        (tarai* (tarai* (- x 1.0) y z) (tarai* (- y 1.0) z x) (tarai* (- z 1.0) x y)) ))

(defun fib (n)
    (the <fixnum> n)
    (cond ((= n 1) 1)
          ((= n 2) 1)
          (t (+ (fib (- n 1)) (fib (- n 2)))) ))

(defun fib* (n)
    (cond ((= n 1.0) 1.0)
          ((= n 2.0) 1.0)
          (t (+ (fib* (- n 1.0))
                (fib* (- n 2.0))))))

(defun ack (m n)
    (the <fixnum> m)(the <fixnum> n)
    (cond ((= m 0) (+ n 1))
          ((= n 0) (ack (- m 1) 1))
          (t (ack (- m 1) (ack m (- n 1)))) ))

