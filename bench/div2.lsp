;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     div2.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: div2.lsp,v 1.8 2013/06/18 05:21:53 jullien Exp $

;;; (14-15) DIV2 -- Benchmark which divides by 2 using lists of n ()'s.
;;; This file contains a recursive as well as an iterative test.

;;; call (test-1 *ll*)
;;; call (test-2 *ll*)

(defun create-n (len)
  (for ((n len (- n 1))
        (a () (cons () a)))
       ((= n 0) a)))

(defglobal *ll* (create-n 200))

(defun iterative-div2 (lst)
   (for ((l lst (cdr (cdr l)))
         (a () (cons (car l) a)))
        ((null l) a)))

(defun recursive-div2 (l)
   (and l
        (cons (car l) (recursive-div2 (cdr (cdr l))))))

(defun test-1 (l)
   (for ((i 300 (- i 1)))
        ((= i 0))
        (iterative-div2 l)
        (iterative-div2 l)
        (iterative-div2 l)
        (iterative-div2 l)))

(defun test-2 (l)
   (for ((i 300 (- i 1)))
        ((= i 0))
        (recursive-div2 l)
        (recursive-div2 l)
        (recursive-div2 l)
        (recursive-div2 l)))
