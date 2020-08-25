
(defun listn (n)
   (if (not (= 0 n))
       (cons n (listn (- n 1)))))

(defun takl (x y z)
   (if (not (shorterp y x))
       z
       (takl (takl (cdr x) y z)
             (takl (cdr y) z x)
             (takl (cdr z) x y))))