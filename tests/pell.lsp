;;Pell number
  
(defun pell (n)
    (cond ((= n 1) 1)
          ((= n 2) 2)
          (t (+ (* 2 (pell (- n 1)))
                (pell (- n 2))))))

