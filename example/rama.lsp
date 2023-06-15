;;; Ramanujan's formula
;;; lim max=>inifinit ram(max,1) -> 2.0
;;; base is any number. 

(defun ram (max base)
    (labels ((r (n)
               (if (> n max)
                   base
                   (sqrt (+ 1 (* n (r (+ n 1))))) )))
        (r 2)))
