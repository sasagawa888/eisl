(import "test")

($ap 1 "Arvyy")

(defmacro m1 (a)
  `(defmacro m2 (b)
      `(list ,,a ,b)))

(m1 1)
($assert (m2 2) (list 1 2))

($test (convert 97.0 <string>) "97.0")

(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <program-error>)) t)
            (return-from exit nil))
        (foo1)
        ($assert t nil)))

($test
    (+ 1
       (catch 'foo
         (+ 2 (throw 'foo 1)))
       3)
    5)

(defclass <foo> ()
    ((bar :reader get-bar :writer set-bar :accessor bar :initarg bar :boundp bar-boundp)))

(let ((f (create (class <foo>) 'bar 1)))
  ($test (get-bar f) 1)
  (set-bar 2 f)
  ($test (get-bar f) 2))

;; check inheritance
(defclass <foo2> (<foo>) ())
(let ((f (create (class <foo2>) 'bar 2)))
  ($test (get-bar f) 2))


(defdynamic *dyn1* 1)

($test
    (dynamic *dyn1*)
    1)

(dynamic-let ((*dyn1* 2)
              (*dyn2* 3))
  ($test (dynamic *dyn1*) 2)
  ($test (dynamic *dyn2*) 3)
  (set-dynamic 4 *dyn1*) 
  ($test (dynamic *dyn1*) 4))

($test (dynamic *dyn1*) 1)

(let ((out (create-string-output-stream)))
  (format out "abc~%de")
  (finish-output out) 
  (let ((stream (create-string-input-stream (get-output-stream-string out))))
      ($test (read-line stream) "abc")
      ($test (read-line stream) "de")
      ($test (read-line stream nil) nil)))

($assert `#(1 ,@(progn '(2 3))) (vector 1 2 3))

(defun test-print (str)
    (format-object (standard-output) str nil)
    (format-char (standard-output) #\newline))

;; I think the intention of the test is probably something like this.
(block exit
    (with-handler
        (lambda (c)
            (test-print "OK3.1")
            (continue-condition c "OK3.2")
            (test-print "FAIL3"))
        (let ((v (cerror "abc" "123")))
            (test-print v))))

#|
in filesignal.lisp
(block exit
    (with-handler
        (lambda (c)
            (test-print "OK3.1")
            (continue-condition c "OK3.2")
            (test-print "FAIL3"))
        (let ((v (signal-condition (create (class <simple-error>) 'format-string "message") t)))
            (test-print v))))
|#

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

;; ISLisp 15.2.2
#|
(defgeneric (setf foo2) (value a))
(defmethod (setf foo2) (value a)
    (test-print a)
    (test-print value))

(setf (foo2 10) 11)
|#


;; check initialize-object
(defclass <foo3> () ((bar3 :reader get-bar3 :writer set-bar3 :initarg bar)))
(defmethod initialize-object ((f <foo3>) :rest args)
    (set-bar3 3 f)
    (call-next-method))
($test (get-bar3 (create (class <foo3>) 'bar 0)) 3)

