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
       ((/) '/)
       ((*) '*)
       ((^) '^)
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
           (if (atom? arg)
               (cons (op f) arg)
               (list (op f) (pret1 (arg1 f) -1)) ))
        (pret1 f -1)))

(defun pret1 (f win)
    (cond ((null f) f)
          ((atom f) (list f))
          ((and (eq? (op f) '-) (null (arg2 f))) (append '(-) (pret2 (arg1 f) 1)))
          (t (let ((wf (weight (op f))))
                (if (< wf win)
                    (list (pret2 f wf))
                    (pret2 f wf) )))))

(defun pret2 (f wf)
    (append (pret1 (arg1 f) wf) (list (op f)) (pret1 (arg2 f) wf)) )


;;----------------------------------------------------------------------------------
;;

(defun /nestp (f)
    (and (listp f) (eq (op f) '/)) )

(defun +nestp (f)
    (and (listp f) (eq (op f) '+)) )

(defun *simp1 (f)
    (cond ((atom f) (list f))
          ((eq (op f) '*) (mapcan #'*simp1 (cdr f)))
          (t (list (simps f))) ))


(defun *simp (f)
    (cond ((= (length f) 3)
           (cond ((eq (arg1 f) 0) 0)                                                      ;0*a=0
                 ((eq? (arg2 f) 0) 0)                                                     ;a*0=0
                 ((eq (arg1 f) 1) (simps (arg2 f)))                                       ;1*a=a
                 ((eq (arg2 f) 1) (simps (arg1 f)))                                       ;a*1=a
                 ((/nestp (arg2 f))
                  (list
                   '/
                   (list '* (simps (arg1 f)) (simps (arg1 (arg2 f))))
                   (simps (arg2 (arg2 f)))));(* a (/ b c)) = (/ (* a b) c)
                 ((not (lat (cdr f))) (cons '* (*simp1 f)))
                 ((eq (arg1 f) (arg2 f)) (list '^ (arg1 f) 2))                            ;(* a a) -> (^ a 2) 
                 (t (list '* (simps (arg1 f)) (simps (arg2 f))))))
          ((member 0 (cdr f)) 0)                                                          ; (* a .. 0 .. z)=0 
          ((and (numberp (arg1 f)) (listp (arg2 f)) (eq (op (arg2 f)) '+))
           (simps (cons '+ (mapcar (lambda (c)
                                      (list '* (arg1 f) c)) (cdr (arg2 f))))))
          ((not (lat (cdr f))) (cons '* (*simp1 f)))
          (t (cons '* (mapcar #'simps (cdr f))))))

;;
(defun lat (ls)
    (cond ((null ls) t)
          ((atom (car ls)) (lat (cdr ls)))
          (t nil) ))

(defun +simp (f)
    (cond ((eq (arg1 f) 0) (if (= (length f) 3)
                               (arg2 f)
                               (simps (cons '+ (cddr f))) ))
          ((and (eq (arg2 f) 0) (= (length f) 3)) (simps (arg1 f)))
          ((eq (arg1 f) (arg2 f)) (list '* 2 (simps (arg1 f))))
          (t (cons '+ (mapcar #'simps (cdr f))))))



(defun -simp (f)
    (cond ((= (length f) 2)
           (cond ((+nestp (arg1 f))
                  (list
                   '+
                   (list '* -1 (simps (arg1 (arg1 f))))
                   (list '* -1 (simps (arg2 (arg1 f))))));(- (+ a b)) = (+ (* -1 a) (* -1 b))
                 (t (list '* -1 (simps (arg1 f))))));(-a)=(* -1 a)
          ((= (length f) 3)
           (cond ((eq (arg1 f) (arg2 f)) 0)                                               ;(- a a) = 0
                 (t (list '+ (simps (arg1 f)) (list '* -1 (simps (arg2 f)))))))))
; (- a b) = (+ a (* -1 b))

(defun /simp (f)
    (cond ((eq (arg1 f) (arg2 f)) 1)
          ((eq (arg1 f) 0) 0)
          ((eq (arg2 f) '()) 0)
          ((numberp (arg2 f)) (simps (list '* (/ 1 (arg2 f)) (arg1 f))))
          ((and
            (listp (arg2 f))
            (= (length (arg2 f)) 3)
            (numberp (arg1 (arg2 f)))
            (symbolp (arg2 (arg2 f))))
           (let ((cdf (arg2 f)))
              (if (= (length (cddr cdf)) 1)
                  (list '/ (simps (list '* (/ 1 (arg1 cdf)) (arg1 f))) (arg2 cdf))
                  (list
                   '/
                   (simps (list '* (/ 1 (arg1 cdf)) (arg1 f)))
                   (simps (cons (car cdf) (cddr cdf)))))))
          (t (list '/ (simps (arg1 f)) (simps (arg2 f))))))


(defun ^simp (f)
    (cond ((eq (arg2 f) 0) 1)
          ((eq (arg2 f) 1) (arg1 f))
          (t (list (op f) (simps (arg1 f)) (simps (arg2 f)))) ))

;;
(defun sin-simp (f)
    (cond ((and (consp (arg1 f)) (eq? (op (arg1 f)) '*) (eq (arg1 (arg1 f)) 'i))
           (list '* 'i (list 'sinh (arg2 (arg1 f)))))
          ((and (number? (arg1 f)) (= (arg1 f) 0)) 0)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/6 pi))) 0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/4 pi))) '(/ (sqrt 2) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/3 pi))) '(/ (sqrt 3) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/2 pi))) 1)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 2/3 pi))) '(/ (sqrt 3) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 3/4 pi))) '(/ (sqrt 2) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 5/6 pi))) 0.5)
          ((eq (arg1 f) 'pi) 0)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 7/6 pi))) -0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 5/4 pi))) '(* -1 (/ (sqrt 2) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 4/3 pi))) '(* -1 (/ (sqrt 3) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 3/2 pi))) -1)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 4/3 pi))) '(* -1 (/ (sqrt 3) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 7/4 pi))) '(* -1 (/ (sqrt 2) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 11/6 pi))) -0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 2 pi))) 0)
          ((and
            (consp (arg1 f))
            (eq (op (arg1 f)) '*)
            (numberp (arg1 (arg1 f)))
            (> (arg1 (arg1 f)) 2)
            (eq (arg2 (arg1 f)) 'pi))
           (sin-simp (list 'sin (list '* (- (arg1 (arg1 f)) 2) 'pi))))
          ((atom (arg1 f)) (list 'sin (arg1 f)))
          (t
           (let ((arg (simps (arg1 f))))
              (if (equal arg (arg1 f))
                  (list 'sin arg)
                  (cos-simp (list 'sin (simps (arg1 f)))))))))

;;
(defun cos-simp (f)
    (cond ((and (number? (arg1 f)) (= (arg1 f) 0)) 1)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/6 pi))) '(/ (sqrt 3) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/4 pi))) '(/ (sqrt 2) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/3 pi))) 0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 1/2 pi))) 0)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 2/3 pi))) -0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 3/4 pi))) '(* -1 (/ (sqrt 2) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 5/6 pi))) '(* -1 (/ (sqrt 3) 2)))
          ((eq (arg1 f) 'pi) -1)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 7/6 pi))) '(* -1 (/ (sqrt 3) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 5/4 pi))) '(* -1 (/ (sqrt 2) 2)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 4/3 pi))) -0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 3/2 pi))) 0)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 4/3 pi))) 0.5)
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 7/4 pi))) '(/ (sqrt 2) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 11/6 pi))) '(/ (sqrt 3) 2))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* 2 pi))) 1)
          ((and
            (consp (arg1 f))
            (eq? (op (arg1 f)) '*)
            (numberp (arg1 (arg1 f)))
            (> (arg1 (arg1 f)) 2)
            (eq? (arg2 (arg1 f)) 'pi))
           (cos-simp (list 'cos (list '* (- (arg1 (arg1 f)) 2) 'pi))))
          ((atom (arg1 f)) (list 'cos (arg1 f)))
          (t
           (let ((arg (simps (arg1 f))))
              (if (equal arg (arg1 f))
                  (list 'cos arg)
                  (cos-simp (list 'cos (simps (arg1 f)))))))))

;;
(defun atan-simp (f)
    (cond ((and (numberp (arg1 f)) (= (arg1 f) 1)) '(/ pi 4))
          ((and (consp (arg1 f)) (equal (arg1 f) '(/ 1 sqrt (3)))) '(/ pi 6))
          ((and (consp (arg1 f)) (equal (arg1 f) '(sqrt 3))) '(/ pi 3))
          ((and (number? (arg1 f)) (= (arg1 f) -1)) '(* -1 (/ pi 4)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* -1 (/ 1 sqrt (3))))) '(* -1 (/ pi 6)))
          ((and (consp (arg1 f)) (equal (arg1 f) '(* -1 (sqrt 3)))) '(* -1 (/ pi 3)))
          (t
           (let ((arg (simps (arg1 f))))
              (if (equal arg (arg1 f))
                  (list 'atan arg)
                  (atan-simp (list 'atan (simps (arg1 f)))))))))

;;
(defun sinh-simp (f)
    (cond ((and (consp (arg1 f)) (eq (op (arg1 f)) '*) (eq (arg1 (arg1 f)) 'i))
           (list '* 'i (list ('sin (arg2 (arg1 f))))))
          (t f)))


;;
(defun !simp (f)
    (if (>= (arg1 f) 0)
        (factorial (arg1 f))
        (- (factorial (abs (arg1 f)))) ))

;;
(defun factorial (n)
    (if (= n 0)
        1
        (* n (factorial (- n 1))) ))

(defun simps (f)
    (if (atom? f)
        f
        (case (op f)
           ((+) (+simp f))
           ((-) (-simp f))
           ((*) (*simp f))
           ((/) (/simp f))
           ((^) (^simp f))
           ((sin) (sin-simp f))
           ;;
           ((cos) (cos-simp f))
           ;;
           ((atan) (atan-simp f))
           ;;
           ((sinh) (sinh-simp f))
           ;;
           ((!) (!simp f))
           ;;
           (t f) ) ))

(defun simpf (ff)
    (let ((fs (simps ff)))
       (if (equal ff fs)
           ff
           (simpf fs) )))



;;
(defun *comnum (f numb symb imag)
    (cond ((null f)
           (let ((n (*numb numb))
                 (i (*imag imag)) )
              ;�����֒ǉ� ����
              (cond ((and (null n) (null i)) (reverse symb))
                    ((and (not (null n)) (null i)) (cons n (reverse symb)))
                    ((and (null n) (not (null i))) (cons i (reverse symb)))
                    (t
                     (if (atomp i)
                         (cons i (cons n (reverse symb)))
                         (cons 'i (cons (- n) (reverse symb))))))))
          ((numberp (car f)) (*comnum (cdr f) (cons (car f) numb) symb imag))
          ((eq (car f) 'i) (*comnum (cdr f) numb symb (cons (car f) imag)))
          (t (*comnum (cdr f) numb (cons (car f) symb) imag))))

(defun *numb (s)
    (if (null s)
        '()
        (eval (cons '* s)) ))

;;�����֒ǉ� ����
(defun *imag (s)
    (if (null s)
        '()
        (case (mod (length s) 4)
           ((1) 'i)
           ((2) -1)
           ((3) '(* -1 i))
           ((0) 1) ) ))


(defun +comnum (f numb symb)
    (cond ((null f)
           (cond ((null numb) (reverse symb))
                 ((eq (length numb) 1) (append (reverse symb) numb))
                 (t (reverse (cons (eval (cons '+ numb)) symb)))))
          ((numberp (car f)) (+comnum (cdr f) (cons (car f) numb) symb))
          (t (+comnum (cdr f) numb (cons (car f) symb)))))

(defun comnum (f)
    (cond ((null f) '())
          ((atom f) f)
          ((and (atom (op f)) (eq (length f) 2)) (list (op f) (comnum (arg1 f))))
          ((and (eq (op f) '^) (numberp (arg1 f)) (numberp (arg2 f))) (expt (arg1 f) (arg2 f)))
          ((eq (op f) '*)
           (let ((ans (*comnum (cdr f) '() '() '())))
              (cond ((eq (length ans) 1) (car ans))
                    ((lat ans) (cons '* ans))
                    (t (cons '* (mapcar #'comnum ans))))))
          ((eq (op f) '+)
           (let ((ans (+comnum (cdr f) '() '())))
              (cond ((eq (length ans) 1) (car ans))
                    ((lat ans) (cons '+ ans))
                    (t (cons '+ (mapcar #'comnum ans))))))
          (t (list (op f) (comnum (arg1 f)) (comnum (arg2 f))))))


(defun simpc (ff)
    (let ((fc (comnum ff)))
       (if (equal ff fc)
           ff
           (simpc fc) )))

(defun simpl (ff)
    (simpc (simpf ff)) )


;;---------------------------------------------------------------------------
;;;
;;;
(defun *aux (f var)
    (if (null? f)
        '()
        (cons
         (cons (derive (car f) var) (cdr f))
         (mapcar (lambda (c)
                    (cons (car f) c)) (*aux (cdr f) var)))))

;; *
(defun *deriv (fmla var)
    (cons '+ (mapcar (lambda (c)((cons '* c))) (*aux (cdr fmla) var))) )

;; /
(defun /deriv (fmla var)
    (list
     '/
     (list
      '-
      (list '* (derive (arg1 fmla) var) (arg2 fmla))
      (list '* (arg1 fmla) (derive (arg2 fmla) var)))
     (list '^ (arg2 fmla) 2)))


;; +
(defun +deriv (fmla var)
    (cons '+ (mapcar (lambda (c)
                        (derive c var)) (cdr fmla))) )

;; -
(defun -deriv (fmla var)
    (cons '- (mapcar (lambda (c)
                        (derive c var)) (cdr fmla))) )


(defun derive (fmla var)
    (cond ((atom fmla) (if (eq fmla var)
                           1
                           0 ))
          ((free fmla var) 0)
          (t
           (case (op fmla)
              ((+) (+deriv fmla var))
              ((-) (-deriv fmla var))
              ((*) (*deriv fmla var))
              ((/) (/deriv fmla var))
              ((^) (^deriv fmla var))
              ((sin) (sderiv fmla var))
              ((cos) (cderiv fmla var))
              ((tan) (tderiv fmla var))
              ((asin) (asderiv fmla var))
              ((acos) (acderiv fmla var))
              ((atan) (atderiv fmla var))
              ((log) (logderiv fmla var))
              ((sinh) (shderiv fmla var))
              ((cosh) (chderiv fmla var))
              (t "Undefined") ))))


;;sin
(defun sderiv (f var)
    (list '* (derive (arg1 f) var) (list 'cos (arg1 f))) )
;;cos
(defun cderiv (f var)
    (list '* (derive (arg1 f) var) (list '* -1 (list 'sin (arg1 f)))) )

;;tan
(defun tderiv (f var)
    (list '/ (derive (arg1 f) var) (list '^ (list 'cos (arg1 f)) 2)) )

;;asin
(defun asderiv (f var)
    (list '/ (derive (arg1 f) var) '(sqrt (- 1 (^ x 2)))) )

;;acos
(defun acderiv (f var)
    (list '* -1 (list '/ (derive (arg1 f) var) '(sqrt (- 1 (^ x 2))))) )

;;atan
(defun atderiv (f var)
    (list '/ (derive (arg1 f) var) '(+ 1 (^ x 2))) )

;;log
(defun logderiv (f var)
    (list '/ (derive (arg1 f) var) (arg1 f)) )

;;sinh
(defun shderiv (f var)
    (list '* (derive (arg1 f) var) (list 'cosh (arg1 f))) )

;;cosh
(defun chderiv (f var)
    (list '* (derive (arg1 f) var) (list 'sinh (arg1 f))) )

(defun ^deriv (fmla var)
    (cond ((and (depend fmla var) (free (arg2 fmla) var))
           (list
            '*
            (list '* (arg2 fmla) (derive (arg1 fmla) var))
            (list '^ (arg1 fmla) (- (arg2 fmla) 1))))
          ((and (depend fmla var) (free (arg1 fmla) var))
           (list '* (derive (arg2 fmla) var) (list '^ 'e (arg2 fmla))))
          (t (^daux fmla var))))


(defun depend (fmla var)
    (cond ((atom fmla) (if (eq fmla var)
                           t
                           nil ))
          ((eq (length fmla) 2) (depend (arg1 fmla) var))
          ((eq (length fmla) 3) (or (depend (arg1 fmla) var) (depend (arg2 fmla) var)))
          ((depend (cddr fmla) var) t)
          (t nil)))

(defun free (fmla var)
    (not (depend fmla var)) )

(defun nderive (n fmla var)
    (if (= n 0)
        (simpl fmla)
        (nderive (- n 1) (simpl (derive fmla var)) var) ))

(defun dif2 (fmla var)
    (simpl (nderive 2 fmla var)) )

(defun diff (fmla var)
    (prefix->infix (dif (infix->prefix fmla) var)) )


(defun dif (fmla var)
    (simpl (derive fmla var)) )

;;-----------------------------------------------------------------
(defun sint (f var)
    (list '* (list '/ -1 (derive (arg1 f) var)) (list 'cos (arg1 f))) )

(defun cint (f var)
    (list '* (list '/ 1 (derive (arg1 f) var)) (list 'sin (arg1 f))) )

(defun tint (f var)
    (list '* (list '/ -1 (derive (arg1 f) var)) (list 'log (list 'cos (arg1 f)))) )

;;cot
(defun ctint (f var)
    (list '* (list '/ 1 (derive (arg1 f) var)) (list 'log (list 'sin (arg1 f)))) )


(defun lint (f var)
    (list '* (list '/ 1 (derive (arg1 f) var)) (list '- (list '* var (list 'log (arg1 f))) var)) )

(defun ^int (f var)
    (cond ((and (mlin (arg1 f) var) (free (arg2 f) var))
           (cond ((eq (arg2 f) -1)
                  (list '* (list '/ 1 (derive (arg1 f) var)) (list 'log (arg1 f))))
                 (t
                  (list
                   '*
                   (list '/ 1 (list '* (+ (arg2 f) 1) (derive (arg1 f) var)))
                   (list '^ (arg1 f) (+ (arg2 f) 1))))))
          ((and (eq (arg1 f) 'e) (mlin (arg2 f) var))
           (list '* (list '/ 1 (derive (arg2 f) var)) (list '^ 'e (arg2 f))))
          (t
           (list
            '*
            (list '/ (derive (arg2 f) var))
            (list '* (list '/ 1 (list 'log (arg1 f))) (list '- (arg1 f) (arg2 f)))))))

(defun mlin (ff var)
    (if (and (depend ff var) (free (simpl (derive ff var)) var))
        t
        nil ))

(defun intf (f var)
    (cond ((free f var) (cons '* (list f var)))
          ((eq f var) (list '* (/ 1 2) (list '^ f 2)))
          (t
           (case (op f)
              ((sin) (sint f var))
              ((cos) (cint f var))
              ((tan) (tint f var))
              ((cot) (ctint f var))
              ((log) (lint f var))
              ((^) (^int f var))
              (t
               (cond ((matchf '(/ 1 x) f var)                                              ;integral 1/x = log|x|+C
                      (list 'log (arg1 f)))
                     ((matchf '(/ 1 (+ (^ x 2) ?c)) f var)                                 ;integral 1/(x^2+b) = 1/b atan(x/b) + C
                      (list
                       '*
                       (list '/ 1 (list 'sqrt ?c))
                       (list 'atan (list '/ var (list 'sqrt ?c)))))
                     ((matchf '(/ 1 (sqrt (- ?c (^ x 2)))) f var)                          ;integral 1/��d^-x^2 = asin(x/d)+C
                      (list '* (list 'asin (list '/ var (list 'sqrt ?c))))))) ))))

(defun intl (f var)
    (let ((fi (simpl (intf f var))))
       (if (equal fi f)
           f
           (simpl fi) )))


(defun varp (x)
    (and (symbolp x) (char= (character x) #\?)) )

(defun character (x)
    (elt (convert x <string>) 0) )


(defun memberp (a b)
    (if (member a b)
        t
        nil ))

(defun matchf1 (p f var)
    (if (and (matchf2 (arg1 p) (arg1 f) var) (matchf2 (arg2 p) (arg2 f) var))
        t
        (if (and
             (memberp (op p) '(+ *))
             (matchf2 (arg2 p) (arg1 f) var)
             (matchf2 (arg1 p) (arg2 f) var))
            t
            nil)))

(defun matchf2 (p f var)
    (cond ((and (null p) (null f)) t)
          ((or (null p) (null f)) t)
          ((equal p f) t)
          ((varp p) (setq ?c f) t)
          ((and (eq f var) (symbolp p)) t)
          ((and (consp p) (consp f) (eq (op p) (op f)) (= (length f) 3)) (matchf1 p f var))
          ((and (consp p) (consp f) (eq (op p) (op f)) (= (length f) 2))
           (matchf2 (arg1 p) (arg1 f) var))
          (t nil)))

(defglobal ?c '())
(defun matchf (p f var)
    (setq ?c '())
    (matchf2 p f var) )
