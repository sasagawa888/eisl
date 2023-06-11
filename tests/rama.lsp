(defun rum (max base)
    (labels ((r (n)
               (if (> n max)
                   base
                   (sqrt (+ 1 (* n (r (+ n 1))))) )))
        (r 2)))

(defun foo (n m)
    (if (= n 0)
        (sqrt m)
        (sqrt (foo (- n 1) m)) ))
