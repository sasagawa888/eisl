;;; structure editor

(defglobal stack '())
(defglobal current '())

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
    (for ((com (read) (read)))
         ((eq com 'q) t)
         (cond ((eq com 'p) (prints current)))))

(defun prints (x)
    (format (standard-output) "(")
    (prints1 x))

(defun prints1 (x)
    (cond ((null x) (format (standard-output) ")~%"))
          ((atom (car x)) (format (standard-output) " ~A " (car x)) (prints1 (cdr x)))
          (t (format (standard-output) " ## ") (prints1 (cdr x)))))
