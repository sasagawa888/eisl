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
           (t (if (subrp op)
                  op
                  (error "opecode else: " op))) ))

    (defun weight (op)
        (case op
           ((+) 1)
           ((-) 1)
           ((/) 2)
           ((*) 3)
           ((^) 4)
           (t (if (subrp op)
                  6
                  9)) ))

    (defpublic infix->prefix (fmla)
        (infip fmla))

    (defun infip (fmla)
        (if (atom fmla)
            fmla
            (inf1 fmla '() '())))

    (defun inf1 (fmla optr opln)
        (if (or (< (weight (op fmla)) 5) (> (weight (op fmla)) 7))
            (inf2 (cdr fmla) optr (cons (infip (car fmla)) opln))
            (inf3 (cddr fmla) optr (cons (list (op fmla) (infip (arg1 fmla))) opln))))

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

    
    ;;
    ;; translater from string to sexp written by Kenichi Sasagawa
    ;; e.g. "1+2" -> (1 + 2)   "a+(b+x)" -> (a (b + c))
    
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

    (defpublic string->infix (x)
        (let ((s (parse x)))
                (if (= (length s) 1)
                    (car s)
                    s)))

    (defun parse (x)
        (parse1 (convert x <list>) nil))

    (defun parse1 (x token)
        (cond ((null x)
               (cond ((null token) nil)
                     (t (list (convert-token token)))))
              ((char= (car x) #\space) (parse1 (cdr x) token))
              ((operator-p (car x))
               (cond ((null token)
                      (cons (convert (car x) <symbol>) (parse1 (cdr x) nil)))
                     (t (cons (convert-token token) (cons (convert (car x) <symbol>) (parse1 (cdr x) nil))))))
              ((char= (car x) #\()
               (cond ((null token)
                      (cons (parse1 (cdr x) nil) (parse1 *rest-list* nil)))
                     (t (cons (cons (convert-token token) (parse1 (cdr x) nil)) (parse1 *rest-list* nil)))))
              ((char= (car x) #\))
               (cond ((null token)
                      (setq *rest-list* (cdr x)) nil)
                     (t (setq *rest-list* (cdr x)) (list (convert-token token)))))
              (t (parse1 (cdr x) (cons (car x) token)))))

)
