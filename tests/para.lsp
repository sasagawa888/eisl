;;multi-process

;(mp-create 3)

(import "unistd")

(defun foo (x y)
    (mp-part (bar x) (boo y)))

(defun bar (x)
    (sleep 10)
    (if (= x 1) t nil))

(defun boo (x)
    (sleep 1)
    (if (= x 1) t nil))


