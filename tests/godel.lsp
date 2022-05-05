#|
godel number (test unicode)

|#
(import "math")
(import "cxr")

(defglobal dt "∃xy〜(x)∧(y)")

(defglobal code-list
    '((1 #\〜)
      (2 #\∧)
      (3 #\))
      (4 #\∃)
      (5 #\=)
      (6 #\0)
      (7 #\s)
      (8 #\()
      (9 #\))
      (10 #\")
      (11 #\x)
      (13 #\y)))


(defun rev-assoc (key list)
    (if (equal (cadar list) key)
        (caar list)
        (rev-assoc key (cdr list))))

(defun char->integer (ls)
    (mapcar (lambda (x) (rev-assoc x code-list)) ls))

(defun string->integer (str)
    (char->integer (convert str <list>)))

(defun integer->godel (ls)
    (integer->godel1 ls 1))

(defun integer->godel1 (ls n)
    (if (null ls)
        1
        (* (expt (prime n) (car ls)) (integer->godel1 (cdr ls) (+ n 1)))))

(defun encode (str)
    (integer->godel (string->integer str)))

(defun decode (n)
    (decode1 (factorize n)))

(defun decode1 (ls)
    (if (null ls)
        ""
        (string-append (convert (cadr (assoc (cadar ls) code-list))  <string>)
                       (decode1 (cdr ls)))))
         