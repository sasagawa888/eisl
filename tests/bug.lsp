(defun foo (x)
    (let ((y (car x)))
       (bar (elt x 0))
       (bar (elt x 0))
       (bar (elt x 0))))

(defun bar (x) 
    (print x))

(defun last (xs)
  (if (or (null xs) (null (cdr xs)))
      xs
    (last (cdr xs))))

(defun my-nconc (xs ys)
  (set-cdr ys (last xs))
  xs)