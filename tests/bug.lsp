;;multi-process
;; idea memo

(defun tarai (x y z)
    (if (<= x y)
        y
        (let (r (mp-exec (tarai (- x 1) y z) 
                         (tarai (- y 1) z x)
                         (tarai (- z 1) x y)))
                (tarai (elt r 0) (elt r 1) (elt r 2)))))


