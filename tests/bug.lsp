(defun foo (x)
    (let ((y (car x)))
       (bar (elt x 0))
       (bar (elt x 0))
       (bar (elt x 0))))

(defun bar (x) 
    (print x))


