;;distributed parallel

(defun pfib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (dp-call #'+ (fib (- n 1)) (fib (- n 2))))))


(defun fib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib (- n 1)) (fib (- n 2))))))


(defun ptarai (x y z)
    (if (<= x y)
        y
          (dp-call #'tarai (tarai (- x 1) y z)
                 (tarai (- y 1) z x)
                 (tarai (- z 1) x y))))


(defun tarai (x y z)
    (if (<= x y)
        y
          (tarai (tarai (- x 1) y z)
                 (tarai (- y 1) z x)
                 (tarai (- z 1) x y))))
