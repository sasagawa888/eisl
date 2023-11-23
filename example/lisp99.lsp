;;p01
(defun my-last (x)
    (if (null (cdr x))
        (car x)
        (my-last (cdr x)) ))

#|
(defun my-last (x)
    (car (reverse x)) )

(defun my-last (x)
    (while (not (null (cdr x)))
       (setq x (cdr x)))
    (car x) )
|#
;;p02
(defun my-but-last (x)
    (if (< (length x) 2)
        (error "my-but-last: illegal argument" x)
        (my-but-last1 x) ))

(defun my-but-last1 (x)
    (if (null (cdr (cdr x)))
        x
        (my-but-last1 (cdr x)) ))

;;> (my-but-last '(a b c d))
;;(C D)

;;p03
(defun element-at (x n)
    (elt x (- n 1)) )

;;> (element-at '(a b c d e f) 3)
;;C

;;p04
(defun elements (ls)
    (if (null ls)
        0
        (+ 1 (elements (cdr ls))) ))

;;p05
(defun my-reverse (ls)
    (if (null ls)
        nil
        (append (my-reverse (cdr ls)) (list (car ls))) ))

;;p06
(defun palindromep (ls)
    (equal ls (reverse ls)) )


;;p07
(defun my-flatten (x)
    (cond ((null x) nil)
          ((atom x) (list x))
          (t (append (my-flatten (car x)) (my-flatten (cdr x)))) ))

;;> (my-flatten '(a (b (c d) e)))
;;(A B C D E)
;;> 

;;p08
(defun compress (ls)
    (compress1 (car ls) (cdr ls)) )

(defun compress1 (x ls)
    (cond ((null ls) nil)
          ((eq x (car ls)) (compress1 x (cdr ls)))
          (t (cons x (compress1 (car ls) (cdr ls)))) ))

;;p09
(defun pack (x)
    (let ((y (pack1 (car x) '() x)))
       (if (null (cdr y))
           y
           (cons (car y) (pack (cdr y))) )))

(defun pack1 (x y z)
    (cond ((null z) (cons y nil))
          ((not (eq x (car z))) (cons y z))
          (t (pack1 x (cons (car z) y) (cdr z))) ))

;;> (pack '(a a a b b b b c c))
;;((A A A) (B B B B) (C C))
;;> 

;;p10
(defun encode (x)
    (mapcar (lambda (y) 
               (list (length y) (car y))) (pack x)) )

;;> (encode '(a a a b b b b c c))
;;((3 A) (4 B) (2 C))
;;> 

;;p11
(defun encode-modified (x)
    (mapcar (lambda (y) 
               (if (= (length y) 1)
                   (car y)
                   (list (length y) (car y)) )) (pack x)))

;;> (encode-modified '(a a a b b b b c c))
;;((3 A) (4 B) (2 C))
;;> 

;;p12
(defun decode (x)
    (mapcan (lambda (y) 
               (if (atom y)
                   (list y)
                   (decode1 (elt y 0) (elt y 1)) )) x))

(defun decode1 (n x)
    (if (= n 0)
        '()
        (cons x (decode1 (- n 1) x)) ))

;;> (decode '((3 a) (4 B) (1 c)))
;;(A A A B B B B C)
;;> 

;;p13
(defun encode-direct (x)
    (let ((y (encode-direct1 (car x) 0 x)))
       (if (null (cdr y))
           (if (= (elt (car y) 0) 0)
               (car (car y))
               y )
           (cons (car y) (encode-direct (cdr y))))))

(defun encode-direct1 (x n z)
    (cond ((null z) (cons (list n x) nil))
          ((not (eq x (car z))) (cons (list n x) z))
          (t (encode-direct1 x (+ n 1) (cdr z))) ))

;;> (encode-direct '(a a a b b b b c c))
;;((3 A) (4 B) (2 C))
;;> 

;;p14
(defun dupli (x)
    (if (null x)
        '()
        (append (list (car x) (car x)) (dupli (cdr x))) ))

;;> (dupli '(a b c))
;;(A A B B C C)


;;p15
(defun repli (x n)
    (if (null x)
        '()
        (append (repli1 (car x) n) (repli (cdr x) n)) ))

(defun repli1 (x n)
    (if (= n 0)
        '()
        (cons x (repli1 x (- n 1))) ))

;;another version 
(defun replic (x n)
    (mapcan (lambda (y) (repli1 y n)) x) )
;;> (repli '(a b c) 3)
;;(A A A B B B C C C)

;;p16
(defun drop (x n)
    (drop1 x nil n 1) )

(defun drop1 (x y n m)
    (cond ((null x) (reverse y))
          ((= n m) (drop1 (cdr x) y n 1))
          (t (drop1 (cdr x) (cons (car x) y) n (+ m 1))) ))

;;> (drop '(a b c d e f g h i j) 3)
;;(A B D E G H J)
;;> 

;;p17
;;recursive
(defun split (x n)
    (split1 nil x n) )

(defun split1 (x y n)
    (cond ((null y) nil)
          ((= n 0) (list (reverse x) y))
          (t (split1 (cons (car y) x) (cdr y) (- n 1))) ))

;;imperative
#|
(defun split (x n)
    (for ((front nil (cons (car rear) front))
          (rear x (cdr rear))
          (m n (- m 1)) )
         ((= m 0)
          (list (reverse front) rear) )))
|#
;;> (split '(a b c d) 2)
;;((A B) (C D))
;;>


;;p18
(defun slice (x m n)
    (cond ((and (= m 1) (= n 1)) (list (car x)))
          ((and (= m 1) (> n 1)) (cons (car x) (slice (cdr x) m (- n 1))))
          (t (slice (cdr x) (- m 1) (- n 1))) ))
;;> (slice '(a b c d e f g h i k) 3 7)
;;(C D E F G)


;;p19
(defun rotate (x i)
    (cond ((= i 0) x)
          ((> i 0) (rotate (append (cdr x) (list (car x))) (- i 1)))
          ((< i 0) (rotate (append (rotate1 x) (rotate2 x)) (+ i 1))) ))

(defun rotate1 (x)
    (if (null (cdr x))
        x
        (rotate1 (cdr x)) ))

(defun rotate2 (x)
    (if (null (cdr x))
        '()
        (cons (car x) (rotate2 (cdr x))) ))

;;> (rotate '(a b c d e f g h) 3)
;;(D E F G H A B C)
;;> (rotate '(a b c d e f g h) -2)
;;(G H A B C D E F)
;;> 

;;P20
(defun remove-at (ls n)
    (if (= n 1)
        (cdr ls)
        (cons (car ls) (remove-at (cdr ls) (- n 1))) ))

;;> (remove-at '(a b c) 2)
;;(A C)
;;>

;;p21
(defun insert-at (x ls n)
    (if (= n 1)
        (cons x ls)
        (cons (car ls) (insert-at x (cdr ls) (- n 1))) ))

;;> (insert-at 'alfa '(a b c d) 2)
;;(A ALFA B C D)
;;>

;;p22
;recursive
(defun range (m n)
    (if (>= m n)
        nil
        (cons m (range (+ m 1) n)) ))
;imperative
#|
(defun range (m n)
    (for ((m1 m (+ m1 1))
          (ls nil (cons m1 ls)) )
         ((>= m1 n)
          (reverse ls) )))
|#
;;> (range 4 7)
;;(4 5 6)
;;> 

;;p23 
(defun rnd-select (ls n)
    (rnd-select1 ls n '()) )


(defun rnd-select1 (ls n rand)
    (if (= n 0)
        '()
        (let ((m (random (length ls))))
           (if (member m rand)
               (rnd-select1 ls n rand)
               (cons (nth ls m) (rnd-select1 ls (- n 1) (cons m rand))) ))))

(defun nth (ls n)
    (if (= n 0)
        (car ls)
        (nth (cdr ls) (- n 1)) ))


;;p24
(defun lotto-select (n s)
    (rnd-select (range 1 s) n) )

;;p25
(defun rnd-permu (ls)
    (rnd-select ls (length ls)) )

;;p26
;; () -> ()
;; n=1 (a b c) -> ((a)(b)(c))
;; else (append (cons a (combination (- n 1) '(b c)))
;;              (combination n '(b c))) 
(defun combination (n x)
    (cond ((null x) nil)
          ((= n 1) (mapcar (lambda (y) (list y)) x))
          (t  (append (mapcar (lambda (y) (cons (car x) y)) (combination (- n 1) (cdr x)))
                      (combination n (cdr x))))))
;;; e.g. (a b c)
;;; (append 
;;;  (cons 'a (permutation '(b c))
;;;  (cons 'b (permutation '(a c))
;;;  (cons 'c (permutation '(a b))
;;; )
(defun permutation (x)
    (if (null (cdr x))
        (list x)
        (permutation1 x 0 (length x))))

(defun permutation1 (x s e)
    (if (= s e) 
        nil    
        (append (mapcar (lambda (y) (cons (elt x s) y))
                        (permutation (remove-at x (+ s 1))))
                (permutation1 x (+ s 1) e))))


;;p31
(defun is-prime (n)
    (labels ((iter (m limit)
               (cond ((> m limit) t)
                     ((= (mod n m) 0) nil)
                     (t (iter (+ m 2) limit)) )))
        (cond ((< n 2) nil)
              ((= (mod n 2) 0) nil)
              (t (iter 3 (isqrt n))))))

;;> (is-prime 2017)
;;T
;;> (is-prime 7)
;;T
;;>

;;p32
(defun my-gcd (x y)
    (cond ((< x y) (my-gcd y x))
          ((= (mod x y) 0) y)
          (t (my-gcd y (mod x y))) ))

;;p33
(defun coprime (x y)
    (= (my-gcd x y) 1) )

;;p34
(defun totient-phi (n)
    (length (divisors n)) )

(defun divisors (n)
    (divisors1 nil 1 n) )

(defun divisors1 (ls m n)
    (cond ((= m n) (cons m ls))
          ((= (mod n m) 0) (divisors1 (cons m ls) (+ m 1) n))
          (t (divisors1 ls (+ m 1) n)) ))

;;p35
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

;;> (prime-factors 123)
;;(41 3)

;;p36
(defun prime-factors-mult (n)
    (prime-factors-mult1 (prime-factors n)) )

(defun prime-factors-mult1 (x)
    (let ((y (prime-factors-mult2 (car x) 0 x)))
       (if (null (cdr y))
           y
           (cons (car y) (prime-factors-mult1 (cdr y))) )))

(defun prime-factors-mult2 (x n z)
    (cond ((null z) (cons (list x n) nil))
          ((not (= x (car z))) (cons (list x n) z))
          (t (prime-factors-mult2 x (+ n 1) (cdr z))) ))

;;> (prime-factors-mult 315)
;;((7 1) (5 1) (3 2))
;;> 

;;p37
(defun phi (n)
    (if (= n 1)
        1
        (convert
         (* n (product (lambda (ls) 
                          (- 1 (quotient 1 (car ls)))) (prime-factors-mult n)))
         <integer>)))

(defun product (f ls)
    (if (null ls)
        1
        (* (funcall f (car ls))
           (product f (cdr ls)))))

;;p38

;;> (time (totient-phi 10090))
;;Elapsed Time=0.016000
;;<undef>
;;> (time (phi 10090))
;;Elapsed Time=0.000000
;;<undef>
;;> 

;;p40
(defun goldbach (n)
    (let ((i 3))
       (block exit
          (while (< i n)
             (if (and (is-prime i) (is-prime (- n i)))
                 (return-from exit (list i (- n i)))
                 (setq i (+ i 2)) )))))


;;p46
(defun table (v1 v2 exp)
    (let ((exp1 (alpha v1 v2 exp))
          (x nil)(y nil))
        (setq x t)(setq y t)(format (standard-output) "~A ~A ~A~%" (tf x) (tf y) (tf (eval exp1)))
        (setq x t)(setq y nil)(format (standard-output) "~A ~A ~A~%" (tf x) (tf y) (tf (eval exp1)))
        (setq x nil)(setq y t)(format (standard-output) "~A ~A ~A~%" (tf x) (tf y) (tf (eval exp1)))
        (setq x nil)(setq y nil)(format (standard-output) "~A ~A ~A~%" (tf x) (tf y) (tf (eval exp1)))))

(defun alpha (v1 v2 exp)
    (cond ((null exp) nil)
          ((eq v1 exp) 'x)
          ((eq v2 exp) 'y)
          ((atom exp) exp)
          (t (cons (alpha v1 v2 (car exp))
                   (alpha v1 v2 (cdr exp))))))

(defun tf (x)
    (if (null x) 'nil 'true))

;;p49
(defun gray (n)
    (if (= n 1)
        '("0" "1")
        (gray1 (gray (- n 1)))))

(defun gray1 (ls)
    (append (mapcar (lambda (x) (string-append "0" x)) ls)
            (mapcar (lambda (x) (string-append "1" x)) ls)))


;;p54A
(defun istree (x)
    (if (and (= (length x) 3) (atom (elt x 0)) (atom (elt x 1)) (atom (elt x 2)))
        t
        (and
         (= (length x) 3)
         (atom (elt x 0))
         (or (atom (elt x 1)) (istree (elt x 1)))
         (or (atom (elt x 2)) (istree (elt x 2))))))

;;>  (istree '(a (b nil nil) nil))
;;T
;;>  (istree '(a (b nil nil)))
;;NIL
;;> 
