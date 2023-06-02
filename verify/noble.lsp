(import "test")

(defun mult-underflow ()
  (* 1E-200 1E-200))

(defun mult-overflow ()
  (* *positive-infinity*))

(defun add-overflow ()
  (+ *positive-infinity*))

(defun test-underflow-overflow (underflowing)
  ($assert-ordered-operations '(first second third fourth) 
                              (unwind-protect 
                                (with-handler (lambda (condition)
                                                (record-operation 'second)
                                                (continue-condition condition))
                                              (record-operation 'first)
                                              (funcall underflowing)
                                              (record-operation 'third))
                                (record-operation 'fourth))))

(test-underflow-overflow #'mult-underflow)
(test-underflow-overflow #'mult-overflow)
(test-underflow-overflow #'add-overflow)