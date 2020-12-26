
;; read S-expression. each atom is represented as string
(defun sexp-read ()
  (let ((token (get-token)))
    (cond ((and (characterp token)(char= token #\()))
           (sexp-read-list))
          (t token))))
