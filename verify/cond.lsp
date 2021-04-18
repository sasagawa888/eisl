(import "test")
;;; -*- lisp -*-
;;;
;;; Chapter 21 Condition System
;;;

($ap 1 "Condition System")

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (error error-string obj*)  --> <object>
;;;------------------------------------------------------------
($ap 2 "error" P.114)
;;;
($eval 
 (defun simple-error-handler (condition)
   (let ((data ()))
     (setq data
	   (cons (simple-error-format-string condition)
		 (simple-error-format-arguments condition)))
     (throw 'c data))))
;;;
(test (catch 'c
   (with-handler #'simple-error-handler
		 (error "foo")))
 ("foo") equal)
;;;
(test (catch 'c
   (with-handler #'simple-error-handler
		 (error "~A" 123)))
 ("~A" 123) equal)
;;;
($argc error 1 0 1)
;;;
($type error ($string) :target)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (cerror continue-string error-string obj*) --> <object>
;;;------------------------------------------------------------
($ap 2 "cerror" P.115)
;;;
($argc cerror 2 0 1)
;;;
($type cerror ($string) :target "err-string")
($type cerror ($string) "cont-string" :target)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (signal-condition condition continuable)
;;;------------------------------------------------------------
($ap 2 "signal-condition" P.115)
;;;
($eval
 (defun condition-continuable-handler (condition)
   (throw 'c (condition-continuable condition))))
;;;
(test (catch 'c
   (with-handler #'condition-continuable-handler
		 (signal-condition 
		  (catch 'cc (with-handler
			      (lmabda (c) (throw 'cc c))
			      (error "err"))) nil)))
 nil)
;;;
($argc signal-condition 2 0 0)
($type signal-condition 
       ($arithmetic-error 
	$domain-error 
	$parse-error 
	$simple-error 
	$stream-error 
	$undefined-entity) :target nil)

;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (ignore-errors form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "ignore-errors" P.115)
;;;
(test (ignore-errors) nil)
(test (ignore-errors 1) 1 eql)
(test (ignore-errors 1 2) 2 eql)
($eval (defglobal x ()))
(test (ignore-errors
  (setq x (cons 1 x))
  (undef-func)
  (setq x (cons 2 x))
  99) nil equal)
(test x (1) equal)
;;;
($argc ignore-errors 0 0 1)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (condition-continuable condition) --> <object>
;;;------------------------------------------------------------
($ap 2 "condition-continuable" P.116)
;;; continuable
(test (catch 'c
   (with-handler #'condition-continuable-handler
		 (cerror "cont" "err")))
 "cont" equal)
;;; not continuable
(test (catch 'c
   (with-handler #'condition-continuable-handler
		 (error "err")))
 nil)
;;;
($argc condition-continuable 1 0 0)
($type condition-continuable 
       ($arithmetic-error 
	$domain-error 
	$parse-error 
	$simple-error 
	$stream-error 
	$undefined-entity) :target)


;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (continue-condition condition [value]) --> <object>
;;;------------------------------------------------------------
($ap 2 "continue-condition" P.116)
;;;
($eval 
 (defun continue-condition-handler (condition)
   (continue-condition condition)))
;;;
(test (with-handler #'continue-condition-handler
	       (cerror "cont" "err")) nil)
($error (with-handler #'continue-condition-handler
		      (error "err")) <error>)		  
;;;
($eval 
 (defun continue-condition-handler-2 (condition)
   (continue-condition condition 999)))
;;;
(test (with-handler #'continue-condition-handler-2
	       (cerror "cont" "err")) 999 equal)
($error (with-handler #'continue-condition-handler-2
		      (error "err")) <error>)
;;;
($argc continue-condition 1 1 0)
($type continue-condition 
       ($arithmetic-error 
	$domain-error 
	$parse-error 
	$simple-error 
	$stream-error 
	$undefined-entity) :target)
;;;------------------------------------------------------------
;;; [special-operator]
;;;
;;;  (with-handler handler form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "with-handler" P.116)
;;;
($eval
 (defun handler-99 (condition)
   (throw 'c 99)))
;;;
(test (catch 'c
   (with-handler #'handler-99
		 (car 3)))
 99 eql)
;;;
(test (catch 'c
   (with-handler #'handler-99
		 (error "intentional error")))
 99 eql)
;;;
(test (catch 'c
   (with-handler #'handler-99
		 (cerror "continuable" "intentional error")))
 99 eql)
;;; lambda-function
(test (catch 'c
   (with-handler 
    (lambda (condition)
      (throw 'c 999))
    (car 3)))
 999 eql)
;;;
(test (catch 'c
   (with-handler 
    (lambda (condition)
      (throw 'c 999))
    (error "intentional error")))
 999 eql)
;;;
($argc with-handler 1 0 1)
($type with-handler ($function $generic) :target)


;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (arithmetic-error-operation arithmetic-error) --> <function>
;;;  (arithmetic-error-operands arithmetic-error) --> <list>
;;;------------------------------------------------------------
($ap 2 "arithmetic-error-operation" P.116)
($ap 2 "arithmetic-error-operands" P.116)
;;;
($eval
 (defun arithmetic-error-handler (condition)
   (let ((data ()))
     (setq data 
	   (cons (arithmetic-error-operation condition)
		 (arithmetic-error-operands condition)))
     (throw 'c-arithmetic-error data))))

;;; division-by-zero
(test (functionp (car 
 (catch 'c-arithmetic-error
  (with-handler #'arithmetic-error-handler
		(div 3 0))))) t)

(test (equal (function div) (car 
 (catch 'c-arithmetic-error
  (with-handler #'arithmetic-error-handler
		(div 3 0))))) t)

(test (cdr
 (catch 'c-arithmetic-error
  (with-handler #'arithmetic-error-handler
		(div 3 0)))) (3 0) equal)
;;; floating-point-overflow
(test (functionp (car
 (catch 'c-arithmetic-error
  (with-handler #'arithmetic-error-handler
		(* 1e308 1e1))))) t)
(test (equal (function *) (car
 (catch 'c-arithmetic-error
  (with-handler #'arithmetic-error-handler
		(* 1e308 1e1))))) t)
(test (cdr
 (catch 'c-arithmetic-error
  (with-handler #'arithmetic-error-handler
		(* 1e308 1e1)))) (1e308 1e1) equal)
;;; floating-point-underflow
(test (functionp (car
 (catch 'c-arithmetic-error
  (with-handler #'arithmetic-error-handler
		(* 1e-307 1e-10))))) t)
(test (equal (function *) (car
 (catch 'c-arithmetic-error
  (with-handler #'arithmetic-error-handler
		(* 1e-307 1e-10))))) t)
(test (cdr
 (catch 'c-arithmetic-error
  (with-handler #'arithmetic-error-handler
		(* 1e-307 1e-10)))) (1e-307 1e-10) equal)
;;;
($argc arithmetic-error-operation 1 0 0)
($argc arithmetic-error-operands 1 0 0)
($type arithmetic-error-operation ($arithmetic-error) :target)
($type arithmetic-error-operands ($arithmetic-error) :target)
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (domain-error-objet domain-error) --> <object>
;;;  (domain-error-expected-class domain-error) --> <class>
;;;------------------------------------------------------------
($ap 2 "domain-error-object" P.117)
($ap 2 "domain-error-expected-class" P.117)
;;;
($eval
 (defun domain-error-handler (condition)
   (let ((data ()))
     (setq data
	   (cons (domain-error-object condition)
		 (domain-error-expected-class condition)))
     (throw 'c-domain-error data))))
;;; <basic-array>
($eval (defglobal data nil))
($eval (setq data
	     (catch 'c-domain-error
	       (with-handler #'domain-error-handler
			     (aref 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <basic-array>)) t)

;;; <general-array*>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (garef 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <general-array*>)) t)
;;; <basic-vector>
;;; <vector>
;;; <string>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (string-append 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <string>)) t)
;;; <character>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (char= 1 2)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <character>)) t)
;;; <function>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (apply "123" 1 2 3 '(4 5))))))
(test (car data) "123" equal)
(test (eq (cdr data) (class <function>)) t)
;;; <list>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (reverse 1)))))
(test (car data) 1 eql)
(test (eq (cdr data)  (class <list>)) t)
;;; <cons>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (car 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <cons>)) t)
;;; <number>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (max "a")))))
(test (car data) "a" equal)
(test (eq (cdr data) (class <number>)) t)
;;; <float>
;;; <integer>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (div "a" "b")))))
(test (car data) "a" equal)
(test (eq (cdr data) (class <integer>)) t)
;;; <stream>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (read 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <stream>)) t)
;;; <symbol>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (property 1 2)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <symbol>)) t)
;;; <serious-condition>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (condition-continuable 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <serious-condition>)) t)

;;; <arithmetic-error>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (arithmetic-error-operation 1)))))
				  
(test (car data) 1 eql)
(test (eq (cdr data) (class <arithmetic-error>)) t)

;;; <domain-error>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (domain-error-object 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <domain-error>)) t)
;;; <parse-error>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (parse-error-string 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <parse-error>)) t)
;;; <simple-error>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (simple-error-format-string 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <simple-error>)) t)
;;; <stream-error>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (stream-error-stream 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <stream-error>)) t)
;;; <undefined-entity>
($eval (defglobal data nil))
($eval (setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (undefined-entity-name 1)))))
(test (car data) 1 eql)
(test (eq (cdr data) (class <undefined-entity>)) t)
;;;
($argc domain-error-object 1 0 0)
($argc domain-error-expected-class 1 0 0)
;;; domain-error
($type domain-error-object ($domain-error) :target)
($type domain-error-expected-class ($domain-error) :target)
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (parse-error-string parse-error) --> <string>
;;;  (parse-error-expected-class parse-error) --> <class>
;;;------------------------------------------------------------
($ap 2 "parse-error-string" P.117)
($ap 2 "parse-error-expected-class" P.117)
;;;
($eval
 (defun parse-error-handler (condition)
   (let ((data ()))
     (setq data 
	   (cons (parse-error-string condition)
		 (parse-error-expected-class condition)))
     (throw 'c-parse-error data))))
;;;
($eval (defglobal data nil))
($eval (setq data (catch 'c-parse-error 
		    (with-handler #'parse-error-handler
				  (parse-number "abc")))))
(test (car data) "abc" equal)
(test (eq (cdr data) (class <number>)) t)
;;;
($argc parse-error-string 1 0 0)
($argc parse-error-expected-class 1 0 0)
;;; domain-error
($type parse-error-string ($parse-error) :target)
($type parse-error-expected-class ($parse-error) :target)
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (simple-error-format-string simple-error) --> <string>
;;;  (simple-error-format-arguments simple-error) --> <list>
;;;------------------------------------------------------------
($ap 2 "simple-error-format-string" P.118)
($ap 2 "simple-error-format-arguments" P.118)
;;;
($eval
 (defun simple-error-handler (condition)
   (let ((data ()))
     (setq data 
	   (cons (simple-error-format-string condition)
		 (simple-error-format-arguments condition)))
     (throw 'c-simple-error data))))
;;;
(test (catch 'c-simple-error
   (with-handler #'simple-error-handler
		 (error "err: ~S" 123)))
 ("err: ~S" 123) equal)
;;;
(test (catch 'c-simple-error
   (with-handler #'simple-error-handler
		 (cerror "cont: ~S" "err: ~S" 456)))
 ("err: ~S" 456) equal)
;;;
($argc simple-error-format-string 1 0 0)
($argc simple-error-format-arguments 1 0 0)
;;; domain-error
($type simple-error-format-string ($simple-error) :target)
($type simple-error-format-arguments ($simple-error) :target)
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (stream-error-stream stream-error) --> <stream>
;;;------------------------------------------------------------
($ap 2 "stream-error-stream" P.118)
;;;
($eval
 (defun stream-error-handler (condition)
   (let ((data ()))
     (setq data 
	   (cons (stream-error-stream condition)
		 nil))
     (throw 'c-simple-error data))))
;;;
#|
($eval (tp-make-tmp-file))
($eval (defglobal str (open-io-file *tp-example-file*)))
(test (streamp (car
  (catch 'c-simple-error
   (with-handler #'stream-error-handler
		 (read str))))) t)
($eval (close str))
;;;
($argc stream-error-stream 1 0 0)
;;; domain-error
($type stream-error-stream ($stream-error) :target)
|#
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (undefined-entity-name undefined-entity) --> <symbol>
;;;  (undefined-entity-namespace undefined-entity) --> <symbol>
;;;------------------------------------------------------------
($ap 2 "undefined-entity-name" P.118)
($ap 2 "undefined-entity-namespace" P.118)
;;;
($eval
 (defun undefined-entity-handler (condition)
   (let ((data ()))
     (setq data 
	   (cons (undefined-entity-name condition)
		 (undefined-entity-namespace condition)))
     (throw 'c-undefined-entity data))))
;;; variable
(test (catch 'c-undefined-entity
   (with-handler #'undefined-entity-handler
		 undef-var))
 (undef-var . variable) equal)
;;; dynamic-variable
(test (catch 'c-undefined-entity
   (with-handler #'undefined-entity-handler
		 (dynamic undef-dynamic-var)))
 (undef-dynamic-var . dynamic-variable) equal)

;;; function
(test (catch 'c-undefined-entity
   (with-handler #'undefined-entity-handler
		 (undef-func)))
 (undef-func . function) equal)
;;;
($argc undefined-entity-name 1 0 0)
($argc undefined-entity-namespace 1 0 0)
;;; domain-error
($type undefined-entity-name ($undefined-entity) :target)
($type undefined-entity-namespace ($undefined-entity) :target)

;;; end of file
