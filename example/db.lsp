;;; This is based on the "simple database" Rosetta Code task.
;;; However it is not suitable for submission because I made two
;;; changes to the requirements:
;;; 1. Storage is disk-based, using the UNIX ndbm library
;;; 2. Instead of taking command-line arguments, interaction is by menus and form screens

(import "persist")
(import "virtty")

(defglobal *db* nil)

(defconstant *db-file* "db")

(defclass <item> (<dao-class>)
  ;; this is the unit of data stored/displayed in *db*"
  ((title :initform " ")
   (category :initform "default")
   (date :initform (get-universal-time))))

(defun set-category (new-item)
   (setf (gethash (item-category new-item) *db-cat*) 't))

(defun find-item-in-db (&rest maybe-category)
   (if (null maybe-category)
       (car *db*)
       (find (maybe-category) *db* :key #'item-category :test #'string=)))

(defun scan-category ()
   "scan categories from an existing database -- after reading it from disk"
   (dolist (itm *db*) (set-category itm)))

(defun pr-univ-time (utime)
   (multiple-value-bind
         (second minute hour date month year day-of-week dst-p tz)
       (decode-universal-time utime)
      (declare (ignore day-of-week dst-p tz))
      (format nil "~4,'0d-~2,'0d-~2,'0d ~2,'0d:~2,'0d:~2,'0d" year month date hour minute second)))

(defun pr (&optional (item (find-item-in-db)) (stream t))
   "print an item"
   (when item
         (format stream "~a: (~a) (~a)~%"
	             (item-title item)
	             (item-category item)
	             (pr-univ-time (item-date item)))))

(defun pr-per-category ()
   "print the latest item from each category"
   (loop for k being the hash-keys in *db-cat*
	  do (pr (find-item-in-db k))))

(defun pr-all ()
   "print all the items, *db* is sorted by time."
   (dolist (itm *db*)  (pr itm)))

(defun pr-all-categories (&optional (stream t))
   (loop for k being the hash-keys in *db-cat*
      do (format stream "(~a) " k)))

(defun insert-item (item)
   "insert item into database in a time sorted list. okay for a small list, as per spec."
   (let ((first-item (car *db*)) (new-itm item))
        (set-category new-itm)
        (push new-itm *db*)
        (when (and first-item (>= (item-date new-itm) (item-date first-item)))
              (setf *db* (sort *db* #'> :key #'item-date)))
        *db*))

(defun read-db-from-file (&optional (file *db-file*))
   (with-open-file (in file :if-does-not-exist nil)
	  (when in
		    (with-standard-io-syntax (setf *db* (read in)))
		    (scan-category))))

(defun save-db-to-file (&optional (file *db-file*))
   (with-open-file (out file :direction :output :if-exists :supersede)
	  (with-standard-io-syntax
		(print *db* out))))

(defun del-db ()
   (setf *db* nil)
   (save-db-to-file))

(defun del-item ()
   (let ((f (create (class <form>) 't "Delete Item" 'k '("Item"))))
        (dbm-delete (dynamic *db*) (car f))))

(defun add-item-to-db (args)
   (read-db-from-file)
   (insert-item (make-item :title (first args) :category (second args)))
   (save-db-to-file))

(defun help-menu ()
   (format t "clisp db.lisp ~{~15T~a~^~% ~}"
	       '("delete <item-name> -------------------  delete an item"
	         "delete-all ---------------------------  delete the database"
             "insert <item-name> <item-category> ---  insert an item with its category"
	         "show ---------------------------------  shows the latest inserted item"
	         "show-categories ----------------------  show all categories"	    
	         "show-all -----------------------------  show all items"
	         "show-per-category --------------------  show the latest item per category")))

(defun db-cmd-run (args)
   (cond ((and (> (length args) 1) (equal (first args) "delete"))
	      (del-item (second args)))
	     ((equal (first args) "delete-all") (del-db))	
	     ((and (> (length args) 2) (equal (first args) "insert"))
	      (add-item-to-db (rest args)))
	     ((equal (first args) "show") (read-db-from-file) (pr))
	     ((equal (first args) "show-categories") (read-db-from-file) (pr-all-categories))
         ((equal (first args) "show-all") (read-db-from-file) (pr-all))
         ((equal (first args) "show-per-category") (read-db-from-file) (pr-per-category))
         (t (help-menu))))
(defun db-cmd-run (choice)
   (case choice
         ((0) (del-item))
         ((1) (del-db))
         ((2) (add-item-to-db))
         ((3) (pr))
         ((4) (pri-all-categories))
         ((5) (pr-all))
         ((6) (pr-per-category))))

(db-cmd-run (select "Simple Database" '("Delete an item"
                                        "Delete the database"
                                        "Insert an item with its category"
                                        "Show the latest inserted item"
                                        "Show all catagories"
                                        "Show all items"
                                        "Show the latest item per category"
                                        "Quit")))
(let ((choice (main-menu)))
     (while (/= choice 7)
            (db-cmd-run choice)
            (setq choice (main-menu))))
