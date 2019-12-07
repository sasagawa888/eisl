;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     tprint.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: tprint.lsp,v 1.8 2013/06/18 05:21:53 jullien Exp $

;;; (21) TPRINT -- Benchmark to print to the terminal.

;; NOTE,  *test-atoms*  has  been  modified  to  match  ISLISP syntax
;; reader for symbols and numbers.

(defglobal *test-atoms*
          '(abc1 cde2 efg3 ghi4 ijk5 klm6 mno7 opq8 qrs9
            stu0 uvw1 wxy2 xyz3 a123 b234 c345 d456 d567
            e678 f789 g890))

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
   (let ((atcopy (mapcar #'identity atoms))) ;; (copy-list atoms)
        (for ((a atcopy (cdr a)))
             ((null (cdr a)) (set-cdr atoms a)))
        (init-aux m n atoms)))

(defglobal test-pattern (init 6 6 *test-atoms*))

;;; call:  (format (standard-output) "~s~%" test-pattern)
