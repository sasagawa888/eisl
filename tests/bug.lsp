;;compile tests free-variable in nested lambda.


(defun foo (x)
    (let ((a 0))
        ((lambda (x) (setq x 0)) x)))

(defun bar (x)
    (lambda () (lambda () x)))

