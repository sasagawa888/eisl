;;;
;;; formula processing
;;; written by Dr. Simoji
;;; Modified by sasagawa
;;; We will use the code with the permission of Dr. Shimoji. 
;;;

(defmacro formula (:rest x)
    (infix->prefix x) )

(defmacro formulas (x)
    (infix->prefix (string->infix x)) )


(defmodule formula
    ;;formula from simoji sadao's book  
    ;;
    (defun cadr (ls)
        (car (cdr ls)) )

    (defun cddr (ls)
        (cond ((null ls) nil)
              ((null (cdr ls)) nil)
              (t (cdr (cdr ls))) ))

    (defun caar (ls)
        (car (car ls)))

    (defun arg1 (f)
        (elt f 1))

    (defun arg2 (f)
        (elt f 2))

    (defun arg3 (f)
        (elt f 3))

    (defun op (f)
        (elt f 0))

    (defun subst (old new f)
        (cond ((null f) '())
              ((equal (car f) old) (cons new (subst old new (cdr f))))
              ((atom (car f)) (cons (car f) (subst old new (cdr f))))
              (t (cons (subst old new (car f)) (subst old new (cdr f))))))

    (defun remove (x f)
        (cond ((null f) '())
              ((eq (car f) x) (remove x (cdr f)))
              (t (cons (car f) (remove x (cdr f))))))

    ;;-----------------------------------------------------------------------
    ;;
    (defun opcode (op)
        (case op
           ((+) '+)
           ((-) '-)
           ((/) 'quotient)
           ((*) '*)
           ((^) 'expt)
           (t (if (or (subrp op) (macrop op) (funcp op))
                  op
                  (error "opecode else: " op))) ))

    (defun weight (op)
        (case op
           ((+) 1)
           ((-) 1)
           ((/) 2)
           ((*) 3)
           ((^) 4)
           (t (if (or (subrp op) (macrop op) (funcp op))
                  6
                  9)) ))

    (defpublic infix->prefix (fmla)
        (infip fmla))

    (defun infip (fmla)
        (if (atom fmla)
            fmla
            (inf1 fmla '() '())))

    (defun inf1 (fmla optr opln)
        (cond ((or (< (weight (op fmla)) 5) (> (weight (op fmla)) 7))
               (inf2 (cdr fmla) optr (cons (infip (car fmla)) opln)))
              (t (inf3 nil optr (cons (cons (op fmla) (mapcar #'infip (cdr fmla))) opln)))))

    (defun inf2 (fmla optr opln)
        (cond ((and (null fmla) (null optr)) (car opln))
              ((and (not (null fmla)) (or (null optr) (> (weight (car fmla))
                                                         (weight (car optr)))))
               (inf1 (cdr fmla) (cons (car fmla) optr) opln))
              (t
               (inf2
                fmla
                (cdr optr)
                (cons (list (opcode (car optr)) (cadr opln) (car opln)) (cddr opln))))))

    (defun inf3 (fmla optr opln)
        (cond ((and (null fmla) (null opln)) (car opln))
              ((and
                (not (null fmla))
                (or (null optr) (> (weight (car fmla))
                                   (weight (cadr fmla)))))
               (inf1 (cdr fmla) (cons (car fmla) optr) opln))
              (t (inf2 fmla optr opln))))

    ;;
    ;;
    (defpublic prefix->infix (fmla)
        (if (atom fmla)
            fmla
            (pretf fmla)))

    (defun pretf (f)
        (if (= (weight (op f)) 6)
            (let ((arg (pret1 (arg1 f) -1)))
               ;
               (if (atom arg)
                   (cons (op f) arg)
                   (list (op f) (pret1 (arg1 f) -1))))
            (pret1 f -1)))

    (defun pret1 (f win)
        (cond ((null f) f)
              ((atom f) (list f))
              ((and (eq (op f) '-) (null (arg2 f))) (append '(-) (pret2 (arg1 f) 1)))
              (t (let ((wf (weight (op f))))
                    (if (< wf win)
                        (list (pret2 f wf))
                        (pret2 f wf))))))

    (defun pret2 (f wf)
        (append (pret1 (arg1 f) wf) (list (op f)) (pret1 (arg2 f) wf)))

    
    ;; translater from string to sexp written by Kenichi Sasagawa
    ;; e.g. "1+2" -> (1 + 2)   "a+(b+x)" -> (a (b + c))

    (defpublic string->infix (x)
        (let ((s (parse x)))
            (if (and (consp (car s)) (subrp (caar s)) (= (length s) 1))
                (car s)
                s)))
    
    (defun operator-p (x)
        (or (char= x #\+) (char= x #\-) (char= x #\*) (char= x #\/) (char= x #\^)))

    (defglobal *rest-list* nil)
    
    (defun symbol-token-p (x)
        (and (char>= (car x) #\A) (char<= (car x) #\z)))

    (defun integer-token-p (x)
        (and (char>= (car x) #\0) (char<= (car x) #\9) (not (member #\. x))))

    (defun float-token-p (x)
        (and (char>= (car x) #\0) (char<= (car x) #\9) (member #\. x)))

    
    (defun to-upper (x)
        (mapcar
         (lambda (x) 
            (if (and (char>= x #\a) (char<= x #\z))
                (convert (- (convert x <integer>) 32) <character>)
                x))
         x))

    (defun convert-token (x)
        (let ((y (reverse x)))
           (cond ((null x) nil)
                 ((symbol-token-p y) (convert (convert-token1 (to-upper y)) <symbol>))
                 ((integer-token-p y) (convert (convert-token1 y) <integer>))
                 ((float-token-p y) (convert (convert-token1 y) <float>))
                 (t (format (standard-output) "syntax error")))))

    (defun convert-token1 (x)
        (cond ((null x) "")
              (t (string-append (convert (car x) <string>) (convert-token1 (cdr x))))))

    

    (defun parse (x)
        (setq *rest-list* nil)
        (parse1 (convert x <list>) nil nil))

    (defun parse1 (x token stack)
        (cond ((null x)
               (cond ((null token) (reverse stack))
                     (t (reverse (cons (convert-token token) stack)))))
              ((char= (car x) #\space) (parse1 (cdr x) token stack))
              ((operator-p (car x))
               (cond ((null token)
                      (parse1 (cdr x) nil (cons (convert (car x) <symbol>) stack)))
                     (t (parse1 (cdr x) nil (cons (convert (car x) <symbol>) (cons (convert-token token) stack))))))
              ((char= (car x) #\()
               (cond ((null token)
                      (let ((s (parse1 (cdr x) nil nil)))
                        (parse1 (cdr *rest-list*) nil (cons s stack))))
                     ;; function e.g. foo(boo(x),bar(y))
                     (t 
                       (setq *rest-list* x)
                       (for ((s nil (cons (parse2 (reverse (parse1 (cdr *rest-list*) nil nil))) s)))
                            ((char= (car *rest-list*) #\))
                             (parse1 (cdr *rest-list*) nil (cons (cons (convert-token token) (reverse s)) stack)))))))
              ((char= (car x) #\))
               (setq *rest-list* x)
               (cond ((null token) stack)
                     (t (cons (convert-token token) stack) )))
              ((char= (car x) #\,)
               (setq *rest-list* x) 
               (cond ((null token) stack)
                     (t (cons (convert-token token) stack) )))
              (t (parse1 (cdr x) (cons (car x) token) stack))))

    (defun parse2 (x)
        (if (null (cdr x))
            (car x)
            x))

    ;;; translate from infix-Sexpression to string
    
     

)
