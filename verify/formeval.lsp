(import "test")
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
(test #2a((a b) (c d)) #2a((a b) (c d)) equal)
(test #(a b c) #(a b c) equal)
(test 123 123 equal)
(test 1.23 1.23 equal)
(test #\a #\a equal)
(test "foo" "foo" equal)

;;; (b) identifier
(test t t)
(test nil nil)
($eval (defglobal x 1))
(test x 1 equal)
($error unbound-var <unbound-variable>)

;;; (c) compound form: (operator argument*)
;;;   (c-1) operator: special operator
(test (if 1 2 3) 2 equal)

;;;   (c-2) operator: defining operator
(test (defglobal x 2) x equal)
(test x 2 equal)

;;;   (c-3) operator: lambda form
(test ((lambda (x) (+ x x)) 4) 8 equal)

;;;   (c-4) operator: otherwise --> function application form
(test (+ 1 2) 3 equal)
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
(test (functionp (function car)) t)
(test (functionp #'car) t)
;;;
($eval (defun foo-func ()))
(test (functionp (function foo-func)) t)
(test (functionp #'foo-func) t)
;;;
(test (functionp 1) nil)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;  (function function-name) --> <function>
;;;------------------------------------------------------------
($ap 2 "function" P.21)
;;;
($argc function 1 0 0)
;;;
(test (funcall (function -) 3) -3 equal)
(test (funcall #'- 3) -3 equal)
(test (apply (function -) '(4 3)) 1 equal)
(test (apply #'- '(4 3)) 1 equal)
;;; ������dot-list
;($error (function + . 1) <error>)
;;; function-name ���V���{���łȂ�
($error (function #2a((a b) (c d))) <domain-error>)
($error (function #\a) <domain-error>)
($error (function 1234) <domain-error>)
($error (function 1.234) <domain-error>)
($error (function "abc") <domain-error>)
($error (function #(a b c)) <domain-error>)
($error (function (x y)) <domain-error>)
;;; function-name (undefined-function)
($error (function undef-func) <undefined-function>)
;;; The consequences are undefined if the function-name names 
;;; a macro or special form
#|
;($error (function if) <undefined-function>) ;; special form
($eval (defmacro my-macro (x) `(car ,x)))
;($error (function my-macro) <undefined-function>) ;; macro
|#

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;  (lambda lambda-list form*) --> <function>
;;;------------------------------------------------------------
($ap 2 "lambda" P.21)
;;;
(test ((lambda (x y) (+ (* x x) (* y y))) 3 4) 25 equal)
(test ((lambda (x y &rest z) z) 3 4 5 6) (5 6) equal)
(test ((lambda (x y :rest z) z) 3 4 5 6) (5 6) equal)
(test (funcall (lambda (x y) (- y (* x y))) 7 3) -18 equal)
;;;
($eval (defconstant *const-e* 3))
(test ((lambda (*const-e*) *const-e*) 4) 4 equal)
;;; lambda-list not exist
($error (lambda) <program-error>)
;;; lambda-list improper list
($error ((lambda x nil)) <error>)
($error ((lambda (x . y) nil)) <error>)
;;; duplicate identifier
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
;;; �V�X�e���萔
($error ((lambda (nil) nil) 1) <program-error>)
($error ((lambda (t) nil) 1) <program-error>)
($error ((lambda (*pi*) nil) 1) <program-error>)
($error ((lambda (*most-positive-float*) nil) 1) <program-error>)
($error ((lambda (*most-negative-float*) nil) 1) <program-error>)
;;; identifier ���V���{���łȂ�
($error ((lambda (#2a((a b) (c d))) nil) 1) <domain-error>)
($error ((lambda (#\a) nil) 1) <domain-error>)
($error ((lambda (1234) nil) 1) <domain-error>)
($error ((lambda (1.234) nil) 1) <domain-error>)
($error ((lambda ("abc") nil) 1) <domain-error>)
($error ((lambda (#(a b c)) nil) 1) <domain-error>)
($error ((lambda ((x y)) nil) 1) <domain-error>)
;;; &rest, :rest �̌�� identifier �̌�
($error ((lambda (x y &rest) nil) 1 2) <error>)
($error ((lambda (x y :rest) nil) 1 2) <error>)
($error ((lambda (x y &rest z w) nil) 1 2) <error>)
($error ((lambda (x y :rest z w) nil) 1 2) <error>)
;;; &rest, :rest �̌�� identifier ���V���{���łȂ�
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
;;; &rest, :rest �̌�� &rest, :rest
($error ((lambda (&rest &rest) nil) 1) <program-error>)
($error ((lambda (&rest :rest) nil) 1) <program-error>)
($error ((lambda (:rest &rest) nil) 1) <program-error>)
($error ((lambda (:rest &rest) nil) 1) <program-error>)
;;; �w�肳�ꂽlambda-list��,
;;; �֐����󂯎���������̌�����v���Ȃ�(arity-error)
($error ((lambda (x y) nil) 1) <program-error>)
($error ((lambda (x y) nil) 1 2 3) <program-error>)
($error ((lambda (x y &rest z) nil) 1) <program-error>)
($error ((lambda (x y :rest z) nil) 1) <program-error>)
;;; lambda-list �Ɏw�肳�ꂽidentifier �̗L���͈͊O
($error ((lambda () unbound-var)) <unbound-variable>)
($error ((lambda (x) y) 1) <unbound-variable>)
($error ((lambda (x &rest y) z) 1) <unbound-variable>)
($error ((lambda (x :rest y) z) 1) <unbound-variable>)
;;;
(test (let ((x 1))
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
(test (labels ()) nil)
(test (labels () 1) 1 equal)
(test (labels () 1 2) 2 equal)
(test (labels ((evenp (n)
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
(test (functionp (labels ((foo ())) #'foo)) t)
;;; 
($error (labels) <program-error>)
;;; 
($error (labels (f)) <error>)
;($error (labels ((f))) <error>)
;;; lambda-list ���s��
;($error (labels ((f x))) <error>)
;($error (labels ((f (x . y)))) <error>)
;;; function-name ���V���{���łȂ�
;($error (labels ((#2a((a b) (c d)) (x) x))) <domain-error>)
;($error (labels ((#\a (x) x))) <domain-error>)
;($error (labels ((1234 (x) x))) <domain-error>)
;($error (labels ((1.234 (x) x))) <domain-error>)
;($error (labels (("abc" (x) x))) <domain-error>)
;($error (labels ((#(a b c) (x) x))) <domain-error>)
;($error (labels (((x y) (x) x))) <domain-error>)
;;; �L�[���[�h�͑����ł��Ȃ�
;($error (labels ((:a ()))) <program-error>)
;;; function-name �̗L���͈͊O
;($error (labels ((f (x) (g x))) (f 1)) <undefined-function>)
;;; body-forms* �� dot-list
;($error (labels ((f (x) x)) . 1) <error>)
;($error (labels ((f (x) x)) (f 1) . 2) <error>)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;   (flet ((function-name lambda-list form*)*) body-forms*) --> <object>
;;;------------------------------------------------------------
($ap 2 "flet" P.22)
;;;
(test (flet ()) nil)
(test (flet () 1) 1 equal)
(test (flet () 1 2) 2 equal)
(test (flet ((f (x) (+ x 3)))
       (flet ((f (x) (+ x (f x))))
	     (f 7)))
 17
 equal)
;;;
(test (functionp (flet ((foo ())) #'foo)) t)
;;;
($eval (defglobal x nil))
($eval (flet ((f () 2)) (setq x (lambda () (f)))))
(test (funcall x) 2)
;;;
($eval (defglobal x nil))
($eval (flet ((f () 2)) (setq x (lambda () (f)))))
(test (apply x ()) 2)
;;; �����̌�
($error (flet) <program-error>)
;;; �������X�g���s��
;($error (flet (f)) <error>)
;($error (flet ((f))) <error>)
;;; lambda-list ���s��
;($error (flet ((f x))) <error>)
;($error (flet ((f (x . y)))) <error>)
;;; function-name ���V���{���łȂ�
;($error (flet ((#2a((a b) (c d)) (x) x))) <domain-error>)
;($error (flet ((#\a (x) x))) <domain-error>)
;($error (flet ((1234 (x) x))) <domain-error>)
;($error (flet ((1.234 (x) x))) <domain-error>)
;($error (flet (("abc" (x) x))) <domain-error>)
;($error (flet ((#(a b c) (x) x))) <domain-error>)
;($error (flet (((x y) (x) x))) <domain-error>)
;;; �L�[���[�h�͑����ł��Ȃ�
;($error (flet ((:a ()))) <program-error>)
;;; function-name �̗L���͈͊O
;($error (flet ((f (x) (g x))) (f 1)) <undefined-function>)
;($error 
; (flet ((f (x) (g x))
;	(g (x) x))
;       (f 1))  <undefined-function>)
;;; body-forms* �� dot-list
;($error (flet ((f (x) x)) . 1) <error>)
;($error (flet ((f (x) x)) (f 1) . 2) <error>)
;;;
($eval (defun foo-5 () 1))
(test (flet ((foo-5 () (foo-5))) (foo-5)) 1)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (apply function obj* list) --> <object>
;;;------------------------------------------------------------
($ap 2 "apply" P.23)
;;;
(test (apply #'+ '(1 2)) 3 equal)
(test (apply #'+ 3 '(1 2)) 6 equal)
(test (apply #'+ 3 4 '(1 2)) 10 equal)
(test (apply (if (< 1 2) (function max) (function min))
	1 2 (list 3 4)) 4 equal)
($eval (defun compose (f g)
	 (lambda (:rest args)
	   (funcall f (apply g args)))))
(test (funcall (compose (function sqrt) (function *)) 12 75) 30 equal)
;;; �����̌�
($argc apply 2 0 1)
;;; function ���֐��łȂ�(domain-error)
($type apply ($function $generic) :target 1 (quote (2 3)))
;;; list ���^���X�g�łȂ�(improper-arglist)
;($error (apply #'list '(1 . 2)) <program-error>)
;($error (apply #'list 1 '(2 . 3)) <program-error>)
;($error (apply #'list 1 2 '(3 . 4)) <program-error>)
;;;
(test (apply #'list '(1 2)) (1 2) equal)
(test (apply #'list 1 '(2 3)) (1 2 3) equal)
(test (apply #'list 1 2 '(3 4)) (1 2 3 4) equal)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (funcall function obj*) --> <object>
;;;------------------------------------------------------------
($ap 2 "funcall" P.23)
;;;
(test (funcall #'+) 0 equal)
(test (funcall #'+ 1) 1 equal)
(test (funcall #'+ 1 2) 3 equal)
(test (let ((x '(1 2 3)))
   (funcall (cond ((listp x) (function car))
		  (t (lambda (x) (cons x 1)))) x)) 1 equal)
;;; �����̌�
($argc funcall 1 0 1)
;;; function ���֐��łȂ�(domain-error)
($type funcall ($function $generic) :target 1)

($ap 1 "Defining Operators")

;;;------------------------------------------------------------
;;; [defining operator]
;;;
;;;  (defconstant name form) --> <symbol>
;;;------------------------------------------------------------
($ap 2 "defconstant")
;;;

(test (defconstant *const-1* 1) *const-1* equal)
(test (defconstant *const-e* 2.718) *const-e* equal)
(test *const-e* 2.718 equal)
($eval (defun f () *const-e*))
(test (f) 2.718 equal)

;;; �����̌�
($error (defconstant) <program-error>)
($error (defconstant *const-e*) <program-error>)
($error (defconstant *const-e* 2 3) <program-error>)
;;; �������X�g���h�b�g���X�g
($error (defconstant *const-e* 2 . 3) <error>)
;;; �g�b�v���x����`�łȂ�
;($error (+ (defconstant *const-e* 2)) <error>)
;;; name ���V���{���łȂ�
;($error (defconstant #2a((a b c) (d e f)) nil) <domain-error>)
;($error (defconstant #\a nil) <domain-error>)
;($error (defconstant 1234 nil) <domain-error>)
;($error (defconstant "abc" nil) <domain-error>)
;($error (defconstant #(a b c) nil) <domain-error>)
;($error (defconstant (x y) nil) <domain-error>)
;;; �V�X�e����`�̒萔�͕ύX�ł��Ȃ�
;($error (defconstant nil nil) <program-error>)
;($error (defconstant t nil) <program-error>)
;($error (defconstant *pi* nil) <program-error>)
;($error (defconstant *most-positive-float* nil) <program-error>)
;($error (defconstant *most-negative-float* nil) <program-error>)
;;; keyword
;($error (defconstant :a nil) <program-error>)
;($error (defconstant &a nil) <program-error>)

;;;------------------------------------------------------------
;;; [defining operator]
;;;
;;;  (defglobal name form) --> <symbol>
;;;------------------------------------------------------------
($ap 2 "defglobal")
;;;
(test (defglobal *global-1* 1) *global-1* equal)
(test *global-1* 1 equal)
(test (defglobal *global-today* 'wednesday) *global-today* equal)
(test *global-today* wednesday equal)
($eval (defun what-is-today () *global-today*))
(test (what-is-today) wednesday equal)
(test (let ((what-is-today 'thursday)) (what-is-today)) wednesday equal)
(test (let ((*global-today* 'thursday)) (what-is-today)) wednesday equal)
;;; �����̌�
($error (defglobal) <program-error>)
;($error (defglobal *global-2*) <program-error>)
;($error (defglobal *global-2* 2 3) <program-error>)
;;; �������X�g���h�b�g���X�g
;($error (defglobal *global-2* 2 . 3) <error>)
;;; �g�b�v���x����`�łȂ�
;($error (+ (defglobal *global-2* 2)) <error>)
;;; name ���V���{���łȂ�
;($error (defglobal #2a((a b c) (d e f)) nil) <domain-error>)
;($error (defglobal #\a nil) <domain-error>)
;($error (defglobal 1234 nil) <domain-error>)
;($error (defglobal "abc" nil) <domain-error>)
;($error (defglobal #(a b c) nil) <domain-error>)
;($error (defglobal (x y) nil) <domain-error>)
;;; �V�X�e���萔�͕ύX�ł��Ȃ�
;($error (defglobal nil nil) <program-error>)
;($error (defglobal t nil) <program-error>)
;($error (defglobal *pi* nil) <program-error>)
;($error (defglobal *most-positive-float* nil) <program-error>)
;($error (defglobal *most-negative-float* nil) <program-error>)
;;; �萔�͕ύX�ł��Ȃ�
($eval (defconstant *const-e* 2.718))
;($error (defglobal *const-e* nil) <program-error>)
;;; keyword
;($error (defglobal :a nil) <program-error>)
;($error (defglobal &a nil) <program-error>)

;;;------------------------------------------------------------
;;; [defining operator]
;;;
;;;  (defdynamic name form) --> <symbol>
;;;------------------------------------------------------------
($ap 2 "defdynamic")
;;;
(test (defdynamic *dynamic-color* 'red) *dynamic-color* equal)
(test (dynamic *dynamic-color*) red equal)
($eval (defun what-color () (dynamic *dynamic-color*)))
(test (what-color) red equal)
(test (dynamic-let ((*dynamic-color* 'green)) (what-color)) green equal)
;;; nil
(test (defdynamic nil 3) nil equal)
(test (dynamic nil) 3 equal)
;;; �����̌�
($error (defdynamic) <program-error>)
($error (defdynamic *dynamic-2*) <program-error>)
($error (defdynamic *dynamic-2* 2 3) <program-error>)
;;; �������X�g���h�b�g���X�g
($error (defdynamic *dynamic-2* 2 . 3) <error>)
;;; �g�b�v���x����`�łȂ�
;;; ??? I think result of following test is  <domain-error> 
;;; Becuase defdynamic return symbol and symbol is not number
($error (+ (defdynamic *dynamic-2* 2)) <domain-error>)
;($error (+ (defdynamic *dynamic-2* 2)) <error>)
;;; name ���V���{���łȂ�
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
(test (defun my-f-caar (x) (car (car x))) my-f-caar equal)
(test (my-f-caar '((1 2))) 1 equal)
;;; �����̌�
($error (defun) <program-error>)
($error (defun foo) <program-error>)
;;; �������X�g���h�b�g���X�g
($error (defun foo 2 . 3) <error>)
;;; �g�b�v���x����`�łȂ�
($error (+ (defun foo 2)) <error>)
;;; name ���V���{���łȂ�
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
;;; �V�X�e���萔���֐��Ƃ��Ē�`
(test (defun nil ()) nil equal)
(test (defun t ()) t equal)
(test (defun *pi* ()) *pi* equal)
(test (defun *most-positive-float* ()) *most-positive-float*)
(test (defun *most-negative-float* ()) *most-negative-float*)
;;; special operator �͕ύX�ł��Ȃ�
($error (defun if ()) <program-error>)
;;; lambda-list �Ɏw�肳�ꂽ���ʎq�̗L���͈͂��z���Ă���
($eval (defun foo-6 (x) y))
($error (foo-6 1) <unbound-variable>)
;;;
($eval (defun foo-7 (x) x))
(test (foo-7 1) 1 equal)
($argc foo-7 1 0 0)
;;;
($eval (defun foo-8 (x &rest y) (cons x y)))
(test (foo-8 1) (1) equal)
(test (foo-8 1 2) (1 2) equal)
(test (foo-8 1 2 3) (1 2 3) equal)
($argc foo-8 1 0 1)

;;; end of file
