;;; -*- lisp -*-
;;;
;;; Chapter 20: Files
;;;

($ap 1 "Files")

;;;------------------------------------------------------------
;;; [function] 
;;;
;;;  (probe-file filename) --> boolean
;;;------------------------------------------------------------
($ap 2 "probe-file" P.111)
;;;
((probe-file "/tmp/notexist.lsp") nil equal)
;;;
($eval (tp-make-tmp-file))
($eval 
 (defglobal new-file (open-output-file *tp-example-file*)))
($eval
 (close new-file))
((probe-file *tp-example-file*) t)
;;;
($argc probe-file 1 0 0)
($type probe-file ($string) :target)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (file-position stream) --> <integer>
;;;------------------------------------------------------------
($ap 2 "file-position" P.111)
;;; byte-stream
($eval (tp-make-tmp-file))
($eval (defglobal example (open-output-file *tp-example-file* 8)))
((write-byte 104 example) 104 eql)
((file-position example) 1 eql)
((write-byte 101 example) 101 eql)
((file-position example) 2 eql)
((write-byte 108 example) 108 eql)
((file-position example) 3 eql)
((write-byte 108 example) 108 eql)
((file-position example) 4 eql)
((write-byte 111 example) 111 eql)
((file-position example) 5 eql)
($eval (close example))
($eval (defglobal example (open-input-file *tp-example-file* 8)))
((file-position example) 0 eql)
((read-byte example) 104 eql)
((file-position example) 1 eql)
($eval (close example))
;;; char-stream
($eval (tp-make-tmp-file))
($eval (defglobal example (open-output-file *tp-example-file*)))
($eval (format example "hello"))
((file-position example) 5 eql)
($eval (close example))
($eval (defglobal example (open-input-file *tp-example-file*)))
((file-position example) 0 eql)
((read-char example) #\h equal)
((file-position example) 1 eql)
($eval (close example))
;;;
($argc file-position 1 0 0)
;;;
($type file-position ($file-input-stream $file-output-stream) :target)

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (set-file-position stream z) --> <integer>
;;;------------------------------------------------------------
($ap 2 "set-file-position" P.112)
;;;
($eval (tp-make-tmp-file))
($eval (defglobal example (open-output-file *tp-example-file*)))
($eval (format example "hello"))
($eval (close example))
($eval (setq example (open-input-file *tp-example-file* 8)))
((set-file-position example 4) 4 eql)
((file-position example) 4 eql)
((read-byte example) 111 eql)
((set-file-position example 0) 0 eql)
((file-position example) 0 eql)
((read-byte example) 104 eql)
($eval (close example))
;;;
($argc set-file-position 2 0 0)
;;;
($type set-file-position ($file-input-stream $file-output-stream) :target 0)
;;;
($eval (tp-make-tmp-file))
($eval (defglobal example (open-output-file *tp-example-file*)))
($error (set-file-position example -1) <domain-error>)
($error (set-file-position example #x100000000) <error>)
($eval (close example))

;;;------------------------------------------------------------
;;; [function]
;;;
;;;  (file-length filename element-class) --> <integer>
;;;------------------------------------------------------------
($ap 2 "file-length" P.113)
;;;
($eval (tp-make-tmp-file))
($eval (defglobal example (open-output-file *tp-example-file*)))
($eval (format example "hello"))
($eval (close example))
($eval (setq example (open-input-file *tp-example-file* 8)))
((file-length *tp-example-file* 8) 5 eql)
($eval (close example))
;;;
($argc file-length 2 0 0)
($type file-length ($string) :target 8)
;;; element-class 8
($eval (tp-make-tmp-file))
($eval (defglobal example (open-output-file *tp-example-file*)))
($error (file-length *tp-example-file* 7) <error>)
($error (file-length *tp-example-file* 9) <error>)
($eval (close example))

;;; end of file