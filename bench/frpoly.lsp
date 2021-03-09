;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     frpoly.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: frpoly.lsp,v 1.8 2013/06/18 05:21:53 jullien Exp $

;;; (22)  FRPOLY  --  Benchmark  from  Berkeley  based  on polynomial
;;; arithmetic.  Originally  writen in Franz Lisp by Richard Fateman.

;;; NOTE:  PDIFFER1  appears in the code,  but is not defined; is not
;;; called for in the test, however.

(defdynamic v   nil)
(defdynamic *x* nil)
(defdynamic u*  nil)

(defglobal r    nil)
(defglobal r2   nil)
(defglobal r3   nil)

(defmacro pointergp (x y) `(> (property ,x 'order) (property ,y 'order)))

(defmacro pcoefp (e) `(not (consp ,e)))

(defmacro pzerop (x) `(and (numberp ,x) (= ,x 0)))

(defmacro pzero () 0)

(defmacro cplus (x y) `(+ ,x ,y))

(defmacro ctimes (x y) `(* ,x ,y))

(defmacro quo (x y) `(div ,x ,y))

(defmacro oddp (x) `(= (mod ,x 2) 1))

(defmacro pfloor (x y) `(div ,x ,y))

(defun pcoefadd (e c x) 
   (if (pzerop c)
       x
       (cons e (cons c x))))

(defun pcplus (c p)
   (if (pcoefp p)
       (cplus p c)
       (psimp (car p) (pcplus1 c (cdr p)))))

(defun pcplus1 (c x)
   (cond ((null x)
          (if (pzerop c)
              nil
              (cons 0 (cons c nil))))
         ((pzerop (car x))
          (pcoefadd 0 (pplus c (car (cdr x))) nil))
         (t
          (cons (car x) (cons (car (cdr x)) (pcplus1 c (cdr (cdr x))))))))

(defun pctimes (c p) 
   (if (pcoefp p)
       (ctimes c p)
       (psimp (car p) (pctimes1 c (cdr p)))))

(defun pctimes1 (c x)
   (if (null x)
       nil
       (pcoefadd (car x)
                 (ptimes c (car (cdr x)))
                 (pctimes1 c (cdr (cdr x))))))

(defun pplus (x y) 
   (cond
         ((pcoefp x)
          (pcplus x y))
         ((pcoefp y)
          (pcplus y x))
         ((eq (car x) (car y))
          (psimp (car x) (pplus1 (cdr y) (cdr x))))
         ((pointergp (car x) (car y))
          (psimp (car x) (pcplus1 y (cdr x))))
         (t
          (psimp (car y) (pcplus1 x (cdr y))))))

(defun pplus1 (x y)
   (cond
         ((null x) y)
         ((null y) x)
         ((= (car x) (car y))
          (pcoefadd (car x)
                    (pplus (car (cdr x)) (car (cdr y)))
                    (pplus1 (cdr (cdr x)) (cdr (cdr y)))))
         ((> (car x) (car y))
          (cons (car x) (cons (car (cdr x)) (pplus1 (cdr (cdr x)) y))))
         (t (cons (car y) (cons (car (cdr y)) (pplus1 x (cdr (cdr y))))))))

(defun psimp (var x)
   (cond
         ((null x) 0)
         ((not (consp x)) x)
         ((pzerop (car x))
          (car (cdr x)))
         (t
          (cons var x))))

(defun ptimes (x y) 
   (cond
         ((or (pzerop x) (pzerop y))
          (pzero))
         ((pcoefp x)
          (pctimes x y))
         ((pcoefp y)
          (pctimes y x))
         ((eq (car x) (car y))
          (psimp (car x) (ptimes1 (cdr x) (cdr y))))
         ((pointergp (car x) (car y))
          (psimp (car x) (pctimes1 y (cdr x))))
         (t
          (psimp (car y) (pctimes1 x (cdr y))))))

(defun ptimes1 (x y)
   (dynamic-let ((*x* x))
      (dynamic-let ((u* (ptimes2 y)))
         (dynamic-let ((v (dynamic u*)))
            (setf (dynamic *x*) (cdr (cdr (dynamic *x*))))
            (while (dynamic *x*)
                   (ptimes3 y)
                   (setf (dynamic *x*) (cdr (cdr (dynamic *x*)))))
            (dynamic u*)))))

(defun ptimes2 (y)
   (if (null y)
       nil
       (pcoefadd (+ (car (dynamic *x*)) (car y))
                 (ptimes (car (cdr (dynamic *x*))) (car (cdr y)))
                 (ptimes2 (cdr (cdr y))))))

(defun ptimes3 (y) 
   (let ((e ())
         (u ())
         (c ()))
        (tagbody
         a1  (if (null y) 
                 (go r))
             (setq e (+ (car (dynamic *x*)) (car y)))
             (setq c (ptimes (car (cdr y)) (car (cdr (dynamic *x*)))))
             (cond ((pzerop c)
                    (setq y (cdr (cdr y)))
                    (go a1))
                   ((or (null (dynamic v))
                        (> e (car (dynamic v))))
                    (setf (dynamic u*) (setf (dynamic v) (pplus1 (dynamic u*)
                                                                 (list e c))))
                    (setq y (cdr (cdr y)))
                    (go a1))
                   ((= e (car (dynamic v)))
                    (setq c (pplus c (car (cdr (dynamic v)))))
                    (if (pzerop c) ; never true, evidently
                        (setf (dynamic u*)
                              (setf (dynamic v)
                                    (pdiffer1 (dynamic u*)
                                              (list
                                                    (car (dynamic v))
                                                    (car (cdr (dynamic v)))))))
                        (set-car c (cdr (dynamic v))))
                    (setq y (cdr (cdr y)))
                    (go a1)))
         a  (cond ((and (cdr (cdr (dynamic v)))
                        (> (car (cdr (cdr (dynamic v)))) e))
                   (setf (dynamic v) (cdr (cdr (dynamic v))))
                   (go a)))
            (setq u (cdr (dynamic v)))
         b  (if (or (null (cdr u)) (< (car (cdr u)) e))
                (setf (cdr u) (cons e (cons c (cdr u))))
                (go e))
            (setq c (pplus (car (cdr (cdr u))) c))
            (cond ((pzerop c)
                   (setf (cdr u) (cdr (cdr (cdr u))))
                   (go d))
                  (t
                    (set-car c (cdr (cdr u)))))
         e  (setq u (cdr (cdr u)))
         d  (setq y (cdr (cdr y)))
            (if (null y)
                (go r))
            (setq e (+ (car (dynamic *x*)) (car y)))
            (setq c (ptimes (car (cdr y)) (car (cdr (dynamic *x*)))))
         c  (cond ((and (cdr u) (> (car (cdr u)) e))
                  (setq u (cdr (cdr u)))
                  (go c)))
            (go b)
         r
            ;; return nil
            )))

(defun pexptsq (p x)
   (for ((n (pfloor x 2) ; (floor x 2) = (quo x 2)
            (pfloor n 2))
         (s (if (oddp x) p 1)))
        ((= n 0) s)
        (setq p (ptimes p p))
        (and (oddp n) (setq s (ptimes s p)))))

(setf (property 'x 'order) 1)
(setf (property 'y 'order) 2)
(setf (property 'z 'order) 3)

(setq r  (pplus '(x 1 1 0 1) (pplus '(y 1 1) '(z 1 1)))) ; r  = x+y+z+1
(setq r2 (ptimes r 100000))                              ; r2 = 100000*r
(setq r3 (ptimes r 1.0))                                 ; r3 = r in flonums

;;; four sets of three tests, call:
;;; (pexptsq r 2) (pexptsq r2 2) (pexptsq r3 2) 
;;; (pexptsq r 5) (pexptsq r2 5) (pexptsq r3 5)
;;; (pexptsq r 10) (pexptsq r2 10) (pexptsq r3 10)
;;; (pexptsq r 15) (pexptsq r2 15) (pexptsq r3 15)
