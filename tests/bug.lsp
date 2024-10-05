

(defclass <foo> ()
    ((bar :reader get-bar :writer set-bar :accessor bar :initarg bar :boundp bar-boundp)))

(defun test1 ()
    (let ((f (create (class <foo>) 'bar 1)))
        (get-bar f)
        (set-bar 2 f)
        (get-bar f) 2))

;; check inheritance
(defclass <foo2> (<foo>) ())

(defun test2 ()
    (let ((f (create (class <foo2>) 'bar 2)))
        (get-bar f) 2))

#|
generate following code automaticaly by defclass
(IF (NOT (GENERIC-FUNCTION-P (FUNCTION* GET-BAR))) (DEFGENERIC GET-BAR (x)))
(DEFMETHOD GET-BAR ((x <FOO>)) 
     (LET ((y (SLOT-VALUE x (QUOTE BAR))))
      (IF (EISL-DUMMYP y)
          (CERROR "undefined" "reader")) y))

(IF (NOT (GENERIC-FUNCTION-P (FUNCTION* SET-BAR)))(DEFGENERIC SET-BAR (x (y <FOO>))))

(DEFMETHOD SET-BAR (x (y <FOO>)) (SETF (SLOT-VALUE y (QUOTE BAR)) x))
     
(IF (NOT (GENERIC-FUNCTION-P (FUNCTION* BAR))) (DEFGENERIC BAR (x)))

(DEFMETHOD BAR ((x <FOO>)) (LET ((y (SLOT-VALUE x (QUOTE BAR)))) (IF (EISL-DUMMYP y) (CERROR "undefined" "accessor")) y))

(DEFMETHOD BAR ((x <NULL>)) (QUOTE BAR))

(IF (NOT (GENERIC-FUNCTION-P (FUNCTION* BAR-BOUNDP))) (DEFGENERIC BAR-BOUNDP (x)))

(DEFMETHOD BAR-BOUNDP ((x <FOO>)) (NOT (EISL-DUMMYP (SLOT-VALUE x (QUOTE BAR)))))

|#