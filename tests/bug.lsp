(defclass mc11 () ())
(defglobal mc11 (create (class mc11)))

(defglobal *call-tree* nil)

(defun add-call-tree (x)
   (setq *call-tree* (cons x *call-tree*)))

(defun reset-call-tree ()
   (setq *call-tree* nil))

(defun get-call-tree ()
   (reverse *call-tree*))

(defgeneric mc-if-next-call-side-test (x)
   (:method ((x <standard-object>))
      (add-call-tree 'standard-begin)
      (if (next-method-p)
          (call-next-method)
          (add-call-tree 'standard-no-next))
      (add-call-tree 'standard-end))

   (:method ((x mc11))
      (add-call-tree 'mc11-begin)
      (if (next-method-p)
          (call-next-method)
          (add-call-tree 'mc11-no-next))
      (add-call-tree 'mc11-end)))

(defun test-mc-if-next-call-side ()
   (reset-call-tree)
   (mc-if-next-call-side-test mc11)
   (get-call-tree))