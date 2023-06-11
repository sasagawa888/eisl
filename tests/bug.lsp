;;; compiler test with M.hiroi example
(import "macro")
(import "seq")

(defun kakko-p (s)
    (let ((l 0)
          (r 0) )
       (dolist (x (string->list s) (= l r))
          (case x
             ((#\() (incf l))
             ((#\)) (incf r) (when (< l r) (return nil)))
             (t (error "illegal character")) ))))
