
(defun foo ()
   1)

(defun bar (y)
    (string-append (foo) "asdf"))

(defun test1 (x)
  ;(length x)
  (string-append x "asdf"))

(defun test2 (y)
  (+ y 1)
  (string-append y "asdf"))

(defun test3 (x)
    (length x))

(defun baz ()
    (c-lang "res = Fmakeint(2);")
    (c-return <fixnum>))

(defun uoo (x)
    (+ x (baz)))