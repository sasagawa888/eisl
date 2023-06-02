(defun sss ()
    (unwind-protect 
        (mult-underflow)
        (print 'cleanup)))


(defun test-error-handler (condition)
    (print "first")
    (continue-condition condition)
    (print "second") )

(defun boo ()
    (with-handler #'test-error-handler (cerror "foo" "bar")) )


(defun mult-underflow ()
    (* 1E-200 1E-200) )

(defun mult-overflow ()
    (* *positive-infinity*) )

(defun add-overflow ()
    (+ *positive-infinity*) )

(defun test-underflow-overflow (underflowing)
    (unwind-protect (with-handler (lambda (condition) 
                                     (print 'second)
                                     (continue-condition condition))
                                  (print 'first)
                                  (funcall underflowing)
                                  (print 'third))
                    (print 'fourth)))

(defun foo ()
    (test-underflow-overflow #'mult-underflow) )

(defun uoo ()
    (test-underflow-overflow #'mult-overflow) )

(defun woo ()
    (test-underflow-overflow #'add-overflow) )
