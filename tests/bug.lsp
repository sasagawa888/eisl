

(defun foo ()
    (bar (format (standard-output) "~A ~%" 1)
         (format (standard-output) "~A ~%" 2)
         (format (standard-output) "~A ~%" 3)))


(defun bar (x y z) nil)
         