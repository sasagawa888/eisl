(defun foo ()
    (let ((x ()))
       (tagbody (setq x (cons 1 x))
                a
                (setq x (cons 2 x))
               (setq x (cons 3 x)))
       x ))

