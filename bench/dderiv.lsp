;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     dderiv.lsp
;;;; Author:    Vaughan Pratt
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: dderiv.lsp,v 1.7 2013/06/18 05:21:53 jullien Exp $

;;; (13) DDERIV -- Symbolic derivative benchmark written by Vaughn Pratt.  

;;; This  benchmark  is  a  variant of the simple symbolic derivative
;;; program  (DERIV).  The  main change is that it is `table-driven.'
;;; Instead  of  using  a  large COND that branches on the CAR of the
;;; expression,  this  program  finds  the  code  that  will take the
;;; derivative  on the property list of the atom in the CAR position.
;;; So,  when the expression is (+ .  <rest>),  the code stored under
;;; the  atom '+ with indicator DERIV will take <rest> and return the
;;; derivative for '+.

;;;
;;; call (dderiv-run)
;;;

(defun dderiv-aux (a) 
   (list '/ (dderiv a) a))

(defun dderiv+ (a)
   (cons '+ (mapcar #'dderiv a)))

(defun dderiv- (a)
   (cons '- (mapcar #'dderiv a)))

(defun dderiv* (a)
   (list '* (cons '* a) (cons '+ (mapcar #'dderiv-aux a))))

(defun dderiv/ (a)
   (list '-
         (list '/ (dderiv (car a)) (cadr a))
         (list '/
               (car a)
               (list '* (cadr a) (cadr a) (dderiv (cadr a))))))

(set-property #'dderiv- '- 'dderiv)
(set-property #'dderiv* '* 'dderiv)
(set-property #'dderiv+ '+ 'dderiv)
(set-property #'dderiv/ '/ 'dderiv)

(defun dderiv (a)
   (if (consp a)
       (let ((dderiv-var (property (car a) 'dderiv)))
            (if dderiv-var
                (funcall dderiv-var (cdr a))
                'error))
       (if (eq a 'x) 1 0)))


(defun dderiv-run ()
  (for ((i 0 (+ i 1)))
       ((= i 1000))
       (dderiv '(+ (* 3 x x) (* a x x) (* b x) 5))
       (dderiv '(+ (* 3 x x) (* a x x) (* b x) 5))
       (dderiv '(+ (* 3 x x) (* a x x) (* b x) 5))
       (dderiv '(+ (* 3 x x) (* a x x) (* b x) 5))
       (dderiv '(+ (* 3 x x) (* a x x) (* b x) 5))))
