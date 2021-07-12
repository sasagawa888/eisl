;;; Support for indexed files.
;;; See the man page for details:
;;; https://man.openbsd.org/dbm_open
;;; Lisp functions are similar to the C ones.
;;; Note however that both keys and values must be strings, binary data isn't supported like it would be in C.
;;;
;;; Note that for Linux you'll need to install whatever is the equivalent of the `libgdbm-dev` and `libgdm-compat-dev` Ubuntu packages for your distro.
;;;
;;; See persist.lsp for a higher-level way to do things.

(c-include "<ndbm.h>")
(c-include "<fcntl.h>")
(c-option "-lgdbm_compat -lgdbm" linux)

;; This is the best way I could see to export C #define contants?
(defun ndbm-rdonly ()
   (c-lang "res = O_RDONLY | INT_FLAG;"))
(defun ndbm-wronly ()
   (c-lang "res = O_WRONLY | INT_FLAG;"))
(defun ndbm-rdwr ()
   (c-lang "res = O_RDWR | INT_FLAG;"))
(defun ndbm-creat ()
   (c-lang "res = O_CREAT | INT_FLAG;"))

(defun ndbm-open (file flags mode)
   ;; Open an ndbm file
   (the <string> file)(the <fixnum> flags)(the <fixnum> mode)
   (c-lang "char *res_str;")
   (c-lang "res_str = fast_sprint_hex_long(dbm_open(Fgetname(FILE), FLAGS & INT_MASK, MODE & INT_MASK));")
   (c-lang "res = Fmakefaststrlong(res_str);"))

(defun ndbm-insert ()
   (c-lang "res = DBM_INSERT | INT_FLAG;"))
(defun ndbm-replace ()
   (c-lang "res = DBM_REPLACE | INT_FLAG;"))

(defun ndbm-store (db key content store-mode)
   ;; Store a record to the file
   (the <longnum> db)(the <string> key)(the <string> content)(the <fixnum> store-mode)
   (c-lang "datum key, content;");
   (c-lang "key.dptr = Fgetname(KEY); key.dsize = strlen(key.dptr) + 1;")
   (c-lang "content.dptr = Fgetname(CONTENT); content.dsize = strlen(content.dptr) + 1;")
   (c-lang "res = dbm_store(Fgetlong(DB), key, content, STORE_MODE & INT_MASK) | INT_FLAG;"))

(defun ndbm-fetch (db key)
   ;; Fetch a record from the file
   (the <longnum> db)(the <string> key)
   (c-lang "datum key, content;")
   (c-lang "key.dptr = Fgetname(KEY); key.dsize = strlen(key.dptr) + 1;")
   (c-lang "content = dbm_fetch(Fgetlong(DB), key);")
   (c-lang "res = (content.dptr == NULL) ? NIL : Fmakestr(content.dptr);"))

(defun ndbm-delete (db key)
   ;; Delete a record from the file
   (the <longnum> db)(the <string> key)
   (c-lang "datum key;")
   (c-lang "key.dptr = Fgetname(KEY); key.dsize = strlen(key.dptr) + 1;")
   (c-lang "res = dbm_delete(Fgetlong(DB), key) | INT_FLAG;"))

(defun ndbm-close (db)
   ;; Close an open dbm file
   (the <longnum> db)
   (c-lang "res = NIL; dbm_close(Fgetlong(DB));"))
