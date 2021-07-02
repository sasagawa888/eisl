(import "ndbm")

(defdynamic *db* nil)

(defclass <dao-class> () ((content :accessor content :initarg c)) (:abstractp t))
(defgeneric key (obj))
(defgeneric serialize (obj))

(defgeneric insert-dao (obj))
(defmethod insert-dao ((obj <dao-class>))
   (let ((str (create-string-output-stream))
         (l (serialize obj)))
        (format str "~S" l)
        (dbm-store (dynamic *db*) (key obj) (get-output-stream-string str) (persist-replace))))

(defun get-dao (klass key)
   (let* ((res-str (dbm-fetch (dynamic *db*) key))
          (res-l (read res-str)))
         (create klass 'c res-l)))
