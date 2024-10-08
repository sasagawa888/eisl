
(import "test")

(defclass foo-5 () 
   ((a :reader read-foo-a
       :writer write-foo-a
       :accessor access-foo-a
       :boundp boundp-foo-a
       :initarg a
       :initform 1)))
;;
($test (generic-function-p #'read-foo-a) t)
($test (generic-function-p #'write-foo-a) t)
($test (generic-function-p #'access-foo-a) t)
($test (generic-function-p #'boundp-foo-a) t)