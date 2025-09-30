
(defun foo (x)
    (lambda (x) x))

(defun bar (x)
    (lambda (y) x))

(defun setup ()
        (set-property (lambda (x env) (assert x env)) 'assert 'builtin))
