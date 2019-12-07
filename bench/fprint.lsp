;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     fprint.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: fprint.lsp,v 1.8 2013/06/18 05:21:53 jullien Exp $

;;; (19) FPRINT -- Benchmark to print to a file.

;; NOTE,  *test-atoms*  has  been  modified  to  match  ISLISP syntax
;; reader for symbols and numbers.

(defglobal *test-atoms*
           '(abcdef12 cdefgh23 efghij34 ghijkl45 ijklmn56 klmnop67 
             mnopqr78 opqrst89 qrstuv90 stuvwx01 uvwxyz12 
             wxyzab23 xyzabc34 _23456ab [34567bc {45678cd 
             <56789de >67890xf ]78901fg }89012gh *90123hi))

(defun init-aux (m n atoms)
   (cond ((= m 0)
          (car atoms))
         (t (for ((i n (- i 2))
                  (a ()))
                 ((< i 1) a)
                 (setf a (cons (car atoms) a))
                 (setf atoms (cdr atoms))
                 (setf a (cons (init-aux (- m 1) n atoms) a))))))

(defun init (m n atoms)
   (let ((at (mapcar #'identity atoms))) ;; (copy-list atoms)
        (for ((a at (cdr a)))
             ((null (cdr a)) (set-cdr at a)))
        (init-aux m n at)))

(defglobal test-pattern (init 6 6 *test-atoms*))

(defun fprint ()
   (let ((stream (open-output-file "fprint.tst")))
        (format stream "~S~%" test-pattern)
        (close stream)
        t))

;;; call:  (fprint)
