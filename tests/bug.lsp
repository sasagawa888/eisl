(defglobal *call-tree* nil)
(defun add-call-tree (x)
   (setq *call-tree* (cons x *call-tree*)))


(defgeneric foo-sub-7 (x))
(defmethod foo-sub-7 ((x <integer>)) 
	 (add-call-tree 'primary-<integer>))
(defmethod foo-sub-7 (x)
	 (add-call-tree 'primary-<object>))
(defmethod foo-sub-7 :before ((x <integer>)) 
	 (add-call-tree 'before-<integer>))
(defmethod foo-sub-7 :before (x)
	 (add-call-tree 'before-<object>))
(defmethod foo-sub-7 :after ((x <integer>)) 
	 (add-call-tree 'after-<integer>))
(defmethod foo-sub-7 :after (x)
	 (add-call-tree 'after-<object>))

(defun foo-17 (x)
   (setq *call-tree* nil)
   (foo-sub-7 x)
   (reverse *call-tree*))

#|
($test (foo-17 3) (before-<integer>
	  before-<object>
	  primary-<integer>
	  after-<object>
	  after-<integer>) 
 equal)
($test (foo-17 3.3) (before-<object>
	    primary-<object>
	    after-<object>)
 equal)
|#

(defgeneric (setf foo-18) (x y z))
(defmethod (setf foo-18) (x y z) (list x y z))

(defun foo-18* ()
	(setf (foo-18 1 2) 3))

(defgeneric foo-32 (x)
   (:method ((x <integer>))
	    (list x (call-next-method) (call-next-method)))
   (:method ((x <number>))
	    (* x x))
   (:method (x)
	    'never-called))

;($test (foo-32 3) (3 9 9) equal)

(defgeneric foo-36 (a b &rest c)
   (:method (a b &rest c)
	    (list 'default a b))
   (:method ((a <string>) (b <string>) &rest c)
	    (list (call-next-method) (string-append a b)))
   (:method ((a <integer>) (b <number>) &rest c)
	    (list (call-next-method) (list 'number a b)))
   (:method ((a <integer>) (b <integer>) &rest c)
	    (let ((x (list (foo-36 "foo" "bar" "yab"))))
	      ;;
	      (setq a (* a 10))
	      (setq b (* b 10))
	      (if (next-method-p)
		  (setq x (cons (call-next-method) x)))
	      (setq x (cons (list a b c) x))
	      x)))
 

#|
($test (foo-36 4 5 6 7 8)
 ((40 50 (6 7 8))
  ((default 4 5) (number 4 5))
  ((default "foo" "bar") "foobar"))
 equal)
;;
|#

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

