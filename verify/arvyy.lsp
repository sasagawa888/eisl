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


