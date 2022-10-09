#|
Prolog interpreter

data type
variable _name e.g. _x _y _z
anoymous _
variant (% sym n) e.g. (% _x 1)
variant variable (% sym num) to avoid lack of memory

data base   symbol (set-property '((foo a)) 'prolog 'foo)  predicate
                   (set-property '(((foo _x)(bar _x))) 'prolog 'foo)  clause


builtin predicate (set-property (lambda (x env) ...) 'builtin 'bar)

environment ((var0 . val0)(var1 . val1) ... (varn , valn))

unify(x,y,env) -> if success return env, else return 'no

builtin predicate
(assert x)
(halt)
(listing) 
(is x y)
(ask)

|#

(import "test")

(defglobal epilog nil)  ;halt switch
(defglobal user nil)    ;user defined predicate and clause name
(defglobal variable nil) ;variable included in goal

(defun prolog ()
    (setup)
    (for ()
         (epilog (setq epilog nil) 'goodbye)
         (format (standard-output) ":-? ")
         (let ((goal (read)))
            (setq variable (findvar goal))
            (display (prove-all (addtail goal '(ask)) nil 0)))))


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
        env
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
    (funcall (property (car x) 'builtin) (cdr (deref x env)) env))

(defun setup ()
    (set-property (lambda (x env) (assert x env)) 'assert 'builtin)
    (set-property (lambda (x env) (setq epilog t)) 'halt 'builtin)
    (set-property (lambda (x env) (listing x env)) 'listing 'builtin)
    (set-property (lambda (x env) (ask variable env)) 'ask 'builtin)
    (set-property (lambda (x env) (is x env)) 'is 'builtin)
    t)

(defun assert (x env)
    (let ((arg1 (elt x 0)))
      (cond ((predicatep arg1)
             (if (not (member (car arg1) user)) (setq user (cons (car arg1) user)))
             (set-property (addtail (property (car arg1) 'prolog) arg1) (car arg1) 'prolog)) 
            ((clausep arg1)
             (if (not (member (car (car arg1)) user)) (setq user (cons (car (car arg1)) user)))
             (set-property (addtail (property (car (car arg1)) 'prolog) arg1) (car (car arg1)) 'prolog ))))
    env)

(defun listing (x env)
    (cond ((null x) (mapc (lambda (y) (listing1 y)) user))
          (t (mapc (lambda (y) (listing1 y)) x)))
    env)

(defun listing1 (x)
    (for ((dt (property x 'prolog) (cdr dt)))
         ((null dt) t)
         (print (car dt))))

(defun findvar (x)
    (cond ((eq (car x) 'assert) nil)
          (t (findvar1 x))))

(defun findvar1 (x)
    (cond ((null x) nil)
          ((variablep (car x)) (cons (car x) (findvar1 (cdr x))))
          ((atom (car x)) (findvar1 (cdr x)))
          ((listp (car x)) (append (findvar1 (car x)) (findvar1 (cdr x))))))

(defun ask (x env)
    (block ask
        (if (null x) (return-from ask 'yes))
        (for ((dt x (cdr x)))
             ((null dt))
             (format (standard-output) "~A = ~A~%" (car dt) (deref (car dt) env)))
        (read-char) ; discard input
        (let ((key (read-char)))
           (while (and (not (char= key #\.)) (not (char= key #\;)) (not (char= key #\newline)))
               (setq key (read-char)))
           (cond ((char= key #\.) 'yes)
                 ((char= key #\newline) 'yes)
                 ((char= key #\;) 'no)))))

      
(defun is (x env)
    (let ((arg1 (elt x 0))
          (arg2 (elt x 1)))
        (unify arg1 (eval arg2) env)))      


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

(defun addtail (x y)
    (cond ((predicatep x) (list x y))
          ((null (cdr x)) (list (car x) y))
          (t (cons (car x) (addtail (cdr x) y)))))


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
($test (findvar '(foo _x _y)) (_x _y))
($test (addtail '(foo _x) '(ask)) ((foo _x)(ask)))
($test (addtail '((foo _x)(bar _x)) '(ask)) ((foo _x)(bar _x)(ask)))
