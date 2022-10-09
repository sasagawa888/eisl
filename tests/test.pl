;; test code from PAIP

(assert (likes kim robin))
(assert (likes sandy lee))
(assert (likes sandy kim))
(assert (likes robin cats))
(assert ((likes sandy _x) (likes _x cats)))
(assert ((likes kim _x) (likes _x lee) (likes _x kim)))
(assert (likes _x _x))
