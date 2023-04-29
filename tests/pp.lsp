(defun pp-quote (x lm)
    (pp-text ""')
    (pp1 (car (cdr x)) (+ lm 1) t) )
