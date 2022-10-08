#|
Prolog interpreter

data type
variable (% sym num) to avoid lack of memory

data base   symbol (set-property '((foo a)) 'prolog 'foo)  predicate
                   (set-property '(((foo _x)(bar _x))) 'prolog 'foo)  clause

variable _name e.g. _x _y _z
anoymous _
variant (% sym n) e.g. ($ _x 1)

builtin predicate (set-property (lambda (x) ...) 'builtin 'bar)

environment ((var0 . val0)(var0 . val0))


|#


(defun setup ()
    (set-property (lambda (x) (assert x)) 'builtin 'assert))

(defun predicatep (x)
    (and (listp x) (symbolp (car x))))

(defun clausep (x)
    (and (listp x) (listp (car x))))

(defun builtinp (x)
    (fnctionp (property x 'builtin)))

(defun variablep (x)
    (string= (elt (convert x <string>) 0) "_"))

(defun anoymousp (x)
    (eq x '_))

(defun variantp (x)
    (and (listp x) (eq (car x) '%)))

(defun deref (x env)
    (cond ((numberp x) x)
          ((variable x) (deref1 x))
          ((listp x (cons (deref (car ls) env)
                          (deref (cdr ls) env))))))
                
(defun deref1 (x env)
    (cond ((null env) x)
          ((equal x (car (car env))) (cdr (car env)))
          (t (deref1 x (cdr env)))))