;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     takl.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: takl.lsp,v 1.7 2013/06/18 05:21:53 jullien Exp $

;;; (5) TAKL -- Like TAK, but without any explicit arithmetic.

;;; call (takl ll-18 ll-12 ll-6)

(defun listn (n)
   (if (not (= 0 n))
       (cons n (listn (- n 1)))))

(defconstant ll-18 (listn 18))
(defconstant ll-12 (listn 12))
(defconstant ll-6  (listn 6))

(defmacro shorterp (x y)
   `(< (length ,x) (length ,y)))

(defun takl (x y z)
   (if (not (shorterp y x))
       z
       (takl (takl (cdr x) y z)
             (takl (cdr y) z x)
             (takl (cdr z) x y))))

;;; call: (takl ll-18 ll-12 ll-6)
