#|
The Rules of Representing Roman Numerals:

① I, V, X, L, C, D, M represent 1, 5, 10, 50, 100, 500, 1000 respectively.

② These characters are combined in writing. 
In this case, larger numbers are written to the left. 
For example, 23 is written as XXIII, and writing XIIXI or similar combinations is incorrect. 
When all numeral symbols are added together, they represent the displayed number.

③ 4 and 9 are written as IV and IX respectively. 
These are numbers obtained by subtracting the left numeral from the right numeral. 
This subtraction rule is only used when the right numeral is exactly 5 times or 10 times the value of the left numeral. 
For instance, 99 is written as XCIX, but writing IC is not permitted.
|#

(import "test")

(defun roman-to-arabian (str)
    (cond ((string= str "") 0)
          (t (let* ((right (roman-to-arabian (string-cdr str)))
                    (next (if (>= (length str) 2) (elt str 1) nil)))
                (case (elt str 0)
                   ((#\I) (if (member next '(#\V #\X #\L #\C #\D #\M)) (- right 1) (+ right 1)))
                   ((#\V) (if (member next '(#\X #\L #\C #\D #\M)) (- right 5) (+ right 5)))
                   ((#\X) (if (member next '(#\L #\C #\D #\M)) (- right 10) (+ right 10)))
                   ((#\L) (if (member next '(#\C #\D #\M)) (- right 50) (+ right 50)))
                   ((#\C) (if (member next '(#\D #\M)) (- right 100) (+ right 100)))
                   ((#\D) (if (member next '(#\M)) (- right 500) (+ right 500)))
                   ((#\M) (+ right 1000)))))))

(defun multiplep (m n)
    (or (and (>= n (* 5 m)) (= (mod n (* 5 m)) 0))
        (and (>= n (* 10 m)) (= (mod n (* 10 m)) 0))))


(defun string-cdr (str)
    (list-to-string (cdr (convert str <list>))))

(defun list-to-string (ls)
    (cond ((null ls) "")
          (t (string-append (create-string 1 (car ls))
                            (list-to-string (cdr ls))))))
    

(defun arabian-to-roman (n)
    (cond ((= n 0) "")
          ((>= n 1000) (string-append "M" (arabian-to-roman (- n 1000))))
          ((>= n 500) (string-append "D" (arabian-to-roman (- n 500))))
          ((>= n 100) (string-append "C" (arabian-to-roman (- n 100))))
          ((>= n 50) (string-append "L" (arabian-to-roman (- n 50))))
          ((>= n 10) (string-append "X" (arabian-to-roman (- n 10))))
          ((>= n 5) (string-append "V" (arabian-to-roman (- n 5))))
          (t (string-append "I" (arabian-to-roman (- n 1))))))


($test (roman-to-arabian "XXIII") 23)
($test (roman-to-arabian "VI") 6)
($test (roman-to-arabian "IV") 4)
($test (roman-to-arabian "XCIX") 99)

($test (arabian-to-roman 2) "II")
($test (arabian-to-roman 6) "VI")