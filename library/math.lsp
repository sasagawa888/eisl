(defmacro when (test :rest body)
    `(if ,test (progn ,@body)) )

(defmacro unless (test :rest body)
    `(if (not ,test) (progn ,@body)) )

(defglobal *e* 2.718281828459045)
(defglobal *gamma* 0.57721566490153286060)

(defun oddp (n)
    (and (integerp n) (= (mod n 2) 1)) )

(defun evenp (n)
    (and (integerp n) (= (mod n 2) 0)) )

(defun zerop (n)
    (= n 0) )

(defun square (n)
    (* n n) )

(defun set-aref1 (val mat i j)
    (set-aref val mat (- i 1) (- j 1)) )

(defun aref1 (mat i j)
    (aref mat (- i 1) (- j 1)) )

(defun mult-scalar-mat (s mat)
    (let ((m (elt (array-dimensions mat) 0))
          (n (elt (array-dimensions mat) 1)) )
       (for ((i 1 (+ i 1)))
            ((> i m)
             mat )
            (for ((j 1 (+ j 1)))
                 ((> j n))
                 (set-aref1 (* s (aref1 mat i j)) mat i j)))))

(defun matrix-ident (n)
    (let ((m (create-array (list n n) 0)))
       (for ((i 1 (+ i 1)))
            ((> i n)
             m )
            (set-aref1 1 m i i))))

(defun square-matrix-p (x)
    (let ((dim (array-dimensions x)))
       (and (= (length dim) 2) (= (elt dim 0) (elt dim 1))) ))

(defun tr (x)
    (unless (square-matrix-p x) (error "tr require square matrix" x))
    (let ((l (elt (array-dimensions x) 0)))
       (for ((i 1 (+ i 1))
             (y 0) )
            ((> i l)
             y )
            (setq y (+ (aref1 x i i) y)))))


(defun sub-matrix (x r s)
    (let* ((m (elt (array-dimensions x) 0))
           (n (elt (array-dimensions x) 1))
           (y (create-array (- m 1) (- n 1) 0)) )
        (for ((i 0 (+ i 1)))
             ((>= i m)
              y )
             (for ((j 0 (+ j 1)))
                  ((>= j n))
                  (cond ((and (< i r) (< j s)) (set-aref1 (aref1 x i j) y i j))
                        ((and (> i r) (< j s)) (set-aref1 (aref1 x i j) y (- i 1) j))
                        ((and (< i r) (> j s)) (set-aref1 (aref1 x i j) y i (- j 1)))
                        ((and (> i r) (> j s)) (set-aref1 (aref1 x i j) y (- i 1) (- j 1)))
                        ((and (= i r) (= j s)) nil))))))

(defun det (x)
    (unless (square-matrix-p x) (error "det require square matrix" x))
    (let ((m (elt (array-dimensions x) 0)))
       (det1 x m) ))



(defun det1 (x m)
    (if (= m 2)
        (- (* (aref1 x 1 1) (aref1 x 2 2))
           (* (aref1 x 1 2) (aref1 x 2 1)))
        (for ((i 1 (+ i 1))
              (y 0) )
             ((> i m)
              y )
             (setq y (+ (* (sign (+ i 1)) (aref1 x i 1) (det1 (sub-matrix x i 1) (- m 1))) y)))))

(defun sign (x)
    (expt -1 x) )

(defun transpose (x)
    (let* ((m (elt (array-dimensions x) 0))
           (n (elt (array-dimensions x) 1))
           (y (create-array (list n m) 0)) )
        (for ((i 1 (+ i 1)))
             ((> i m)
              y )
             (for ((j 1 (+ j 1)))
                  ((> j n))
                  (set-aref1 (aref1 x i j) y j i)))))


(defun inv (x)
    (unless (square-matrix-p x) (error "inv require square matrix" x))
    (let ((m (elt (array-dimensions x) 0))
          (n (elt (array-dimensions x) 1)) )
       (if (> m 2)
           (inv1 x m)
           (inv0 x m))))

(defun inv0 (x m)
    (let ((mat (create-array (list m m) 0))
          (d (det x)) )
       (when (= d 0) (error "inv determinant is zero" x))
       (cond ((= m 1) (set-aref1 (quotient 1 d) mat 1 1) mat)
             (t
              (set-aref1 (aref1 x 2 2) mat 1 1)
              (set-aref1 (aref1 x 1 1) mat 2 2)
              (set-aref1 (- (aref1 x 1 2)) mat 1 2)
              (set-aref1 (- (aref1 x 2 1)) mat 2 1)
              (mult-scalar-mat (quotient 1 d) mat)))))

(defun inv1 (x m)
    (let ((d (det x)))
       (when (= d 0) (error "inv determinant is zero" x))
       (* (quotient 1 d) (transpose (inv2 x m))) ))

(defun inv2 (x m)
    (let ((y (create-array (list m m) 0)))
       (for ((i 1 (+ i 1)))
            ((> i m)
             y )
            (for ((j 1 (+ j 1)))
                 ((> j m))
                 (set-aref1 y i j (* (sign (+ i j)) (det (sub-matrix x i j))))))))


(defun sum (f ls)
    (if (null ls)
        0
        (+ (funcall f (car ls))
           (sum f (cdr ls)))))


(defun product (f ls)
    (if (null ls)
        1
        (* (funcall f (car ls))
           (product f (cdr ls)))))


(defun for-all (f ls)
    (cond ((null ls) t)
          ((not (funcall f (car ls))) nil)
          (t (for-all f (cdr ls))) ))

(defun at-least (f ls)
    (cond ((null ls) nil)
          ((funcall f (car ls)) t)
          (t (at-least f (cdr ls))) ))

(defun gauss-primes (x)
    (quotient x (log x)) )



(defun coprimep (m n)
    (= (gcd m n) 1) )

(defun divisiblep (m n)
    (and (integerp m) (integerp n) (= (mod m n) 0)) )

(defun eqmodp (m n a)
    (= (mod m a) (mod n a)) )

(defun primep (n)
    (if (< n 100000000000)
        (deterministic-prime-p n)
        (rabin-miller-p n) ))

(defun deterministic-prime-p (n)
    (labels ((iter (x y)
               (cond ((> x y) t)
                     ((divisiblep n x) nil)
                     ((= x 2) (iter 3 y))
                     (t (iter (+ x 2) y)) )))
        (if (< n 2)
            nil
            (iter 2 (sqrt n)))))


(defun primepi (n)
    (labels ((iter (x y)
               (cond ((> x n) y)
                     ((primep x) (iter (+ x 1) (+ y 1)))
                     (t (iter (+ x 1) y)) )))
        (iter 2 0)))

(defun tau (n)
    (labels ((iter (ls m)
               (if (null ls)
                   m
                   (iter (cdr ls) (* (+ (elt (elt ls 0) 1) 1) m)) )))
        (if (= n 1)
            1
            (iter (factorize n) 1))))

(defun expt-1 (n)
    (if (oddp n)
        -1
        1 ))

(defun liouville-lambda (n)
    (expt-1 (omega n)) )

(defun omega (n)
    (if (= n 1)
        0
        (sum (lambda (x)(((elt x 1)))) (factorize n)) ))



(defun g (n)
    (sum #'liouville-lambda (divisors n)) )


(defun sigma2 (ls)
    (let ((p (elt ls 0))
          (k (elt ls 1)) )
       (quotient (- (expt p (+ k 1)) 1) (- p 1))))

(defun sigma (n)
    (cond ((< n 1) nil)
          ((= n 1) 1)
          (t (product #'sigma2 (factorize n))) ))


(defun perfectp (n)
    (= (sigma n) (* 2 n)) )

;;2^p -1
(defun mersenne (p)
    (- (expt 2 p) 1) )

(defun double-perfect-number-p (n)
    (= (sigma n) (* 3 n)) )

(defun find-double-perfect (n)
    (labels ((iter (m ls)
               (cond ((> m n) ls)
                     ((double-perfect-number-p m) (iter (+ m 1) (cons m ls)))
                     (t (iter (+ m 1) ls)) )))
        (iter 1 '())))


(defun fermatp (n)
    (labels ((iter (m)
               (cond ((< m 1) t)
                     ((not (= 1 (gaussmod (+ (random (- n 2)) 1) (- n 1) n))) nil)
                     (t (iter (- m 1))) )))
        (iter 10)))

(defun lucasp (p)
    (labels ((iter (n i m)
               (cond ((and (= i (- p 1)) (zerop (mod n m))) t)
                     ((and (= i (- p 1)) (not (zerop (mod n m)))) nil)
                     (t (iter (mod (- (expt n 2) 2) m) (+ i 1) m)) )))
        (cond ((< p 2) nil)
              ((= p 2) t)
              (t (iter 4 1 (mersenne p))))))

(defun fermat-number (n)
    (+ (expt 2 (expt 2 n)) 1) )

(defun rm1 (n)
    (labels ((iter (k q)
               (if (oddp q)
                   (list k q)
                   (iter (+ k 1) (div q 2)) )))
        (iter 0 (- n 1))))

(defun rm2 (a q n)
    (not (= (gaussmod a q n) 1)) )

(defun rm3 (a k q n)
    (labels ((iter (i)
               (cond ((>= i k) t)
                     ((= (gaussmod a (* (expt 2 i) q) n) -1) nil)
                     (t (iter (+ i 1))) )))
        (iter 0)))

(defun rm4 (n a)
    (let* ((ls (rm1 n))
           (k (elt ls 0))
           (q (elt ls 1)) )
        (and (rm2 a q n) (rm3 a k q n))))

(defun rabin-miller-p (n)
    (labels ((iter (m)
               (cond ((< m 1) nil)
                     ((rm4 n (+ (random (min (- n 2) 32767)) 1)) t)
                     (t (iter (- m 1))) )))
        (if (= n 2)
            t
            (not (iter 10)))))



(defun gaussmod (a k m)
    (let ((k1 (expmod a k m)))
       (cond ((and (> k1 0) (> k1 (quotient m 2)) (< k1 m)) (- k1 m))
             ((and (< k1 0) (< k1 (- (quotient m 2))) (> k1 (- m))) (+ k1 m))
             (t k1) )))

(defun twin-primes (n m)
    (labels ((iter (i j ls)
               (cond ((> i j) (reverse ls))
                     ((and (primep i) (primep (+ i 2)))
                      (iter (+ i 2) j (cons (list i (+ i 2)) ls)))
                     (t (iter (+ i 2) j ls)))))
        (cond ((<= n 2) (iter 3 (+ n m) '()))
              ((evenp n) (iter (+ n 1) (+ n m) '()))
              (t (iter n (+ n m) '())))))



(defun divisors (n)
    (labels ((iter (m o ls)
               (cond ((> m o) ls)
                     ((divisiblep n m) (iter (+ m 1) o (cons m ls)))
                     (t (iter (+ m 1) o ls)) )))
        (cond ((not (integerp n)) (error "divisors require natural number" n))
              ((< n 1) (error "divisors require natural number" n))
              ((= n 1) '(1))
              (t (cons n (iter 1 (ceiling (quotient n 2)) '()))))))


(defun prime-factors (n)
    (labels ((iter (p x ls z)
               (cond ((> p z) (cons x ls))
                     ((= (mod x p) 0) (let ((n1 (div x p)))
                                         (iter 2 n1 (cons p ls) (isqrt n1)) ))
                     ((= p 2) (iter 3 x ls z))
                     (t (iter (+ p 2) x ls z)))))
        (cond ((< n 0) nil)
              ((< n 2) (list n))
              (t (iter 2 n '() (isqrt n))))))

;;p^a + q^b + r^c ((p a)(q b)(r c))
(defun factorize (n)
    (labels ((iter (ls p n mult)
               (cond ((null ls) (cons (list p n) mult))
                     ((= (car ls) p) (iter (cdr ls) p (+ n 1) mult))
                     (t (iter (cdr ls) (car ls) 1 (cons (list p n) mult))) )))
        (let ((ls (prime-factors n)))
           (iter (cdr ls) (car ls) 1 '()))))

;;(n=p^a q^b r^c) = n(1-1/p)(1-1/q)(1-1/r)
(defun phi (n)
    (if (= n 1)
        1
        (convert
         (* n (product (lambda (ls)
                          (- 1 (quotient 1 (elt ls 0)))) (factorize n)))
         <integer>)))


(defun primitive-root-p (n p)
    (labels ((iter (i)
               (cond ((>= i (- p 1)) t)
                     ((= (expmod n i p) 1) nil)
                     (t (iter (+ i 1))) )))
        (and (iter 1) (= (expmod n (- p 1) p) 1))))

;;sicp
;; a^n (mod m)
(defun expmod (a n m)
    (cond ((= 0 n) 1)
          ((evenp n) (mod (square (expmod a (div n 2) m)) m))
          (t (mod (* a (expmod a (- n 1) m)) m)) ))


(defun primitive-root (p)
    (labels ((iter (n)
               (cond ((> n p) nil)
                     ((primitive-root-p n p) n)
                     (t (iter (+ n 1))) )))
        (iter 2)))


(defun ind (r a p)
    (labels ((iter (i)
               (cond ((> i p) nil)
                     ((= (expmod r i p) a) i)
                     (t (iter (+ i 1))) )))
        (iter 0)))



;;
(defun highly-composite-number-p (n)
    (cond ((<= n 0) nil)
          ((= n 1) t)
          (t (> (tau n) (max-tau (- n 1) 0))) ))

(defun max-tau (n m)
    (let ((x (tau n)))
       (cond ((= n 1) m)
             ((> x m) (max-tau (- n 1) x))
             (t (max-tau (- n 1) m)) )))
