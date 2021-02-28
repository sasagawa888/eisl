;;; -*- lisp -*-
;;;
;;; Chapter 4 Forms and Evaluation

($ap 1 "Forms and Evaluation")

($ap 1 "The Evaluation Model")

;;;------------------------------------------------------------
;;;   4.6 The Evaluation Model
;;;------------------------------------------------------------

;;;------------------------------------------------------------
;;; (a) literal
(#2a((a b) (c d)) #2a((a b) (c d)) equal)
(#(a b c) #(a b c) equal)
(123 123 equal)
(1.23 1.23 equal)
(#\a #\a equal)
("foo" "foo" equal)

;;; (b) identifier
(t t)
(nil nil)
($eval (defglobal x 1))
(x 1 equal)
($error unbound-var <unbound-variable>)

;;; (c) compound form: (operator argument*)
;;;   (c-1) operator: special operator
((if 1 2 3) 2 equal)

;;;   (c-2) operator: defining operator
((defglobal x 2) x equal)
(x 2 equal)

;;;   (c-3) operator: lambda form
(((lambda (x) (+ x x)) 4) 8 equal)

;;;   (c-4) operator: otherwise --> function application form
((+ 1 2) 3 equal)
($error (undef-func) <undefined-function>)

;;; (d) otherwise --> undefined-function
($error (1 2) <undefined-function>)

;;;------------------------------------------------------------
($ap 1 "Functions")

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (functionp obj) --> boolean
;;;------------------------------------------------------------
($ap 2 "functionp" P.20)
;;;
($argc functionp 1 0 0)
;;; 
($predicate functionp $function $generic)
;;;
((functionp (function car)) t)
((functionp #'car) t)
;;;
($eval (defun foo-func ()))
((functionp (function foo-func)) t)
((functionp #'foo-func) t)
;;;
((functionp 1) nil)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;  (function function-name) --> <function>
;;;------------------------------------------------------------
($ap 2 "function" P.21)
;;;
($argc function 1 0 0)
;;;
((funcall (function -) 3) -3 equal)
((funcall #'- 3) -3 equal)
((apply (function -) '(4 3)) 1 equal)
((apply #'- '(4 3)) 1 equal)
;;; 引数がdot-list
($error (function + . 1) <error>)
;;; function-name がシンボルでない
($error (function #2a((a b) (c d))) <domain-error>)
($error (function #\a) <domain-error>)
($error (function 1234) <domain-error>)
($error (function 1.234) <domain-error>)
($error (function "abc") <domain-error>)
($error (function #(a b c)) <domain-error>)
($error (function (x y)) <domain-error>)
;;; function-name に対する束縛がない(undefined-function)
($error (function undef-func) <undefined-function>)
;;; The consequences are undefined if the function-name names 
;;; a macro or special form
#|
($error (function if) <undefined-function>) ;; special form
($eval (defmacro my-macro (x) `(car ,x)))
($error (function my-macro) <undefined-function>) ;; macro
|#

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;  (lambda lambda-list form*) --> <function>
;;;------------------------------------------------------------
($ap 2 "lambda" P.21)
;;;
(((lambda (x y) (+ (* x x) (* y y))) 3 4) 25 equal)
(((lambda (x y &rest z) z) 3 4 5 6) (5 6) equal)
(((lambda (x y :rest z) z) 3 4 5 6) (5 6) equal)
((funcall (lambda (x y) (- y (* x y))) 7 3) -18 equal)
;;;
($eval (defconstant *const-e* 3))
(((lambda (*const-e*) *const-e*) 4) 4 equal)
;;; lambda-list がない
($error (lambda) <program-error>)
;;; lambda-list の形式が不当
($error ((lambda x nil)) <error>)
($error ((lambda (x . y) nil)) <error>)
;;; 同じidentifier
($error ((lambda (x x) nil) 1 2) <error>)
($error ((lambda (x &rest x) nil) 1 2 3) <error>)
($error ((lambda (x :rest x) nil) 1 2 3) <error>)
;;; keyword
($error ((lambda (:a) nil) 1) <program-error>)
($error ((lambda (&a) nil) 1) <program-error>)
($error ((lambda (:rest &a) nil) 1) <program-error>)
($error ((lambda (:rest :a) nil) 1) <program-error>)
($error ((lambda (&rest &a) nil) 1) <program-error>)
($error ((lambda (&rest :a) nil) 1) <program-error>)
;;; システム定数
($error ((lambda (nil) nil) 1) <program-error>)
($error ((lambda (t) nil) 1) <program-error>)
($error ((lambda (*pi*) nil) 1) <program-error>)
($error ((lambda (*most-positive-float*) nil) 1) <program-error>)
($error ((lambda (*most-negative-float*) nil) 1) <program-error>)
;;; identifier がシンボルでない
($error ((lambda (#2a((a b) (c d))) nil) 1) <domain-error>)
($error ((lambda (#\a) nil) 1) <domain-error>)
($error ((lambda (1234) nil) 1) <domain-error>)
($error ((lambda (1.234) nil) 1) <domain-error>)
($error ((lambda ("abc") nil) 1) <domain-error>)
($error ((lambda (#(a b c)) nil) 1) <domain-error>)
($error ((lambda ((x y)) nil) 1) <domain-error>)
;;; &rest, :rest の後の identifier の個数
($error ((lambda (x y &rest) nil) 1 2) <error>)
($error ((lambda (x y :rest) nil) 1 2) <error>)
($error ((lambda (x y &rest z w) nil) 1 2) <error>)
($error ((lambda (x y :rest z w) nil) 1 2) <error>)
;;; &rest, :rest の後の identifier がシンボルでない
($error ((lambda (x &rest #2a((a b) (c d))) nil) 1) <domain-error>)
($error ((lambda (x :rest #2a((a b) (c d))) nil) 1) <domain-error>)
($error ((lambda (x &rest #\a) nil) 1) <domain-error>)
($error ((lambda (x :rest #\a) nil) 1) <domain-error>)
($error ((lambda (x &rest 1234) nil) 1) <domain-error>)
($error ((lambda (x :rest 1234) nil) 1) <domain-error>)
($error ((lambda (x &rest 1.234) nil) 1) <domain-error>)
($error ((lambda (x :rest 1.234) nil) 1) <domain-error>)
($error ((lambda (x &rest "abc") nil) 1) <domain-error>)
($error ((lambda (x :rest "abc") nil) 1) <domain-error>)
($error ((lambda (x &rest #(a b c)) nil) 1) <domain-error>)
($error ((lambda (x :rest #(a b c)) nil) 1) <domain-error>)
($error ((lambda (x &rest (x y)) nil) 1) <domain-error>)
($error ((lambda (x :rest (x y)) nil) 1) <domain-error>)
;;; &rest, :rest の後に &rest, :rest
($error ((lambda (&rest &rest) nil) 1) <program-error>)
($error ((lambda (&rest :rest) nil) 1) <program-error>)
($error ((lambda (:rest &rest) nil) 1) <program-error>)
($error ((lambda (:rest &rest) nil) 1) <program-error>)
;;; 指定されたlambda-listと,
;;; 関数が受け取った引数の個数が一致しない(arity-error)
($error ((lambda (x y) nil) 1) <program-error>)
($error ((lambda (x y) nil) 1 2 3) <program-error>)
($error ((lambda (x y &rest z) nil) 1) <program-error>)
($error ((lambda (x y :rest z) nil) 1) <program-error>)
;;; lambda-list に指定されたidentifier の有効範囲外
($error ((lambda () unbound-var)) <unbound-variable>)
($error ((lambda (x) y) 1) <unbound-variable>)
($error ((lambda (x &rest y) z) 1) <unbound-variable>)
($error ((lambda (x :rest y) z) 1) <unbound-variable>)
;;;
((let ((x 1))
   (lambda () 1)
   (lambda () 2)
   x) 1 equal)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;   (labels ((function-name lambda-list form*)*) body-forms*) --> <object>
;;;------------------------------------------------------------
($ap 2 "labels" P.22)
;;;
((labels ()) nil)
((labels () 1) 1 equal)
((labels () 1 2) 2 equal)
((labels ((evenp (n)
		 (if (= n 0)
		     t
		   (oddp (- n 1))))
	  (oddp (n)
		 (if (= n 0)
		     nil
		   (evenp (- n 1)))))
	 (evenp 88))
 t)
;;;
((functionp (labels ((foo ())) #'foo)) t)
;;; 引数の個数
($error (labels) <program-error>)
;;; 束縛リストが不当
($error (labels (f)) <error>)
($error (labels ((f))) <error>)
;;; lambda-list が不当
($error (labels ((f x))) <error>)
($error (labels ((f (x . y)))) <error>)
;;; function-name がシンボルでない
($error (labels ((#2a((a b) (c d)) (x) x))) <domain-error>)
($error (labels ((#\a (x) x))) <domain-error>)
($error (labels ((1234 (x) x))) <domain-error>)
($error (labels ((1.234 (x) x))) <domain-error>)
($error (labels (("abc" (x) x))) <domain-error>)
($error (labels ((#(a b c) (x) x))) <domain-error>)
($error (labels (((x y) (x) x))) <domain-error>)
;;; キーワードは束縛できない
($error (labels ((:a ()))) <program-error>)
;;; function-name の有効範囲外
($error (labels ((f (x) (g x))) (f 1)) <undefined-function>)
;;; body-forms* が dot-list
($error (labels ((f (x) x)) . 1) <error>)
($error (labels ((f (x) x)) (f 1) . 2) <error>)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;   (flet ((function-name lambda-list form*)*) body-forms*) --> <object>
;;;------------------------------------------------------------
($ap 2 "flet" P.22)
;;;
((flet ()) nil)
((flet () 1) 1 equal)
((flet () 1 2) 2 equal)
((flet ((f (x) (+ x 3)))
       (flet ((f (x) (+ x (f x))))
	     (f 7)))
 17
 equal)
;;;
((functionp (flet ((foo ())) #'foo)) t)
;;;
($eval (defglobal x nil))
($eval (flet ((f () 2)) (setq x (lambda () (f)))))
((funcall x) 2)
;;;
($eval (defglobal x nil))
($eval (flet ((f () 2)) (setq x (lambda () (f)))))
((apply x ()) 2)
;;; 引数の個数
($error (flet) <program-error>)
;;; 束縛リストが不当
($error (flet (f)) <error>)
($error (flet ((f))) <error>)
;;; lambda-list が不当
($error (flet ((f x))) <error>)
($error (flet ((f (x . y)))) <error>)
;;; function-name がシンボルでない
($error (flet ((#2a((a b) (c d)) (x) x))) <domain-error>)
($error (flet ((#\a (x) x))) <domain-error>)
($error (flet ((1234 (x) x))) <domain-error>)
($error (flet ((1.234 (x) x))) <domain-error>)
($error (flet (("abc" (x) x))) <domain-error>)
($error (flet ((#(a b c) (x) x))) <domain-error>)
($error (flet (((x y) (x) x))) <domain-error>)
;;; キーワードは束縛できない
($error (flet ((:a ()))) <program-error>)
;;; function-name の有効範囲外
($error (flet ((f (x) (g x))) (f 1)) <undefined-function>)
($error 
 (flet ((f (x) (g x))
	(g (x) x))
       (f 1))  <undefined-function>)
;;; body-forms* が dot-list
($error (flet ((f (x) x)) . 1) <error>)
($error (flet ((f (x) x)) (f 1) . 2) <error>)
;;;
($eval (defun foo-5 () 1))
((flet ((foo-5 () (foo-5))) (foo-5)) 1)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (apply function obj* list) --> <object>
;;;------------------------------------------------------------
($ap 2 "apply" P.23)
;;;
((apply #'+ '(1 2)) 3 equal)
((apply #'+ 3 '(1 2)) 6 equal)
((apply #'+ 3 4 '(1 2)) 10 equal)
((apply (if (< 1 2) (function max) (function min))
	1 2 (list 3 4)) 4 equal)
($eval (defun compose (f g)
	 (lambda (:rest args)
	   (funcall f (apply g args)))))
((funcall (compose (function sqrt) (function *)) 12 75) 30 equal)
;;; 引数の個数
($argc apply 2 0 1)
;;; function が関数でない(domain-error)
($type apply ($function $generic) :target 1 (quote (2 3)))
;;; list が真リストでない(improper-arglist)
($error (apply #'list '(1 . 2)) <program-error>)
($error (apply #'list 1 '(2 . 3)) <program-error>)
($error (apply #'list 1 2 '(3 . 4)) <program-error>)
;;;
((apply #'list '(1 2)) (1 2) equal)
((apply #'list 1 '(2 3)) (1 2 3) equal)
((apply #'list 1 2 '(3 4)) (1 2 3 4) equal)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (funcall function obj*) --> <object>
;;;------------------------------------------------------------
($ap 2 "funcall" P.23)
;;;
((funcall #'+) 0 equal)
((funcall #'+ 1) 1 equal)
((funcall #'+ 1 2) 3 equal)
((let ((x '(1 2 3)))
   (funcall (cond ((listp x) (function car))
		  (t (lambda (x) (cons x 1)))) x)) 1 equal)
;;; 引数の個数
($argc funcall 1 0 1)
;;; function が関数でない(domain-error)
($type funcall ($function $generic) :target 1)

($ap 1 "Defining Operators")

;;;------------------------------------------------------------
;;; [defining operator]
;;;
;;;  (defconstant name form) --> <symbol>
;;;------------------------------------------------------------
($ap 2 "defconstant")
;;;
((defconstant *const-1* 1) *const-1* equal)
((defconstant *const-e* 2.718) *const-e* equal)
(*const-e* 2.718 equal)
($eval (defun f () *const-e*))
((f) 2.718 equal)
;;; 引数の個数
($error (defconstant) <program-error>)
($error (defconstant *const-e*) <program-error>)
($error (defconstant *const-e* 2 3) <program-error>)
;;; 引数リストがドットリスト
($error (defconstant *const-e* 2 . 3) <error>)
;;; トップレベル定義でない
($error (+ (defconstant *const-e* 2)) <error>)
;;; name がシンボルでない
($error (defconstant #2a((a b c) (d e f)) nil) <domain-error>)
($error (defconstant #\a nil) <domain-error>)
($error (defconstant 1234 nil) <domain-error>)
($error (defconstant "abc" nil) <domain-error>)
($error (defconstant #(a b c) nil) <domain-error>)
($error (defconstant (x y) nil) <domain-error>)
;;; システム定義の定数は変更できない
($error (defconstant nil nil) <program-error>)
($error (defconstant t nil) <program-error>)
($error (defconstant *pi* nil) <program-error>)
($error (defconstant *most-positive-float* nil) <program-error>)
($error (defconstant *most-negative-float* nil) <program-error>)
;;; keyword
($error (defconstant :a nil) <program-error>)
($error (defconstant &a nil) <program-error>)

;;;------------------------------------------------------------
;;; [defining operator]
;;;
;;;  (defglobal name form) --> <symbol>
;;;------------------------------------------------------------
($ap 2 "defglobal")
;;;
((defglobal *global-1* 1) *global-1* equal)
(*global-1* 1 equal)
((defglobal *global-today* 'wednesday) *global-today* equal)
(*global-today* wednesday equal)
($eval (defun what-is-today () *global-today*))
((what-is-today) wednesday equal)
((let ((what-is-today 'thursday)) (what-is-today)) wednesday equal)
((let ((*global-today* 'thursday)) (what-is-today)) wednesday equal)
;;; 引数の個数
($error (defglobal) <program-error>)
($error (defglobal *global-2*) <program-error>)
($error (defglobal *global-2* 2 3) <program-error>)
;;; 引数リストがドットリスト
($error (defglobal *global-2* 2 . 3) <error>)
;;; トップレベル定義でない
($error (+ (defglobal *global-2* 2)) <error>)
;;; name がシンボルでない
($error (defglobal #2a((a b c) (d e f)) nil) <domain-error>)
($error (defglobal #\a nil) <domain-error>)
($error (defglobal 1234 nil) <domain-error>)
($error (defglobal "abc" nil) <domain-error>)
($error (defglobal #(a b c) nil) <domain-error>)
($error (defglobal (x y) nil) <domain-error>)
;;; システム定数は変更できない
($error (defglobal nil nil) <program-error>)
($error (defglobal t nil) <program-error>)
($error (defglobal *pi* nil) <program-error>)
($error (defglobal *most-positive-float* nil) <program-error>)
($error (defglobal *most-negative-float* nil) <program-error>)
;;; 定数は変更できない
($eval (defconstant *const-e* 2.718))
($error (defglobal *const-e* nil) <program-error>)
;;; keyword
($error (defglobal :a nil) <program-error>)
($error (defglobal &a nil) <program-error>)

;;;------------------------------------------------------------
;;; [defining operator]
;;;
;;;  (defdynamic name form) --> <symbol>
;;;------------------------------------------------------------
($ap 2 "defdynamic")
;;;
((defdynamic *dynamic-color* 'red) *dynamic-color* equal)
((dynamic *dynamic-color*) red equal)
($eval (defun what-color () (dynamic *dynamic-color*)))
((what-color) red equal)
((dynamic-let ((*dynamic-color* 'green)) (what-color)) green equal)
;;; nil
((defdynamic nil 3) nil equal)
((dynamic nil) 3 equal)
;;; 引数の個数
($error (defdynamic) <program-error>)
($error (defdynamic *dynamic-2*) <program-error>)
($error (defdynamic *dynamic-2* 2 3) <program-error>)
;;; 引数リストがドットリスト
($error (defdynamic *dynamic-2* 2 . 3) <error>)
;;; トップレベル定義でない
($error (+ (defdynamic *dynamic-2* 2)) <error>)
;;; name がシンボルでない
($error (defdynamic #2a((a b c) (d e f)) nil) <domain-error>)
($error (defdynamic #\a nil) <domain-error>)
($error (defdynamic 1234 nil) <domain-error>)
($error (defdynamic "abc" nil) <domain-error>)
($error (defdynamic #(a b c) nil) <domain-error>)
($error (defdynamic (x y) nil) <domain-error>)
;;; keyword
($error (defdynamic :a nil) <program-error>)
($error (defdynamic &a nil) <program-error>)

;;;------------------------------------------------------------
;;; [defining operator]
;;;
;;;  (defun function-name lambda-list form*) --> <symbol>
;;;------------------------------------------------------------
($ap 2 "defun")
;;;
((defun my-f-caar (x) (car (car x))) my-f-caar equal)
((my-f-caar '((1 2))) 1 equal)
;;; 引数の個数
($error (defun) <program-error>)
($error (defun foo) <program-error>)
;;; 引数リストがドットリスト
($error (defun foo 2 . 3) <error>)
;;; トップレベル定義でない
($error (+ (defun foo 2)) <error>)
;;; name がシンボルでない
($error (defun #2a((a b c) (d e f)) nil) <domain-error>)
($error (defun #\a nil) <domain-error>)
($error (defun 1234 nil) <domain-error>)
($error (defun "abc" nil) <domain-error>)
($error (defun #(a b c) nil) <domain-error>)
($error (defun (x y) nil) <domain-error>)
;;; keyword 
($error (defun :a ()) <program-error>)
($error (defun &a ()) <program-error>)
;;; same variable
($error (defun foo (x x) nil) <error>)
($error (defun foo (x &rest x) nil) <error>)
($error (defun foo (x :rest x) nil) <error>)
;;; システム定数を関数として定義
((defun nil ()) nil equal)
((defun t ()) t equal)
((defun *pi* ()) *pi* equal)
((defun *most-positive-float* ()) *most-positive-float*)
((defun *most-negative-float* ()) *most-negative-float*)
;;; special operator は変更できない
($error (defun if ()) <program-error>)
;;; lambda-list に指定された識別子の有効範囲を越えている
($eval (defun foo-6 (x) y))
($error (foo-6 1) <unbound-variable>)
;;;
($eval (defun foo-7 (x) x))
((foo-7 1) 1 equal)
($argc foo-7 1 0 0)
;;;
($eval (defun foo-8 (x &rest y) (cons x y)))
((foo-8 1) (1) equal)
((foo-8 1 2) (1 2) equal)
((foo-8 1 2 3) (1 2 3) equal)
($argc foo-8 1 0 1)

;;; end of file
