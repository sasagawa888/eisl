;;compile tests free-variable in nested lambda.


(defun foo (x)
    (lambda () (lambda () x)))
