;; This is an attempt at something like the "Data Access Objects" feature from Postmodern,
;; a Common Lisp interface to the PostgreSQL database.

(import "ndbm")

(defdynamic *db* nil)

(defclass <dao-class> () ((content :accessor content :initarg c)) (:abstractp t))
(defgeneric key (obj))
(defgeneric serialize (obj))

(defgeneric persist--write-dao (obj store-mode))
(defmethod persist--write-dao ((obj <dao-class>) store-mode)
   (let ((str (create-string-output-stream))
         (l (serialize obj)))
        (format str "~S" l)
        (ndbm-store (dynamic *db*) (key obj) (get-output-stream-string str) store-mode)))

(defgeneric insert-dao (obj))
(defmethod insert-dao ((obj <dao-class>))
   (persist--write-dao obj (ndbm-insert)))

(defgeneric update-dao (obj))
(defmethod update-dao ((obj <dao-class>))
   (persist--write-dao obj (ndbm-replace)))

(defun get-dao (klass key)
   (let* ((res-str (ndbm-fetch (dynamic *db*) key))
          (res-l (read res-str)))
         (create klass 'c res-l)))
