;;; structure editor

(defglobal stack '())
(defglobal current '())
(defglobal index nil)

(defun push (x)
    (setq stack (cons x stack)))

(defun pop ()
    (let ((x (car stack)))
        (setq stack (cdr stack))
        x))

(defun editf (x)
    (setq current (eisl-get-myself x))
    (edits))

(defun edits ()
    (for ((com (reads) (reads)))
         ((eq com 'q) t)
         (cond ((eq com 'p) (prints current))
               ((eq com 'i) (insert (read) current index))
               ((integerp com) (setq index com)))))


(defun reads ()
    (format (standard-output) "* ")
    (read))

(defun prints (x)
    (format (standard-output) "(")
    (prints1 x))

(defun prints1 (x)
    (cond ((null x) (format (standard-output) ")~%"))
          ((atom (car x)) (format (standard-output) " ~A " (car x)) (prints1 (cdr x)))
          (t (format (standard-output) " ## ") (prints1 (cdr x)))))

;; insert x nth y
(defun insert (x y n)
    (if (= n 1)
        (set-cdr (cons x (cdr y)) y)
        (insert x (cdr y) (- n 1))))
        