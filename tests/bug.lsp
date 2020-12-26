
(defun whitespacep (c) (or (char= c #\space) (char= c #\newline)))
(defun digitp (c) (and (char>= c #\0) (char<= c #\9)))
(defun specialp (c) (member c '(#\+ #\- #\* #\/ #\( #\))))

(defun list-to-string (chars)
  (let ((string (create-string (length chars)))
        (i 0))
    (while chars
      (setf (aref string i) (car chars))
      (setq i (+ i 1))
      (setq chars (cdr chars)))
    string))
