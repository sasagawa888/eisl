;;compile tests free-variable in nested lambda.


(defun foo (x)
    ((lambda (x) x) x))
