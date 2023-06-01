
(defun test-error-handler (condition)
    (print "first")
    (continue-condition condition)
    (print "second") )

(defun boo ()
    (with-handler #'test-error-handler (cerror "foo" "bar")) )


(import "test")

(defun mult-underflow ()
    (* 1E-200 1E-200) )

(defun mult-overflow ()
    (* *positive-infinity*) )

(defun add-overflow ()
    (+ *positive-infinity*) )

(defun test-underflow-overflow (underflowing)
    ($assert-ordered-operations '(first second third fourth)
                                (unwind-protect (with-handler (lambda (condition) 
                                                                 (record-operation 'second)
                                                                 (continue-condition condition))
                                                              (record-operation 'first)
                                                              (funcall underflowing)
                                                              (record-operation 'third))
                                                (record-operation 'fourth))))

(defun foo ()
    (test-underflow-overflow #'mult-underflow) )

(defun uoo ()
    (test-underflow-overflow #'mult-overflow) )

(defun woo ()
    (test-underflow-overflow #'add-overflow) )
