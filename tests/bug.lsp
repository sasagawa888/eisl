;;compile tests free-variable in nested lambda.
(import "lazy")

(defun tarai* (x y z)
    (dtarai (delay x) (delay y) (delay z)))


(defun dtarai (x y z)
    (print (force x))
    (if (<= (force x) (force y))
        (force y)
        (dtarai (delay (dtarai (delay (- (force x) 1)) y z))
                (delay (dtarai (delay (- (force y) 1)) z x))
                (delay (dtarai (delay (- (force z) 1)) x y)))))
