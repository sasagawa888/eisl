(import "test")

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
;; is it specified in ISLisp ?
#|
(defgeneric (setf foo2) (value a))
(defmethod (setf foo2) (value a)
    (test-print a)
    (test-print value))

(setf (foo2 10) 11)
|#
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
