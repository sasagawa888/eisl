
(defun foo ()
   "asdf")

(defun bar (y)
    (string-append (foo) "asdf"))

(defun test1 (x)
  (length x)
  (string-append x "asdf"))

(defun test2 (y)
  (+ y 1)
  (string-append y "asdf"))