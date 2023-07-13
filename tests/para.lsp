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
    (if (<= x y)
        y
        (plet ((x1 (tarai1 (- x 1) y z))
               (y1 (tarai1 (- y 1) z x))
               (z1 (tarai1 (- z 1) x y)))
            (tarai x1 y1 z1))))

(defun tarai1 (x y z)
    ;(the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (tarai1 (tarai1 (- x 1) y z)
                (tarai1 (- y 1) z x)
                (tarai1 (- z 1) x y))))


(defun count (n)
    (plet ((a (count1 1 (div n 2)))
           (b (count1 (+ (div n 2) 1) n)))
     t))

(defun count1 (m n)
    (if (= m n)
        t
        (count1 (+ m 1) n)))