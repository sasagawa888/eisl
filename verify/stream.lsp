(import "test")

(defconstant *tp-tmp-dir* "verify/")

(defglobal *tp-file-no* 0)
(defglobal *tp-example-file* nil)

(defun tp-make-tmp-file ()
  (setq *tp-example-file* 
	(string-append 
	 *tp-tmp-dir* 
	 "islsp" 
	 (convert (setq *tp-file-no* (+ *tp-file-no* 1)) <string>)
	 ".dat")))
(defconstant *tp-tmp-input-file* (tp-make-tmp-file))
(defconstant *tp-tmp-output-file* (tp-make-tmp-file))
(defconstant *tp-tmp-error-file* (tp-make-tmp-file))

;;; -*- lisp -*-
;;;
;;; Chapter 18 Stream class
;;;

($ap 1 "Stream class")

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (streamp obj) --> boolean
;;;------------------------------------------------------------
($ap 2 "streamp" P.101)
;;;
($test (streamp (standard-input)) t)
($test (streamp (standard-output)) t)
($test (streamp (error-output)) t)
($test (streamp '()) nil)
($test (streamp '(a b c)) nil)
;;;
($argc streamp 1 0 0)
;;;
($predicate streamp $file-input-stream $file-output-stream
                    $string-input-stream $string-output-stream)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (open-stream-p obj) --> boolean
;;;------------------------------------------------------------
($ap 2 "open-stream-p" P.101)
;;;
($test (open-stream-p (standard-input)) t)
($test (open-stream-p (standard-output)) t)
($test (open-stream-p (error-output)) t)
($test (open-stream-p '()) nil)
($test (open-stream-p '(a b c)) nil)
;;; �����̌�
($argc open-stream-p 1 0 0)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (input-stream-p obj) --> boolean
;;;------------------------------------------------------------
($ap 2 "input-stream-p" P.101)
;;;
($test (input-stream-p (standard-input)) t)
($test (input-stream-p (standard-output)) nil)
($test (input-stream-p (error-output)) nil)
($test (input-stream-p '()) nil)
($test (input-stream-p '(a b c)) nil)
;;;
($argc input-stream-p 1 0 0)
;;;
($predicate input-stream-p $file-input-stream $string-input-stream)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (output-stream-p obj) --> boolean
;;;------------------------------------------------------------
($ap 2 "output-stream-p" P.101)
;;;
($test (output-stream-p (standard-input)) nil)
($test (output-stream-p (standard-output)) t)
($test (output-stream-p (error-output)) t)
($test (output-stream-p '()) nil)
($test (output-stream-p "hello") nil)
;;;
($argc output-stream-p 1 0 0)
;;;
($predicate output-stream-p $file-output-stream $string-output-stream)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (standard-input) --> <stream>
;;;------------------------------------------------------------
($ap 2 "standard-input" P.102)
;;;
;;; �����̌�
($argc standard-input 0 0 0)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (standard-output) --> <stream>
;;;------------------------------------------------------------
($ap 2 "standard-output" P.102)
;;;
;;; �����̌�
($argc standard-output 0 0 0)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (error-output) --> <stream>
;;;------------------------------------------------------------
($ap 2 "error-output" P.102)
;;;
;;; �����̌�
($argc error-output 0 0 0)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;  (with-standard-input stream-form form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "with-standard-input" P.102)
;;;
($test
 (with-standard-input (create-string-input-stream "this is a string")
		      (list (read) (read)))
 (this is)
 equal)
;;; �����̌�
($argc with-standard-input 1 0 1)
;;; stream-from �� input-stream
($type with-standard-input ($file-input-stream $string-input-stream) 
       :target)
;;;
($eval (defglobal s (create-string-input-stream "abc")))
($test (read-char s) #\a)
($eval (close s))
($error (read-char s) <stream-error>)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;  (with-standard-output stream-form form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "with-standard-output" P.102)
;;;
;;; �����̌�
($argc with-standard-output 1 0 1)
;;; stream-from �� output-stream
($type with-standard-output ($file-output-stream $string-output-stream) 
       :target)

;;;------------------------------------------------------------
;;; [special operator] 
;;;
;;;  (with-error-output stream-form form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "with-error-output" P.102)
;;;
;;; �����̌�
($argc with-error-output 1 0 1)
;;; stream-from �� output-stream
($type with-error-output ($file-output-stream $string-output-stream) 
       :target)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (open-input-file filename [element-class]) --> <stream>
;;;------------------------------------------------------------
($ap 2 "open-input-file" P.102)
;;;
($eval (tp-make-tmp-file))
($eval 
 (defglobal outstream (open-output-file *tp-example-file*)))
($eval (close outstream))
($eval 
 (defglobal instream (open-input-file *tp-example-file*)))
($test (open-stream-p instream) t)
($test (input-stream-p instream) t)
($test (output-stream-p instream) nil)
($eval (close instream))
;;; element-class
($eval (tp-make-tmp-file))
($eval 
 (defglobal byte-outstream (open-output-file *tp-example-file* 8)))
($eval (close byte-outstream))
($eval 
 (defglobal byte-instream (open-input-file *tp-example-file* 8)))
($test (open-stream-p byte-instream) t)
($eval (close byte-instream))
($error (open-input-file *tp-example-file* 7) <error>)
($error (open-input-file *tp-example-file* 9) <error>)
;;;
($argc open-input-file 1 1 0)
($type open-input-file ($string) :target 8)

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (open-output-file filename [element-class]) --> <stream>
;;;------------------------------------------------------------
($ap 2 "open-output-file" P.102)
;;;
($eval (tp-make-tmp-file))
($eval 
 (defglobal outstream (open-output-file *tp-example-file*)))
($test (open-stream-p outstream) t)
($test (output-stream-p outstream) t)
($test (input-stream-p outstream) nil)
($eval (close outstream))
($test (open-stream-p outstream) nil)
($test (output-stream-p outstream) t)
($test (input-stream-p outstream) nil)
;;; element-class
($eval (tp-make-tmp-file))
($eval 
 (defglobal byte-outstream (open-output-file *tp-example-file* 8)))
($test (open-stream-p byte-outstream) t)
($test (output-stream-p byte-outstream) t)
($test (input-stream-p byte-outstream) nil)
($eval (close byte-outstream))
($error (open-output-file *tp-example-file* 7) <error>)
($error (open-output-file *tp-example-file* 9) <error>)
;;;
($argc open-output-file 1 1 0)
($type open-output-file ($string) :target 8)
;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (open-io-file filename [element-class]) --> <stream>
;;;------------------------------------------------------------
($ap 2 "open-io-file" P.102)
;;;
($eval (tp-make-tmp-file))
($eval 
 (defglobal iostream (open-io-file *tp-example-file*)))
($test (open-stream-p iostream) t)
($test (output-stream-p iostream) t)
($test (input-stream-p iostream) t)
($eval (format iostream "hello"))
($eval (set-file-position iostream 0))
($test (read iostream) hello)
($eval (close iostream))
($test (open-stream-p iostream) nil)
($test (output-stream-p iostream) t)
($test (input-stream-p iostream) t)
;;; element-class
($eval (tp-make-tmp-file))
($eval 
 (defglobal byte-iostream (open-io-file *tp-example-file* 8)))
($test (open-stream-p byte-iostream) t)
($test (output-stream-p byte-iostream) t)
($test (input-stream-p byte-iostream) t)
($eval (close byte-iostream))
($error (open-io-file *tp-example-file* 7) <error>)
($error (open-io-file *tp-example-file* 9) <error>)
;;;
($argc open-io-file 1 1 0)
($type open-io-file ($string) :target 8)
;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (with-open-input-file (name file [element-class]) form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "with-open-input-file" P.103)
;;; �����̌�
($error (with-open-input-file) <program-error>)
($error (with-open-input-file . 1) <program-error>)
;;; bind-list ���s��
($error (with-open-input-file 1) <error>)
($error (with-open-input-file ()) <error>)
($error (with-open-input-file (foo)) <error>)
;;; name ���V���{���łȂ�
($eval (tp-make-tmp-file))
($error (with-open-input-file (#2a((a b) (c d)) *tp-example-file*)) 
	<domain-error>)
($error (with-open-input-file (#\a *tp-example-file*)) <domain-error>)
($error (with-open-input-file (1234 *tp-example-file*)) <domain-error>)
($error (with-open-input-file (1.234 *tp-example-file*)) <domain-error>)
($error (with-open-input-file ("abc" *tp-example-file*)) <domain-error>)
($error (with-open-input-file (#(a b c) *tp-example-file*)) <domain-error>)
($error (with-open-input-file ((x y) *tp-example-file*)) <domain-error>)
;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (with-open-output-file (name file [element-class]) form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "with-open-output-file" P.103)
;;; �����̌�
($error (with-open-output-file) <program-error>)
($error (with-open-output-file . 1) <program-error>)
;;; bind-list ���s��
($error (with-open-output-file 1) <error>)
($error (with-open-output-file ()) <error>)
($error (with-open-output-file (foo)) <error>)
;;; name ���V���{���łȂ�
($eval (tp-make-tmp-file))
($error (with-open-output-file (#2a((a b) (c d)) *tp-example-file*)) 
	<domain-error>)
($error (with-open-output-file (#\a *tp-example-file*)) <domain-error>)
($error (with-open-output-file (1234 *tp-example-file*)) <domain-error>)
($error (with-open-output-file (1.234 *tp-example-file*)) <domain-error>)
($error (with-open-output-file ("abc" *tp-example-file*)) <domain-error>)
($error (with-open-output-file (#(a b c) *tp-example-file*)) <domain-error>)
($error (with-open-output-file ((x y) *tp-example-file*)) <domain-error>)
;;;------------------------------------------------------------
;;; [special operator]
;;;
;;;  (with-open-io-file (name file [element-class]) form*) --> <object>
;;;------------------------------------------------------------
($ap 2 "with-open-io-file" P.103)
;;;
;;; �����̌�
($error (with-open-io-file) <program-error>)
($error (with-open-io-file . 1) <program-error>)
;;; bind-list ���s��
($error (with-open-io-file 1) <error>)
($error (with-open-io-file ()) <error>)
($error (with-open-io-file (foo)) <error>)
;;; name ���V���{���łȂ�
($eval (tp-make-tmp-file))
($error (with-open-io-file (#2a((a b) (c d)) *tp-example-file*)) 
	<domain-error>)
($error (with-open-io-file (#\a *tp-example-file*)) <domain-error>)
($error (with-open-io-file (1234 *tp-example-file*)) <domain-error>)
($error (with-open-io-file (1.234 *tp-example-file*)) <domain-error>)
($error (with-open-io-file ("abc" *tp-example-file*)) <domain-error>)
($error (with-open-io-file (#(a b c) *tp-example-file*)) <domain-error>)
($error (with-open-io-file ((x y) *tp-example-file*)) <domain-error>)

;;;
($eval (tp-make-tmp-file))
($test (with-open-output-file (outstream *tp-example-file*)
			(format outstream "hello")) nil)
($test (with-open-input-file (instream *tp-example-file*)
		       (read instream)) hello)
($eval (tp-make-tmp-file))
($test (with-open-io-file (iostream *tp-example-file*)
		    (format iostream "hello ")
		    (format iostream "world")
		    (set-file-position iostream 0)
		    (list
		     (read iostream)
		     (read iostream)))
 (hello world) equal)
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (close stream) --> implementation defined
;;;------------------------------------------------------------
($ap 2 "close" P.103)
;;; �����̌�
($argc close 1 0 0)
;;; stream �`�F�b�N
($type close 
       ($file-input-stream 
	$file-output-stream 
	$string-input-stream 
	$string-output-stream) :target)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (create-string-input-stream string) --> <stream>
;;;------------------------------------------------------------
($ap 2 "create-string-input-stream" P.103)
;;;
($test (let ((str (create-string-input-stream "this is a string")))
   (list (read str) (read str) (read str))) (this is a) equal)
;;; �����̌�
($argc create-string-input-stream 1 0 0)
;;; string �`�F�b�N
($type create-string-input-stream ($string) :target)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (create-string-output-stream) --> <stream>
;;;------------------------------------------------------------
($ap 2 "create-string-output-stream" P.103)
;;;
($test (let ((str (create-string-output-stream)))
   (format str "hello")
   (format str "world")
   (get-output-stream-string str)) "helloworld" equal)
;;; �����̌�
($argc create-string-output-stream 0 0 0)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (get-output-stream-string stream) --> <string>
;;;------------------------------------------------------------
($ap 2 "get-output-stream-string" P.103)
;;;
($test (let ((out-str (create-string-output-stream)))
   (format out-str "This is a string")
   (let ((part1 (get-output-stream-string out-str)))
     (format out-str "right!")
     (list part1 (get-output-stream-string out-str))))
 ("This is a string" "right!") equal)
;;; �����̌�
($argc get-output-stream-string 1 0 0)
;;; stream �`�F�b�N
($type get-output-stream-string ($string-output-stream) :target)

(system "rm verify/*.dat")
;;; end of file


