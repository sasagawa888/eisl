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
    (if (< n 1000000000000000000)
        (deterministic-prime-p n)
        (rabin-miller-p n) ))

(defun deterministic-prime-p (n)
    (labels
     ((iter
       (x y)
       (cond ((> x y) t)
             ((divisiblep n x) nil)
             ((= x 2) (iter 3 y))
             (t (iter (+ x 2) y)))))
     (if (< n 2)
         nil
         (iter 2 (sqrt n)))))


(defun primepi (n)
    (labels
     ((iter (x y) (cond ((> x n) y)
                        ((primep x) (iter (+ x 1) (+ y 1)))
                        (t (iter (+ x 1) y)))))
     (iter 2 0)))

(defun tau (n)
    (labels
     ((iter (ls m) (if (null ls)
                       m
                       (iter (cdr ls) (* (+ (elt (elt ls 0) 1) 1) m)))))
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
        (sum (lambda (x)((elt x 1))) (factorize n)) ))



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
    (labels
     ((iter
       (m ls)
       (cond ((> m n) ls)
             ((double-perfect-number-p m) (iter (+ m 1) (cons m ls)))
             (t (iter (+ m 1) ls)))))
     (iter 1 '())))


(defun fermatp (n)
    (labels
     ((iter
       (m)
       (cond ((< m 1) t)
             ((not (= 1 (gaussmod (+ (random (- n 2)) 1) (- n 1) n))) nil)
             (t (iter (- m 1))))))
     (iter 10)))

(defun lucasp (p)
    (labels
     ((iter
       (n i m)
       (cond ((and (= i (- p 1)) (zerop (mod n m))) t)
             ((and (= i (- p 1)) (not (zerop (mod n m)))) nil)
             (t (iter (mod (- (expt n 2) 2) m) (+ i 1) m)))))
     (cond ((< p 2) nil)
           ((= p 2) t)
           (t (iter 4 1 (mersenne p))))))

(defun fermat-number (n)
    (+ (expt 2 (expt 2 n)) 1) )

(defun rm1 (n)
    (labels ((iter (k q) (if (oddp q)
                             (list k q)
                             (iter (+ k 1) (div q 2)) ))) (iter 0 (- n 1))))

(defun rm2 (a q n)
    (not (= (gaussmod a q n) 1)) )

(defun rm3 (a k q n)
    (labels
     ((iter
       (i)
       (cond ((>= i k) t)
             ((= (gaussmod a (* (expt 2 i) q) n) -1) nil)
             (t (iter (+ i 1))))))
     (iter 0)))

(defun rm4 (n a)
    (let* ((ls (rm1 n))
           (k (elt ls 0))
           (q (elt ls 1)) )
        (and (rm2 a q n) (rm3 a k q n))))

(defun rabin-miller-p (n)
    (labels
     ((iter
       (m)
       (cond ((< m 1) nil)
             ((rm4 n (+ (random (min (- n 2) 32767)) 1)) t)
             (t (iter (- m 1))))))
     (if (= n 2)
         t
         (not (iter 10)))))



(defun gaussmod (a k m)
    (let ((k1 (expmod a k m)))
       (cond ((and (> k1 0) (> k1 (quotient m 2)) (< k1 m)) (- k1 m))
             ((and (< k1 0) (< k1 (- (quotient m 2))) (> k1 (- m))) (+ k1 m))
             (t k1) )))

(defun twin-primes (n m)
    (labels
     ((iter
       (i j ls)
       (cond ((> i j) (reverse ls))
             ((and (primep i) (primep (+ i 2))) (iter (+ i 2) j (cons (list i (+ i 2)) ls)))
             (t (iter (+ i 2) j ls)))))
     (cond ((<= n 2) (iter 3 (+ n m) '()))
           ((evenp n) (iter (+ n 1) (+ n m) '()))
           (t (iter n (+ n m) '())))))



(defun divisors (n)
    (labels
     ((iter
       (m o ls)
       (cond ((> m o) ls)
             ((divisiblep n m) (iter (+ m 1) o (cons m ls)))
             (t (iter (+ m 1) o ls)))))
     (cond ((not (integerp n)) (error "divisors require natural number" n))
           ((< n 1) (error "divisors require natural number" n))
           ((= n 1) '(1))
           (t (cons n (iter 1 (ceiling (quotient n 2)) '()))))))


(defun prime-factors (n)
    (labels
     ((iter
       (p x ls z)
       (cond ((> p z) (cons x ls))
             ((= (mod x p) 0) (let ((n1 (div x p)))
                                 (iter 2 n1 (cons p ls) (isqrt n1))))
             ((= p 2) (iter 3 x ls z))
             (t (iter (+ p 2) x ls z)))))
     (cond ((< n 0) nil)
           ((< n 2) (list n))
           (t (iter 2 n '() (isqrt n))))))

;;p^a + q^b + r^c ((p a)(q b)(r c))
(defun factorize (n)
    (labels
     ((iter
       (ls p n mult)
       (cond ((null ls) (cons (list p n) mult))
             ((= (car ls) p) (iter (cdr ls) p (+ n 1) mult))
             (t (iter (cdr ls) (car ls) 1 (cons (list p n) mult))))))
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
    (labels
     ((iter (i) (cond ((>= i (- p 1)) t)
                      ((= (expmod n i p) 1) nil)
                      (t (iter (+ i 1))))))
     (and (iter 1) (= (expmod n (- p 1) p) 1))))

;;sicp
;; a^n (mod m)
(defun expmod (a n m)
    (cond ((= 0 n) 1)
          ((evenp n) (mod (square (expmod a (div n 2) m)) m))
          (t (mod (* a (expmod a (- n 1) m)) m)) ))


(defun primitive-root (p)
    (labels
     ((iter (n) (cond ((> n p) nil)
                      ((primitive-root-p n p) n)
                      (t (iter (+ n 1))))))
     (iter 2)))


(defun ind (r a p)
    (labels ((iter (i) (cond ((> i p) nil)
                             ((= (expmod r i p) a) i)
                             (t (iter (+ i 1))) ))) (iter 0)))



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

;;
(defun cadr (ls)
    (car (cdr ls)) )

(defun cddr (ls)
    (cond ((null ls) nil)
          ((null (cdr ls)) nil)
          (t (cdr (cdr ls))) ))


(defun arg1 (f)
    (elt f 1) )

(defun arg2 (f)
    (elt f 2) )

(defun arg3 (f)
    (elt f 3) )

(defun op (f)
    (elt f 0) )

(defun subst (old new f)
    (cond ((null f) '())
          ((equal (car f) old) (cons new (subst old new (cdr f))))
          ((atom (car f)) (cons (car f) (subst old new (cdr f))))
          (t (cons (subst old new (car f)) (subst old new (cdr f)))) ))


(defun remove (x f)
    (cond ((null f) '())
          ((eq (car f) x) (remove x (cdr f)))
          (t (cons (car f) (remove x (cdr f)))) ))

;;-----------------------------------------------------------------------
;;

(defun opcode (op)
    (case op
       ((+) '+)
       ((-) '-)
       ((/) '/)
       ((*) '*)
       ((^) '^)
       (t (if (subrp op)
              op
              (error "opecode else: " op) )) ))

(defun weight (op)
    (case op
       ((+) 1)
       ((-) 1)
       ((/) 2)
       ((*) 3)
       ((^) 4)
       (t (if (subrp op)
              6
              9 )) ))


(defun infix->prefix (fmla)
    (infip fmla) )

(defun infip (fmla)
    (if (atom fmla)
        fmla
        (inf1 fmla '() '()) ))

(defun inf1 (fmla optr opln)
    (if (or (< (weight (op fmla)) 5) (> (weight (op fmla)) 7))
        (inf2 (cdr fmla) optr (cons (infip (car fmla)) opln))
        (inf3 (cddr fmla) optr (cons (list (op fmla) (infip (arg1 fmla))) opln)) ))

(defun inf2 (fmla optr opln)
    (cond ((and (null fmla) (null optr)) (car opln))
          ((and (not (null fmla)) (or (null optr) (> (weight (car fmla))
                                                     (weight (car optr)))))
           (inf1 (cdr fmla) (cons (car fmla) optr) opln))
          (t
           (inf2
            fmla
            (cdr optr)
            (cons (list (opcode (car optr)) (cadr opln) (car opln)) (cddr opln))))))

(defun inf3 (fmla optr opln)
    (cond ((and (null fmla) (null opln)) (car opln))
          ((and (not (null fmla)) (or (null? optr) (> (weight (car fmla))
                                                      (weight (cadr fmla)))))
           (inf1 (cdr fmla) (cons (car fmla) optr) opln))
          (t (inf2 fmla optr opln))))



;;
;;
(defun prefix->infix (fmla)
    (if (atom fmla)
        fmla
        (pretf fmla) ))

(defun pretf (f)
    (if (= (weight (op f)) 6)
        (let ((arg (pret1 (arg1 f) -1)))
           ;
           (if (atom? arg)
               (cons (op f) arg)
               (list (op f) (pret1 (arg1 f) -1)) ))
        (pret1 f -1)))

(defun pret1 (f win)
    (cond ((null f) f)
          ((atom f) (list f))
          ((and (eq? (op f) '-) (null (arg2 f))) (append '(-) (pret2 (arg1 f) 1)))
          (t (let ((wf (weight (op f))))
                (if (< wf win)
                    (list (pret2 f wf))
                    (pret2 f wf) )))))

(defun pret2 (f wf)
    (append (pret1 (arg1 f) wf) (list (op f)) (pret1 (arg2 f) wf)) )


;;----------------------------------------------------------------------------------
;;

(defun /nestp (f)
    (and (listp f) (eq (op f) '/)) )

(defun +nestp (f)
    (and (listp f) (eq (op f) '+)) )

(defun *simp1 (f)
    (cond ((atom f) (list f))
          ((eq (op f) '*) (mapcan #'*simp1 (cdr f)))
          (t (list (simps f))) ))


(defun *simp (f)
    (cond ((= (length f) 3)
           (cond ((eq (arg1 f) 0) 0)                                                      ;0*a=0
                 ((eq? (arg2 f) 0) 0)                                                     ;a*0=0
                 ((eq (arg1 f) 1) (simps (arg2 f)))                                       ;1*a=a
                 ((eq (arg2 f) 1) (simps (arg1 f)))                                       ;a*1=a
                 ((/nestp (arg2 f))
                  (list
                   '/
                   (list '* (simps (arg1 f)) (simps (arg1 (arg2 f))))
                   (simps (arg2 (arg2 f)))));(* a (/ b c)) = (/ (* a b) c)
                 ((not (lat (cdr f))) (cons '* (*simp1 f)))
                 ((eq (arg1 f) (arg2 f)) (list '^ (arg1 f) 2))                            ;(* a a) -> (^ a 2) 
                 (t (list '* (simps (arg1 f)) (simps (arg2 f))))))
          ((member 0 (cdr f)) 0)                                                          ; (* a .. 0 .. z)=0 
          ((and (numberp (arg1 f)) (listp (arg2 f)) (eq (op (arg2 f)) '+))
           (simps (cons '+ (mapcar (lambda (c)
                                      (list '* (arg1 f) c)) (cdr (arg2 f))))))
          ((not (lat (cdr f))) (cons '* (*simp1 f)))
          (t (cons '* (mapcar #'simps (cdr f))))))

;;
(defun lat (ls)
    (cond ((null ls) t)
          ((atom (car ls)) (lat (cdr ls)))
          (t nil) ))

(defun +simp (f)
    (cond ((eq (arg1 f) 0) (if (= (length f) 3)
                               (arg2 f)
                               (simps (cons '+ (cddr f))) ))
          ((and (eq (arg2 f) 0) (= (length f) 3)) (simps (arg1 f)))
          ((eq (arg1 f) (arg2 f)) (list '* 2 (simps (arg1 f))))
          (t (cons '+ (mapcar #'simps (cdr f))))))



(defun -simp (f)
    (cond ((= (length f) 2)
           (cond ((+nestp (arg1 f))
                  (list
                   '+
                   (list '* -1 (simps (arg1 (arg1 f))))
                   (list '* -1 (simps (arg2 (arg1 f))))));(- (+ a b)) = (+ (* -1 a) (* -1 b))
                 (t (list '* -1 (simps (arg1 f))))));(-a)=(* -1 a)
          ((= (length f) 3)
           (cond ((eq (arg1 f) (arg2 f)) 0)                                               ;(- a a) = 0
                 (t (list '+ (simps (arg1 f)) (list '* -1 (simps (arg2 f)))))))))
; (- a b) = (+ a (* -1 b))

(defun /simp (f)
    (cond ((eq (arg1 f) (arg2 f)) 1)
          ((eq (arg1 f) 0) 0)
          ((eq (arg2 f) '()) 0)
          ((numberp (arg2 f)) (simps (list '* (/ 1 (arg2 f)) (arg1 f))))
          ((and
            (listp (arg2 f))
            (= (length (arg2 f)) 3)
            (numberp (arg1 (arg2 f)))
            (symbolp (arg2 (arg2 f))))
           (let ((cdf (arg2 f)))
              (if (= (length (cddr cdf)) 1)
                  (list '/ (simps (list '* (/ 1 (arg1 cdf)) (arg1 f))) (arg2 cdf))
                  (list
                   '/
                   (simps (list '* (/ 1 (arg1 cdf)) (arg1 f)))
                   (simps (cons (car cdf) (cddr cdf)))))))
          (t (list '/ (simps (arg1 f)) (simps (arg2 f))))))


(defun ^simp (f)
    (cond ((eq (arg2 f) 0) 1)
          ((eq (arg2 f) 1) (arg1 f))
          (t (list (op f) (simps (arg1 f)) (simps (arg2 f)))) ))

;;
(defun sin-simp (f)
    (cond ((and (consp (arg1 f)) (eq? (op (arg1 f)) '*) (eq (arg1 (arg1 f)) 'i))
           (list '* 'i (list 'sinh (arg2 (arg1 f)))))
          ((and (number? (arg1 f)) (= (arg1 f) 0)) 0)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/6 pi))) 0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/4 pi))) '(/ (sqrt 2) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/3 pi))) '(/ (sqrt 3) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/2 pi))) 1)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 2/3 pi))) '(/ (sqrt 3) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 3/4 pi))) '(/ (sqrt 2) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 5/6 pi))) 0.5)
          ((eq (arg1 f) 'pi) 0)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 7/6 pi))) -0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 5/4 pi))) '(* -1 (/ (sqrt 2) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 4/3 pi))) '(* -1 (/ (sqrt 3) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 3/2 pi))) -1)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 4/3 pi))) '(* -1 (/ (sqrt 3) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 7/4 pi))) '(* -1 (/ (sqrt 2) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 11/6 pi))) -0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 2 pi))) 0)
          ((and
            (consp (arg1 f))
            (eq (op (arg1 f)) '*)
            (numberp (arg1 (arg1 f)))
            (> (arg1 (arg1 f)) 2)
            (eq (arg2 (arg1 f)) 'pi))
           (sin-simp (list 'sin (list '* (- (arg1 (arg1 f)) 2) 'pi))))
          ((atom (arg1 f)) (list 'sin (arg1 f)))
          (t
           (let ((arg (simps (arg1 f))))
              (if (equal arg (arg1 f))
                  (list 'sin arg)
                  (cos-simp (list 'sin (simps (arg1 f)))))))))

;;
(defun cos-simp (f)
    (cond ((and (number? (arg1 f)) (= (arg1 f) 0)) 1)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/6 pi))) '(/ (sqrt 3) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/4 pi))) '(/ (sqrt 2) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/3 pi))) 0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/2 pi))) 0)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 2/3 pi))) -0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 3/4 pi))) '(* -1 (/ (sqrt 2) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 5/6 pi))) '(* -1 (/ (sqrt 3) 2)))
          ((eq (arg1 f) 'pi) -1)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 7/6 pi))) '(* -1 (/ (sqrt 3) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 5/4 pi))) '(* -1 (/ (sqrt 2) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 4/3 pi))) -0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 3/2 pi))) 0)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 4/3 pi))) 0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 7/4 pi))) '(/ (sqrt 2) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 11/6 pi))) '(/ (sqrt 3) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 2 pi))) 1)
          ((and
            (consp (arg1 f))
            (eq? (op (arg1 f)) '*)
            (numberp (arg1 (arg1 f)))
            (> (arg1 (arg1 f)) 2)
            (eq? (arg2 (arg1 f)) 'pi))
           (cos-simp (list 'cos (list '* (- (arg1 (arg1 f)) 2) 'pi))))
          ((atom (arg1 f)) (list 'cos (arg1 f)))
          (t
           (let ((arg (simps (arg1 f))))
              (if (equal arg (arg1 f))
                  (list 'cos arg)
                  (cos-simp (list 'cos (simps (arg1 f)))))))))

;;
(defun atan-simp (f)
    (cond ((and (numberp (arg1 f)) (= (arg1 f) 1)) '(/ pi 4))
          ((and (consp (arg1 f)) (equal (arg1 f) '(/ 1 sqrt (3)))) '(/ pi 6))
          ((and (consp (arg1 f)) (equal (arg1 f) '(sqrt 3))) '(/ pi 3))
          ((and (number? (arg1 f)) (= (arg1 f) -1)) '(* -1 (/ pi 4)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* -1 (/ 1 sqrt (3))))) '(* -1 (/ pi 6)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* -1 (sqrt 3)))) '(* -1 (/ pi 3)))
          (t
           (let ((arg (simps (arg1 f))))
              (if (equal arg (arg1 f))
                  (list 'atan arg)
                  (atan-simp (list 'atan (simps (arg1 f)))))))))

;;
(defun sinh-simp (f)
    (cond ((and (consp (arg1 f)) (eq (op (arg1 f)) '*) (eq (arg1 (arg1 f)) 'i))
           (list '* 'i (list ('sin (arg2 (arg1 f))))))
          (t f)))


;;
(defun !simp (f)
    (if (>= (arg1 f) 0)
        (factorial (arg1 f))
        (- (factorial (abs (arg1 f)))) ))

;;
(defun factorial (n)
    (if (= n 0)
        1
        (* n (factorial (- n 1))) ))

(defun simps (f)
    (if (atom? f)
        f
        (case (op f)
           ((+) (+simp f))
           ((-) (-simp f))
           ((*) (*simp f))
           ((/) (/simp f))
           ((^) (^simp f))
           ((sin) (sin-simp f))
           ;;
           ((cos) (cos-simp f))
           ;;
           ((atan) (atan-simp f))
           ;;
           ((sinh) (sinh-simp f))
           ;;
           ((!) (!simp f))
           ;;
           (t f) ) ))

(defun simpf (ff)
    (let ((fs (simps ff)))
       (if (equal ff fs)
           ff
           (simpf fs) )))



;;
(defun *comnum (f numb symb imag)
    (cond ((null f)
           (let ((n (*numb numb))
                 (i (*imag imag)) )
              ;�����֒ǉ� ����
              (cond ((and (null n) (null i)) (reverse symb))
                    ((and (not (null n)) (null i)) (cons n (reverse symb)))
                    ((and (null n) (not (null i))) (cons i (reverse symb)))
                    (t
                     (if (atomp i)
                         (cons i (cons n (reverse symb)))
                         (cons 'i (cons (- n) (reverse symb))))))))
          ((numberp (car f)) (*comnum (cdr f) (cons (car f) numb) symb imag))
          ((eq (car f) 'i) (*comnum (cdr f) numb symb (cons (car f) imag)))
          (t (*comnum (cdr f) numb (cons (car f) symb) imag))))

(defun *numb (s)
    (if (null s)
        '()
        (eval (cons '* s)) ))

;;�����֒ǉ� ����
(defun *imag (s)
    (if (null s)
        '()
        (case (mod (length s) 4)
           ((1) 'i)
           ((2) -1)
           ((3) '(* -1 i))
           ((0) 1) ) ))


(defun +comnum (f numb symb)
    (cond ((null f)
           (cond ((null numb) (reverse symb))
                 ((eq (length numb) 1) (append (reverse symb) numb))
                 (t (reverse (cons (eval (cons '+ numb)) symb)))))
          ((numberp (car f)) (+comnum (cdr f) (cons (car f) numb) symb))
          (t (+comnum (cdr f) numb (cons (car f) symb)))))

(defun comnum (f)
    (cond ((null f) '())
          ((atom f) f)
          ((and (atom (op f)) (eq (length f) 2)) (list (op f) (comnum (arg1 f))))
          ((and (eq (op f) '^) (numberp (arg1 f)) (numberp (arg2 f))) (expt (arg1 f) (arg2 f)))
          ((eq (op f) '*)
           (let ((ans (*comnum (cdr f) '() '() '())))
              (cond ((eq (length ans) 1) (car ans))
                    ((lat ans) (cons '* ans))
                    (t (cons '* (mapcar #'comnum ans))))))
          ((eq (op f) '+)
           (let ((ans (+comnum (cdr f) '() '())))
              (cond ((eq (length ans) 1) (car ans))
                    ((lat ans) (cons '+ ans))
                    (t (cons '+ (mapcar #'comnum ans))))))
          (t (list (op f) (comnum (arg1 f)) (comnum (arg2 f))))))


(defun simpc (ff)
    (let ((fc (comnum ff)))
       (if (equal ff fc)
           ff
           (simpc fc) )))

(defun simpl (ff)
    (simpc (simpf ff)) )


;;---------------------------------------------------------------------------
;;;
;;;
(defun *aux (f var)
    (if (null? f)
        '()
        (cons
         (cons (derive (car f) var) (cdr f))
         (mapcar (lambda (c)
                    (cons (car f) c)) (*aux (cdr f) var)))))

;; *
(defun *deriv (fmla var)
    (cons '+ (mapcar (lambda (c)((cons '* c))) (*aux (cdr fmla) var))) )

;; /
(defun /deriv (fmla var)
    (list
     '/
     (list
      '-
      (list '* (derive (arg1 fmla) var) (arg2 fmla))
      (list '* (arg1 fmla) (derive (arg2 fmla) var)))
     (list '^ (arg2 fmla) 2)))


;; +
(defun +deriv (fmla var)
    (cons '+ (mapcar (lambda (c)
                        (derive c var)) (cdr fmla))) )

;; -
(defun -deriv (fmla var)
    (cons '- (mapcar (lambda (c)
                        (derive c var)) (cdr fmla))) )


(defun derive (fmla var)
    (cond ((atom fmla) (if (eq fmla var)
                           1
                           0 ))
          ((free fmla var) 0)
          (t
           (case (op fmla)
              ((+) (+deriv fmla var))
              ((-) (-deriv fmla var))
              ((*) (*deriv fmla var))
              ((/) (/deriv fmla var))
              ((^) (^deriv fmla var))
              ((sin) (sderiv fmla var))
              ((cos) (cderiv fmla var))
              ((tan) (tderiv fmla var))
              ((asin) (asderiv fmla var))
              ((acos) (acderiv fmla var))
              ((atan) (atderiv fmla var))
              ((log) (logderiv fmla var))
              ((sinh) (shderiv fmla var))
              ((cosh) (chderiv fmla var))
              (t "Undefined") ))))


;;sin
(defun sderiv (f var)
    (list '* (derive (arg1 f) var) (list 'cos (arg1 f))) )
;;cos
(defun cderiv (f var)
    (list '* (derive (arg1 f) var) (list '* -1 (list 'sin (arg1 f)))) )

;;tan
(defun tderiv (f var)
    (list '/ (derive (arg1 f) var) (list '^ (list 'cos (arg1 f)) 2)) )

;;asin
(defun asderiv (f var)
    (list '/ (derive (arg1 f) var) '(sqrt (- 1 (^ x 2)))) )

;;acos
(defun acderiv (f var)
    (list '* -1 (list '/ (derive (arg1 f) var) '(sqrt (- 1 (^ x 2))))) )

;;atan
(defun atderiv (f var)
    (list '/ (derive (arg1 f) var) '(+ 1 (^ x 2))) )

;;log
(defun logderiv (f var)
    (list '/ (derive (arg1 f) var) (arg1 f)) )

;;sinh
(defun shderiv (f var)
    (list '* (derive (arg1 f) var) (list 'cosh (arg1 f))) )

;;cosh
(defun chderiv (f var)
    (list '* (derive (arg1 f) var) (list 'sinh (arg1 f))) )

(defun ^deriv (fmla var)
    (cond ((and (depend fmla var) (free (arg2 fmla) var))
           (list
            '*
            (list '* (arg2 fmla) (derive (arg1 fmla) var))
            (list '^ (arg1 fmla) (- (arg2 fmla) 1))))
          ((and (depend fmla var) (free (arg1 fmla) var))
           (list '* (derive (arg2 fmla) var) (list '^ 'e (arg2 fmla))))
          (t (^daux fmla var))))


(defun depend (fmla var)
    (cond ((atom fmla) (if (eq fmla var)
                           t
                           nil ))
          ((eq (length fmla) 2) (depend (arg1 fmla) var))
          ((eq (length fmla) 3) (or (depend (arg1 fmla) var) (depend (arg2 fmla) var)))
          ((depend (cddr fmla) var) t)
          (t nil)))

(defun free (fmla var)
    (not (depend fmla var)) )

(defun nderive (n fmla var)
    (if (= n 0)
        (simpl fmla)
        (nderive (- n 1) (simpl (derive fmla var)) var) ))

(defun dif2 (fmla var)
    (simpl (nderive 2 fmla var)) )

(defun diff (fmla var)
    (prefix->infix (dif (infix->prefix fmla) var)) )


(defun dif (fmla var)
    (simpl (derive fmla var)) )

;;-----------------------------------------------------------------
(defun sint (f var)
    (list '* (list '/ -1 (derive (arg1 f) var)) (list 'cos (arg1 f))) )

(defun cint (f var)
    (list '* (list '/ 1 (derive (arg1 f) var)) (list 'sin (arg1 f))) )

(defun tint (f var)
    (list '* (list '/ -1 (derive (arg1 f) var)) (list 'log (list 'cos (arg1 f)))) )

;;cot
(defun ctint (f var)
    (list '* (list '/ 1 (derive (arg1 f) var)) (list 'log (list 'sin (arg1 f)))) )


(defun lint (f var)
    (list '* (list '/ 1 (derive (arg1 f) var)) (list '- (list '* var (list 'log (arg1 f))) var)) )

(defun ^int (f var)
    (cond ((and (mlin (arg1 f) var) (free (arg2 f) var))
           (cond ((eq (arg2 f) -1)
                  (list '* (list '/ 1 (derive (arg1 f) var)) (list 'log (arg1 f))))
                 (t
                  (list
                   '*
                   (list '/ 1 (list '* (+ (arg2 f) 1) (derive (arg1 f) var)))
                   (list '^ (arg1 f) (+ (arg2 f) 1))))))
          ((and (eq (arg1 f) 'e) (mlin (arg2 f) var))
           (list '* (list '/ 1 (derive (arg2 f) var)) (list '^ 'e (arg2 f))))
          (t
           (list
            '*
            (list '/ (derive (arg2 f) var))
            (list '* (list '/ 1 (list 'log (arg1 f))) (list '- (arg1 f) (arg2 f)))))))

(defun mlin (ff var)
    (if (and (depend ff var) (free (simpl (derive ff var)) var))
        t
        nil ))

(defun intf (f var)
    (cond ((free f var) (cons '* (list f var)))
          ((eq f var) (list '* (/ 1 2) (list '^ f 2)))
          (t
           (case (op f)
              ((sin) (sint f var))
              ((cos) (cint f var))
              ((tan) (tint f var))
              ((cot) (ctint f var))
              ((log) (lint f var))
              ((^) (^int f var))
              (t
               (cond ((matchf '(/ 1 x) f var)                                              ;integral 1/x = log|x|+C
                      (list 'log (arg1 f)))
                     ((matchf '(/ 1 (+ (^ x 2) ?c)) f var)                                 ;integral 1/(x^2+b) = 1/b atan(x/b) + C
                      (list
                       '*
                       (list '/ 1 (list 'sqrt ?c))
                       (list 'atan (list '/ var (list 'sqrt ?c)))))
                     ((matchf '(/ 1 (sqrt (- ?c (^ x 2)))) f var)                          ;integral 1/��d^-x^2 = asin(x/d)+C
                      (list '* (list 'asin (list '/ var (list 'sqrt ?c))))))) ))))

(defun intl (f var)
    (let ((fi (simpl (intf f var))))
       (if (equal fi f)
           f
           (simpl fi) )))


(defun varp (x)
    (and (symbolp x) (char= (character x) #\?)) )

(defun character (x)
    (elt (convert x <string>) 0) )


(defun memberp (a b)
    (if (member a b)
        t
        nil ))

(defun matchf1 (p f var)
    (if (and (matchf2 (arg1 p) (arg1 f) var) (matchf2 (arg2 p) (arg2 f) var))
        t
        (if (and
             (memberp (op p) '(+ *))
             (matchf2 (arg2 p) (arg1 f) var)
             (matchf2 (arg1 p) (arg2 f) var))
            t
            nil)))

(defun matchf2 (p f var)
    (cond ((and (null p) (null f)) t)
          ((or (null p) (null f)) t)
          ((equal p f) t)
          ((varp p) (setq ?c f) t)
          ((and (eq f var) (symbolp p)) t)
          ((and (consp p) (consp f) (eq (op p) (op f)) (= (length f) 3)) (matchf1 p f var))
          ((and (consp p) (consp f) (eq (op p) (op f)) (= (length f) 2))
           (matchf2 (arg1 p) (arg1 f) var))
          (t nil)))

(defglobal ?c '())
(defun matchf (p f var)
    (setq ?c '())
    (matchf2 p f var) )
