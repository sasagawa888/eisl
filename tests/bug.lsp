
(defun pfib (n)
    (the <fixnum> n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (pcall + (pfib (- n 1)) (pfib (- n 2))))))

