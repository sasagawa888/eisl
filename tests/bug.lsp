(defgeneric (setf foo2) (value a))
(defmethod (setf foo2) (value a)
    (print a)
    (print value))

(setf (foo2 10) 11)
