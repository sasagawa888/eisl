
(defun pcount (n)
    (plet ((a (count 1 (div n 2)))
           (b (count (+ (div n 2) 1) n)))
     t))

(defun count (m n)
    (for ((i m (+ i 1)))
         ((= i n) t)
         (sin (cos (tan i)))))

