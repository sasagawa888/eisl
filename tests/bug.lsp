(defglobal error-count 0)

(defun outer-handler (condition)
  (continue-condition condition "outer handler continued"))

(defun inner-handler (condition)
  (if (< error-count 2) 
      (progn 
        (setf error-count (+ error-count 1))
        (continue-condition condition "inner handler continued"))
      (signal-condition condition (condition-continuable condition))))

(defun foo ()
  (with-handler #'outer-handler 
                (with-handler #'inner-handler
                              (print (cerror "foo" "bar"))
                              (print (cerror "herp" "derp"))
                              (print (cerror "bing" "bong")))))


