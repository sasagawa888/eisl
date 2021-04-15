;;; csv-test
(import "csv")

(defun test ()
    (test1)
    (test2))
    
(defun test1 ()
    (let ((instream (open-input-file "tests/test.csv")))
        (format (standard-output) "~S~%" (read-csv instream))
        (close instream)))


(defun test2 ()
    (let ((instream (open-input-file "tests/test.csv")))
        (format (standard-output) "~S~%" (parse-csv instream))
        (close instream)))

