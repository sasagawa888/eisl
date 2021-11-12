(defglobal *call-tree* nil)
(defun add-call-tree (x)
   (setq *call-tree* (cons x *call-tree*)))


(defgeneric foo-37 (a b c)
   (:method (a b c)
	    (list 'default a b))
   (:method ((a <string>) (b <string>) c)
	    (list (call-next-method) (string-append a b)))
   (:method ((a <integer>) (b <number>) c)
	    (list (call-next-method) (list 'number a b)))
   (:method ((a <integer>) (b <integer>) c)
	    (let ((x (list (foo-37 "foo" "bar" "yab"))))
	      ;;
	      (setq a (* a 10))
	      (setq b (* b 10))
	      (if (next-method-p)
		  (setq x (cons (call-next-method) x)))
	      (setq x (cons (list a b c) x))
	      x)))
 
#|
;($test (foo-37 4 5 6)
; ((40 50 6)
;  ((default 4 5) (number 4 5))
;  ((default "foo" "bar") "foobar"))
; equal)
;;
|#