
(defun whitespacep (c) (or (char= c #\space) (char= c #\newline)))
(defun digitp (c) (and (char>= c #\0) (char<= c #\9)))
(defun specialp (c) (member c '(#\+ #\- #\* #\/ #\( #\))))

