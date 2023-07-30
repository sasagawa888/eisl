
(defun foo (a b c)
    (plock (print a)(print b)(print c)))

(defun bar (a b c)
    (pexec (count 0 a) (count 1 b) (count 2 c)))

(defun pcount (n)
    (plet ((a (count 1 (div n 2)))
           (b (count (+ (div n 2) 1) n)))
     t))

(defun count (m n)
    (for ((i m (+ i 1)))
         ((= i n) t)
         (sin (cos (tan i)))))

