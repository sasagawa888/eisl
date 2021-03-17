;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     fib20.lsp
;;;; Author:    C. Jullien
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: fib20.lsp,v 1.8 2013/06/18 05:21:53 jullien Exp $

;;; (1) FIB -- The Fibonnacci Function.
;;; This test is not part of initial Gabriel's Benchmarks.

;; call (fib 20)

(defun fib (n)
   (cond ((= n 1) 1)
         ((= n 2) 1)
         (t (+ (fib (- n 1)) (fib (- n 2))))))

(defgeneric gfib (n)
   (:method ((n <integer>))
      (cond ((= n 1) 1)
            ((= n 2) 1)
            (t (+ (gfib (- n 1)) (gfib (- n 2)))))))
