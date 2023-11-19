#|
The Rules of Representing Roman Numerals:

I, V, X, L, C, D, M represent 1, 5, 10, 50, 100, 500, 1000 respectively.

repeat same symbol max 3 times.

subtruct when right numeric is 5 or 10 times multiple number of left numeric. 

|#

(import "test")

(defun roman-to-arabian (str)
   (roman-to-arabian1 (convert str <list>)))

(defun roman-to-arabian1 (ls)
    (cond ((null ls) 0)
          ((char= (car ls) #\I)
                       (cond ((singlep ls) (+ (roman-to-arabian1 (cdr ls)) 1))
                             ((doublep ls) (+ (roman-to-arabian1 (cdr (cdr ls))) 2))
                             ((triplep ls) (+ (roman-to-arabian1 (cdr (cdr (cdr ls)))) 3))
                             ((reversep ls) (- (roman-to-arabian1 (cdr ls)) 1))
                             (t (error "not permitted"))))                
          ((char= (car ls) #\V)
                       (cond ((singlep ls) (+ (roman-to-arabian1 (cdr ls)) 5))
                             ((doublep ls) (+ (roman-to-arabian1 (cdr (cdr ls))) 10))
                             ((triplep ls) (+ (roman-to-arabian1 (cdr (cdr (cdr ls)))) 15))
                             ((reversep ls) (- (roman-to-arabian1 (cdr ls)) 5))
                             (t (error "not permitted"))))
          ((char= (car ls) #\X)
                       (cond ((singlep ls) (+ (roman-to-arabian1 (cdr ls)) 10))
                             ((doublep ls) (+ (roman-to-arabian1 (cdr (cdr ls))) 20))
                             ((triplep ls) (+ (roman-to-arabian1 (cdr (cdr (cdr ls)))) 30))
                             ((reversep ls) (- (roman-to-arabian1 (cdr ls)) 10))
                             (t (error "not permitted"))))
          ((char= (car ls) #\L)
                       (cond ((singlep ls) (+ (roman-to-arabian1 (cdr ls)) 50))
                             ((doublep ls) (+ (roman-to-arabian1 (cdr (cdr ls))) 100))
                             ((triplep ls) (+ (roman-to-arabian1 (cdr (cdr (cdr ls)))) 150))
                             ((reversep ls) (- (roman-to-arabian1 (cdr ls)) 50))
                             (t (error "not permitted"))))
          ((char= (car ls) #\C)
                       (cond ((singlep ls) (+ (roman-to-arabian1 (cdr ls)) 100))
                             ((doublep ls) (+ (roman-to-arabian1 (cdr (cdr ls))) 200))
                             ((triplep ls) (+ (roman-to-arabian1 (cdr (cdr (cdr ls)))) 300))
                             ((reversep ls) (- (roman-to-arabian1 (cdr ls)) 100))
                             (t (error "not permitted"))))
          ((char= (car ls) #\D) 
                       (cond ((singlep ls) (+ (roman-to-arabian1 (cdr ls)) 500))
                             ((doublep ls) (+ (roman-to-arabian1 (cdr (cdr ls))) 1000))
                             ((triplep ls) (+ (roman-to-arabian1 (cdr (cdr (cdr ls)))) 1500))
                             ((reversep ls) (- (roman-to-arabian1 (cdr ls)) 500))
                             (t (error "not permitted"))))
          ((char= (car ls) #\M)
                       (cond ((singlep ls) (+ (roman-to-arabian1 (cdr ls)) 1000))
                             ((doublep ls) (+ (roman-to-arabian1 (cdr (cdr ls))) 2000))
                             ((triplep ls) (+ (roman-to-arabian1 (cdr (cdr (cdr ls)))) 3000))
                             (t (error "not permitted"))))))



(defun singlep (ls)
    (cond ((null (cdr ls)) t)
          ((smallerp (elt ls 1) (elt ls 0)) t)
          (t nil)))

(defun doublep (ls)
    (or (and (= (length ls) 2) (char= (elt ls 0) (elt ls 1)))
        (and (> (length ls) 2) (char= (elt ls 0) (elt ls 1)) (smallerp (elt ls 2) (elt ls 1)))))

(defun triplep (ls)
    (or (and (= (length ls) 3) (char= (elt ls 0) (elt ls 1)) (char= (elt ls 0) (elt ls 2)))
        (and (= (length ls) 3)
             (char= (elt ls 0) (elt ls 1))
             (char= (elt ls 0) (elt ls 2)) 
             (smallerp (elt ls 3) (elt ls 2)))))

(defun reversep (ls)
    (and (>= (length ls) 2) (multiplep (elt ls 0) (elt ls 1))))

(defun smallerp (l r)
    (cond ((char= l #\I) (member r '(#\V #\X #\L #\C #\D #\M)))
          ((char= l #\V) (member r '(#\X #\L #\C #\D #\M)))
          ((char= l #\X) (member r '(#\L #\C #\D #\M)))
          ((char= l #\L) (member r '(#\C #\D #\M)))
          ((char= l #\C) (member r '(#\D #\M)))
          ((char= l #\D) (member r '(#\M)))))

(defun multiplep (l r)
    (cond ((char= l #\I) (member r '(#\V #\X)))
          ((char= l #\V) (member r '(#\L)))
          ((char= l #\X) (member r '(#\L #\C)))
          ((char= l #\L) (member r '(#\D)))
          ((char= l #\C) (member r '(#\M)))
          ((char= l #\D) nil)))

(defun arabian-to-roman (n)
      (cond ((< n 0) (error "not permitted"))
            ((> n 3999) (error "not permitted"))
            (t (arabian-to-roman1 n))))

(defun arabian-to-roman1 (n)
    (cond ((= n 0) "")
          ((>= n 1000) (string-append "M" (arabian-to-roman1 (- n 1000))))
          ((= (div n 100) 9) (string-append "CM" (arabian-to-roman1 (- n 900))))
          ((= (div n 100) 4) (string-append "CD" (arabian-to-roman1 (- n 400))))
          ((>= n 500) (string-append "D" (arabian-to-roman1 (- n 500))))
          ((>= n 100) (string-append "C" (arabian-to-roman1 (- n 100))))
          ((= (div n 10) 9) (string-append "XC" (arabian-to-roman1 (- n 90))))
          ((= (div n 10) 4) (string-append "VC" (arabian-to-roman1 (- n 40))))
          ((>= n 50) (string-append "L" (arabian-to-roman1 (- n 50))))
          ((>= n 10) (string-append "X" (arabian-to-roman1 (- n 10))))
          ((= n 9) "IX")
          ((= n 4) "IV")
          ((>= n 5) (string-append "V" (arabian-to-roman1 (- n 5))))
          (t (string-append "I" (arabian-to-roman1 (- n 1))))))



($test (roman-to-arabian "XXIII") 23)
($test (roman-to-arabian "VI") 6)
($test (roman-to-arabian "IV") 4)
($test (roman-to-arabian "XCIX") 99)
($test (roman-to-arabian "CMXCIX") 999)

($error (roman-to-arabian "XIIXI") <simple-error>)
($error (roman-to-arabian "IC") <simple-error>)
($error (roman-to-arabian "DCDXCIX") <simple-error>)

($test (arabian-to-roman 2) "II")
($test (arabian-to-roman 6) "VI")
($test (arabian-to-roman 4) "IV")
($test (arabian-to-roman 99) "XCIX")
($test (arabian-to-roman 999) "CMXCIX")

