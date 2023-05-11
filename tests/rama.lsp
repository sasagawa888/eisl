(defun rum (max base)
  (labels
      ((r (n)
         (if (> n max)
             base
             (sqrt (+ 1 (* n (r (+ n 1))))))))
    (r 2)))
