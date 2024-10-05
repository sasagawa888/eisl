(import "test")

(defclass <foo> ()
    ((bar :reader get-bar :writer set-bar :accessor bar :initarg bar :boundp bar-boundp)))

(let ((f (create (class <foo>) 'bar 1)))
  ($assert (get-bar f) 1)
  (set-bar 2 f)
  ($assert (get-bar f) 2))
#|
;; check inheritance
(defclass <foo2> (<foo>) ())
(let ((f (create (class <foo2>) 'bar 2)))
  ($assert (get-bar f) 2))

;; check initialize-object
(defclass <foo3> () ((bar3 :reader get-bar3 :writer set-bar3 :initarg bar)))
(defmethod initialize-object ((f <foo3>) :rest args)
    (set-bar3 3 f)
    (call-next-method))
($assert (get-bar3 (create (class <foo3>) 'bar 0)) 3)
|#

;; check accessor
(let ((obj (create (class <foo>))))
  (setf (bar obj) 4)
  ($assert (bar obj) 4))

;; check boundp
(let ((obj (create (class <foo>))))
  ($assert (bar-boundp obj) nil)
  (setf (bar obj) 6)
  ($assert (bar-boundp obj) t))

;; check class lookup error
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <undefined-entity>)) t)
            ($assert (undefined-entity-name condition) '<doesntexist>)
            ($assert (undefined-entity-namespace condition) 'class)
            (return-from exit nil))
        (class <doesntexist>)
        (format (standard-output) "FAIL~%")))


(defun test-print (int)
    (format-integer (standard-output) int 10)
    (format-char (standard-output) #\newline))

(defgeneric foo1 (a b))
(defmethod foo1 :before (a b) (test-print 2))
(defmethod foo1 :before ((a <integer>) (b <integer>)) (test-print 1))
(defmethod foo1 (a b) (test-print 3))
(defmethod foo1 ((a <integer>) (b <integer>))
    (call-next-method)
    (test-print 4))
(defmethod foo1 :after (a b) (test-print 5))
(defmethod foo1 :after ((a <integer>) (b <integer>)) (test-print 6))
(defmethod foo1 :around (a b)
    (call-next-method)
    (test-print 7))
(defmethod foo1 :around ((a <integer>) (b <integer>))
    (call-next-method)
    (test-print 8)
    a)

(let ((result (foo1 9 10)))
  (test-print result))


;; test setf
(defgeneric (setf foo2) (value a))
(defmethod (setf foo2) (value a)
    (test-print a)
    (test-print value))

;;error
;(setf (foo2 10) 11)

;; test no next-method error reporting
(defgeneric foo3 (value))
(defmethod foo3 ((value <number>))
    (call-next-method))
(block exit
    (with-handler
        (lambda (condition)
            ;; can't portably test anything about condition
            ;; since spec doesn't tell what it exactly should be
            (return-from exit nil))
        (foo3 1)
        (print "FAIL")))
