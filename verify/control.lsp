(import "test")
;;; -*- lisp -*-
;;;
;;; Chapter 6: Control Structure
;;;

($ap 1 "Control Structure")

;;;------------------------------------------------------------
;;; literal constants
;;;
(test #2a((a b c) (d e f)) #2a((a b c) (d e f)) equal)
(test #1a(a b c) #(a b c) equal)
(test #0a1 #0a1 equal)
(test #\a #\a equal)
(test 145932 145932 equal)
(test "abc" "abc" equal)
(test #(a b c) #(a b c) equal)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;  (quote obj) --> <object>
;;;------------------------------------------------------------
($ap 2 "quote" P.31)
;;;
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
;;; 
($argc quote 1 0 0)
;;;
;;($error (quote 1 . 2) <error>)

;;;------------------------------------------------------------
;;; var --> <object>
;;;------------------------------------------------------------
($eval (defglobal x 0))
(test x 0 eql)
(test (let ((x 1)) x) 1 eql)
(test x 0 eql)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;  (setq var form) --> <object>
;;;------------------------------------------------------------
($ap 2 "setq" P.32)
;;; 
($eval (defglobal x 2))
(test (+ x 1) 3 equal)
(test (setq x 4) 4 equal)
(test (+ x 1) 5 equal)
(test (let ((x 1)) (setq x 2) x) 2 equal)
(test (+ x 1) 5 equal)
;;;
($argc setq 2 0 0)
;;;
($error (setq x 1 . 2) <error>)
;;;
($error (setq #2a((a b c) (d e f)) nil) <domain-error>)
($error (setq #\a nil) <domain-error>)
($error (setq 1234 nil) <domain-error>)
($error (setq "abc" nil) <domain-error>)
($error (setq #(a b c) nil) <domain-error>)
($error (setq (x y) nil) <domain-error>)
;;;
($error (setq y nil) <unbound-variable>)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;  (setf place form) --> <object>
;;;------------------------------------------------------------
($ap 2 "setf" P.32)
;;;
($argc setf 2 0 0)
;;;
($eval (defglobal x 2))
(test (+ x 1) 3 equal)
(test (setf x 4) 4 equal)
(test (+ x 1) 5 equal)
(test (let ((x 1)) (setf x 2) x) 2 equal)
(test (+ x 1) 5 equal)
($eval (setq x '(1 . 2)))
(test (setf (car x) 2) 2 equal)
(test x (2 . 2) equal)
;;;
($eval (defmacro first (spot) `(car ,spot)))
($eval (defglobal x '(10 20)))
(test (first x) 10 equal)
(test (setf (first x) 2) 2)
(test x (2 20) equal)
;;;
($eval (defmacro first2 (spot) `(first ,spot)))
($eval (defglobal x '(10 20)))
(test (first2 x) 10 equal)
(test (setf (first2 x) 2) 2)
(test x (2 20) equal)
;;;
($eval (defmacro last (spot) `(cdr ,spot)))
($eval (defglobal x '(10 20)))
(test (last x) (20) equal)
(test (setf (last x) 2) 2)
(test x (10 . 2) equal)
;;;
($eval (defmacro last2 (spot) `(last ,spot)))
($eval (defglobal x '(10 20)))
(test (last2 x) (20) equal)
(test (setf (last2 x) 2) 2)
(test x (10 . 2) equal)
;;;
($eval (defmacro my-dynamic (spot) `(dynamic ,spot)))
($eval (defdynamic x 3))
(test (my-dynamic x) 3 equal)
(test (setf (my-dynamic x) 2) 2)
(test (my-dynamic x) 2 equal)
;;;
($eval (defmacro my-dynamic2 (spot) `(my-dynamic ,spot)))
($eval (defdynamic x 3))
(test (my-dynamic x) 3 equal)
(test (setf (my-dynamic2 x) 2) 2)
(test (my-dynamic2 x) 2 equal)
;;;
($eval (defmacro my-elt (seq z) `(elt ,seq ,z)))
($eval (defglobal x '(10 20 30)))
(test (my-elt x 0) 10)
(test (my-elt x 1) 20)
(test (my-elt x 2) 30)
(test (setf (my-elt x 1) 2) 2)
(test x (10 2 30) equal)
;;;
($eval (defmacro my-elt2 (seq z) `(my-elt ,seq ,z)))
($eval (defglobal x '(10 20 30)))
(test (my-elt2 x 0) 10)
(test (my-elt2 x 1) 20)
(test (my-elt2 x 2) 30)
(test (setf (my-elt2 x 1) 2) 2)
(test x (10 2 30) equal)
;;;
($error (setf x 1 . 2) <error>)
;;; place
($error (setf #2a((a b c) (d e f)) nil) <error>)
($error (setf #\a nil) <error>)
($error (setf 1234 nil) <error>)
($error (setf "abc" nil) <error>)
($error (setf #(a b c) nil) <error>)
($error (setf (x y) nil) <error>)
;;; place
($error (setf (foo x) nil) <error>)
($error (setf (foo (foo x)) nil) <error>)
;;;
($error (setf y nil) <unbound-variable>)
;;;
($eval (defglobal x 0))
($eval (defmacro p () 'x))
(test (setf (p) 9) 9)
(test x 9)
;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (let ((var form)*) body-form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "let" P.33)
;;;
($argc let 1 0 1)
;;;
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
;;;
($error (let) <program-error>)
;;;
($error (let x 1) <error>)
($error (let (x) 1) <error>)
($error (let (x 1) 1) <error>)
($error (let ((x)) 1) <error>)
($error (let ((x 1 2)) 1) <error>)
($error (let ((x 1 . 2)) 1) <error>)
($error (let (((x 1))) 1) <error>)
;;;
($error (let ((#2a((a b c) (d e f)) 1)) 1) <domain-error>)
($error (let ((#\a 1)) 1) <domain-error>)
($error (let ((1234 1)) 1) <domain-error>)
($error (let (("abc" 1)) 1) <domain-error>)
($error (let ((#(a b c) 1)) 1) <domain-error>)
($error (let (((x y) 1)) 1) <domain-error>)
;;;
($error (let ((:a 1))) <program-error>)
;;;
($error (let ((nil 1))) <program-error>)
($error (let ((t 1))) <program-error>)
($error (let ((*pi* 1))) <program-error>)
($error (let ((*most-positive-float* 1))) <program-error>)
($error (let ((*most-negative-float* 1))) <program-error>)
;;;
($error (let ((x 1)) z) <unbound-variable>)
($eval (let ((z 1)) z))
($error z <unbound-variable>)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (let* ((var form)*) body-form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "let*" P.34)
;;;
($argc let* 1 0 1)
;;;
(test (let ((x 2) (y 3))
   (let* ((x 7)
	  (z (+ x y)))
     (* z x))) 70 equal)
(test (let ((x 1) (y 2))
   (let* ((x y) (y x))
     (list x y))) (2 2) equal)
;;;
($error (let*) <program-error>)
;;;
($error (let* x 1) <error>)
($error (let* (x) 1) <error>)
($error (let* (x 1) 1) <error>)
($error (let* ((x)) 1) <error>)
($error (let* ((x 1 2)) 1) <error>)
($error (let* ((x 1 . 2)) 1) <error>)
($error (let* (((x 1))) 1) <error>)
;;;
($error (let* ((#2a((a b c) (d e f)) 1)) 1) <domain-error>)
($error (let* ((#\a 1)) 1) <domain-error>)
($error (let* ((1234 1)) 1) <domain-error>)
($error (let* (("abc" 1)) 1) <domain-error>)
($error (let* ((#(a b c) 1)) 1) <domain-error>)
($error (let* (((x y) 1)) 1) <domain-error>)
;;;
($error (let* ((:a 1))) <program-error>)
;;;
($error (let* ((nil 1))) <program-error>)
($error (let* ((t 1))) <program-error>)
($error (let* ((*pi* 1))) <program-error>)
($error (let* ((*most-positive-float* 1))) <program-error>)
($error (let* ((*most-negative-float* 1))) <program-error>)
;;;
($error (let* ((x 1)) z) <unbound-variable>)
($eval (let* ((z 1)) z))
($error z <unbound-variable>)
;;;
($eval (defglobal x ()))
($eval
 (let* ((y 1)
        (l (lambda () y))
	(z 2))
   (setq x (cons l (lambda () z)))))
(test (funcall (car x)) 1)
(test (funcall (cdr x)) 2)
;;;
($eval (defglobal x ()))
($eval
 (let* ((y 1)
        (l (lambda () y))
	(y 2))
   (setq x (cons l (lambda () y)))))
(test (funcall (car x)) 1)
(test (funcall (cdr x)) 2)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (dynamic var) --> <object>
;;;------------------------------------------------------------
($ap 2 "dynamic" P.35)
;;;
($argc dynamic 1 0 0)
;;;
($eval (defdynamic x 3))
(test (dynamic x) 3 equal)
;($error (dynamic z) <unbound-variable>)
;;;
;($error (dynamic x . y) <error>)
;;;
;($error (dynamic :a) <unbound-variable>)

;;;------------------------------------------------------------
;;; [special form]
;;;
;;;  (setf (dynamic var) form) --> <object>
;;;------------------------------------------------------------
($ap 2 "(setf (dynamic var) form)" P.35)
;;;
($eval (defdynamic x 3))
(test (dynamic x) 3 equal)
(test (setf (dynamic x) 4) 4 equal)
(test (dynamic x) 4 equal)
;($error (setf (dynamic z) 5) <unbound-variable>)
;;;
;($error (setf (dynamic x)) <program-error>)
;($error (setf (dynamic x) 1 2) <program-error>)
;;; place
;($error (setf (dynamic) 1) <error>)
;($error (setf (dynamic . x) 1) <error>)
;($error (setf (dynamic x . y) 1) <error>)
;($error (setf (dynamic x y) 1) <error>)
;;; 
;($error (setf (dynamic x) 1 . 2) <error>)
;;;
;($error (setf (dynamic :a) 1) <program-error>)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (dynamic-let ((var form)*) body-form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "dynamic-let" P.35)
;;;
($argc dynamic-let 1 0 1)
;;;
($eval (defun foo-1 (x)
	 (dynamic-let ((y x))
		      (bar-1 1))))
($eval (defun bar-1 (x)
	 (+ x (dynamic y))))
(test (foo-1 2) 3 equal)
;;;
($eval (defdynamic dynx 1))
(test (dynamic-let ((dynx 2)) (dynamic dynx)) 2)
(test (dynamic dynx) 1)
;;;
($error (dynamic-let) <program-error>)
;;;
($error (dynamic-let x 1) <error>)
($error (dynamic-let (x) 1) <error>)
($error (dynamic-let (x 1) 1) <error>)
($error (dynamic-let ((x)) 1) <error>)
($error (dynamic-let ((x 1 2)) 1) <error>)
($error (dynamic-let ((x 1 . 2)) 1) <error>)
($error (dynamic-let (((x 1))) 1) <error>)
;;;
($error (dynamic-let ((#2a((a b c) (d e f)) 1)) 1) <domain-error>)
($error (dynamic-let ((#\a 1)) 1) <domain-error>)
($error (dynamic-let ((1234 1)) 1) <domain-error>)
($error (dynamic-let (("abc" 1)) 1) <domain-error>)
($error (dynamic-let ((#(a b c) 1)) 1) <domain-error>)
($error (dynamic-let (((x y) 1)) 1) <domain-error>)
;;;
($error (dynamic-let ((:a 1))) <program-error>)
;;;
($error (dynamic-let ((dynx 1)) dynx) <unbound-variable>)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (if test-form then-form [else-form]) --> <object>
;;;------------------------------------------------------------
($ap 2 "if" P.36)
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
;;; 
($argc if 2 1 0)
;;;
($error (if 1 2 . 3) <program-error>)
($error (if nil 2 . 3) <program-error>)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (cond (test form*)*) --> <object>
;;;------------------------------------------------------------
($ap 2 "cond" P.36)
;;;
($argc cond 0 0 1)
;;;
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
;;; (test form)
($error (cond ()) <error>)
($error (cond 1) <error>)
;;;
($error (cond (t . 1)) <error>)
($error (cond (t 1 . 2)) <error>)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (case keyform ((key*) form*)* [(t form*)]) --> <object>
;;;------------------------------------------------------------
($ap 2 "case" P.37)
;;;
($argc case 1 0 1)
;;;
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
;;;
($error (case 1 ()) <error>)
($error (case 1 (1)) <error>)
;;;
($error (case 'a (t 1) ((a b c) 0)) <error>)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (case-using predform keyform ((key*) form*)* [(t form*)]) --> <object>
;;;------------------------------------------------------------
($ap 2 "case-using" P.37)
;;;
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
;;; predform
($type case-using ($function $generic) :target 1)
;;;
;($error (case-using #'= 1 ()) <error>)
;($error (case-using #'= 1 (1)) <error>)
;;;
;($error (case-using #'string= "a" (t 1) (("a" "b" "c") 0)) <error>)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (progn form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "progn" P.38)
;;;
(test (progn) nil)
(test (progn 1) 1 eql)
(test (progn 1 2) 2 eql)
;;;
(test (progn (defglobal *global-x* 1) (defglobal *global-y* 2)) *global-y*)
(test *global-x* 1 eql)
(test *global-y* 2 eql)
;;;
($eval (defglobal x 0))
(test (progn
   (setq x 5)
   (+ x 1)) 6 eql)
;;;
($argc progn 0 0 1)
;;; dot-list
($error (progn . 1) <error>)
($error (progn 1 . 2) <error>)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (while test-form body-form*) --> <null>
;;;------------------------------------------------------------
($ap 2 "while" P.39)
;;;
(test (while nil) nil)
(test (while nil 1) nil)
(test (let ((x '()) (i 5))
   (while (> i 0)
     (setq x (cons i x))
     (setq i (- i 1)))
   x) (1 2 3 4 5) equal)
;;;
($argc while 1 0 1)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (for (iteration-spec*) (end-test result*) form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "for" P.39)
;;;
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
;;;
($argc for 2 0 1)
;($error (for) <program-error>)
;;; (end-test result)
;($error (for ()) <program-error>)
;($error (for () ()) <error>)
;;; iteration-spec
;($error (for (x) (t 1)) <error>)
;($error (for ((x)) (t 1)) <error>)
;($error (for ((x x x x)) (t 1)) <error>)
;;; iteration-spec
;($error (for ((#2a((a b) (c d)) nil)) (t)) <domain-error>)
;($error (for ((#\a nil)) (t)) <domain-error>)
;($error (for ((1234 nil)) (t)) <domain-error>)
;($error (for ((1.234 nil)) (t)) <domain-error>)
;($error (for (("abc" nil)) (t)) <domain-error>)
;($error (for ((#(a b c) nil)) (t)) <domain-error>)
;($error (for (((x y) nil)) (t)) <domain-error>)
;;; var 
;($error (for ((x 0 (+ x 1))
;	      (x 1 (+ x 2))) (t)) <error>)
;;;
;($error (for ((:a 1)) (t)) <program-error>)
;;;
;($error (for ((nil 1)) (t)) <program-error>)
;($error (for ((t 1)) (t)) <program-error>)
;($error (for ((*pi* 1)) (t)) <program-error>)
;($error (for ((*most-positive-float* 1)) (t)) <program-error>)
;($error (for ((*most-negative-float* 1)) (t)) <program-error>)
;;; unbound-variable
;($error (for ((x 0)) (t y)) <unbound-variable>)
;($error (for ((x 0 (+ y 1))) ((= x 1) 1)) <unbound-variable>)
;;; close
($eval (defglobal x nil))
($eval (for ((i 0 (+ i 1)))
	    ((= i 10))
	    (if (= i 0) (setq x (lambda () i)))))
(test (funcall x) 10 eql)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (block name form*) --> <object>
;;;  (return-from name result-form) transfers control and data
;;;------------------------------------------------------------
($ap 2 "block" P.40)
($ap 2 "return-from" P.40)
;;;
(test (block x) nil)
(test (block nil) nil)
(test (block x 1) 1 eql)
(test (block x 1 2) 2 eql)
;;;
($eval (defglobal x nil))
(test (block b
	(setq x (cons 1 x))
	(setq x (cons 2 x))
	999) 999 eql)
(test x (2 1) equal)
;;;
($eval (defglobal x nil))
(test (block b
	(setq x (cons 1 x))
	(return-from b 888)
	(setq x (cons 2 x))
	999) 888 eql)
(test x (1) equal)
;;;
($eval (defglobal x nil))
($eval (defun terminate-1 (x) (return-from b x)))
;($error
; (block b
;	(setq x (cons 1 x))
;	(terminate-1 777)
;	(setq x (cons 2 x))
;	999) <control-error>)
;;;
(test (block x
	(+ 10 (return-from x 6) 22)) ;;; Bad programming style
 6 eql)
($eval 
 (defun f1 ()
   (block b
	  (let ((f (lambda () (return-from b 'exit))))
	    ;; big computation
	    (f2 f)))))
($eval 
 (defun f2 (g)
   ;; big computation
   (funcall g)))
(test (f1) exit)
(test (block sum-block
	(for ((x '(1 a 2 3) (cdr x))
	      (sum 0 (+ sum (car x))))
	     ((null x) sum)
	     (cond ((not (numberp (car x))) (return-from sum-block 0)))))
 0 eql)
($eval 
 (defun bar-2 (x y)
   (let ((foo #'car))
     (let ((result
	    (block bl
		   (setq foo (lambda () (return-from bl 'first-exit)))
		   (if x (return-from bl 'second-exit) 'third-exit))))
       (if y (funcall foo) nil)
       result))))
(test (bar-2 t nil) second-exit)
(test (bar-2 nil nil) third-exit)
;($error (bar-2 nil t) <control-error>)
;($error (bar-2 t t) <control-error>)
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
;;;
($argc block 1 0 1)
;($error (block) <program-error>)
;($error (block . 1) <program-error>)
($argc return-from 2 0 0)
;($error (block b
;	       (return-from b)) <program-error>)
;($error (block b
;	       (return-from b 1 2)) <program-error>)
;;; dot-list
;($error (block b . 1) <error>)
;($error (block b
;	       (return-from b 1 . 2)) <error>)
;;; block tag 
;($error (block #2a((a b) (c d))) <domain-error>)
;($error (block #\a) <domain-error>)
;($error (block 1234) <domain-error>)
;($error (block 1.234) <domain-error>)
;($error (block "abc") <domain-error>)
;($error (block #(a b c)) <domain-error>)
;($error (block (x y)) <domain-error>)
;($error (return-from #2a((a b) (c d)) 1) <domain-error>)
;($error (return-from #\a 1) <domain-error>)
;($error (return-from 1234 1) <domain-error>)
;($error (return-from 1.234 1) <domain-error>)
;($error (return-from "abc" 1) <domain-error>)
;($error (return-from #(a b c) 1) <domain-error>)
;($error (return-from (x y) 1) <domain-error>)
;;; block tag
;($error (block :a) <error>)
;($error (return-from :a 1) <error>)
;;;
;($error (block b
;	       (return-from c 88)
;	       99) <control-error>)
;;; invalid-tag
;($error
; (block b1
;	(block b2
;	       (unwind-protect 
;		   (return-from b1 888) ;;; b2 invalid
;		 (return-from b2 999)))) <control-error>)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (catch tag-form form*) --> <object>
;;;  (throw tag-form result-form) transfers control and data
;;;------------------------------------------------------------
($ap 2 "catch" P.42)
($ap 2 "throw" P.42)
;;;
(test (catch 'a) nil)
(test (catch 'a 1) 1 eql)
(test (catch 'a 1 2) 2 eql)
;;;
($eval (defglobal x nil))
(test (catch 'c
   (setq x (cons 1 x))
   (setq x (cons 2 x))
   999) 999 eql)
(test x (2 1) equal)
;;;
($eval (defglobal x nil))
(test (catch 'c
   (setq x (cons 1 x))
   (throw 'c 888)
   (setq x (cons 2 x))
   999) 888 eql)
(test x (1) equal)
;;;
($eval (defglobal x nil))
($eval (defun terminate-2 (x) (throw 'c x)))
(test (catch 'c
   (setq x (cons 1 x))
   (terminate-2 777)
   (setq x (cons 2 x))
   999) 777 eql)
(test x (1) equal)
;;;
($eval 
 (defun foo-3 (x)
   (catch 'block-sum (bar-3 x))))
($eval 
 (defun bar-3 (x)
   (for ((l x (cdr l))
	 (sum 0 (+ sum (car l))))
	((null l) sum)
	(cond ((not (numberp (car l))) (throw 'block-sum 0))))))
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
;;;
($argc catch 1 0 1)
;($error (catch) <program-error>)
;($error (catch . 1) <program-error>)
($argc throw 2 0 0)
;($error (catch 'c
;	       (throw 'c)) <program-error>)
;($error (catch 'c
;	       (throw 'c 1 2)) <program-error>)
;;; dot-list
;($error (catch 'c . 1) <error>)
;($error (catch 'c
;	       (throw 'c 1 . 2)) <error>)
;;; catch tag <number> <character> 
;($error (catch 1234) <error>)
;($error (catch 1.234) <error>)
;($error (catch #\a) <error>)
;($error (throw 1234 nil) <error>)
;($error (throw 1.234 nil) <error>)
;($error (throw #\a nil) <error>)
;;; 
;($error (catch 'c
;	  (throw 'd 88) 99) <control-error>)
;;; invalid-tag
;($error
; (catch 'c1
;	(catch 'c2
;	       (unwind-protect 
;		   (throw 'c1 888)  ;;; c2 invalid
;		 (throw 'c2 999)))) <control-error>)

#|
;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (tagbody {tagbody-tag | form}*) --> <object>
;;;  (go tagbody-tag) transfers control
;;;------------------------------------------------------------
($ap 2 "tagbody" P.43)
($ap 2 "go" P.43)
;;;
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
    tag		(setq x (cons 2 x))
    (setq x (cons 3 x)))
   x) (3 2 1) equal)
(test (let ((x ()))
   (tagbody
    (setq x (cons 1 x))
    (go tag)
    (setq x (cons 2 x))
    tag		(setq x (cons 3 x)))
   x) (3 1) equal)
;;; closure
(test (let ((x ()))
   (tagbody
    (setq x (cons 1 x))
    (lambda () 1)
    (go tag1)
    (setq x (cons 2 x))
    tag1
    (setq x (cons 3 x)))
   x) (3 1) equal)
(test (let ((x ()))
   (tagbody
    (setq x (cons 1 x))
    (lambda () 1)
    (lambda () 2)
    (go tag1)
    (setq x (cons 2 x))
    tag1
    (setq x (cons 3 x)))
   x) (3 1) equal)
(test (let ((x ()))
   (tagbody
    (setq x (cons 1 x))
    ((lambda () (go tag1)))
    (setq x (cons 2 x))
    tag1
    (setq x (cons 3 x)))
   x) (3 1) equal)
;;;
($argc tagbody 0 0 1)
;($error (tagbody
;	 (go)) <program-error>)
($argc go 1 0 0)
;($error (tagbody
;	 (go tag 1)) <program-error>)
;;; dot-list
;($error (tagbody . 1) <error>)
;($error (tagbody
;	 (go tag . 1)) <error>)
;;;
;($error
; (let ((x ()))
;   (tagbody
;    (setq x (cons 1 x))
;    (go tag-notexist)
;    (setq x (cons 2 x))
;    tag		(setq x (cons 3 x)))
;   x) <control-error>)
;;; invalid-tag
;($error
; (tagbody
;  tag1
;  (tagbody
;   tag2
;   (unwind-protect 
;       (go tag1) ;;; tag2 invalid
;     (go tag2)))) <control-error>)
;;;
;;;($error
;; (tagbody tag ((lambda ()) (go tagbody))) <control-error>)
|#
;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (unwind-protect form cleanup-form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "unwind-protect" P.44)
;;;
(test (unwind-protect 1) 1 eql)
;;;
($eval (defglobal x nil))
(test (unwind-protect
     (progn (setq x (cons 1 x)) x)
   (setq x (cons 2 x))
   (setq x (cons 3 x))) (1) equal)
(test x (3 2 1) equal)
;;;
($eval (defglobal x nil))
(test (catch 'c
  (unwind-protect
      (progn (setq x (cons 1 x))
	     (throw 'c 777)
	     888)
    (setq x (cons 2 x))
    999)) 777 eql)
(test x (2 1) equal)
;;;
($eval (defglobal x nil))
($eval (defun nest1 (y)
	 (unwind-protect
	     (progn (setq x (cons 1 x))
		    (nest2 y))
	   (setq x (cons 2 x)))))
($eval (defun nest2 (y)
	 (unwind-protect
	     (progn (setq x (cons 3 x))
		    (throw 'exit y))
	   (setq x (cons 4 x)))))
(test (catch 'exit
   (nest1 777)) 777 eql)
(test x (2 4 3 1) equal)

;;;
($eval 
 (defun foo-4 (x)
   (catch 'duplicates
     (unwind-protect (bar-4 x)
       (for ((l x (cdr l)))
	    ((null l) (remove-property l 'label) 'unused)
	    (remove-property (car l) 'label))))))
($eval
 (defun bar-4 (l)
   (cond ((and (symbolp l) (property l 'label))
	  (throw 'duplicates 'found))
	 ((symbolp l) (setf (property l 'label) t))
	 ((bar-4 (car l)) (bar-4 (cdr l)))
	 (t nil))))
(test (foo-4 '(a b c)) t)
(test (property 'a 'label) nil)
(test (foo-4 '(a b a c)) found)
(test (property 'a 'label) nil)
($eval
 (defun test ()
   (catch 'outer (test2))))
($eval
 (defun test2 ()
   (block inner
	  (test3 (lambda ()
		   (return-from inner 7))))))
($eval
 (defun test3 (fun)
   (unwind-protect (test4) (funcall fun))))
($eval
 (defun test4 ()
   (throw 'outer 6)))
;($error (test) <control-error>)
;;; 
($argc unwind-protect 1 0 1)
;($error (unwind-protect) <program-error>)
;($error (unwind-protect . 1) <program-error>)

;;; end of file
