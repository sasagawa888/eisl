(defun baz ()
  (with-handler (lambda (condition) 
                  (throw 'tag "handled"))
                (catch 'tag
                                        (error "error"))
                (catch 'tag
                                        (error "error"))))


(defun foo ()
  (let ((error-count 0)) 
    (flet ((inner-handler (condition)
             (if (< error-count 2) 
                 (progn 
                   (setf error-count (+ error-count 1))
                   (continue-condition condition "inner handler continued"))
                 (signal-condition condition (condition-continuable condition))))
           (outer-handler (condition)
             (continue-condition condition "outer handler continued"))) 
      (with-handler #'outer-handler 
                    (with-handler #'inner-handler
                      (cerror "foo" "bar")
                      (cerror "herp" "derp")
                      (cerror "bing" "bong"))))))