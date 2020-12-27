;リスト : FizzBuzz 問題
; written by M.hiroi

(defun display (x)
  (format (standard-output) "~A " x))

(defun fizzbuzz ()
  (for ((x 0 (+ x 1)))
       ((> x 100))
       (cond ((= (mod x 15) 0)
              (display "FizzBuzz"))
             ((= (mod x 3) 0)
              (display "Fizz"))
             ((= (mod x 5) 0)
              (display "Buzz"))
             (t (display x)))))