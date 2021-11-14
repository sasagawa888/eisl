(defglobal *call-tree* nil)
(defun add-call-tree (x)
   (setq *call-tree* (cons x *call-tree*)))


(defgeneric (setf foo-18) (x y z))
(defmethod (setf foo-18) (x y z) (list x y z))

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

(defclass c00 () ())
(defclass c11 () ())
(defclass c22 (c11) ())
(defclass c33 (c22) ())
;;


(defglobal c00 (create (class c00)))
(defglobal c11 (create (class c11)))
(defglobal c22 (create (class c22)))
(defglobal c33 (create (class c33)))
(defgeneric foo-sub-30 (x)
   ;; <object>
   (:method (x) 
	    (add-call-tree 'primary-<object>))
   ;; <standard-object>
   (:method ((x <standard-object>))
	    (add-call-tree 'primary-<standard-object>-begin)
	    (call-next-method)
	    (add-call-tree 'primary-<standard-object>-end))
   (:method :around ((x <standard-object>))
	    (add-call-tree 'around-<standard-object>-begin)
	    (if (next-method-p)
		(call-next-method))
	    (add-call-tree 'around-<standard-object>-end))
   (:method :before ((x <standard-object>))
	    (add-call-tree 'before-<standard-object>))
   (:method :after ((x <standard-object>))
	    (add-call-tree 'after-<standard-object>))
   ;; c11
   (:method ((x c11))
	    (add-call-tree 'primary-c1-begin)
	    (call-next-method)
	    (add-call-tree 'primary-c1-end))
   (:method :around ((x c11))
	    (add-call-tree 'around-c1-begin)
	    (if (next-method-p)
		(call-next-method))
	    (add-call-tree 'around-c1-end))
   (:method :before ((x c11))
	    (add-call-tree 'before-c1))
   (:method :after ((x c11))
	    (add-call-tree 'after-c1))
   ;; c22
   (:method ((x c22))
	    (add-call-tree 'primary-c2-begin)
	    (call-next-method)
	    (add-call-tree 'primary-c2-end))
   (:method :around ((x c22))
	    (add-call-tree 'around-c2-begin)
	    (if (next-method-p)
		(call-next-method))
	    (add-call-tree 'around-c2-end))
   (:method :before ((x c22))
	    (add-call-tree 'before-c2))
   (:method :after ((x c22))
	    (add-call-tree 'after-c2))
   ;; c33
   (:method ((x c33))
	    (add-call-tree 'primary-c3-begin)
	    (call-next-method)
	    (add-call-tree 'primary-c3-end))
   (:method :around ((x c33))
	    (add-call-tree 'around-c3-begin)
	    (if (next-method-p)
		(call-next-method))
	    (add-call-tree 'around-c3-end))
   (:method :before ((x c33))
	    (add-call-tree 'before-c3))
   (:method :after ((x c33))
	    (add-call-tree 'after-c3))
   )

;;
(defun foo-30 (x)
   (setq *call-tree* nil)
   (foo-sub-30 x)
   (reverse *call-tree*))
;;

