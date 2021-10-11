#|
bikkuri common lisp 
from masahito kurihara's book
|#


(defglobal *new-id* 0)

(defun new-id () (setq *new-id* (+ *new-id* 1)))

(defclass !object ()
    ((id :accessor id! :initform (new-id))))

(defclass !atom (!object) ())
(defclass !list (!object) ())
(defclass !number (!atom)
    ((number :accessor number! :initarg number)))
(defclass !string (!atom)
    ((string :accessor string! :initarg string)))

(defun eq! (!x !y) (= (id! !x) (id! !y)))

(defgeneric !cl (x))
(defmethod !cl ((num <integer>))
    (create (class !number) 'number num))
(defmethod !cl ((str <string>))
    (create (class !string) 'string str))

(defgeneric cl! (x))
(defmethod cl! ((!num !number))
    (number! !num))
(defmethod cl! ((!str !string))
    (string! !str))

(defun !lisp ()
    (for ()
         (nil t)
         (print-prompt)
         (!print! (!eval!(!read!)))))

(defun print-prompt () (format (standard-output) "%!CL>"))

(defun !read! () (!cl (read)))

(defun !print! (!obj)
    (print (cl! !obj)))

(defgeneric !eval! (x))
(defmethod !eval! ((!obj !object)) !obj)
(defmethod !eval! ((!obj !number)) !Obj)
(defmethod !eval! ((!obj !string)) !obj)
