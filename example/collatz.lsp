;;; collatz problem

(defun collatz (n)
    (format (standard-output) "~D->" n)
    (cond ((= n 1) t)
          ((= (mod n 2) 0) (collatz (div n 2)))
          (t (collatz (+ (* 3 n) 1)))))