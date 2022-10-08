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

builtin predicate
(assert x)
(halt)
(ask x)

|#

(defun prove (x y env n)
    (prove-all (cons x y) env n))

(defun prove-all (x env n) 
    (cond ((null x) t)
          ((predicatep (car x)) )
          ((builtinp (car x)) )
    ))


(defun unify (x y env)
    (cond ((and (null x) (null y)) env)
          ((and (variablep x) (not (variablep y)))
           (unify (deref x) y env))
          ((and (not (variablep x) (variablep y)))
           (unify x (deref y) env))
          ((and (listp x) (listp y)) 
           (unify (deref x env) (deref y env)))
          ((and (null x) (not (null y))) nil)
          ((and (not (null x))) (null y) nil)))

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
          ((variablep x) (deref1 x env))
          ((anoymousp x) x)
          ((variantp x) (deref1 x env))
          ((listp x (cons (deref (car ls) env)
                          (deref (cdr ls) env))))))
                
; e.g.  env=((_a . 1)(_b . _a))   (deref1 '_b env)->1             
(defun deref1 (x env)
    (let ((x1 (member x env)))
        (cond ((null x1) x)
              ((variablep x1) (deref1 x1 env))
              ((variantp x1) (deref1 x1 env))
              (t x1))))