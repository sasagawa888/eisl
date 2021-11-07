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

