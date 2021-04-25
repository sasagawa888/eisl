
(defun foo ()
(let ((t1 (get-internal-real-time))
       (dummy (tak 24 12 6))
       (t2 (get-internal-real-time)))
       (print t1)
       (print t2)
   (< t1 t2))
)


(defun tak (x y z)
         (if (not (< y x))
             z
             (tak (tak (- x 1) y z)
                  (tak (- y 1) z x)
                  (tak (- z 1) x y))))
