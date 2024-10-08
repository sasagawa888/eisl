(defgeneric (setf foo2) (value a))
(defmethod (setf foo2) (value a)
    (test-print a)
    (test-print value))

;(setf (foo2 10) 11)
