(import "test")
;;;
;;; Chapter 8: Macros
;;;

($ap 1 "Macros")

;;;------------------------------------------------------------
($test `(list ,(+ 1 2) 4) (list 3 4) equal)
($test (let ((name 'a)) `(list name ,name ',name)) (list name a (quote a)) equal)
($test `(a ,(+ 1 2) ,@(create-list 3 'x) b) (a 3 x x x b) equal)
($test `((foo ,(- 10 3)) ,@(cdr '(c)) . ,(car '(cons)))
 ((foo 7) . cons) equal)
($test `(a `(b ,(+ 1 2) ,(foo ,(+ 1 3) d) e) f)
 (a `(b ,(+ 1 2) ,(foo 4 d) e) f) equal)
($test (let ((name1 'x)
       (name2 'y))
   `(a `(b ,,name1 ,',name2 d) e))
 (a `(b ,x ,'y d) e) equal)

;;;------------------------------------------------------------
;;; [defining operator]
;;;
;;;  (defmacro macro-name lambda-list form*) --> <symbol>
;;;------------------------------------------------------------
($test (defmacro my-caar (x) (list 'car (list 'car x))) my-caar)
($test (my-caar '((a b) (c d))) a)
($test (my-caar '(((a b) (c d)) ((e f) (g h)))) (a b) equal)
;;;
($eval (defmacro my-first (x) `(car ,x)))
($eval (defmacro my-first2 (x) `(my-first ,x)))
($test (my-first '(1 2)) 1 eql)
($test (my-first2 '(1 2)) 1 eql)
;;;
($error (defmacro) <program-error>)
($error (defmacro foo) <program-error>)
;;;
($error (defmacro foo 2 . 3) <error>)
;;; toplevel 
($error1 (+ (defmacro foo (x))) <error>)
;;; macro-name 
($error (defmacro #2a((a b) (c d)) ()) <domain-error>)
($error (defmacro #\a ()) <domain-error>)
($error (defmacro 1234()) <domain-error>)
($error (defmacro 123456789 ()) <domain-error>)
($error (defmacro 1.234 ()) <domain-error>)
($error (defmacro "abc" ()) <domain-error>)
($error (defmacro #(a b c) ()) <domain-error>)
($error (defmacro (x y) ()) <domain-error>)
;;; lambda-list
($eval (defmacro foo (x) y))
($error (foo 1) <unbound-variable>)

;;;
($eval (defmacro foo (x &rest y) `(list ,x ,@y)))
($test (foo 1) (1) equal)
($test (foo 1 2) (1 2) equal)
($test (foo 1 2 3) (1 2 3) equal)
($argc foo 1 0 1)
($error (foo 1 . 2) <error>)
;;;
($eval (defmacro foo (x y) `(list ,x ,y)))
($test (foo 1 2) (1 2) equal)
($argc foo 2 0 0)
($error (foo 1 2 . 3) <error>)

;;; end of file

