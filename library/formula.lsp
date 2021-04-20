;;;
;;; formula processing
;;; written by Dr. Simoji
;;; Modified by sasagawa
;;; We will use the code with the permission of Dr. Shimoji. 
;;;

(defmacro formula (:rest x)
    (infix->prefix x) )


;;formula from simoji sadao's book  
;;
(defun cadr (ls)
    (car (cdr ls)) )

(defun cddr (ls)
    (cond ((null ls) nil)
          ((null (cdr ls)) nil)
          (t (cdr (cdr ls))) ))

(defun arg1 (f)
    (elt f 1) )

(defun arg2 (f)
    (elt f 2) )

(defun arg3 (f)
    (elt f 3) )

(defun op (f)
    (elt f 0) )

(defun subst (old new f)
    (cond ((null f) '())
          ((equal (car f) old) (cons new (subst old new (cdr f))))
          ((atom (car f)) (cons (car f) (subst old new (cdr f))))
          (t (cons (subst old new (car f)) (subst old new (cdr f)))) ))

(defun remove (x f)
    (cond ((null f) '())
          ((eq (car f) x) (remove x (cdr f)))
          (t (cons (car f) (remove x (cdr f)))) ))
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
              (error "opecode else: " op) )) ))

(defun weight (op)
    (case op
       ((+) 1)
       ((-) 1)
       ((/) 2)
       ((*) 3)
       ((^) 4)
       (t (if (subrp op)
              6
              9 )) ))

(defun infix->prefix (fmla)
    (infip fmla) )

(defun infip (fmla)
    (if (atom fmla)
        fmla
        (inf1 fmla '() '()) ))

(defun inf1 (fmla optr opln)
    (if (or (< (weight (op fmla)) 5) (> (weight (op fmla)) 7))
        (inf2 (cdr fmla) optr (cons (infip (car fmla)) opln))
        (inf3 (cddr fmla) optr (cons (list (op fmla) (infip (arg1 fmla))) opln)) ))

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
          ((and (not (null fmla)) (or (null? optr) (> (weight (car fmla))
                                                      (weight (cadr fmla)))))
           (inf1 (cdr fmla) (cons (car fmla) optr) opln))
          (t (inf2 fmla optr opln))))
;;
;;
(defun prefix->infix (fmla)
    (if (atom fmla)
        fmla
        (pretf fmla) ))

(defun pretf (f)
    (if (= (weight (op f)) 6)
        (let ((arg (pret1 (arg1 f) -1)))
           ;
           (if (atom arg)
               (cons (op f) arg)
               (list (op f) (pret1 (arg1 f) -1)) ))
        (pret1 f -1)))

(defun pret1 (f win)
    (cond ((null f) f)
          ((atom f) (list f))
          ((and (eq (op f) '-) (null (arg2 f))) (append '(-) (pret2 (arg1 f) 1)))
          (t (let ((wf (weight (op f))))
                (if (< wf win)
                    (list (pret2 f wf))
                    (pret2 f wf) )))))

(defun pret2 (f wf)
    (append (pret1 (arg1 f) wf) (list (op f)) (pret1 (arg2 f) wf)) )

