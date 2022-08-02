(defun foo (x)
    (if (= x 0)
        1
        (* x (foo (- x 1)))))


