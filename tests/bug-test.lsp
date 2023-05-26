(import "test")

#| 
;;; invalid-tag
($error
  (block b1
         (block b2
                (unwind-protect 
                  (return-from b1 888) ;;; b2 invalid
                  (return-from b2 999)))) <control-error>)

|#
(defun boo ()
  (block b1
         (block b2
                (unwind-protect 
                  (return-from b1 888) ;;; b2 invalid
                  (return-from b2 999)))))

(defun unwind1 ()
  ($assert-ordered-operations
    '(first second third)
    (unwind-protect 
      (progn
        (catch 'tag
               (unwind-protect
                 (throw 'tag "thrown")
                 (record-operation 'first)))
        (record-operation 'second))
      (record-operation 'third))))

(defun unwind2 ()
  ($assert-ordered-operations
    '(first second)
    (unwind-protect
      (progn
        (catch 'tag
               (throw 'tag "thrown"))
        (record-operation 'first))
      (record-operation 'second))))


(defun unwind3 ()
  ($assert-ordered-operations
    '("asdf1" "asdf2")
    (unwind-protect
      (record-operation (catch 'tag (throw 'tag "asdf1")))
      (record-operation "asdf2"))))

(defun unwind4 ()
  ($assert (catch 'tag (throw 'tag "asdf1")) "asdf1"))

(defun baz ()
  (with-handler (lambda (condition) 
                  (throw 'tag "handled"))
                (record-operation (catch 'tag
                                        (error "error")))
                (record-operation (catch 'tag
                                        (error "error")))))

(defun baz-test ()
  ($assert-ordered-operations
    '("handled" "handled")
    (baz)))

(defun baz-unwind-test ()
  ($assert-ordered-operations
    '("handled" "handled" "cleanup")
    (unwind-protect 
      (baz)
      (record-operation "cleanup"))))

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
                      (record-operation (cerror "foo" "bar"))
                      (record-operation (cerror "herp" "derp"))
                      (record-operation (cerror "bing" "bong")))))))

(defun foo-test ()
  ($assert-ordered-operations
    '("inner handler continued" 
      "inner handler continued" 
      "outer handler continued") 
    (foo)))

(defun foo-unwind-test ()
  ($assert-ordered-operations
    '("inner handler continued" 
      "inner handler continued" 
      "outer handler continued"
      "cleanup") 
    (unwind-protect (foo)
    (record-operation "cleanup"))))

(defun test-all ()
  (unwind1)
  (unwind2)
  (unwind3)
  (unwind4)
  (baz-test)
  (baz-unwind-test)
  (foo-test)
  (foo-unwind-test))


(defglobal a #2a((3 1 1 2)(5 1 3 4)(2 0 1 0)(1 3 2 1)))
