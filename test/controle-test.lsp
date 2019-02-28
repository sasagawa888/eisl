;
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
              (format (standard-output) "~S is bad~%" ',form1)))))

;;; ;;
(test #2a((a b c) (d e f)) #2a((a b c) (d e f)) equal)
(test #1a(a b c) #(a b c) equal)
(test #0a1 #0a1 equal)
(test #\a #\a equal)
(test 145932 145932 equal)
(test "abc" "abc" equal)
(test #(a b c) #(a b c) equal)
(test (quote a) a equal)
(test (quote #(a b c)) #(a b c) equal)
(test (quote (+ 1 2)) (+ 1 2) equal)
(test '() nil equal)
(test 'a a equal)
(test '#(a b c) #(a b c) equal)
(test '(car l) (car l) equal)
(test '(+ 1 2) (+ 1 2) equal)
(test '(quote a) (quote a) equal)
(test ''a (quote a) equal)
(test (car ''a) quote equal)
(defglobal x 0)
(test x 0 eql)
(test (let ((x 1)) x) 1 eql)
(test x 0 eql)
(defglobal x 2)
(test (+ x 1) 3 equal)
(test (setq x 4) 4 equal)
(test (+ x 1) 5 equal)
(test (let ((x 1)) (setq x 2) x) 2 equal)
(test (+ x 1) 5 equal)

(defglobal x 2)
(test (+ x 1) 3 equal)
(test (setf x 4) 4 equal)
(test (+ x 1) 5 equal)
(test (let ((x 1)) (setf x 2) x) 2 equal)
(test (+ x 1) 5 equal)
(setq x '(1 . 2))
(test (setf (car x) 2) 2 equal)
(test x (2 . 2) equal)

(defmacro first (spot) `(car ,spot))
(defglobal x '(10 20))
(test (first x) 10 equal)
(test (setf (first x) 2) 2)
(test x (2 20) equal)
;;;
(defmacro first2 (spot) `(first ,spot))
(defglobal x '(10 20))
(test (first2 x) 10 equal)
(test (setf (first2 x) 2) 2)
(test x (2 20) equal)
;;;
(defmacro last (spot) `(cdr ,spot))
(defglobal x '(10 20))
(test (last x) (20) equal)
(test (setf (last x) 2) 2)
(test x (10 . 2) equal)
;;;
(defmacro last2 (spot) `(last ,spot))
(defglobal x '(10 20))
(test (last2 x) (20) equal)
(test (setf (last2 x) 2) 2)
(test x (10 . 2) equal)
;;;
(defmacro my-dynamic (spot) `(dynamic ,spot))
(defdynamic x 3)
(test (my-dynamic x) 3 equal)
(test (setf (my-dynamic x) 2) 2)
(test (my-dynamic x) 2 equal)
;;;
(defmacro my-dynamic2 (spot) `(my-dynamic ,spot))
(defdynamic x 3)
(test (my-dynamic x) 3 equal)
(test (setf (my-dynamic2 x) 2) 2)
(test (my-dynamic2 x) 2 equal)
;;;
(defmacro my-elt (seq z) `(elt ,seq ,z))
(defglobal x '(10 20 30))
(test (my-elt x 0) 10)
(test (my-elt x 1) 20)
(test (my-elt x 2) 30)
(test (setf (my-elt x 1) 2) 2)
(test x (10 2 30) equal)
;;;
(defmacro my-elt2 (seq z) `(my-elt ,seq ,z))
(defglobal x '(10 20 30))
(test (my-elt2 x 0) 10)
(test (my-elt2 x 1) 20)
(test (my-elt2 x 2) 30)
(test (setf (my-elt2 x 1) 2) 2)
(test x (10 2 30) equal)

(defglobal x 0)
(defmacro p () 'x)
(test (setf (p) 9) 9)
(test x 9)
(test (let ()) nil)
(test (let () 1) 1 equal)
(test (let () 1 2) 2 equal)
(test (let ((x 2) (y 3))
   (* x y)) 6 equal)
(test (let ((x 2) (y 3))
   (let ((x 7)
     (z (+ x y)))
     (* z x))) 35 equal)
(test (let ((x 1) (y 2))
   (let ((x y) (y x))
     (list x y))) (2 1) equal)

(test (let ((x 2) (y 3))
   (let* ((x 7)
      (z (+ x y)))
     (* z x))) 70 equal)
(test (let ((x 1) (y 2))
   (let* ((x y) (y x))
     (list x y))) (2 2) equal)

(let* ((z 1)) z)

 (let* ((y 1)
        (l (lambda () y))
    (z 2))
   (setq x (cons l (lambda () z))))
(test (funcall (car x)) 1)
(test (funcall (cdr x)) 2)
;;;
(defglobal x ())
(let* ((y 1)
        (l (lambda () y))
    (y 2))
   (setq x (cons l (lambda () y))))
(test (funcall (car x)) 1)
(test (funcall (cdr x)) 2)
(defdynamic x 3)
(test (dynamic x) 3 equal)

(defdynamic x 3)
(test (dynamic x) 3 equal)
(test (setf (dynamic x) 4) 4 equal)
(test (dynamic x) 4 equal)

(defun foo-1 (x)
     (dynamic-let ((y x))
              (bar-1 1)))
(defun bar-1 (x)
     (+ x (dynamic y)))
(test (foo-1 2) 3 equal)

;;;
(defdynamic dynx 1)
(test (dynamic-let ((dynx 2)) (dynamic dynx)) 2)
(test (dynamic dynx) 1)
;;;
(test (if 1 2 3) 2 eql)
(test (if 1 2) 2 eql)
(test (if nil 2 3) 3 eql)
(test (if nil 2) nil)
(test (if (> 3 2) 'yes 'no) yes)
(test (if (> 2 3) 'yes 'no) no)
(test (if (> 2 3) 'yes) nil)
(test (if (> 3 2) (- 3 2) (+ 3 2)) 1 eql)
(test (let ((x 7))
   (if (< x 0) x (- x))) -7 eql)

(test (cond) nil equal)
(test (cond (t)) t)
(test (cond (1)) 1 eql)
(test (cond ((> 3 2) 'greater)
       ((< 3 2) 'less)) greater)
(test (cond ((> 3 3) 'greater)
       ((< 3 3) 'less)) nil)
(test (cond ((> 3 3) 'greater)
       ((< 3 3) 'less)
       (t 'equal)) equal)

(test (case 'a ((a b c)) (t 1)) nil)
(test (case 'a ((a b c) 0) (t 1)) 0 eql)
(test (case 'a ((a b c) 0 1) (t 1)) 1 eql)
(test (case 'z ((a b c) 0) (t)) nil)
(test (case 'z ((a b c) 0) (t 0)) 0 eql)
(test (case 'z ((a b c) 0) (t 0 1)) 1 eql)
(test (case 'd ((a b c) 0) ((z) 1)) nil)
;;;
(test (case (* 2 3)
       ((2 3 5 7) 'prime)
       ((4 6 8 9) 'composite)) composite)
(test (case (car '(c d))
       ((a) 'a)
       ((b) 'b)) nil)
(test (case (car '(c d))
       ((a e i o u) 'vowel)
       ((y) 'semivowel)
       (t 'consonant)) consonant)

(test (let ((char #\u))
   (case char
     ((#\a #\e #\i #\o #\u) 'vowels)
     (t 'consonates))) vowels)

(test (case-using #'string= "a" (("a" "b" "c")) (t 2)) nil)
(test (case-using #'string= "a" (("a" "b" "c") 0) (t 2)) 0 equal)
(test (case-using #'string= "a" (("a" "b" "c") 0 1) (t 2)) 1 equal)
(test (case-using #'string= "z" (("a" "b" "c") 2) (t)) nil)
(test (case-using #'string= "z" (("a" "b" "c") 2) (t 0)) 0 equal)
(test (case-using #'string= "z" (("a" "b" "c") 2) (t 0 1)) 1 equal)
(test (case-using #'string= "d" (("a" "b" "c") 0) (("z") 1)) nil)

;;;
(test (case-using #'= (+ 1.0 1.0)
         ((1) 'one)
         ((2) 'two)
         (t 'more)) two)
(test (case-using #'string= "bar"
         (("foo") 1)
         (("bar") 2)) 2 eql)

;;;
(test (progn) nil)
(test (progn 1) 1 eql)
(test (progn 1 2) 2 eql)
;;;
(test (progn (defglobal *global-x* 1) (defglobal *global-y* 2)) *global-y*)
(test *global-x* 1 eql)
(test *global-y* 2 eql)
;;;
(defglobal x 0)
(test (progn
   (setq x 5)
   (+ x 1)) 6 eql)

;
(test (while nil) nil)
(test (while nil 1) nil)
(test (let ((x '()) (i 5))
   (while (> i 0)
     (setq x (cons i x))
     (setq i (- i 1)))
   x) (1 2 3 4 5) equal)

;;; arguments count

(test (for () (t)) nil)
(test (for () (t t)) t)
(test (for () (t 1)) 1 eql)
(test (for () (t 1 2)) 2 eql)
(test (for ((vec (vector 0 0 0 0 0))
       (i 0 (+ i 1)))
      ((= i 5) vec)
      (setf (elt vec i) i)) #(0 1 2 3 4) equal)

(test (let ((x '(1 3 5 7 9)))
   (for ((x x (cdr x))
     (sum 0 (+ sum (car x))))
    ((null x) sum))) 25 eql)
;;; arguments count

(defglobal x nil)
(for ((i 0 (+ i 1)))
        ((= i 10))
        (if (= i 0) (setq x (lambda () i))))
(test (funcall x) 10 eql)


(test (block x) nil)
(test (block nil) nil)
(test (block x 1) 1 eql)
(test (block x 1 2) 2 eql)
;;;
(defglobal x nil)
(test (block b
    (setq x (cons 1 x))
    (setq x (cons 2 x))
    999) 999 eql)
(test x (2 1) equal)
;;;
(defglobal x nil)
(test (block b
    (setq x (cons 1 x))
    (return-from b 888)
    (setq x (cons 2 x))
    999) 888 eql)
(test x (1) equal)
;;;
(defglobal x nil)
(defun terminate-1 (x) (return-from b x))
(test (block x
    (+ 10 (return-from x 6) 22)) ;;; Bad programming style
 6 eql)
(defun f1 ()
   (block b
      (let ((f (lambda () (return-from b 'exit))))
        ;; big computation
        (f2 f))))

(defun f2 (g)
   ;; big computation
   (funcall g))
(test (f1) exit)
(test (block sum-block
    (for ((x '(1 a 2 3) (cdr x))
          (sum 0 (+ sum (car x))))
         ((null x) sum)
         (cond ((not (numberp (car x))) (return-from sum-block 0)))))
 0 eql)

(defun bar-2 (x y)
   (let ((foo #'car))
     (let ((result
        (block bl
           (setq foo (lambda () (return-from bl 'first-exit)))
           (if x (return-from bl 'second-exit) 'third-exit))))
       (if y (funcall foo) nil)
       result)))
(test (bar-2 t nil) second-exit)
(test (bar-2 nil nil) third-exit)

;;; closure
(test (block b
    (lambda () 1)
    (return-from b 999)) 999 eql)
(test (block b
    (lambda () 1)
    (lambda () 2)
    (return-from b 999)) 999 eql)
(test (block b
    ((lambda (x) (return-from b x)) 999)) 999 eql)

(test (catch 'a) nil)
(test (catch 'a 1) 1 eql)
(test (catch 'a 1 2) 2 eql)
;;;
(defglobal x nil)
(test (catch 'c
   (setq x (cons 1 x))
   (setq x (cons 2 x))
   999) 999 eql)
(test x (2 1) equal)
;;;
(defglobal x nil)
(test (catch 'c
   (setq x (cons 1 x))
   (throw 'c 888)
   (setq x (cons 2 x))
   999) 888 eql)
(test x (1) equal)

;;;
(defglobal x nil)
(defun terminate-2 (x) (throw 'c x))
(test (catch 'c
   (setq x (cons 1 x))
   (terminate-2 777)
   (setq x (cons 2 x))
   999) 777 eql)
(test x (1) equal)
;;;
(defun foo-3 (x)
   (catch 'block-sum (bar-3 x)))

(defun bar-3 (x)
   (for ((l x (cdr l))
     (sum 0 (+ sum (car l))))
    ((null l) sum)
    (cond ((not (numberp (car l))) (throw 'block-sum 0)))))

(test (foo-3 '(1 2 3 4)) 10 eql)
(test (foo-3 '(1 2 a 4)) 0 eql)
;;; closure
(test (catch 'c
    (lambda () 1)
    (throw 'c 999)) 999 eql)
(test (catch 'c
    (lambda () 1)
    (lambda () 2)
    (throw 'c 999)) 999 eql)
(test (catch 'c
    ((lambda (x) (throw 'c x)) 999)) 999 eql)

(test (tagbody) nil)
(test (tagbody 1) nil)
(test (tagbody 1 2) nil)
(test (let ((x ()))
   (tagbody
    (setq x (cons 1 x))
    (setq x (cons 2 x))
    (setq x (cons 3 x)))
   x) (3 2 1) equal)
(test (let ((x ()))
   (tagbody
    (setq x (cons 1 x))
    tag     (setq x (cons 2 x))
    (setq x (cons 3 x)))
   x) (3 2 1) equal)
(test (let ((x ()))
   (tagbody
    (setq x (cons 1 x))
    (go tag)
    (setq x (cons 2 x))
    tag     (setq x (cons 3 x)))
   x) (3 1) equal)

;;;
;;; (test (let ((x ()))
;;;    (tagbody
;;;     (setq x (cons 1 x))
;;;     (lambda () 1)
;;;     (go tag1)
;;;     (setq x (cons 2 x))
;;;     tag1
;;;     (setq x (cons 3 x)))
;;;    x) (3 1) equal)
;;; (test (let ((x ()))
;;;    (tagbody
;;;     (setq x (cons 1 x))
;;;     (lambda () 1)
;;;     (lambda () 2)
;;;     (go tag1)
;;;     (setq x (cons 2 x))
;;;     tag1
;;;     (setq x (cons 3 x)))
;;;    x) (3 1) equal)
;;; (test (let ((x ()))
;;;    (tagbody
;;;     (setq x (cons 1 x))
;;;     ((lambda () (go tag1)))
;;;     (setq x (cons 2 x))
;;;     tag1
;;;     (setq x (cons 3 x)))
;;;    x) (3 1) equal)
;;;
(test (unwind-protect 1) 1 eql)
;;; ;;;
(defglobal x nil)
(test (unwind-protect
     (progn (setq x (cons 1 x)) x)
   (setq x (cons 2 x))
   (setq x (cons 3 x))) (1) equal)
(test x (3 2 1) equal)
;;; ;;;
(defglobal x nil)
(test (catch 'c
  (unwind-protect
      (progn (setq x (cons 1 x))
         (throw 'c 777)
         888)
    (setq x (cons 2 x))
    999)) 777 eql)
(test x (2 1) equal)
;;;
(defglobal x nil)
(defun nest1 (y)
     (unwind-protect
         (progn (setq x (cons 1 x))
            (nest2 y))
       (setq x (cons 2 x))))
(defun nest2 (y)
     (unwind-protect
         (progn (setq x (cons 3 x))
            (throw 'exit y))
       (setq x (cons 4 x))))
(test (catch 'exit
   (nest1 777)) 777 eql)
(test x (2 4 3 1) equal)
;;;
(defun foo-4 (x)
   (catch 'duplicates
     (unwind-protect (bar-4 x)
       (for ((l x (cdr l)))
        ((null l) (remove-property l 'label) 'unused)
        (remove-property (car l) 'label)))))

(defun bar-4 (l)
   (cond ((and (symbolp l) (property l 'label))
      (throw 'duplicates 'found))
     ((symbolp l) (setf (property l 'label) t))
     ((bar-4 (car l)) (bar-4 (cdr l)))
     (t nil)))

(test (foo-4 '(a b c)) t)
(test (property 'a 'label) nil)
(test (foo-4 '(a b a c)) found)
(test (property 'a 'label) nil)

(defun test ()
   (catch 'outer (test2)))

(defun test2 ()
   (block inner
      (test3 (lambda ()
           (return-from inner 7)))))

(defun test3 (fun)
   (unwind-protect (test4) (funcall fun)))

(defun test4 ()
   (throw 'outer 6))
