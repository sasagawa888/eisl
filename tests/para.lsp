;;; test paralell

(defun foo ()
    (plet ((a (fib 8))
           (b (fib 9))) (+ a b)))

(defun bar (n)
    (plet ((a (fib (- n 1)))
           (b (fib (- n 2)))) (+ a b)))

(defun fib (n)
    (print n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib (- n 1)) (fib (- n 2))))))

(defun fact (n)
    (if (= n 0)
        1
        (* n (fact (- n 1)))))