#|
tower of Hanoi

e.g. (move 3 'a 'b 'c)
|#

(defun move (n x y z)
    (cond ((= n 1)
           (format (standard-output) "move ~A from ~A to ~A~%" n x y))
          (t (move (- n 1) x z y)
             (format (standard-output) "move ~A from ~A to ~A~%" n x y)
             (move (- n 1) z y x))))

            
