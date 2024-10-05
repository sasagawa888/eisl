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
