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
        


