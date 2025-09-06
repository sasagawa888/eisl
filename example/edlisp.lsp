;;Copyright (C) Kenichi Sasagawa (2017). All Rights Reserved.
;;Subset ISLisp for learning Ver1.1 for EISL

;;Global variables
(defglobal *global* nil)
;;Dynamic variables
(defglobal *dynamic* nil)
;;Functions - ISLisp is LISP2, meaning variable and function namespaces are separate
(defglobal *function* nil)
;;Built-in functions
(defglobal *primitive*
           '(atom + - * div = eq sin cos tan atan print symbolp car))
;;Special forms
(defglobal *special-form*
           '(quote setq if progn defun defglobal defdynamic cond lambda function let let*))

(defun islisp ()
    (initialize)
    (repl) )

(defun repl ()
    (block repl
       (cond ((catch
               'exit
               (for ((s (read) (read)))
                    ((equal s '(quit))
                     (return-from repl t) )
                    (print (eval* s nil))
                    (setq *dynamic* nil)
                    (prompt)))
              t)
             (t (prompt) (repl)))))

;;Initialization
;;Display a message and show the prompt.
(defun initialize ()
    (format (standard-output) "Subset ISLisp for education~%")
    (prompt) )


;;Show the prompt.
(defun prompt ()
    (format (standard-output) "L> ") )

;;Evaluator
(defun eval* (s env)
    (cond ((null s) s)
          ((numberp s) s)
          ((characterp s) s)
          ((stringp s) s)
          ((general-vector-p s) s)
          ((general-array*-p s) s)
          ((symbolp s) (if (eq s t)
                           s
                           (lookup s env) ))
          ((consp s)
           (cond ((eq (car s) 'funcall) (apply* (eval* (elt s 1) env) (cdr (cdr s)) env))
                 ((and (consp (car s)) (eq (car (car s)) 'lambda))
                  (apply* (eval* (car s) env) (evlis (cdr s) env) env))
                 ((special-form-p (car s)) (apply* (car s) (cdr s) env))
                 ((primitivep (car s)) (apply* (car s) (evlis (cdr s) env) env))
                 ((functionp* (car s)) (apply* (car s) (evlis (cdr s) env) env))
                 (t (apply* (function-lookup (car s)) (evlis (cdr s) env) env))))
          (t (error* "undefined object" s))))

(defun apply* (f arg env)
    (cond ((special-form-p f) (special-form f arg env))
          ((primitivep f) (apply (symbol-function f) arg))
          ((functionp* f)
           (let ((env1 (bindarg (elt (elt f 1) 0) arg (elt f 2))))
              (for ((body (cdr (elt f 1)) (cdr body)))
                   ((null (cdr body))
                    (eval* (car body) env1) )
                   (eval* (car body) env1))))
          (t (error* "Illegal function call apply* " f))))

;;Bind actual arguments to formal parameters and add them to the environment.
;;Example: var=(x,y,z) arg=(1,2,3) env=((a . 10))
;; -> env=((x . 1)(y . 2)(z . 3)(a . 10))
(defun bindarg (var arg env)
    (for ((var1 var (cdr var1))
          (arg1 arg (cdr arg1))
          (res nil (cons (cons (car var1) (car arg1)) res)) )
         ((null var1)
          (append res env) )))

;;Evaluate actual arguments and create a list.
(defun evlis (arg env)
    (cond ((null arg) nil)
          (t (cons (eval* (car arg) env) (evlis (cdr arg) env))) ))

;;Find the value bound to symbol sym.
;;First search the local environment, if not found then the global environment.
;;If sym is a built-in function, return primitive.
(defun lookup (sym env)
    (cond ((assoc sym env) (cdr (assoc sym env)))
          ((assoc sym *global*) (cdr (assoc sym *global*)))
          ((primitivep sym) 'primitive)
          (t (error* "Undefined variable " sym)) ))


;;Search for the binding of symbol sym in the function namespace.
(defun function-lookup (sym)
    (cond ((assoc sym *function*) (cdr (assoc sym *function*)))
          (t (error* "Undefined function " sym)) ))

;;Search for the binding of symbol sym in the dynamic environment.
(defun dynamic-lookup (sym)
    (cond ((assoc sym *dynamic*) (cdr (assoc sym *dynamic*)))
          (t (error* "Undefined variable " sym)) ))


;;Bind value val to symbol sym in the local or global environment.
(defun bind (sym val env)
    (cond ((assoc sym env) (set-cdr val (assoc sym env)))
          ((assoc sym *global*) (set-cdr val (assoc sym *global*)))
          (t (error* "Undefined variable " sym)) ))

;;Error handling
(defun error* (msg arg)
    (format (standard-output) msg)
    (print arg)
    (format (standard-output) "~%")
    (throw 'exit nil) )

;;Return t if built-in function
(defun primitivep (x)
    (member x *primitive*) )

;;Return t if user-defined function
(defun functionp* (x)
    (and (consp x) (eq (car x) 'func)) )

;;Return t if special form
(defun special-form-p (x)
    (member x *special-form*) )

;;Call processing depending on the type of special form.
(defun special-form (f arg env)
    (cond ((eq f 'quote) (car arg))
          ((eq f 'lambda) (list 'func arg env))
          ((eq f 'cond) (evcon arg env))
          ((eq f 'setq) (evsetq arg env))
          ((eq f 'defun) (evdefun arg env))
          ((eq f 'if) (evif arg env))
          ((eq f 'let) (evlet arg env))
          ((eq f 'let*) (evlet* arg env))
          ((eq f 'progn) (evprogn arg env))
          ((eq f 'defglobal) (evdefglobal arg env))
          ((eq f 'defdynamic) (evdefdynamic arg env))
          ((eq f 'dynamic) (evdynamic arg env))
          ((eq f 'function) (if (primitivep (car arg))
                                (car arg)
                                (function-lookup (car arg)) ))))

;;Special form cond
(defun evcon (arg env)
    (cond ((not (null (car (car arg)))) (evprogn (cdr (car arg)) env))
          (t (evcon (cdr arg) env)) ))

;;Special form if
(defun evif (arg env)
    (if (not (null (eval* (elt arg 0) env)))
        (eval* (elt arg 1) env)
        (eval* (elt arg 2) env) ))

;;Special form let
(defun evlet (arg env)
    (for ((vars (car arg) (cdr vars))
          (env1 env) )
         ((null vars)
          (setq env env1) )
         (setq env1 (cons (cons (elt (car vars) 0) (eval* (elt (car vars) 1) env)) env1)))
    (for ((body (cdr arg) (cdr body)))
         ((null (cdr body))
          (eval* (car body) env) )
         (eval* (car body) env)))

;;Special form let*
(defun evlet* (arg env)
    (for ((vars (car arg) (cdr vars)))
         ((null vars)
          t )
         (setq env (cons (cons (elt (car vars) 0) (eval* (elt (car vars) 1) env)) env)))
    (for ((body (cdr arg) (cdr body)))
         ((null (cdr body))
          (eval* (car body) env) )
         (eval* (car body) env)))

;;Special form progn
(defun evprogn (arg env)
    (for ((body arg (cdr body)))
         ((null (cdr body))
          (eval* (car body) env) )
         (eval* (car body) env)))

;;Special form setq
(defun evsetq (arg env)
    (bind (car arg) (eval* (elt arg 1) env) env)
    (car arg) )

;;Special form defglobal
(defun evdefglobal (arg env)
    (cond ((assoc (elt arg 0) *global*)
           (set-cdr (eval* (elt arg 1) env) (assoc (elt arg 0) *global*))
           (elt arg 0))
          (t (setq *global* (cons (cons (elt arg 0) (elt arg 1)) *global*)) (elt arg 0))))

;;Special form dynamic
(defun evdynamic (arg env)
    (dynamic-lookup (elt arg 0)) )

;;Special form defdynamic
(defun evdefdynamic (arg env)
    (cond ((assoc (elt arg 0) *dynamic*)
           (set-cdr (eval* (elt arg 1) env) (assoc (elt arg 0) *dynamic*))
           (elt arg 0))
          (t (setq *dynamic* (cons (cons (elt arg 0) (elt arg 1)) *dynamic*)) (elt arg 0))))


;;Processing of special form defun
;;If present in the function namespace, overwrite the definition; otherwise, add it.
;;It is stored as an association list like (name . (func (args body) env)).
(defun evdefun (arg env)
    (cond ((assoc (elt arg 0) *function*)
           (set-cdr (list 'func (cdr arg) env) (assoc (elt arg 0) *function*)))
          (t (setq *function* (cons (cons (elt arg 0) (list 'func (cdr arg) env)) *function*))))
    (elt arg 0))

