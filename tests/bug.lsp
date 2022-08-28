(with-open-io-file
 (io "ests/test.txt")
  (while (read-line io nil)) ; read fails
  (format io "line~%") ; write fails
 (format (standard-output) "~A~%" (file-position io)))