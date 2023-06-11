;;; bug compiled flet
#| 
(defun foo (x)
    (flet ((f (x)
               (+ x 3) ))
        (flet ((f (x)
                   (+ x (f x)) ))
            (f x))) )
|#
;; alpha convert
;; if body of flet is flet, alpha convert.

(defun boo (x)
    (flet ((f (x)
               (+ x 3) ))
        (flet ((f (x)
                   (+ x (f x)) ))
            (f x))) )

(defun bar (x)
    (flet ((f (x)
               (+ x 3) ))
      (f x)))