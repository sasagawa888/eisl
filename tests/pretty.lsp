;;
;; prity printer

(defglobal lp 0) ;;left-position

(defun pp (x)
    (pp1 x (standard-output) 0))

(defun pp1 (x stream lm)
    (cond ((consp x)
           (cond ((eq (car x) 'cond) (pp-cond x stream lm))
                 ((eq (car x) 'defun) (pp-defun x stream lm))
                 (t (space lm stream) (format stream "~S" x))))
          ((numberp x) (space lm stream) (format-object stream x t))))


(defun pp-write (x stream)
    (setq lp (+ lp (length x)))
    (format stream x))


(defun pp-cond (x stream lm)
    (space lm stream)
    (pp-write "(cond (" stream)
    (pp-body (cdr x) stream (+ lm 7))
    (format stream ")"))

(defun pp-body (x stream lm)
    (for ((s x (cdr s))
          (n (length x) (- n 1)))
         ((null s) t)
         (pp1 (car s) stream lm)
         (if (> n 1)
            (newline stream))))


(defun space (n stream)
    (for ((m (- n lp) (- m 1)))
         ((<= m 0) t)
         (format stream " ")))

(defun newline (stream)
    (setq lp 0)
    (format stream "~%"))





           