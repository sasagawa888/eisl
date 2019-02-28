(defmacro test(form1 form2 :rest pred)
  (cond ((null pred)
         `(if (equal ,form1 ',form2)
              (format (standard-output) "" ',form1)
              ;;(format (standard-output) "~S is ok~%" ',form1)
              (format (standard-output) "~S is bad~%" ',form1)))
        ((and (not (null pred))(consp form1))
         `(if (,@pred ,form1 ',form2)
              (format (standard-output) "" ',form1)
              ;;(format (standard-output) "~S is ok~%" ',form1)
              (format (standard-output) "~S is bad~%" ',form1)))))


(defclass foo-5 ()
   ((a :reader read-foo-a
       :writer write-foo-a
       :accessor access-foo-a
       :boundp boundp-foo-a
       :initarg a
       :initform 1)))
;;
(test (generic-function-p #'read-foo-a) t)
(test (generic-function-p #'write-foo-a) t)
(test (generic-function-p #'access-foo-a) t)
(test (generic-function-p #'boundp-foo-a) t)
;;
(defglobal x (create (class foo-5)))
;;
(test (boundp-foo-a x) t)
(test (read-foo-a x) 1 eql)
(test (access-foo-a x) 1 eql)
;;
(test (write-foo-a 10 x) 10 eql)
(test (boundp-foo-a x) t)
(test (read-foo-a x) 10 eql)
(test (access-foo-a x) 10 eql)
;;
(test (setf (access-foo-a x) 100) 100 eql)
(test (boundp-foo-a x) t)
(test (read-foo-a x) 100 eql)
(test (access-foo-a x) 100 eql)

;;
(defglobal x (create (class foo-5) 'a 10))
;;
(test (boundp-foo-a x) t)
(test (read-foo-a x) 10 eql)
(test (access-foo-a x) 10 eql)
;;
(defglobal x (create (class foo-5) 'b 99))
;;
(test (boundp-foo-a x) t)
(test (read-foo-a x) 1 eql)
(test (access-foo-a x) 1 eql)
;;
(defclass foo-6 ()
   ((a :reader read-foo-a
       :writer write-foo-a
       :accessor access-foo-a
       :boundp boundp-foo-a)))
;;
(defglobal x (create (class foo-6)))
;;
(test (boundp-foo-a x) nil)
(test (write-foo-a 10 x) 10 eql)
(test (boundp-foo-a x) t)
(test (read-foo-a x) 10 eql)
(test (access-foo-a x) 10 eql)
(defglobal x (create (class foo-5) 'b 99))
;;
(test (boundp-foo-a x) t)
(test (read-foo-a x) 1 eql)
(test (access-foo-a x) 1 eql)
;;
(defclass foo-6 ()
   ((a :reader read-foo-a
       :writer write-foo-a
       :accessor access-foo-a
       :boundp boundp-foo-a)))
;;
(defglobal x (create (class foo-6)))
;;
(test (boundp-foo-a x) nil)
(test (write-foo-a 10 x) 10 eql)
(test (boundp-foo-a x) t)
(test (read-foo-a x) 10 eql)
(test (access-foo-a x) 10 eql)

(defgeneric foo-g-1 (x))
(test (generic-function-p #'foo-g-1) t)
(defun foo-9 (x))
(test (generic-function-p #'foo-9) nil)

(defgeneric foo-g-4 (x))
(defmethod foo-g-4 (x) 'object-1)
(defmethod foo-g-4 :around (x) 'around-object-1)
(defmethod foo-g-4 :before (x) 'before-object-1)
(defmethod foo-g-4 :after (x) 'after-object-1)
;;
(defclass aa () ())
(defgeneric foo-g-5 (x))
(defmethod foo-g-5 ((x aa)) 'aa-1)
(defmethod foo-g-5 :around ((x aa)) 'around-aa-1)
(defmethod foo-g-5 :before ((x aa)) 'before-aa-1)
(defmethod foo-g-5 :after ((x aa)) 'after-aa-1)

(defclass c1 () ())
(defclass c2 (c1) ())
(defclass c3 (c2) ())
(defclass c4 () ())
(defglobal c1 (create (class c1)))
(defglobal c2 (create (class c2)))
(defglobal c3 (create (class c3)))
(defglobal c4 (create (class c4)))

(defgeneric foo-g-30 (x y)
   (:method (x y)
        '(<object> <object>))
   (:method (x (y c1))
        '(<object> c1))
   (:method (x (y c2))
        '(<object> c2))
   (:method (x (y c3))
        '(<object> c3))
   (:method ((x c1) y)
        '(c1 <object>))
   (:method ((x c1) (y c1))
        '(c1 c1))
   (:method ((x c1) (y c2))
        '(c1 c2))
   (:method ((x c1) (y c3))
        '(c1 c3))
   (:method ((x c2) y)
        '(c2 <object>))
   (:method ((x c2) (y c1))
        '(c2 c1))
   (:method ((x c2) (y c2))
        '(c2 c2))
   (:method ((x c2) (y c3))
        '(c2 c3))
   (:method ((x c3) y)
        '(c3 <object>))
   (:method ((x c3) (y c1))
        '(c3 c1))
   (:method ((x c3) (y c2))
        '(c3 c2))
   (:method ((x c3) (y c3))
        '(c3 c3))
   )

(test (foo-g-30 1 1) (<object> <object>) equal)
(test (foo-g-30 1 c1) (<object> c1) equal)
(test (foo-g-30 1 c2) (<object> c2) equal)
(test (foo-g-30 1 c3) (<object> c3) equal)
(test (foo-g-30 1 c4) (<object> <object>) equal)
(test (foo-g-30 c1 1) (c1 <object>) equal)
(test (foo-g-30 c1 c1) (c1 c1) equal)
(test (foo-g-30 c1 c2) (c1 c2) equal)
(test (foo-g-30 c1 c3) (c1 c3) equal)
(test (foo-g-30 c1 c4) (c1 <object>) equal)
(test (foo-g-30 c2 1) (c2 <object>) equal)
(test (foo-g-30 c2 c1) (c2 c1) equal)
(test (foo-g-30 c2 c2) (c2 c2) equal)
(test (foo-g-30 c2 c3) (c2 c3) equal)
(test (foo-g-30 c2 c4) (c2 <object>) equal)
(test (foo-g-30 c3 1) (c3 <object>) equal)
(test (foo-g-30 c3 c1) (c3 c1) equal)
(test (foo-g-30 c3 c2) (c3 c2) equal)
(test (foo-g-30 c3 c3) (c3 c3) equal)
(test (foo-g-30 c3 c4) (c3 <object>) equal)
(test (foo-g-30 c4 1) (<object> <object>) equal)
(test (foo-g-30 c4 c1) (<object> c1) equal)
(test (foo-g-30 c4 c2) (<object> c2) equal)
(test (foo-g-30 c4 c3) (<object> c3) equal)
(test (foo-g-30 c4 c4) (<object> <object>) equal)
;;
