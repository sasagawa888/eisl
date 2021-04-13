;;;
;;; macro for Elixir like pipe operator
;;;

(defun pipe-macro (pipe func)
    (cond ((null pipe) func)
          ((eq (car pipe) '|>) (pipe-macro (cdr pipe) func))
          (t (pipe-macro (cdr pipe) (pipe-macro1 (car pipe) func))) ))

(defun pipe-macro1 (fun funcs)
    (cons (car fun) (cons funcs (cdr fun))) )

(defmacro pipe (:rest expr)
    (pipe-macro (cdr expr) (car expr)) )
