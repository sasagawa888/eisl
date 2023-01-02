(import "test")

(defconstant *tp-tmp-dir* "/tmp/")

(defglobal *tp-file-no* 0)
(defglobal *tp-example-file* nil)

(defun tp-make-tmp-file ()
  (setq *tp-example-file* 
	(string-append 
	 *tp-tmp-dir* 
	 "islsp" 
	 (convert (setq *tp-file-no* (+ *tp-file-no* 1)) <string>))))
(defconstant *tp-tmp-input-file* (tp-make-tmp-file))
(defconstant *tp-tmp-output-file* (tp-make-tmp-file))
(defconstant *tp-tmp-error-file* (tp-make-tmp-file))

;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (write-byte 100 byte-stream)
		    (read byte-stream)) <domain-error>)
;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (write-byte 100 byte-stream)
		    (read-char byte-stream)) <domain-error>)

;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (write-byte 100 byte-stream)
		    (preview-char byte-stream)) <domain-error>)
($eval (tp-make-tmp-file))
($test (with-open-output-file (out *tp-example-file*)
			(format out "This is an example")
			(format out "~%")
			(format out "look at the output file"))
 nil)
($eval
 (defglobal str (open-input-file *tp-example-file*)))
($test (read-line str) "This is an example" equal)
($test (read-line str) "look at the output file" equal)
($error (read-line str) <end-of-stream>)
($error (read-line str t) <end-of-stream>)
($test (read-line str nil) nil)
($test (read-line str nil "the end") "the end" equal)
($eval (close str))
;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (write-byte 100 byte-stream)
		    (read-line byte-stream)) <domain-error>)

($eval (tp-make-tmp-file))
($test (with-open-output-file (out *tp-example-file*)
			(format out "This is an example"))
 nil)
($test (with-open-input-file (in *tp-example-file*)
		       (stream-ready-p in))
 t)
;;; closed stream �̓G���[
($eval (defglobal in-stream (open-io-file *tp-example-file*)))
($eval (close in-stream))
($error (stream-ready-p in-stream) <stream-error>)

;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (write-byte 100 byte-stream)
		    (stream-ready-p byte-stream)) <domain-error>)
;;;
;;; byte-stream

($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-char byte-stream #\a)) <domain-error>)
;;;
($argc format-char 2 0 0)
($type format-char ($file-output-stream $string-output-stream) :target #\a)
($type format-char ($character) (create-string-output-stream) :target)
;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-float byte-stream 1.234)) <domain-error>)
;;;
($argc format-float 2 0 0)
($type format-float ($file-output-stream $string-output-stream) :target 1.234)
($type format-float ($integer $float) (create-string-output-stream) :target)

;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-fresh-line byte-stream)) <domain-error>)
;;;
($argc format-fresh-line 1 0 0)
($type format-fresh-line ($file-output-stream $string-output-stream) :target)

;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-integer byte-stream 1 10)) <domain-error>)
;;;
($argc format-integer 3 0 0)
($type format-integer ($file-output-stream $string-output-stream) 
       :target 10 10)
($type format-integer ($integer) (create-string-output-stream) 
       :target 10)

;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-object byte-stream 1 t)) <domain-error>)
;;;
($argc format-object 3 0 0)
($type format-object ($file-output-stream $string-output-stream) 
       :target nil nil)

;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-tab byte-stream 1)) <domain-error>)
;;;
($eval (tp-make-tmp-file))
($eval 
 (defglobal byte-example (open-output-file *tp-example-file*)))
($test (format byte-example "hello") nil)
($eval (close byte-example))
($eval (setq byte-example (open-input-file *tp-example-file* 8)))
($test (read-byte byte-example) 104 eql)
($test (read-byte byte-example) 101 eql)
($test (read-byte byte-example) 108 eql)
($test (read-byte byte-example) 108 eql)
($test (read-byte byte-example) 111 eql)
($error (read-byte byte-example) <end-of-stream>)
($error (read-byte byte-example t) <end-of-stream>)
($test (read-byte byte-example nil) nil)
($test (read-byte byte-example nil "the end") "the end" equal)
($eval (close byte-example))
;;; character-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (char-stream *tp-example-file*)
		    (format char-stream "foo")
		    (read-byte char-stream)) <domain-error>)
;;;
($argc read-byte 1 2 0)
;;;
($type read-byte ($file-input-stream $string-input-stream) :target)

($ap 2 "write-byte" P.111)
;;;
($eval (tp-make-tmp-file))
($eval
 (let ((out-str (open-output-file *tp-example-file* 8)))
   (write-byte #b101 out-str)
   (close out-str)))
($eval 
 (defglobal in-str (open-input-file *tp-example-file* 8)))
($test (read-byte in-str) 5 equal)
($eval (close in-str))
;;; character-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (char-stream *tp-example-file*)
		    (write-byte 100 char-stream)) <domain-error>)
;;;
($argc write-byte 2 0 0)
;;;
($type write-byte ($file-output-stream $string-output-stream) 5 :target)
;;; 0 <= z <= 255
($eval (tp-make-tmp-file))
($eval (defglobal byte-outstream (open-output-file *tp-example-file* 8)))
($error (write-byte -1 byte-outstream) <error>)
($test (write-byte 0 byte-outstream) 0 eql)
($test (write-byte 255 byte-outstream) 255 eql)
($error (write-byte 256 byte-outstream) <error>)
($eval (close byte-outstream))
