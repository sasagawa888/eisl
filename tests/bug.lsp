
(defglobal f (lambda (x) x))

(defun foo (x)
    (setq f (lambda (y) x)))

