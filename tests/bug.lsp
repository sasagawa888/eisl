
(defclass foo-6 ()
   ((a :reader read-foo-a
       :writer write-foo-a
       :accessor access-foo-a
       :boundp boundp-foo-a)))

(defglobal x (create (class foo-6)))