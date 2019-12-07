;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     ctak.lsp
;;;; Author:    ??
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: ctak.lsp,v 1.7 2013/06/18 05:21:53 jullien Exp $

;;; (4) CTAK -- Version of TAK that uses CATCH and THROW.

(defun ctak (x y z)
   (catch 'ctak-aux (ctak-aux x y z)))

(defun ctak-aux (x y z)
   (if (>= y x)
       (throw 'ctak-aux z)
       (ctak-aux (catch 'ctak-aux (ctak-aux (- x 1) y z))
                 (catch 'ctak-aux (ctak-aux (- y 1) z x))
                 (catch 'ctak-aux (ctak-aux (- z 1) x y)))))
