;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     cpbench.lsp
;;;; Author:    C. Jullien
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: cpbench.lsp,v 1.8 2013/06/18 05:21:53 jullien Exp $

;;;
;;; Compiles Gabriel's benchmarks.
;;;

(format (standard-output) ";; Gabriel's benchmark suite for ISLISP.~%")

(defglobal *gabriel-files* '(
        "boyer"
        "browse"
        "ctak"
        "dderiv"
        "deriv"
        "destru"
        "div2"
        "fft"
        "fib20"
        "fprint"
        "fread"
        "frpoly"
        "puzzle"
        "stak"
        "tak"
        "takl"
        "takr"
        "tprint"
        "traverse"
        "triang"
))

(mapc (lambda (x)
         (format (standard-output) ";; compiling ~A ..~%" x)
         (setq x (string-append "bench/" x ".lsp"))
         (compile-file x)) ;;modify for EISL
      *gabriel-files*)
