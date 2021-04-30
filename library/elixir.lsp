;;;
;;; Elixir like macros
;;; 

;;; pattern match
;;; 
;;; (defpattern foo
;;;      ((+ _a _b) (+ _a 2))
;;;      ((- _a _a) (- _a 3)))
;;; expand defun with macros
;;;(defun foo (x)   
;;;  (let ((_a nil)
;;;        (_b nil))
;;;     (cond ((and (consp x) (eq (car x) '+) (setq _a (car (cdr x))) (setq _b (car (cdr (cdr x)))))
;;;            (+ _a _2))
;;;           ((and (consp x) (eq (car x) '0) (setq _a (car (cdr x))) (equal _a (car (cdr (cdr x)))))
;;;            (- _a 3)))))

(defmacro defpattern (name :rest body)
    (let* ((arg (gensym))
           (vars (extract-variables body nil nil))
           (body1 (expand-body arg body)) )
        `(defun ,name (:rest ,arg) (let ,vars
                                  ,body1))))

(defmacro match (x :rest body)
    (let ((vars (extract-variables body nil nil))
          (body1 (expand-body x body)) )
       `(let ,vars ,body1)))
       
;; anyway return T
(defmacro setq* (var val)
    `(progn (setq ,var ,val) t) )

;;;
;;; macro for Elixir like pipe operator
;;;



;;; functions for macros

(defmodule elixir
    (defpublic expand-body (x body)
        (cons 'cond (expand-body1 x body)) )

    (defun expand-body1 (x body)
        (mapcar (lambda (y) 
                   (cons (expand-match x (car y)) (cdr y))) body) )

    ;; e.g. _a _x  return T
    (defun variablep (x)
        (and (symbolp x) (char= (car (convert (convert x <string>) <list>)) #\_)) )

    ;; (((+ _a 2)...) ((* _b 3)...)) return ((_a nil)(_b nil))
    (defpublic extract-variables (body var ans)
        (cond ((and (null body) (null var)) (reverse ans))
              ((null var) (extract-variables (cdr body) (extract-variable (car (car body))) ans))
              ((not (member (car var) ans))
               (extract-variables body (cdr var) (cons (car var) ans)))
              (t (extract-variables body (cdr var) ans))))

    ;; e.g. (+ _a 2 _b) return ((_a nil)(_b nil))
    (defun extract-variable (x)
        (cond ((null x) nil)
              ((variablep x) (cons (list x nil) nil))
              ((atom x) nil)
              ((consp (car x)) (append (extract-variable (car x)) (extract-variable (cdr x))))
              ((variablep (car x)) (cons (list (car x) nil) (extract-variable (cdr x))))
              (t (extract-variable (cdr x)))))

    ;; e.g. x and (+ _a _b)  ans = (and (eq (car x) '+) (setq _a (car (cdr x)) (setq _b (car (cdr (cdr x))))
    ;; env = (_a _b)
    ;; return (env . ans)
    (defun expand-match (x y)
        (cond ((null y) (list 'null x))
              ((consp y)
               (cons 'and (reverse (cdr (expand-match1 x y nil (cons (list 'consp x) nil))))))
              (t (cons 'and (reverse (cdr (expand-match1 x y nil nil)))))))

    (defun expand-match1 (x y env ans)
        (cond ((null y) (cons env ans))
              ((numberp y) (cons env (cons (list '= x y) ans)))
              ((characterp y) (cons env (cons (list 'char= x y) ans)))
              ((stringp y) (cons env (cons (list 'string= x y) ans)))
              ((general-vector-p y) (cons env (cons (list 'equal x y) ans)))
              ((general-array*-p y) (cons env (cons (list 'equal x y) ans)))
              ((and (variablep y) (not (member y env)))
               (cons (cons y env) (cons (list 'setq* y x) ans)))
              ((and (variablep y) (member y env)) (cons env (cons (list 'equal x y) ans)))
              ((and (symbolp y) (eq y 'else)) (cons env (cons t ans)))
              ((symbolp y) (cons env (cons (list 'eq x (list 'quote y)) ans)))
              ((and (consp y) (eq (car y) ':rest))
               (cons env (cons (list 'setq* (car (cdr y)) x) ans)))
              ((and (consp y) (eq (car y) '&rest))
               (cons env (cons (list 'setq* (car (cdr y)) x) ans)))
              ((and (consp y) (consp (car y)))
               (let ((res
                     (expand-match1
                      (list 'car x)
                      (car y)
                      env
                      (cons (list 'consp (list 'car x)) nil))))
                  (expand-match1 (list 'cdr x) (cdr y) (car res) (append (cdr res) ans))))
              ((consp y)
               (let ((res (expand-match1 (list 'car x) (car y) env ans)))
                  (expand-match1 (list 'cdr x) (cdr y) (car res) (cdr res))))))

    ;;for pipe macro
    (defpublic pipe-macro (pipe1 func)
        (cond ((null pipe1) func)
              ((eq (car pipe1) '|>) (pipe-macro (cdr pipe1) func))
              (t (pipe-macro (cdr pipe1) (pipe-macro1 (car pipe1) func)))))

    (defun pipe-macro1 (fun funcs)
        (cons (car fun) (cons funcs (cdr fun))))

)

;; pipe macro depend on function pipe-macro
;; so, pipe-macro must be defined befor pip macro
(defmacro pipe (:rest expr)
    (pipe-macro (cdr expr) (car expr)) )

