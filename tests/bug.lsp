
(defglobal f nil)

(defun foo (x)
    (setq f (lambda (y) x)))

