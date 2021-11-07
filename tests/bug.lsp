(defglobal *call-tree* nil)
(defun add-call-tree (x)
   (setq *call-tree* (cons x *call-tree*)))

(defgeneric foo-sub-3 (x))
(defmethod foo-sub-3 ((x <integer>)) 
	 (add-call-tree 'primary-<integer>))
(defmethod foo-sub-3 :around ((x <integer>)) 
	 (add-call-tree 'around-<integer>))
(defmethod foo-sub-3 :before ((x <integer>)) 
	 (add-call-tree 'before-<integer>))
(defmethod foo-sub-3 :after ((x <integer>)) 
	 (add-call-tree 'after-<integer>))

(defun foo-13 (x)
   (setq *call-tree* nil)
   (foo-sub-3 x)
   (reverse *call-tree*))

;($test (foo-13 3) (around-<integer>) equal)
;($error (foo-13 3.3) <error>)


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
 

;($test (foo-37 4 5 6)
; ((40 50 6)
;  ((default 4 5) (number 4 5))
;  ((default "foo" "bar") "foobar"))
; equal)
;;