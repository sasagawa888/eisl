;;; test paralell

(defun foo ()
    (plet ((a (fact 10))
           (b (fact 11))) (+ a b)))

(defun fact (n)
    (if (= n 0)
        1
        (* n (fact (- n 1)))))