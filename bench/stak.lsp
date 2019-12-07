;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     stak.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: stak.lsp,v 1.7 2013/06/18 05:21:53 jullien Exp $

;;; (3) STAK -- Version of TAK that uses special binding to pass arguments.

(defdynamic stak-x ())
(defdynamic stak-y ())
(defdynamic stak-z ())

(defun stak (st-x st-y st-z)
   (setf (dynamic stak-x) st-x)
   (setf (dynamic stak-y) st-y)
   (setf (dynamic stak-z) st-z)
   (stak-aux))

(defun stak-aux ()
   (if (>= (dynamic stak-y) (dynamic stak-x))
       (dynamic stak-z)
       (dynamic-let ((stak-x (dynamic-let ((stak-x (- (dynamic stak-x) 1))
                                           (stak-y (dynamic stak-y))
                                           (stak-z (dynamic stak-z)))
                                          (stak-aux)))
                     (stak-y (dynamic-let ((stak-x (- (dynamic stak-y) 1))
                                           (stak-y (dynamic stak-z))
                                           (stak-z (dynamic stak-x)))
                                          (stak-aux)))
                     (stak-z (dynamic-let ((stak-x (- (dynamic stak-z) 1))
                                           (stak-y (dynamic stak-x))
                                           (stak-z (dynamic stak-y)))
                                          (stak-aux))))
                    (stak-aux))))

;;; call (stak 18 12 6)
