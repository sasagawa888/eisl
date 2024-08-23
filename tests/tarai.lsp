;;sample code for type inference
;;benchmark test


(defun tarai (x y z)
    ;(the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
          (tarai (tarai (- x 1) y z)
                 (tarai (- y 1) z x)
                 (tarai (- z 1) x y))))

(defun tarai* (x y z)
    (if (<= x y)
        y
        (tarai* (tarai* (- x 1.0) y z)
                (tarai* (- y 1.0) z x)
                (tarai* (- z 1.0) x y))))

(defun fib (n)
    (the <fixnum> n)
    (cond ((= n 1) 1)
          ((= n 2) 1)
          (t (+ (fib (- n 1)) (fib (- n 2)))) ))

(defun fib* (n)
    (cond ((= n 1.0) 1.0)
          ((= n 2.0) 1.0)
          (t (+ (fib* (- n 1.0)) (fib* (- n 2.0)))) ))

(defun fib** (n)
    (cond ((< n 2) 1)
          (t (+ (fib** (- n 1)) (fib** (- n 2)))) ))

(defun ack (m n)
    (the <fixnum> m)(the <fixnum> n)
    (cond ((= m 0) (+ n 1))
          ((= n 0) (ack (- m 1) 1))
          (t (ack (- m 1) (ack m (- n 1)))) ))


(defgeneric gfib (n)
    (:method ((n <integer>))
             (cond ((= n 1) 1)
                   ((= n 2) 1)
                   (t (+ (gfib (- n 1)) (gfib (- n 2)))))))

(defun tak (x y z)
    (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (>= y x)
        z
        (tak (tak (- x 1) y z) (tak (- y 1) z x) (tak (- z 1) x y)) ))

(defun listn (n)
    (if (not (= 0 n))
        (cons n (listn (- n 1))) ))


(defconstant ll-18 (listn 18))
(defconstant ll-12 (listn 12))
(defconstant ll-6 (listn 6))
(defconstant ll-32 (listn 32))
(defconstant ll-16 (listn 16))
(defconstant ll-8 (listn 8))

(defmacro shorterp (x y)
    `(< (length ,x) (length ,y)) )

(defun takl (x y z)
    (if (not (shorterp y x))
        z
        (takl (takl (cdr x) y z) (takl (cdr y) z x) (takl (cdr z) x y)) ))

;;call: (takl ll-32 ll-16 ll-8)

(defun ctak (x y z)
    (catch 'ctak-aux (ctak-aux x y z)) )

(defun ctak-aux (x y z)
    (if (>= y x)
        (throw 'ctak-aux z)
        (ctak-aux (catch 'ctak-aux (ctak-aux (- x 1) y z))
                  (catch 'ctak-aux (ctak-aux (- y 1) z x))
                  (catch 'ctak-aux (ctak-aux (- z 1) x y)))))


