(defglobal *call-tree* nil)

(defun add-call-tree (x)
   (setq *call-tree* (cons x *call-tree*)))

;;
(defclass c00 () ())
(defclass c11 () ())
(defclass c22 (c11) ())
(defclass c33 (c22) ())
;;
(defglobal c00 (create (class c00)))
(defglobal c11 (create (class c11)))
(defglobal c22 (create (class c22)))
(defglobal c33 (create (class c33)))
;;
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
#|
(test (foo-30 1) (primary-<object>) equal)
(test (foo-30 c00) (around-<standard-object>-begin
	      before-<standard-object>
	      primary-<standard-object>-begin
	      primary-<object>
	      primary-<standard-object>-end
	      after-<standard-object>
	      around-<standard-object>-end)
 equal)
(test (foo-30 c11) (around-c1-begin
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
|#

;;; 比較関数
(defgeneric compare (x y))

;;; 数値用
(defmethod compare ((x <number>) (y <number>))
  (cond ((= x y) 0)
	((< x y) -1)
	(t 1)))

