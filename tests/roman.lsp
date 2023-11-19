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

Why XIIXI is incorrect?

|#

(import "test")

(defun roman-to-arabian (str)
    (cond ((string= str "") 0)
          (t (let* ((right (roman-to-arabian (string-cdr str)))
                    (next (if (>= (length str) 2) (elt str 1) nil)))
                (case (elt str 0)
                   ((#\I) (cond ((member next '(#\I nil)) (+ right 1))
                                ((member next '(#\V #\X)) (- right 1))
                                (t (error "not permitted"))))
                   ((#\V) (cond ((member next '(#\I #\V nil)) (+ right 5))
                                ((member next '(#\L #\C)) (- right 5))
                                (t (error "not permitted"))))
                   ((#\X) (cond ((member next '(#\I #\V #\X nil)) (+ right 10))
                                ((member next '(#\L #\C #\D #\M)) (- right 10))
                                (t (error "not permitted"))))
                   ((#\L) (cond ((member next '(#\I #\V #\X #\L nil)) (+ right 50))
                                ((member next '(#\D)) (- right 50))
                                (t (error "not permitted"))))
                   ((#\C) (cond ((member next '(#\I #\V #\X #\L #\C nil)) (+ right 100))
                                ((member next '(#\D #\M)) (- right 100))
                                (t (error "not permitted"))))
                   ((#\D) (cond ((member next '(#\I #\V #\X #\L #\C #\D nil)) (+ right 500))
                                ((member next '(#\M)) (- right 500))
                                (t (error "not permitted"))))
                   ((#\M) (+ right 1000)))))))



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

;($error (roman-to-arabian "XIIXI") <simple-error>)
($error (roman-to-arabian "IC") <simple-error>)

($test (arabian-to-roman 2) "II")
($test (arabian-to-roman 6) "VI")