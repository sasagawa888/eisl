;; test code from PAIP

(assert (likes kim robin))
(assert (likes sandy lee))
(assert (likes sandy kim))
(assert (likes robin cats))
(assert ((likes sandy _x) (likes _x cats)))
(assert ((likes kim _x) (likes _x lee) (likes _x kim)))
(assert (likes _x _x))


;; factorial
(assert (fact 0 1))
(assert ((fact _n _m)
         (is _n1 (- _n 1))
         (fact _n1 _m1)
         (is _m (* _n _m1))))
        
;; call lisp function
(assert ((ack _x _y _z)(is _z (ack _x _y))))

(defun ack (m n)
    (cond ((= m 0) (+ n 1))
          ((= n 0) (ack (- m 1) 1))
          (t (ack (- m 1) (ack m (- n 1)))) ))
