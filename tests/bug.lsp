(defun find-double-perfect (n)
    (labels ((iter (m ls)
               (cond ((> m n) ls)
                     ((double-perfect-number-p m) (iter (+ m 1) (cons m ls)))
                     (t (iter (+ m 1) ls)) )))
        (iter 1 '())))

