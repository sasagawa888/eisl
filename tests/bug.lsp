
;; inference a s-expression
;; if x is true return type-env else return 'no
(defun inference (x type-env)
    (cond ((and (symbolp x) (eq x t)) type-env)
          ((and (symbolp x) (eq x nil)) type-env)
          ((symbolp x)
           (let ((y (refer x type-env)))
              (if y
                  type-env
                  (unify x (class <object>) type-env))))
          ((atom x) type-env)
          ((and (consp x) (eq (car x) 'the)) (unify (class* (elt x 1)) (elt x 2) type-env))
          ((and (consp x) (eq (car x) 'not))                                               ; ignore not function
           type-env)
          ((and (consp x) (eq (car x) 'setq))
           (cond ((not (symbolp (elt x 1))) (warning "setq type mismatch" (elt x 1)) type-env)
                 (t (cons (cons (elt x 1) (find-class (elt x 2) type-env)) type-env))))
          ((and (consp x) (eq (car x) 'convert))                                           ; ignore convert function
           type-env)
          ((and (consp x) (eq (car x) 'catch)) (inference (elt x 2) type-env))
          ((and (consp x) (eq (car x) 'throw)) (inference (elt x 2) type-env))
          ((and (consp x) (eq (car x) 'quote)) type-env)
          ((and (consp x) (eq (car x) 'cond)) (inference-cond x type-env))
          ((and (consp x) (eq (car x) 'case)) (inference-case x type-env))
          ((and (consp x) (eq (car x) 'if)) (inference-if x type-env))
          ((and (consp x) (eq (car x) 'let)) (inference-let x type-env))
          ((and (consp x) (eq (car x) 'let*)) (inference-let x type-env))
          ((and (consp x) (eq (car x) 'for)) (inference-for x type-env))
          ((and (consp x) (eq (car x) 'while)) (inference-while x type-env))
          ((and (consp x) (eq (car x) 'labels)) (inference-labels x type-env))
          ((and (consp x) (eq (car x) 'flet)) (inference-labels x type-env))
          ((and (consp x) (eq (car x) 'function)) (inference-function x type-env))
          ((and (consp x) (macrop x)) (inference (macroexpand-1 x) type-env))
          ((and (consp x) (member (car x) '(+ - * = > < >= <= /=))) (inference-numeric x type-env))
          ((and (consp x) (subrp (car x)))
           (let ((type-subr (property (car x) 'inference)))
              (block exit-inference
                 (for ((type type-subr (cdr type)))
                      ((null type)
                       (warning "subr type mismatch" x)
                       'no )
                      (let ((new-env (inference-arg (cdr x) (cdr (car type)) type-env)))
                         (if (not (eq new-env 'no))
                             (return-from exit-inference new-env)))))))
          ((consp x)
           (let ((type (find-function-type (car x))))
              (if type
                  (inference-arg (cdr x) (elt type 1) type-env))))
          (t (warning "can't inference " x) 'no)))

