;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     deriv.lsp
;;;; Author:    Vaughan Pratt
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: deriv.lsp,v 1.7 2013/06/18 05:21:53 jullien Exp $

;;; (12) DERIV -- Symbolic derivative benchmark written by Vaughn Pratt.  
;;; It uses a simple subset of Lisp and does a lot of CONSing. 

;;; call (deriv-run)

(defun deriv-aux (a) (list '/ (deriv a) a))

(defun deriv (a)
   (cond 
         ((not (consp a))
          (if (eq a 'x) 1 0))
         ((eq (car a) '*)
          (list '* a (cons '+ (mapcar #'deriv-aux (cdr a)))))
         ((eq (car a) '+)       
          (cons '+ (mapcar #'deriv (cdr a))))
         ((eq (car a) '-) 
          (cons '- (mapcar #'deriv (cdr a))))
         ((eq (car a) '/)
          (list '-
                (list '/ (deriv (cadr a)) (caddr a))
                (list '/
                      (cadr a)
                      (list '* (caddr a) (caddr a) (deriv (caddr a))))))
         (t 'error)))

(defun deriv-run ()
   (for ((i 0 (+ i 1)))
        ((= i 1000))
        (deriv '(+ (* 3 x x) (* a x x) (* b x) 5))
        (deriv '(+ (* 3 x x) (* a x x) (* b x) 5))
        (deriv '(+ (* 3 x x) (* a x x) (* b x) 5))
        (deriv '(+ (* 3 x x) (* a x x) (* b x) 5))
        (deriv '(+ (* 3 x x) (* a x x) (* b x) 5))))
