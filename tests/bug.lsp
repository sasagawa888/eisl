(import "test")

(defun disp (x)
	(mapcar #'get-method-body (get-method x)))

(defglobal *call-tree* nil)

(defun add-call-tree (x)
   (setq *call-tree* (cons x *call-tree*)))
;;
(test (defclass c00 () ()) c00)
(test (defclass c11 () ()) c11)
(test (defclass c22 (c11) ()) c22)
(test (defclass c33 (c22) ()) c33)
;;
($eval (defglobal c00 (create (class c00))))
($eval (defglobal c11 (create (class c11))))
($eval (defglobal c22 (create (class c22))))
($eval (defglobal c33 (create (class c33))))
;;
#|
(AROUND-<STANDARD-OBJECT>-BEGIN
BEFORE-<STANDARD-OBJECT>
PRIMARY-<STANDARD-OBJECT>-BEGIN
PRIMARY-<OBJECT>
PRIMARY-<STANDARD-OBJECT>-END
AFTER-<STANDARD-OBJECT>
AROUND-<STANDARD-OBJECT>-END)
but got 
AROUND-<STANDARD-OBJECT>-BEGIN
PRIMARY-<STANDARD-OBJECT>-BEGIN
PRIMARY-<OBJECT>
PRIMARY-<STANDARD-OBJECT>-END
AROUND-<STANDARD-OBJECT>-END
AFTER-<STANDARD-OBJECT>) 

T
|#
($eval 
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
   ))

;;
($eval
 (defun foo-30 (x)
   (setq *call-tree* nil)
   (foo-sub-30 x)
   (reverse *call-tree*)))
;;
;(test (foo-30 1) (primary-<object>) equal)
(test (foo-30 c00) (around-<standard-object>-begin
	      before-<standard-object>
	      primary-<standard-object>-begin
	      primary-<object>
	      primary-<standard-object>-end
	      after-<standard-object>
	      around-<standard-object>-end)
 equal)