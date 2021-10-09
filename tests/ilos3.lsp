#|
bikkuri common lisp 
from masahito kurihara' book
|#


(defglobal *new-id* 0)

(defun new-id () (setq *new-id* (+ *new-id* 1)))

(defclass !object ()
    ((id :accessor id! :initform (new-id))))

(defclass !atom (!object) ())
(defclass !list (!object) ())
(defclass !number (!atom)
    ((number :accessor number! :initarg number)))

(defun eq! (!x !y) (= (id! !x) (id! !y)))

(defgeneric !cl (x))
(defmethod !cl ((num <number>))
    (create (class !number) 'number num))

(defgeneric cl! (x))
(defmethod cl! ((num !number))
    (number! num))

(defun !lisp ()
    (for ()
         (nil t)
         (print-prompt)
         (!print! (!eval!(!read!)))))

(defun print-prompt () (format (standard-output) "~%!CL>"))

(defun !read! () (!cl (read)))

(defun !print! (!obj)
    (format (standard-output) "~A" (cl! !obj)))

(defgeneric !eval! (x))
(defmethod !eval! ((!obj !object)) !obj)
