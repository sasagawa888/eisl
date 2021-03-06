(defun f (str)
   (let ((substr (subseq str 0 3)))
        (format (standard-output) "~A~%" substr)))

(defun g (str)
  (let ((substr str))
        (format (standard-output) "~A~%" str)))


(defun h (str)
   (let ((substr str))
        (format (standard-output) "~A~%")))