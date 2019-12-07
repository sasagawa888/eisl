;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     tak.lsp
;;;; Author:    Ikuo Takeuchi
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: tak.lsp,v 1.7 2013/06/18 05:21:53 jullien Exp $

;;; (2) TAK -- Variant of the Takeuchi function, function-call-heavy.

;;; call (tak 18 12 6)

(defun tak (x y z)
   (if (>= y x)
       z
       (tak (tak (- x 1) y z)
            (tak (- y 1) z x)
            (tak (- z 1) x y))))
