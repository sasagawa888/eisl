
(defun gets (prompt)
  (format (standard-output) prompt)
  (with-open-input-file in "/dev/stdin")
    (read-line in nil))
#|
(defun gets (prompt)
  (format (standard-output) prompt)
  (read-line (standard-input) nil))
|#
(format (standard-output) "Word: ~A~%" (gets "> "))
(format (standard-output) "Word: ~A~%" (gets "> "))
(format (standard-output) "Word: ~A~%" (gets "> "))