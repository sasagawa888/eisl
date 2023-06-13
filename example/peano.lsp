;;; Peano axioms
;;; e.g. 3 = (s (s (s 0)))
;;;      0 = 0

(defconstant zero 0)

(defun plus1 (x)
    (cons 's (list x)))

(defun minus1 (x)
    (elt x 1))

(defun plus (x y)
    (if (equal y zero)
        x 
        (plus (plus1 x) (minus1 y))))

(defun minus (x y)
    (if (equal y zero)
        x 
        (minus (minus1 x) (minus1 y))))

(defun mult (x y)
    (if (equal x zero)
        zero
        (mult (plus x x) (minus1 y))))

(defun greater (x y)
    (> (length x) (length y)))

(defun eqn (x y)
    (equal x y))

(defun peano (n)
    (if (= n 0)
        zero
        (plus1 (peano (- n 1)))))

(defun integer (x)
    (if (equal x zero)
        0
        (+ 1 (integer (minus1 x)))))