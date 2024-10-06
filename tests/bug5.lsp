
(import "test")

($assert (streamp (create-string-input-stream "foo")) t)
($assert (streamp (create-string-output-stream)) t)
($assert (streamp 123) nil)

($assert (input-stream-p (create-string-input-stream "foo")) t)
($assert (input-stream-p (create-string-output-stream)) nil)
($assert (input-stream-p 123) nil)

($assert (output-stream-p (create-string-input-stream "foo")) nil)
($assert (output-stream-p (create-string-output-stream)) t)
($assert (output-stream-p 123) nil)

($assert (output-stream-p (standard-output)) t)
($assert (output-stream-p (error-output)) t)
($assert (input-stream-p (standard-input)) t)

(let ((stream (create-string-input-stream "a")))
  ($assert (read-char stream) #\a)
  ($assert (read-char stream nil) nil))

(let ((stream (create-string-input-stream "a")))
  ($assert (read-char stream) #\a)
  ($assert (read-char stream nil 'foo) 'foo))

(let ((stream (create-string-input-stream "a")))
  ($assert (read-char stream) #\a)
  (block exit
    (with-handler
      (lambda (err)
        ($assert (instancep err (class <end-of-stream>)) t)
        (return-from exit nil))
      (read-char stream t)
      ($assert nil t)))) ;; shouldn't get here

(let ((stream (create-string-input-stream "a")))
  ($assert (preview-char stream) #\a)
  ($assert (preview-char stream) #\a)
  (read-char stream)
  ($assert (preview-char stream nil) nil))


(let ((out (create-string-output-stream)))
  (format out "abc~%de")
  (finish-output out) 
  (let ((stream (create-string-input-stream (get-output-stream-string out))))
      ($assert (read-line stream) "abc")
      ($assert (read-line stream) "de")
      ($assert (read-line stream nil) nil)))

(let ((stream (create-string-input-stream "hello #(1 2 3) 123 #\\A")))
  ($assert (read stream) 'hello)
  ($assert (read stream) #(1 2 3))
  ($assert (read stream) 123)
  ($assert (read stream) #\A)
  ($assert (read stream nil "the end") "the end"))
