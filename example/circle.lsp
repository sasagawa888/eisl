;;; numerical integration 
;;; calculate area of circle

(defun / (x y) (quotient x y ))
(defun ^ (x y) (expt x y))

(defun area (r n)
    (let* ((theta (/ (* 2 *pi*) n))
           (triang (* (^ r 2) (^ (cos (/ theta 2)) 2) (sin (/ theta 2)))))
        (* n triang)))





