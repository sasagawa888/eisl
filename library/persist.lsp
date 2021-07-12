;;; This is an attempt at something like the "Data Access Objects" feature from Postmodern,
;;; a Common Lisp interface to the PostgreSQL database.
;;; See https://marijnhaverbeke.nl/postmodern/

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

(defgeneric insert-dao (obj)
   ;; Insert a new object into the open dbm file *db*
   )
(defmethod insert-dao ((obj <dao-class>))
   (persist--write-dao obj (ndbm-insert)))

(defgeneric update-dao (obj)
   ;; Update an existing record in a dbm file
   )
(defmethod update-dao ((obj <dao-class>))
   (persist--write-dao obj (ndbm-replace)))

(defun get-dao (klass key)
   ;; Get a record from the dbm file, indexed by key.
   ;; Return type is an instance of "klass".
   (let ((maybe-res-str (ndbm-fetch (dynamic *db*) key)))
        (if (null maybe-res-str)
            nil
            (let* ((strm (create-string-input-stream maybe-res-str))
                   (res-l (read strm)))
                  (create klass 'c res-l)))))
