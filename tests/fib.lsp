(defun foo (n)
    (if (= n 0)
        t 
        (foo (- n 1))))


(defun bar (x :rest y)
    (if (= x 0)
        t 
        (bar (- x 1) y 1)))

(defun fib* (n)
    (cond ((= n 1.0) 1.0)                              ;基底１
          ((= n 2.0) 1.0)                              ;基底２
          (t (+ (fib* (- n 1.0))
                (fib* (- n 2.0)) ))))

(defun fib (n)
    (cond ((= n 1) 1)
          ((= n 2) 1)
          (t (+ (fib (- n 1)) (fib (- n 2)))) ))


