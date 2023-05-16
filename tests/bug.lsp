(defun handler (condition)
  (throw 'tag "handled"))

(defun baz ()
  (with-handler #'handler
                (print (catch 'tag
                              (error "error")))
                (print (catch 'tag
                              (error "error")))))

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


(defglobal a #2a((3 1 1 2)(5 1 3 4)(2 0 1 0)(1 3 2 1)))