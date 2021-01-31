;;; protable prolog interpreter  ver2.0 by H.Nakashima 1983.04.09
;;;                                     modified for ISLisp by K.Sasagawa
;;;                                     modified Ver0.11 2016/10     

;;; usage
;;; (assert (member *x (*x . *y)))
;;; (assert (member *x (*x1 . *y))(member *x *y)) 
;;; 
;;; (assert (print *x) (call print *x))
;;; (assert (plus *x *y *z) (eval (+ *x *y) *z) (print *z))

(defglobal fetched-subst '())
(defglobal undo-list '())
(defglobal epilog nil)

(defun display (x)
    (format (standard-output) "~A" x) )

(defun newline ()
    (format (standard-output) "~%") )

;;in ISLisp when cdr recieve nil, invoke error.
;;so, cdr* is compatible with Common Lisp
(defun cdr* (x)
    (if (null x)
        nil
        (cdr x) ))

(defun caar (x)
    (car (car x)) )

(defun cadr (x)
    (car (cdr* x)) )

(defun cddr (x)
    (cdr* (cdr* x)) )

(defun cddar (x)
    (cdr* (cdr* (car x))) )


(defun prolog ()
    (display "Portable Prolog (in ISLisp)")
    (set-up)
    (for ( )
         (epilog)
         (setq fetched-subst '())
         (setq undo-list '())
         (display (refutes (cons (read-with-prompt) '()) (cons '() '()) (cons '() '()) '())))
    (setq epilog nil))

(defun read-with-prompt ()
    (newline)
    (display ": ")
    (read) )

(defun define-clause (clause)
    (let ((definition (property (caar clause) 'prolog)))
       (if (not definition)
           (set-property (cons clause '()) (caar clause) 'prolog)
           (set-property (append definition (cons clause '())) (caar clause) 'prolog) )
       (display "defined")
       (newline)
       t))

(defun refutes (clause old-subst new-subst cue)
    (cond ((null clause)
           (cond ((null cue) '*s*)
                 (t (refutes (car (first cue)) (cdr* (first cue)) (cons '() '()) (cdr* cue)))))
          ((and (varp clause) (assignedp clause old-subst))
           (refutes (fetch-value clause old-subst) fetched-subst new-subst cue))
          ((and (varp (first clause)) (assignedp (first clause) old-subst))
           (refutes
            (cons (fetch-value (first clause) old-subst) '())
            fetched-subst
            new-subst
            (cons (cons (cdr* clause) old-subst) cue)))
          (t (refute clause (property (caar clause) 'prolog) old-subst new-subst cue))))

(defun refute (clause definitions old-subst new-subst cue)
    (cond ((not definitions)
           ;;definition==nil means that clause is system predicate
           (cond ((and
                   (try-sys (car clause) old-subst)
                   (refutes (cdr* clause) old-subst (cons '() '()) cue))
                  t)
                 (t (undo undo-list))))
          ;;else cluase is user defined predicate
          (t (resolve clause definitions new-subst old-subst cue))))


;;prove user defined predicate
(defun resolve (clause definitions new-subst old-subst cue)
    ;;if definition of clause is null, then end.
    (cond ((null definitions) nil)
          ;;check unification of head part. if unify head check body part.  
          ((and
            (unify (car clause) old-subst (caar definitions) new-subst)
            (refutes
             (cdr* (first definitions))
             new-subst
             (cons '() '())
             (cons (cons (cdr* clause) old-subst) cue)))
           t)
          ;;if not unify, undo and check next definition
          (t (undo undo-list) (resolve clause (cdr* definitions) new-subst old-subst cue))))

;;unbind variables for back-track
(defun undo (u)
    (cond ((null u) (setq undo-list '()) nil)
          (t (set-cdr (cddar u) (car u)) (undo (cdr* u))) ))
(defun link (x x-subst y y-subst)
    (cond ((and (eq x y) (eq x-subst y-subst)) t)
          (t
           (setq
            undo-list
            (cons
             (set-cdr
              (cons (cons x (cons (fetch y y-subst) fetched-subst)) (cdr* x-subst))
              x-subst)
             undo-list)))))
(defun unify (x x-subst y y-subst)
    (cond ((varp x)
           (cond ((assignedp x x-subst) (unify (fetch x x-subst) fetched-subst y y-subst))
                 (t (link x x-subst y y-subst))))
          ((varp y) (unify y y-subst x x-subst))
          ((atom x) (eql x y))
          ((atom y) nil)
          ((unify (car x) x-subst (car y) y-subst) (unify (cdr* x) x-subst (cdr* y) y-subst))
          (t nil)))

(defun fetch (x subst)
    (setq fetched-subst subst)
    (cond ((varp x)
           (let ((v (assoc x (cdr* subst))))
              (cond ((not v) x)
                    (t (setq fetched-subst (cddr v)) (fetch (second v) (cddr v))))))
          (t x)))

;;set system predicate
(defun set-up ()
    (set-property
     (lambda (form subst)
        (define-clause (fetch-value form subst)))
     'assert
     'primitive)
    
    (set-property
     (lambda (form subst)
        (let ((f (fetch-value (first form) subst)))
           (apply (symbol-function f) (mapcar (lambda (x)
                                                 (fetch-value x subst)) (cdr* form)))))
     'call
     'primitive)
    
    (set-property (lambda (form subst)
                     (setq epilog t)) 'halt 'primitive)
    
    (set-property
     (lambda (form subst)
        (let ((f (fetch-value (car (first form)) subst)))
           (cond ((unify
                   (apply
                    (symbol-function f)
                    (mapcar (lambda (x)
                               (fetch-value x subst)) (cdr* (first form))))
                   subst
                   (second form)
                   subst)
                  t)
                 (t nil))))
     'eval
     'primitive))
;;execute system predicate
(defun try-sys (form subst)
    (if (property (car form) 'primitive)
        (apply (property (car form) 'primitive) (list (cdr* form) subst))
        nil ))

;;Is it variable? ex *x *y 
(defun varp (x)
    (and (symbolp x) (char= (aref (convert x <string>) 0) #\*)) )

(defun assignedp (x subst)
    (assoc x (cdr* subst)) )

(defun fetch-value (x subst)
    (cond ((varp x)
           (let ((v (assoc x (cdr* subst))))
              (if (not v)
                  x
                  (fetch-value (second v) (cddr v)))))
          ((atom x) x)
          (t (cons (fetch-value (car x) subst) (fetch-value (cdr* x) subst)))))


(defun first (x)
    (car x) )

(defun second (x)
    (cadr x) )

(defun third (x)
    (caddr x) )



