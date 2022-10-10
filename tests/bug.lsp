(defun foo (x)
   (catch 'exit
      (with-handler 
          (lambda (c) (throw 'exit c))
                 (bar x))))


(defun bar (x)
    (car x))


(defun uoo (x)
    (eval x))
