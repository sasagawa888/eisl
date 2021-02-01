(defun foo (x)
    (char= #\newline #\C) )

(defun boo (x)
    (eq x 'abc) )


(defun foo1 (x :rest y)
    (print x)
    (print y) )

