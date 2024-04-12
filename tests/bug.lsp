;;compile tests free-variable in nested lambda.


(defun foo (x)
    (lambda () (lambda () x)))

(import "lazy")

(defun tarai* (x y z)
    (dtarai (delay x) (delay y) (delay z)))


(defun dtarai (x y z)
    (format (standard-output) "~A ~A ~A~%" (force x) (force y) (force z))
    (if (<= (force x) (force y))
        (force y)
        (dtarai (delay (dtarai (delay (- (force x) 1)) (force y) (force z)))
                (delay (dtarai (delay (- (force y) 1)) (force z) (force x)))
                (delay (dtarai (delay (- (force z) 1)) (force x) (force y))))))
