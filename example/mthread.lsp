;;----------- multi-thread-----------------


(defun pfib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (mt-call #'+ (fib (- n 1)) (fib (- n 2))))))


(defun fib1 (n)
    (mt-let ((a (fib (- n 1)))
             (b (fib (- n 2))))
        (+ a b)))

(defun fib (n)
    ;(the <fixnum> n) 
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib (- n 1)) (fib (- n 2))))))

(defun ptarai (x y z)
    ;(the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (mt-call #'ptarai (tarai (- x 1) y z)
                          (tarai (- y 1) z x)
                          (tarai (- z 1) x y))))

(defun tarai (x y z)
    ;(the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (tarai (tarai (- x 1) y z)
               (tarai (- y 1) z x)
               (tarai (- z 1) x y))))

(defun ptarai2 (x y z)
    (mt-let ((a (tarai x y z))
             (b (tarai x y z)))
        a))

(defun tarai2 (x y z)
    (let ((a (tarai x y z))
          (b (tarai x y z)))
        a))


(defun pcount (n)
    (mt-exec (count1 1 (div n 2))
             (count1 (+ (div n 2) 1) n)))

(defun count (n)
    (count1 1 n))

(defun count1 (m n)
    (for ((i m (+ i 1)))
         ((= i n) t)
         (sin (cos (tan i)))))

(defun error-test ()
    (mt-let ((a (+ 1 2))
             (b (error "error-test-parallel")))
        a))


(defun rfib (n)
    (for ((i 2 (+ i 1))
          (f1 1 (+ i f1))
          (f0 0 f1))
         ((= i n) (+ n f1))))

(defun repeat-fib30 (n)
    (for ((i 0 (+ i 1)))
         ((= i n) t)
         (rfib 30)))

(defun para-fib30 (n)
    (mt-exec (repeat-fib30 (div n 2)) (repeat-fib30 (div n 2))))

(defun seq-fib30 (n)
    (repeat-fib30 n))


