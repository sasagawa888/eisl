(defun flet1 ()
  (flet ((test-func () T))
    (let* ((result "flet test"))
      result)))

(defun flet2 ()
  (flet ((test-func () T))
      "flet test")) 



(defun baz ()
    (with-handler (lambda (condition) (throw 'tag "handled"))
                  (print (catch 'tag (error "error")))
                  (print (catch 'tag (error "error")))))

(defun fact (n)
    (let ((a 1))
       (labels ((rec (x)
                  (if (< x 1)
                      1
                      (* x (rec (- x 1))) )))
           (rec n))))



(defglobal error-count 0)

(defun outer-handler (condition)
    (continue-condition condition "outer handler continued") )

(defun inner-handler (condition)
    (if (< error-count 2)
        (progn (setf error-count (+ error-count 1))
               (continue-condition condition "inner handler continued"))
        (signal-condition condition (condition-continuable condition))))

(defun foo ()
    (with-handler #'outer-handler
                  (with-handler #'inner-handler
                                (print (cerror "foo" "bar"))
                                (print (cerror "herp" "derp"))
                                (print (cerror "bing" "bong")))))

(defun foo1 ()
    (let ((error-count 0))
       (flet ((inner-handler (condition)
                  (if (< error-count 2)
                      (progn (setf error-count (+ error-count 1))
                             (continue-condition condition "inner handler continued"))
                      (signal-condition condition (condition-continuable condition))))(outer-handler (condition)
                  (continue-condition condition "outer handler continued")))
           (with-handler #'outer-handler
                         (with-handler #'inner-handler
                                       (cerror "foo" "bar")
                                       (cerror "herp" "derp")
                                       (cerror "bing" "bong"))))))



(defun unwind1 ()
    (unwind-protect (progn (catch 'tag
                                  (unwind-protect
                                   (throw 'tag "thrown")
                                   (print "should be printed first")))
                           (print "should be printed second"))
                    (print "should be printed third")))

(defun unwind2 ()
    (unwind-protect (progn (catch 'tag (throw 'tag "thrown"))
                           (print "should be printed first"))
                    (print "should be printed second")))
