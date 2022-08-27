(defun foo ()
(with-open-io-file
 (io "tests/test.txt")
  (while (read-line io nil)) ; read fails
  (format io "line~%") ; write fails
 (format (standard-output) "~A~%" (file-position io))))