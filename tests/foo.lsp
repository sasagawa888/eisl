;;; test code for paralell compile

(defun foo (x y) (+ x y))
(defun foo1 (x y) (= x y))
(defun foo2 (x y) (> x y))
(defun foo3 (x y) (>= x y))
(defun foo4 (x y) (< x y))
(defun foo5 (x y) (<= x y))
(defun foo6 (x y) (mod x y))
(defun foo7 (x y) (- x y))
(defun foo8 (x y) (* x y))
(defun foo9 (x y) (div x y))
(defun foo10 (x y) (quotient x y))

