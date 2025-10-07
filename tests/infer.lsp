;; type inferencer test cases
(defun foo ()
   1)

(defun bar (y)
    (string-append (foo) "asdf"))

(defun test1 (x)
  (length x)
  (append x "asdf"))

(defun test2 (y)
  (let ((z (+ y 1)))
    (append z "asdf")))

(defun test3 (x)
    (length x))

(defun baz ()
    (c-lang "res = Fmakeint(2);")
    (c-return <fixnum>))

(defun uoo (x)
    (append x (baz)))


(defun tarai (x y z)
    (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
          (tarai (tarai (- x 1) y z)
                 (tarai (- y 1) z x)
                 (tarai (- z 1) x y))))
