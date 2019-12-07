;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     fread.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: fread.lsp,v 1.7 2013/06/18 05:21:53 jullien Exp $

;;;; (20) FREAD -- Benchmark to read from a file.

(defun fread ()
   (if (not (probe-file "fprint.tst"))
       (format (standard-output)
               "Define fprint.tst by running the FPRINT benchmark!~%"))
   (let ((stream (open-input-file "fprint.tst")))
        (read stream)
        (close stream)
        t))

;;; call:  (fread)
