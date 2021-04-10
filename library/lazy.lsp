;;; Lazy 
;;; written by M.Hiroi
;;; originaly written by R. Kent Dybvig in Scheme

(defmacro delay (expr)
  `(make-promise (lambda () ,expr)))

(defun make-promise (f)
  (let ((flag nil) (result nil))
    (lambda ()
      (if (not flag)
        (let ((x (funcall f)))
          (cond ((not flag)
                 (setq flag t)
                 (setq result x)))))
      result)))

(defun force (promise)
  (funcall promise))


(defmacro stream-cons (a b)
  `(cons ,a (delay ,b)))


(defun stream-car (s) (car s))


(defun stream-cdr (s) (force (cdr s)))

