(c-include "<ndbm.h>")
(c-include "<fcntl.h>")

(defdynamic *db* nil)

(defun persist-rdonly ()
   (c-lang "res = O_RDONLY | INT_FLAG;"))
(defun persist-wronly ()
   (c-lang "res = O_WRONLY | INT_FLAG;"))
(defun persist-rdwr ()
   (c-lang "res = O_RDWR | INT_FLAG;"))
(defun persist-creat ()
   (c-lang "res = O_CREAT | INT_FLAG;"))

(defun dbm-open (file flags mode)
   (the <string> file)(the <fixnum> flags)(the <fixnum> mode)
   (c-lang "char *res_str;")
   (c-lang "res_str = fast_sprint_hex_long(dbm_open(Fgetname(FILE), FLAGS & INT_MASK, MODE & INT_MASK));")
   (c-lang "res = Fmakefaststrlong(res_str);"))

(defun persist-insert ()
   (c-lang "res = DBM_INSERT | INT_FLAG;"))
(defun persist-replace ()
   (c-lang "res = DBM_REPLACE | INT_FLAG;"))

(defun dbm-store (db key content store-mode)
   (the <longnum> db)(the <string> key)(the <string> content)(the <fixnum> store-mode)
   (c-lang "datum key, content;");
   (c-lang "key.dptr = Fgetname(KEY); key.dsize = strlen(key.dptr);")
   (c-lang "content.dptr = Fgetname(CONTENT); content.dsize = strlen(content.dptr) + 1;")
   (c-lang "res = dbm_store(Fgetlong(DB), key, content, STORE_MODE & INT_MASK);"))

(defun dbm-fetch (db key)
   (the <longnum> db)(the <string> key)
   (c-lang "datum key, content;")
   (c-lang "key.dptr = Fgetname(KEY); key.dsize = strlen(key.dptr);")
   (c-lang "content = dbm_fetch(Fgetlong(DB), key);")
   (c-lang "res = Fmakestr(content.dptr);"))

(defun dbm-delete (db key)
   (the <longnum> db)(the <string> key)
   (c-lang "datum key;")
   (c-lang "key.dptr = Fgetname(KEY); key.dsize = strlen(key.dptr);")
   (c-lang "res = dbm_delete(Fgetlong(DB), key);"))

(defun dbm-close (db)
   (the <longnum> db)
   (c-lang "res = NIL; dbm_close(Fgetlong(DB));"))

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
