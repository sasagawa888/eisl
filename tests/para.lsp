;;; test paralell

(defun pfib (n)
    (the <fixnum> n) 
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (pcall + (pfib (- n 1)) (pfib (- n 2))))))

(defun fib (n)
    (the <fixnum> n) 
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib (- n 1)) (fib (- n 2))))))

(defun ptarai (x y z)
    ;(the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (plet ((x1 (tarai (- x 1) y z))
               (y1 (tarai (- y 1) z x))
               (z1 (tarai (- z 1) x y)))
            (ptarai x1 y1 z1))))

(defun tarai (x y z)
    ;(the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (tarai (tarai (- x 1) y z)
               (tarai (- y 1) z x)
               (tarai (- z 1) x y))))


(defun pcount (n)
    (plet ((a (count 1 (div n 2)))
           (b (count (+ (div n 2) 1) n)))
     t))

(defun count (m n)
    (if (= m n)
        t
        (count (+ m 1) n)))