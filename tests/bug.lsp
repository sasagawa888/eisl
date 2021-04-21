
(defmacro defpattern (name :rest body)
    (let* ((arg (gensym))
           (vars (extract-variables body nil nil))
           (body1 (expand-body arg body)))
        `(defun ,name (,arg) 
            (lett ,vars ,body1))))
