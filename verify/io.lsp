(import "test")
;;; -*- lisp -*-
;;;
;;; Chapter 19: Input and Output
;;;

($ap 1 "Input and Output")

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (read [input-stream [eos-error-p] [eos-value]]]) --> <object>
;;;------------------------------------------------------------
($ap 2 "read" P.106)
;;;
($eval 
 (defglobal str (create-string-input-stream "hello #(1 2 3) 123 #\\A")))
(test (read str) hello)
(test (read str) #(1 2 3) equal)
(test (read str) 123 eql)
(test (read str) #\A equal)
(test (read str nil "the end") "the end" equal)
(test (read str nil) nil)
($error (read str t) <end-of-stream>)
($error (read str 1) <end-of-stream>)
($error (read str) <end-of-stream>)
;;; byte-stream
#|
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (write-byte 100 byte-stream)
		    (read byte-stream)) <domain-error>)
|#
;;;
($argc read 0 3 0)
;;;
($type read ($file-input-stream $string-input-stream) :target nil nil)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (read-char [input-stream [eos-error-p] [eos-value]]]) --> <object>
;;;------------------------------------------------------------
($ap 2 "read-char" P.106)
;;;
($eval 
 (defglobal str (create-string-input-stream "hi")))
(test (read-char str) #\h equal)
(test (read-char str) #\i equal)
;; following two case segmentation error
($error (read-char str) <end-of-stream>)
($error (read-char str t) <end-of-stream>)
(test (read-char str nil) nil)
(test (read-char str nil "the end") "the end" equal)
;;; #\space
($eval 
 (defglobal str (create-string-input-stream "hi c")))
(test (read-char str) #\h equal)
(test (read-char str) #\i equal)
(test (read-char str) #\space equal)
(test (read-char str) #\c equal)
(test (read-char str nil "the end") "the end" equal)
;;; #\newline
($eval 
 (defglobal str (create-string-input-stream "hi
c")))
(test (read-char str) #\h equal)
(test (read-char str) #\i equal)
(test (read-char str) #\newline equal)
(test (read-char str) #\c equal)
(test (read-char str nil "the end") "the end" equal)

#|
;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (write-byte 100 byte-stream)
		    (read-char byte-stream)) <domain-error>)
|#
;;;
($argc read-char 0 3 0)
;;;
($type read-char ($file-input-stream $string-input-stream) :target nil nil)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (preview-char [input-stream [eos-error-p] [eos-value]]]) --> <object>
;;;------------------------------------------------------------
($ap 2 "preview-char" P.107)
;;;
($eval (defglobal str (create-string-input-stream "123")))
(test (preview-char str) #\1 equal)
(test (read-char str) #\1 equal)
(test (preview-char str) #\2 equal)
(test (read-char str) #\2 equal)
(test (preview-char str) #\3 equal)
(test (read-char str) #\3 equal)
($error (preview-char str) <end-of-stream>)
($error (preview-char str t) <end-of-stream>)
(test (preview-char str nil) nil)
(test (preview-char str nil "the end") "the end" equal)
;;;
(test (let ((s (create-string-input-stream "foo")))
   (list (preview-char s) (read-char s) (read-char s)))
 (#\f #\f #\o) equal)

#|
;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (write-byte 100 byte-stream)
		    (preview-char byte-stream)) <domain-error>)
|#
;;;
($argc preview-char 0 3 0)
;;;
($type preview-char ($file-input-stream $string-input-stream) :target nil nil)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (read-line [input-stream [eos-error-p] [eos-value]]]) --> <object>
;;;------------------------------------------------------------
($ap 2 "read-line" P.107)
;;;
#|
($eval (tp-make-tmp-file))
(test (with-open-output-file (out *tp-example-file*)
			(format out "This is an example")
			(format out "~%")
			(format out "look at the output file"))
 nil)
($eval
 (defglobal str (open-input-file *tp-example-file*)))
(test (read-line str) "This is an example" equal)
(test (read-line str) "look at the output file" equal)
($error (read-line str) <end-of-stream>)
($error (read-line str t) <end-of-stream>)
(test (read-line str nil) nil)
(test (read-line str nil "the end") "the end" equal)
($eval (close str))
;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (write-byte 100 byte-stream)
		    (read-line byte-stream)) <domain-error>)
|#
;;;
($argc read-line 0 3 0)
;;;
($type read-line ($file-input-stream $string-input-stream) :target nil nil)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (stream-ready-p input-stream) --> boolean
;;;------------------------------------------------------------
($ap 2 "stream-ready-p" P.107)
;;;
#|
($eval (tp-make-tmp-file))
(test (with-open-output-file (out *tp-example-file*)
			(format out "This is an example"))
 nil)
(test (with-open-input-file (in *tp-example-file*)
		       (stream-ready-p in))
 t)
;;; closed stream �̓G���[
($eval (defglobal in-stream (open-io-file *tp-example-file*)))
($eval (close in-stream))
($error (stream-ready-p in-stream) <stream-error>)
|#
;;; string stream
(test (let ((s (create-string-input-stream "foo")))
   (stream-ready-p s)) t)

($eval (defglobal s (create-string-input-stream "12")))
(test (stream-ready-p s) t)
(test (read-char s) #\1 equal)
(test (stream-ready-p s) t)
(test (read-char s) #\2 equal)
(test (stream-ready-p s) nil)

#|
;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (write-byte 100 byte-stream)
		    (stream-ready-p byte-stream)) <domain-error>)
;;;
|#
($argc stream-ready-p 1 0 0)
;;;
($type stream-ready-p ($file-input-stream $string-input-stream) :target)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (format output-stream format-string obj*) --> <null>
;;;------------------------------------------------------------
($ap 2 "format" P.108)
;;;
(test (let ((s (create-string-output-stream)))
   (format s "No result")
   (get-output-stream-string s))
 "No result" equal)
(test (let ((s (create-string-output-stream)))
   (format s "The result is ~A and nothing else." "meningtis")
   (get-output-stream-string s))
 "The result is meningtis and nothing else." equal)
(test (let ((s (create-string-output-stream)))
   (format s "The result i~C" #\s)
   (get-output-stream-string s))
 "The result is" equal)
(test (let ((s (create-string-output-stream)))
   (format s "The results are ~S and ~S." 1 #\a)
   (get-output-stream-string s))
 "The results are 1 and #\\a." equal)
(test (let ((s (create-string-output-stream)))
   (format s "Binary code ~B" 150)
   (get-output-stream-string s))
 "Binary code 10010110" equal)
(test (let ((s (create-string-output-stream)))
   (format s "permission ~O" 493)
   (get-output-stream-string s))
 "permission 755" equal)
(test (let ((s (create-string-output-stream)))
   (format s "You ~X ~X" 2989 64206)
   (get-output-stream-string s))
 "You BAD FACE" equal)
(test (let ((s (create-string-output-stream)))
   (format s "~&Name ~10Tincome ~20Ttax~&")
   (format s "~A ~10T~D ~20T~D" "Grummy" 23000 7500)
   (get-output-stream-string s))
 "Name      income    tax
Grummy    23000     7500" equal)
(test (let ((s (create-string-output-stream)))
   (format s "This will be split into~%two lines.")
   (get-output-stream-string s))
 "This will be split into
two lines." equal)
#|
;;; byte-stream
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format byte-stream "")) <domain-error>)
|#
;;; directive A
($error (let ((s (create-string-output-stream)))
   (format s "~A")
   (get-output-stream-string s)) <error>)
;;; directive B
($error (let ((s (create-string-output-stream)))
   (format s "~B")
   (get-output-stream-string s)) <error>)
;;;
($type format ($integer) (create-string-output-stream) "~B" :target)
;;; directive C
($error (let ((s (create-string-output-stream)))
   (format s "~C")
   (get-output-stream-string s)) <error>)
;;;
($type format ($character) (create-string-output-stream) "~C" :target)
;;; directive D
($error (let ((s (create-string-output-stream)))
   (format s "~D")
   (get-output-stream-string s)) <error>)
;;;
($type format ($integer) (create-string-output-stream) "~D" :target)
;;; directive G
($error (let ((s (create-string-output-stream)))
   (format s "~G")
   (get-output-stream-string s)) <error>)
;;;
($type format ($integer $float) (create-string-output-stream) "~G" :target)
;;; directive O
($error (let ((s (create-string-output-stream)))
   (format s "~O")
   (get-output-stream-string s)) <error>)
;;;
($type format ($integer) (create-string-output-stream) "~O" :target)
;;; directive R
($error (let ((s (create-string-output-stream)))
   (format s "~10R")
   (get-output-stream-string s)) <error>)
;;;
($error (let ((s (create-string-output-stream)))
   (format s "~1R" 1)
   (get-output-stream-string s)) <error>)
($error (let ((s (create-string-output-stream)))
   (format s "~37R" 1)
   (get-output-stream-string s)) <error>)
;;;
($type format ($integer) (create-string-output-stream) "~2R" :target)
;;; directive S
($error (let ((s (create-string-output-stream)))
   (format s "~S")
   (get-output-stream-string s)) <error>)
;;; directive X
($error (let ((s (create-string-output-stream)))
   (format s "~X")
   (get-output-stream-string s)) <error>)
;;;
($type format ($integer) (create-string-output-stream) "~X" :target)
;;; directive ~%
(test (let ((s (create-string-output-stream)))
   (format s "1st~%2nd" 1 #\a)
   (get-output-stream-string s))
 "1st
2nd" equal)
;;; directive ~&
(test (let ((s (create-string-output-stream)))
   (format s "1st~&2nd" 1 #\a)
   (get-output-stream-string s))
 "1st
2nd" equal)
;;; directive ~
(test (let ((s (create-string-output-stream)))
   (format s "~~" 1 #\a)
   (get-output-stream-string s))
 "~" equal)

;;;
($argc format 2 0 1)
;;;
($type format ($file-output-stream $string-output-stream) :target "")
($type format ($string) (create-string-output-stream) :target)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (format-char output-stream char) --> <null>
;;;------------------------------------------------------------
($ap 2 "format-char" P.110)
;;;
(test (let ((s (create-string-output-stream)))
   (format-char s #\a)
   (get-output-stream-string s))
 "a" equal)
;;; byte-stream
#|
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-char byte-stream #\a)) <domain-error>)
;;;
($argc format-char 2 0 0)
($type format-char ($file-output-stream $string-output-stream) :target #\a)
($type format-char ($character) (create-string-output-stream) :target)
|#
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (format-float output-stream float) --> <null>
;;;------------------------------------------------------------
($ap 2 "format-float" P.110)
;;;
(test (let ((s (create-string-output-stream)))
   (format-float s 1)
   (get-output-stream-string s))
 "1.0" equal)
(test (let ((s (create-string-output-stream)))
   (format-float s 1.234)
   (get-output-stream-string s))
 "1.234" equal)
;;; byte-stream
#|
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-float byte-stream 1.234)) <domain-error>)
;;;
($argc format-float 2 0 0)
($type format-float ($file-output-stream $string-output-stream) :target 1.234)
($type format-float ($integer $float) (create-string-output-stream) :target)
|#
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (format-fresh-line output-stream) --> <null>
;;;------------------------------------------------------------
($ap 2 "format-float" P.110)
;;;
(test (let ((s (create-string-output-stream)))
   (format-fresh-line s)
   (format-object s 123 nil)
   (get-output-stream-string s))
 "123" equal)
(test (let ((s (create-string-output-stream)))
   (format-fresh-line s)
   (format-object s 123 nil)
   (format-fresh-line s)
   (format-object s 456 nil)
   (get-output-stream-string s))
 "123
456" equal)
;;; byte-stream
#|
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-fresh-line byte-stream)) <domain-error>)
;;;
($argc format-fresh-line 1 0 0)
($type format-fresh-line ($file-output-stream $string-output-stream) :target)
|#
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (format-integer output-stream integer radix) --> <null>
;;;------------------------------------------------------------
($ap 2 "format-integer" P.110)
;;;
(test (let ((s (create-string-output-stream)))
   (format-integer s 1 10)
   (get-output-stream-string s))
 "1" equal)
(test (let ((s (create-string-output-stream)))
   (format-integer s 10 2)
   (get-output-stream-string s))
 "1010" equal)
(test (let ((s (create-string-output-stream)))
   (format-integer s 10 8)
   (get-output-stream-string s))
 "12" equal)
(test (let ((s (create-string-output-stream)))
   (format-integer s 10 16)
   (get-output-stream-string s))
 "A" equal)
(test (let ((s (create-string-output-stream)))
   (format-integer s 35 36)
   (get-output-stream-string s))
 "Z" equal)
;;; byte-stream
#|
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
|#
;;; radix 
($error 
 (let ((s (create-string-output-stream)))
   (format-integer s 35 1)
   (get-output-stream-string s)) <error>)
($error 
 (let ((s (create-string-output-stream)))
   (format-integer s 35 37)
   (get-output-stream-string s)) <error>)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (format-object output-stream obj escape-p) --> <null>
;;;------------------------------------------------------------
($ap 2 "format-object" P.110)
;;; <string>
(test (let ((s (create-string-output-stream)))
   (format-object s "string" t)
   (get-output-stream-string s))
 "\"string\"" equal)
(test (let ((s (create-string-output-stream)))
   (format-object s "string" nil)
   (get-output-stream-string s))
 "string" equal)
;;; <character>
(test (let ((s (create-string-output-stream)))
   (format-object s #\a t)
   (get-output-stream-string s))
 "#\\a" equal)
(test (let ((s (create-string-output-stream)))
   (format-object s #\a nil)
   (get-output-stream-string s))
 "a" equal)
;;; byte-stream
#|
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-object byte-stream 1 t)) <domain-error>)
;;;
($argc format-object 3 0 0)
($type format-object ($file-output-stream $string-output-stream) 
       :target nil nil)
|#
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (format-tab output-stream column) --> <null>
;;;------------------------------------------------------------
($ap 2 "format-tab" P.110)
;;;
(test (let ((s (create-string-output-stream)))
   (format-tab s 10)
   (format-object s 10 nil)
   (get-output-stream-string s))
 "          10" equal)
(test (let ((s (create-string-output-stream)))
   (format-tab s 10)
   (format-object s 10 nil)
   (format-fresh-line s)
   (format-tab s 10)
   (format-object s 20 nil)
   (get-output-stream-string s))
 "          10
          20" equal)
;;;
(test (let ((s (create-string-output-stream)))
   (format-object s 10000 nil)
   (format-tab s 3)
   (get-output-stream-string s))
 "10000 " equal)
;;; byte-stream
#|
($eval (tp-make-tmp-file))
($error 
 (with-open-io-file (byte-stream *tp-example-file* 8)
		    (format-tab byte-stream 1)) <domain-error>)
;;;
|#
($argc format-tab 2 0 0)
($type format-tab ($file-output-stream $string-output-stream) :target nil)
($type format-tab ($integer) (create-string-output-stream) :target)
;;; column 
($error (format-tab (create-string-output-stream) -1) <error>)
($error (format-tab (create-string-output-stream) #x100000000) 
	<error>)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;   (read-byte input-stream [eos-error-p [eos-value]]) --> <integer>
;;;------------------------------------------------------------
($ap 2 "read-byte" P.110)
;;;
#|
($eval (tp-make-tmp-file))
($eval 
 (defglobal byte-example (open-output-file *tp-example-file*)))
(test (format byte-example "hello") nil)
($eval (close byte-example))
($eval (setq byte-example (open-input-file *tp-example-file* 8)))
(test (read-byte byte-example) 104 eql)
(test (read-byte byte-example) 101 eql)
(test (read-byte byte-example) 108 eql)
(test (read-byte byte-example) 108 eql)
(test (read-byte byte-example) 111 eql)
($error (read-byte byte-example) <end-of-stream>)
($error (read-byte byte-example t) <end-of-stream>)
(test (read-byte byte-example nil) nil)
(test (read-byte byte-example nil "the end") "the end" equal)
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
|#
;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (write-byte z output-stream) --> <integer>
;;;------------------------------------------------------------
($ap 2 "write-byte" P.111)
;;;
#|
($eval (tp-make-tmp-file))
($eval
 (let ((out-str (open-output-file *tp-example-file* 8)))
   (write-byte #b101 out-str)
   (close out-str)))
($eval 
 (defglobal in-str (open-input-file *tp-example-file* 8)))
(test (read-byte in-str) 5 equal)
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
(test (write-byte 0 byte-outstream) 0 eql)
(test (write-byte 255 byte-outstream) 255 eql)
($error (write-byte 256 byte-outstream) <error>)
($eval (close byte-outstream))
|#
;;; end of file