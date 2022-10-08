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

environment ((var0 . val0)(var1 . val1) ... (varn , valn))


unify(x,y,env) -> if success return env, else return 'no

builtin predicate
(assert x)
(halt)
(ask x)

|#

(import "test")

(defglobal epilog nil)

(defun prolog ()
    (setup)
    (for ()
         (epilog)
         (format (standard-output) ":-? ")
         (print (prove (read) nil 0)))
    (setq epilog nil))



;; x: goal
;; y: continuation
;; env: environment assoc list
;; n: nest level integer 1 ...
;; if success goal return 'yes else return 'no
(defun prove (x env n)
    (block prove
        (cond ((userp x) 
               (let ((def (property 'prolog (car x))))
                  (while def
                      (cond ((predicatep (car def))  
                             (let ((env1 (unify x (car def))))
                                (if (successp env1)
                                    (return-from prove 'yes))))
                            ((clausep (car def))
                             (let ((env1 (unify x (car (car def)))))
                                (if (successp env1)
                                  (let ((env2 (prove-all (alfa-convert (cdr (car def) n)) env (+ n 1))
                                     (if (successp env2) 
                                         (return-from prove 'yes))))))))) 
                      (setq def (cdr def)))      
                   (return-from prove nil)))      
              ((builtinp x) (call-builtin x env)))))
                                 

;; SLD resolution
;; x: continuation P1,P2,...Pn.
;; at fist resolve P1 with prove, and second P2 ... Pn
;; if success return 'yes else return 'no
(defun prove-all (x env n) 
    (if (null x)
        'yes
        (let ((env1 (prove (car x) env) n))
           (if (successp env1)
               (prove-all (cdr x) env1 n)
               'no))))   
    
(defun successp (x)
    (not (eq x 'no)))

;; if unify success return env else return 'no
(defun unify (x y env)
    (cond ((and (null x) (null y)) env)
          ((and (variablep x) (not (variablep y)))
           (let ((x1 (deref x)))
             (if (variablep x1)
                 (cons (cons x1 y) env)
                 (unify x1 y env))))
          ((and (not (variablep x) (variablep y)))
           (let ((y1 (deref y)))
             (if (variablep y1)
                 (cons (cons y1 x) env)
                 (unify x y1 env))))
          ((and (variablep x) (variablep y))
           (let ((x1 (deref x))
                 (y1 (deref y)))
              (if (and (variablep x) (variablep y))
                  (cons (cons x1 y1) env)
                  (unify (deref x) (deref y) env))))
          ((or (anoymousp x) (anoymousp y)) env)
          ((and (atom x) (atom y) (eq x t)) env)
          ((and (listp x) (listp y)) 
           (let ((env1 (unify (car x) (car y) env)))
               (if (successp env1)
                   (unify (cdr x) (cdr y) env)
                   'no)))
          ((and (null x) (not (null y))) 'no)
          ((and (not (null x))) (null y) 'no)))

(defun call-builtin (x env)
    (funcall (property (car x) 'builtin) (cdr (deref x env))))

(defun setup ()
    (set-property (lambda (x) (assert x)) 'assert 'builtin)
    (set-property (lambda (x) (setq epilog t)) 'halt 'builtin)
    t)

(defun assert (x)
    (let ((arg1 (elt x 0)))
      (cond ((predicatep arg1)
             (set-property (cons arg1 (property (car arg1) 'prolog)) (car arg1) 'prolog)) 
            ((clausep arg1)
             (set-property (cons arg1 (property (car (car arg1)) 'prolog)) (car (car arg1)) 'prolog ))))
    'yes)


(defun predicatep (x)
    (and (listp x) (symbolp (car x))))

(defun clausep (x)
    (and (listp x) (listp (car x))))

(defun userp (x)
    (and (listp x)
         (functionp (property (car x) 'prolog))))

(defun builtinp (x)
    (and (listp x)
         (functionp (property (car x) 'builtin))))

(defun variablep (x)
    (or (and (symbolp x) (char= (elt (convert x <string>) 0) #\_))
        (variantp x)))

(defun anoymousp (x)
    (eq x '_))

(defun variantp (x)
    (and (listp x) (eq (car x) '%)))

(defun deref (x env)
    (cond ((null x) nil)
          ((numberp x) x)
          ((variablep x) (deref1 x env))
          ((anoymousp x) x)
          ((atom x) x)
          ((listp x) (cons (deref (car x) env)
                          (deref (cdr x) env)))))
                
; e.g.  env=((_a . 1)(_b . _a))   (deref1 '_b env)->1             
(defun deref1 (x env)
    (let ((x1 (member x env)))
        (cond ((null x1) x)
              ((variablep x1) (deref1 x1 env))
              ((variantp x1) (deref1 x1 env))
              (t x1))))