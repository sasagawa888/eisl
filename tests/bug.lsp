;;multi-process
;; idea memo

(mp-create 3)

(defun tarai (x y z)
    (if (<= x y)
        y
        (mp-call tarai (tarai (- x 1) y z) 
                       (tarai (- y 1) z x)
                       (tarai (- z 1) x y))))

(mp-close)



