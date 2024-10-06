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