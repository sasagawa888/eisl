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
         (display (prove (read) nil 0)))
    (setq epilog nil))


(defun display (x)
    (if (eq x 'no)
        (print 'no)
        (print 'yes)))

;; x: goal
;; y: continuation
;; env: environment assoc list
;; n: nest level integer 1 ...
;; if success goal return env else return 'no
(defun prove (x env n)
    (block prove
        (cond ((userp x) 
               (let ((def (property (car x) 'prolog)))
                  (while def
                      (cond ((predicatep (car def))  
                             (let ((env1 (unify x (car def) env)))
                                (if (successp env1)
                                    (return-from prove env1))))
                            ((clausep (car def))
                             (let* ((def1 (alfa-convert (car def) n))
                                    (env1 (unify x (car def1) env)))
                                    (print def1)
                                (if (successp env1)
                                  (let ((env2 (prove-all (cdr def1) env1 (+ n 1))))
                                     (if (successp env2) 
                                         (return-from prove env2)))))))
                      (setq def (cdr def)))      
                  (return-from prove 'no)))      
              ((builtinp x) (call-builtin x env)))))
                                 

;; SLD resolution
;; x: continuation P1,P2,...Pn.
;; at fist resolve P1 with prove, and second P2 ... Pn
;; if success return 'yes else return 'no
(defun prove-all (x env n) 
    (if (null x)
        'yes
        (let ((env1 (prove (car x) env n)))
           (if (successp env1)
               (prove-all (cdr x) env1 n)
               'no))))   
    
(defun successp (x)
    (not (eq x 'no)))

;; if unify success return env else return 'no
(defun unify (x y env)
    (cond ((and (null x) (null y)) env)
          ((or (anoymousp x) (anoymousp y)) env)
          ((and (variablep x) (not (variablep y)))
           (let ((x1 (deref x env)))
             (if (variablep x1)
                 (cons (cons x1 y) env)
                 (unify x1 y env))))
          ((and (not (variablep x)) (variablep y))
           (let ((y1 (deref y env)))
             (if (variablep y1)
                 (cons (cons y1 x) env)
                 (unify x y1 env))))
          ((and (variablep x) (variablep y))
           (let ((x1 (deref x env))
                 (y1 (deref y env)))
              (if (and (variablep x1) (variablep y1))
                  (cons (cons x1 y1) env)
                  (unify (deref x env) (deref y env) env))))
          ((and (atom x) (atom y) (eq x y)) env)
          ((and (listp x) (listp y)) 
           (let ((env1 (unify (car x) (car y) env)))
               (if (successp env1)
                   (unify (cdr x) (cdr y) env1)
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
         (not (null (property (car x) 'prolog)))))

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
          ((anoymousp x) x)
          ((variablep x) (deref1 x env))
          ((atom x) x)
          ((listp x) (cons (deref (car x) env)
                           (deref (cdr x) env)))))
                
; e.g.  env=((_a . 1)(_b . _a))   (deref1 '_b env)->1             
(defun deref1 (x env)
    (let ((x1 (assoc-equal x env)))
        (cond ((null x1) x)
              ((variablep (cdr x1)) (deref1 (cdr x1) env))
              (t (cdr x1)))))

(defun assoc-equal (x env)
    (cond ((null env) nil)
          ((equal x (car (car env))) (car env))
          (t (assoc-equal x (cdr env)))))

(defun alfa-convert (x n)
    (cond ((null x) nil)
          ((anoymousp x) x)
          ((variablep x) (list '% x n))
          ((atom x) x)
          ((listp x) (cons (alfa-convert (car x) n)
                           (alfa-convert (cdr x) n)))))

($test (anoymousp '_) t)
($test (variablep '_) t)
($test (variablep '_x) t)
($test (variantp '(% _x 1)) t)
($test (variablep '(% _x 1)) t)
($test (predicatep '(foo 1)) t)
($test (clausep '((foo _x)(bar _x))) t)
($test (unify 1 1 nil) nil)
($test (unify 1 2 nil) no)
($test (unify '_ 'a nil) nil)
($test (unify '(foo 1) '(foo 1) nil) nil)
($test (unify '(foo _x) '(foo 1) nil) ((_x . 1)))
($test (unify '(foo 1) '(foo _y) nil) ((_y . 1)))
($test (unify '(foo _z) '(foo _y) nil) ((_z . _y)))
($test (unify '(foo (% _x 0)) '(foo 1) '(((% _x 0) . 1))) (((% _x 0) . 1)))
($test (deref '_x '((_x . 3))) 3)
($test (deref '(foo _x) '((_x . 3))) (foo 3))
($test (deref '(foo _x) '((_a . 2)(_x . _a))) (foo 2))
($test (alfa-convert '((foo _x)(bar _x)) 2) ((foo (% _x 2))(bar (% _x 2))))