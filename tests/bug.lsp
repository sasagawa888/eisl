;;compile tests free-variable in nested lambda.


(defun foo (x)
    (let ((a 0))
        ((lambda (x) (setq a x)) x)
        a))

(defun bar (x)
    (lambda () (lambda () x)))

