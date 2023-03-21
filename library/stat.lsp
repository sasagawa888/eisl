;;; stat

(defmodule stat
    (import "sort" quick-sort)
    
    (defpublic average (ls)
        (quotient (apply #'+ ls) (length ls)) )

    (defpublic median (ls)
        (let* ((n (length ls))
               (m (div n 2))
               (ls1 (quick-sort ls)) )
            (if (oddp n)
                (elt ls1 m)
                (average (list (elt ls (- m 1)) (elt ls m))))))

    (defpublic mode (ls)
        (let ((ls1 (pack (quick-sort ls))))
           (mode1 (cdr ls1) (car ls1))))

    (defun mode1 (ls x)
        (cond ((null ls) (car x))
              ((> (length (car ls)) (length x)) (mode1 (cdr ls) (car ls)))
              (t (mode1 (cdr ls) x))))

    (defun oddp (n)
        (= (mod n 2) 1))

    (defun pack (x)
        (let ((y (pack1 (car x) '() x)))
           (if (null (cdr y))
               y
               (cons (car y) (pack (cdr y))))))

    (defun pack1 (x y z)
        (cond ((null z) (cons y nil))
              ((not (eq x (car z))) (cons y z))
              (t (pack1 x (cons (car z) y) (cdr z)))))

)
