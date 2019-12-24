(defmacro test(form1 form2 :rest pred)
  (cond ((null pred)
         `(if (equal ,form1 ',form2)
              (format (standard-output) "" ',form1)
              ;;(format (standard-output) "~S is ok~%" ',form1)
              (format (standard-output) "~S is bad~%" ',form1)))
        ((and (not (null pred))(consp form1))
         `(if (,@pred ,form1 ',form2)
              (format (standard-output) "" ',form1)
              ;;(format (standard-output) "~S is ok~%" ',form1)
              (format (standard-output) "~S is bad ~S ~%" ',form1 ,form1)))))


(defglobal x 10)

(test (let ((x ()))
   (tagbody
    (setq x (cons 1 x))
    (setq x (cons 2 x))
    (setq x (cons 3 x)))
   x) (3 2 1) equal)

(defglobal x nil)
(test (unwind-protect
     (progn (setq x (cons 1 x)) x)
   (setq x (cons 2 x))
   (setq x (cons 3 x))) (1) equal)
(test x (3 2 1) equal)
;;; ;;;

 (test (let ((x ()))
    (tagbody
     (setq x (cons 1 x))
     ((lambda () (go tag1)))
     (setq x (cons 2 x))
     tag1
     (setq x (cons 3 x)))
    x) (3 1) equal)
