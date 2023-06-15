;;; test code for compiler

;;; tail call
(defun factorial (n acc)
  (if (<= n 1)
      acc
      (factorial (- n 1) (* n acc))))

;;; test code for formatter
(defun pp-quote (x lm)
    (pp-text "'")
    (pp1 (car (cdr x)) (+ lm 1) t) )