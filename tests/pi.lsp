;; for BIGNUM test
;; calculate PI with bignum using brent-salamin method
;; e.g. (pi-brent-salamin 1000)

(defun square-root (x)
    (isqrt x) )

(defun square (x)
    (* x x) )


#|
;;For Common-Lisp
(defun div (x y)
    (floor x y))
|#

; Compute pi using the 'brent-salamin' method.
(defun pi-brent-salamin (nb-digits)
    (let ((one (expt 10 nb-digits)))
       (pi-brent-salamin1 one one (square-root (div (square one) 2)) (div one 4) 1) ))

(defun pi-brent-salamin1 (one a b tt x)
    (if (= a b)
        (div (square (+ a b)) (* 4 tt))
        (let ((new-a (div (+ a b) 2)))
           (pi-brent-salamin1 one
                              new-a
                              (square-root (* a b))
                              (- tt (div (* x (square (- new-a a))) one))
                              (* 2 x)))))

