#|
Prolog interpreter
data type
variable _name e.g. _x _y _z
anoymous _
variant (% sym n) e.g. (% _x 1)
variant variable (% sym num) to avoid lack of memory
predicate e.g. (human taro)
clause e.g.  ((error _x) (human _x))   head part is car and body part is cdr 
data base   symbol (set-property '((foo a)) 'prolog 'foo)  predicate
                   (set-property '(((foo _x)(bar _x))) 'prolog 'foo)  clause
builtin predicate (set-property (lambda (x env) ...) 'builtin 'bar)
environment ((var0 . val0)(var1 . val1) ... (varn , valn))
unify(x,y,env) -> if success return env, else return 'no
question  add goal (ask) builtin to display variable
builtin predicate
(assert x) (halt) (listing) (listing x) (is x y) (consult x) (reconsult x) (ask)
(fail) (true) (= x y) (== x y) (= x y) (> x y) (>= x y) (< x y) (<= x y)
(trace) (notrace) (write) (nl) (system x) (eval x) (save x)
|#

(defmodule peisl
    (defglobal epilog nil)    ;halt switch
    (defglobal user nil)      ;user defined predicate and clause name
    (defglobal variable nil)  ;variable included in goal
    (defglobal trace nil)     ;trace switch
    (defglobal find nil)      ;for findall save find value 

    (defpublic prolog ()
        (for ( )
             (epilog
              (setq epilog nil)
              'goodbye )
             (format (standard-output) "-? ")
             (let ((goal (read)))
                (setq variable (findvar goal))
                (let ((res
                      (catch 'exit
                             (with-handler (lambda (c) (throw 'exit c))
                                           (prove-all (addask goal) nil 0)))))
                   (cond ((instancep res (class <error>))
                          (format (standard-output) "System error ~A~%" (class-of res)))
                         ((not (eq res 'error)) (display res)))))))

    (defun display (x)
        (if (eq x 'no)
            (format (standard-output) "~A~%" 'no)
            (format (standard-output) "~A~%" 'yes)))

    (defpublic -? (x)
        (prove x nil nil 0))

    ;; x: goal
    ;; y: continuation
    ;; env: environment assoc list
    ;; n: nest level integer 1 ...
    ;; if success goal return env else return 'no
    (defun prove (x y env n)
        (trace* "call" x n env)
        (block prove
           (cond ((userp x)
                  (let ((def (property (car x) 'prolog)))
                     (while def
                        (cond ((predicatep (car def))
                               (let* ((def1 (alfa-convert (car def) n))
                                      (env1 (unify x def1 env)) )
                                   (cond ((successp env1)
                                          (trace* "succ" x n env1)
                                          (let ((env2 (prove-all y env1 n)))
                                             (if (successp env2)
                                                 (return-from prove env2)))))))
                              ((clausep (car def))
                               (let* ((def1 (alfa-convert (car def) n))
                                      (env1 (unify x (car def1) env)) )
                                   (cond ((successp env1)
                                          (trace* "succ" x n env)
                                          (let ((env2
                                                (prove-all (append (cdr def1) y) env1 (+ n 1))))
                                             (if (successp env2)
                                                 (return-from prove env2))))))))
                        (trace* "redo" x n env)
                        (setq def (cdr def)))
                     (trace* "fail" x n env)
                     (return-from prove 'no)))
                 ((builtinp x)
                  (let ((env1 (call-builtin x env)))
                     (if (successp env1)
                         (let ((env2 (prove-all y env1 n)))
                            (if (successp env2)
                                (return-from prove env2)
                                (return-from prove 'no)))
                         (return-from prove 'no))))
                 ((null x) 'yes) ; for consult/reconsult. file end is nil
                 (t (error* "Existence error" x)))))

    ;; SLD resolution
    ;; x: continuation P1,P2,...Pn.
    ;; at fist resolve P1 with prove, and second P2 ... Pn
    ;; if success return env else return 'no
    (defun prove-all (x env n)
        (if (null x)
            env
            (prove (car x) (cdr x) env n)))

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
                     (y1 (deref y env)) )
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
        (set-property (lambda (x env) (assert1 x env)) 'assert 'builtin)
        (set-property (lambda (x env) (halt x env)) 'halt 'builtin)
        (set-property (lambda (x env) (listing x env)) 'listing 'builtin)
        (set-property (lambda (x env) (ask variable env)) 'ask 'builtin)
        (set-property (lambda (x env) (is x env)) 'is 'builtin)
        (set-property (lambda (x env) (consult x env)) 'consult 'builtin)
        (set-property (lambda (x env) (reconsult x env)) 'reconsult 'builtin)
        (set-property (lambda (x env) 'no) 'fail 'builtin)
        (set-property (lambda (x env) env) 'true 'builtin)
        (set-property (lambda (x env) (unify (elt x 0) (elt x 1) env))
                      '=
                      'builtin)
        (set-property (lambda (x env) (if (= (elt x 0) (elt x 1))
                             env
                             'no))
                      '==
                      'builtin)
        (set-property (lambda (x env) (if (not (= (elt x 0) (elt x 1)))
                             env
                             'no))
                      '=
                      'builtin)
        (set-property (lambda (x env) (if (> (elt x 0) (elt x 1))
                             env
                             'no))
                      '>
                      'builtin)
        (set-property (lambda (x env) (if (>= (elt x 0) (elt x 1))
                             env
                             'no))
                      '>=
                      'builtin)
        (set-property (lambda (x env) (if (< (elt x 0) (elt x 1))
                             env
                             'no))
                      '<
                      'builtin)
        (set-property (lambda (x env) (if (<= (elt x 0) (elt x 1))
                             env
                             'no))
                      '<=
                      'builtin)
        (set-property (lambda (x env) (setq trace t)) 'trace 'builtin)
        (set-property (lambda (x env) (setq trace nil)) 'notrace 'builtin)
        (set-property (lambda (x env) (format (standard-output) "~A" x))
                      'write
                      'builtin)
        (set-property (lambda (x env) (format (standard-output) "~%" x))
                      'nl
                      'builtin)
        (set-property (lambda (x env) (system (elt x 0)) env)
                      'system
                      'builtin)
        (set-property (lambda (x env) (eval (cons 'defun x)) env)
                      'defun
                      'builtin)
        (set-property (lambda (x env) (eval (cons 'defgeneric x)) env)
                      'defgeneric
                      'builtin)
        (set-property (lambda (x env) (eval (cons 'defmethod x)) env)
                      'defmethod
                      'builtin)
        (set-property (lambda (x env) (save x))
                      'save
                      'builtin)
        (set-property (lambda (x env) (findall x env))
                      'findall
                      'builtin)        
        t)

    (defpublic assert (x) 
        (assert2 x)
        t)    
    
    (defun assert1 (x env)
        (let ((arg1 (elt x 0)))
            (assert2 arg1)
            env))

    (defun assert2 (x)
        (cond ((predicatep x)
               (if (not (member (car x) user))
                   (setq user (cons (car x) user)))
               (set-property (addtail (property (car x) 'prolog) x) (car x) 'prolog))
              ((clausep x)
               (if (not (member (car (car x)) user))
                   (setq user (cons (car (car x)) user)))
               (set-property (addtail (property (car (car x)) 'prolog) x)
                             (car (car x))
                             'prolog))))

    (defun halt (x env)
        (read-char)           ; discard input
        (mapc (lambda (y) (set-property nil y 'prolog)) user) ;delete prolog code
        (setq epilog t))

    (defun listing (x env)
        (cond ((null x) (mapc (lambda (y) (listing1 y)) (reverse user)))
              (t (mapc (lambda (y) (listing1 y)) x)))
        env)

    (defun listing1 (x)
        (for ((dt (property x 'prolog) (cdr dt)))
             ((null dt)
              t )
             (format (standard-output) "~A~%" (car dt))))

    (defun findvar (x)
        (cond ((not (consp x)) nil)
              ((eq (car x) 'assert) nil)
              (t (remove-double (findvar1 x)))))

    (defun findvar1 (x)
        (cond ((null x) nil)
              ((variablep (car x)) (cons (car x) (findvar1 (cdr x))))
              ((atom (car x)) (findvar1 (cdr x)))
              ((listp (car x)) (append (findvar1 (car x)) (findvar1 (cdr x))))))

    (defun remove-double (x)
        (cond ((null x) nil)
              ((member (car x) (cdr x)) (remove-double (cdr x)))
              (t (cons (car x) (remove-double (cdr x))))))

    (defun ask (x env)
        (block exit
           (if (null x)
               (return-from exit env))
           (for ((dt x (cdr dt)))
                ((null (cdr dt))
                 (format (standard-output)
                        "~A = ~A"
                        (car dt)
                        (deref (car dt) env)) )
                (format (standard-output)
                        "~A = ~A~%"
                        (car dt)
                        (deref (car dt) env)))
           (read-char)        ; discard input
           (let ((key (read-char)))
              (while (and (not (char= key #\.))
                      (not (char= key #\;))
                      (not (char= key #\newline)))
                 (setq key (read-char)))
              (cond ((char= key #\.) 'yes)
                    ((char= key #\newline) 'yes)
                    ((char= key #\;) 'no)))))

    (defun is (x env)
        (let ((arg1 (elt x 0))
              (arg2 (elt x 1)) )
           (unify arg1 (eval arg2) env)))

    (defun consult (x env)
        (let* ((arg1 (elt x 0))
               (instream (open-input-file arg1))
               (sexp t) )
            (while (not (null sexp))
               (setq sexp (read instream nil nil))
               (prove sexp nil nil 0))
            (close instream))
        env)

    (defun reconsult (x env)
        (mapc (lambda (y) (set-property nil y 'prolog)) user)
        (let* ((arg1 (elt x 0))
               (instream (open-input-file arg1))
               (sexp t) )
            (while (not (null sexp))
               (setq sexp (read instream nil nil))
               (prove sexp nil nil 0))
            (close instream))
        env)

    (defun save (x)
        (let ((arg1 (elt x 0)))
            (setq find (cons x find))
            'no))

    (defun findall (x env)
        (let ((arg1 (elt x 0))
              (arg2 (elt x 1))
              (arg3 (elt x 2)))
            (setq find nil)
            (let ((env1 (prove-all (cons arg2 (list (list 'save arg1))) env 0)))
                (unify arg3 (reverse find) env))))

    (defun error* (msg x)
        (format (standard-output) "~A ~A~%" msg x)
        (throw 'exit 'error))

    (defun predicatep (x)
        (and (consp x) (symbolp (car x))))

    (defun clausep (x)
        (and (consp x) (listp (car x))))

    (defun userp (x)
        (and (consp x) (not (null (property (car x) 'prolog)))))

    (defun builtinp (x)
        (and (consp x) (functionp (property (car x) 'builtin))))

    (defun variablep (x)
        (or (and (symbolp x) (char= (elt (convert x <string>) 0) #\_))
            (variantp x)))

    (defun anoymousp (x)
        (eq x '_))

    (defun variantp (x)
        (and (listp x) (eq (car x) '%)))

    (defpublic ~? (x env) (deref x env))

    (defun deref (x env)
        (cond ((null x) nil)
              ((anoymousp x) x)
              ((variablep x) (deref1 x env))
              ((atom x) x)
              ((listp x) (cons (deref (car x) env) (deref (cdr x) env)))))
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
              ((listp x) (cons (alfa-convert (car x) n) (alfa-convert (cdr x) n)))))

    (defun addask (x)
        (cond ((predicatep x) (list x '(ask)))
              ((null (cdr x)) (list (car x) '(ask)))
              (t (cons (car x) (addask (cdr x))))))

    (defun addtail (x y)
        (cond ((null x) (list y))
              ((null (cdr x)) (list (car x) y))
              (t (cons (car x) (addtail (cdr x) y)))))

    (defun trace* (op x n env)
        (if trace
            (format (standard-output) "(~A) ~A ~A~%" n op (deref x env))))

    (setup)

)
