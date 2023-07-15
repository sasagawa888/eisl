;;; ILOS compile tests
(defglobal *call-tree* nil)
;;
(defclass c00 () ())
(defclass c11 () ())
(defclass c22 (c11) ())
(defclass c33 (c22) ())
(defglobal c00 (create (class c00)))
(defglobal c11 (create (class c11)))
(defglobal c22 (create (class c22)))
(defglobal c33 (create (class c33)))
;;
(defun add-call-tree (x)
   (setq *call-tree* (cons x *call-tree*)))

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
#|
;;
($test (foo-30 1) (primary-<object>) equal)
($test (foo-30 c00) (around-<standard-object>-begin
	      before-<standard-object>
	      primary-<standard-object>-begin
	      primary-<object>
	      primary-<standard-object>-end
	      after-<standard-object>
	      around-<standard-object>-end)
 equal)
($test (foo-30 c11) (around-c1-begin
	      around-<standard-object>-begin
	      before-c1
	      before-<standard-object>
	      primary-c1-begin
	      primary-<standard-object>-begin
	      primary-<object>
	      primary-<standard-object>-end
	      primary-c1-end
	      after-<standard-object>
	      after-c1
	      around-<standard-object>-end
	      around-c1-end) 
 equal)

($test (foo-30 c22) (around-c2-begin
	      around-c1-begin
	      around-<standard-object>-begin
	      before-c2
	      before-c1
	      before-<standard-object>
	      primary-c2-begin
	      primary-c1-begin
	      primary-<standard-object>-begin
	      primary-<object>
	      primary-<standard-object>-end
	      primary-c1-end
	      primary-c2-end
	      after-<standard-object>
	      after-c1
	      after-c2
	      around-<standard-object>-end
	      around-c1-end
	      around-c2-end) 
 equal)
($test (foo-30 c33) (around-c3-begin
	      around-c2-begin
	      around-c1-begin
	      around-<standard-object>-begin
	      before-c3
	      before-c2
	      before-c1
	      before-<standard-object>
	      primary-c3-begin
	      primary-c2-begin
	      primary-c1-begin
	      primary-<standard-object>-begin
	      primary-<object>
	      primary-<standard-object>-end
	      primary-c1-end
	      primary-c2-end
	      primary-c3-end
	      after-<standard-object>
	      after-c1
	      after-c2
	      after-c3
	      around-<standard-object>-end
	      around-c1-end
	      around-c2-end 
	      around-c3-end) 
 equal)
;;|#

(defgeneric foo-31 (x)
   (:method ((x <integer>))
	    (lambda (y) (* y (call-next-method))))
   (:method ((x <number>))
	    (* x x)))
(defglobal x (foo-31 3))
#| 
($test (funcall x 5) 45 eql)
($test (funcall x 5) 45 eql)
|#
#| 
(defglobal f nil)
(defgeneric foo-38 (x y))
(defmethod foo-38 (x y) (list x y))
(defmethod foo-38 ((x <integer>) (y <integer>))
	 (setq x (* x 10))
	 (setq y (* y 10))
	 (setq f (lambda () (if (next-method-p) (call-next-method))))
	 (list x y))
 
($test (foo-38 2 3) (20 30) equal)
($test (funcall f) (2 3) equal)
;;
|#
(defglobal f nil)
(defgeneric foo-39 (x y))
(defmethod foo-39 (x y) (list x y))
(defmethod foo-39 ((x <integer>) (y <integer>))
	 (setq x (* x 10))
	 (setq y (* y 10))
	 (setq f (lambda () 
		   (if (next-method-p) (list x y (call-next-method)))))
	 (list x y))

#| 
($test (foo-39 2 3) (20 30) equal)
($test (funcall f) (20 30 (2 3)) equal)
|#