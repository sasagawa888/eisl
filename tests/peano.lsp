;;; peano 

(defglobal zero 0)

(defun plus1 (x)
    (cons 's (list x)))

(defun minus1 (x)
    (elt x 1))
