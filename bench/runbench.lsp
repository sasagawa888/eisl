;;;; -*-Mode: LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     runbench.lsp
;;;; Author:    C. Jullien
;;;; License:   New BSD license
;;;; CVS:       $Id: runbench.lsp,v 1.7 2013/06/18 05:21:53 jullien Exp $

;;; Run Gabriel's benchmarks for ISLISP.

;;;
;;; Please, send bug reports to jullien@eligis.com
;;;

(defglobal *extension*  (or (ignore-errors *cpext*) ".lsp")) ;; .ibc, .lap ...
(defglobal *result*     nil)
(defglobal *total-time* 0.0)
(defglobal *largeint*   (parse-number "#x7fffffffffffffffffff"))
(defglobal *bignum*     (and (integerp *largeint*)
                             (> *largeint* 0)
                             (eql (isqrt *largeint*) 100000)))
(defglobal *bignum* 12345678901234567890)

(defun bench-file (bench)
   (string-append "bench/" bench *extension*))

(defun format-time (time)
   ;; format time '3.3'
   (let ((str (convert time <string>))
         (pos 0))
        (for ((l (convert str <list>) (cdr l))
              (i 0 (+ i 1)))
             ((or (null l) (char= (car l) #\.)) (setq pos i)))
        (setq str (string-append (create-string (- 3 pos) #\space) str))
        (if (< (length str) 7)
            (string-append str (create-string (- 7 (length str)) #\0))
            str)))

(defmacro elapsed-time (form)
   ;; returns the elapsed time to compute this form.
   `(let ((time (get-internal-run-time)))
         (setq *result* ,form)
         (quotient (- (get-internal-run-time) time)
                   (internal-time-units-per-second))))

(defmacro bench (test name exp expect)
  ;; run a bench and display the elapsed time.
  `(let ((time nil)
         (name ,name))
        (setq time         (convert (elapsed-time ,exp) <float>))
        (setq *total-time* (+ *total-time* time))
        (format (standard-output)
                "Test ~A: ~A~A-> ~A, time = ~As.~%"
                ,test
                name
                (create-string (- 8 (length name)))
                (if (equal *result* ,expect) "ok" *result*)
                (format-time time))))


(format (standard-output) "~%")
;(gbc nil)
;;; (1) FIB
(load (bench-file "fib20"))
(bench "01" "Fib" (fib 20) 6765)

;;; (2) TAK
(load (bench-file "tak"))
(bench "02" "Tak" (tak 18 12 6) 7)

;;; (3) STAK
(load (bench-file "stak"))
(bench "03" "Stak" (stak 18 12 6) 7)

;;; (4) CTAK
(load (bench-file "ctak"))
(bench "04" "Ctak" (ctak 18 12 6) 7)

;;; (5) TAKL
(load (bench-file "takl"))
(bench "05" "Takl" (takl ll-18 ll-12 ll-6) '(7 6 5 4 3 2 1))

;;; (6) TAKR
(load (bench-file "takr"))
(bench "06" "Takr" (takr 18 12 6) 7)

;;; (7) BOYER
(load (bench-file "boyer"))
(bench "07" "Boyer" (boyer) nil)

;;; (8) BROWSE
;(load (bench-file "browse"))
;(bench "08" "Browse" (browse) ())

;;; (9) DESTRU
;(gbc)
(load (bench-file "destru"))
(bench "09" "Destru" (destructive 600 50) ())

;;; (10) TRAVINI
;(gbc)
;(load (bench-file "traverse"))
;(bench "10" "Travini" (init-traverse) ())

;;; (11) TRAVRUN
;(gbc)
;(bench "11" "Travrun" (run-traverse) ())

;;; (12) DERIV
(load (bench-file "deriv"))
(bench "12" "Deriv" (deriv-run) ())

;;; (13) DDERIV
(load (bench-file "dderiv"))
(bench "13" "Dderiv" (dderiv-run) ())

;;; (14-15) DIV2
(load (bench-file "div2"))
(bench "14" "Divit" (test-1 *ll*) ())
(bench "15" "Divrec" (test-2 *ll*) ())

;;; (16) FFT
(load (bench-file "fft"))
(bench "16" "FFT" (fft-bench) ())

;;; (17) PUZZLE
(load (bench-file "puzzle"))
(bench "17" "Puzzle" (puzzle-start) 2005)

;;; (18) TRIANG
;(gbc)
;(load (bench-file "triang"))
;(bench "18" "Triang" (gogogo 22) ())

;;; (19) FPRINT
(load (bench-file "fprint"))
(bench "19" "Fprint" (fprint) t)

;;; (20) FREAD
(load (bench-file "fread"))
(bench "20" "Fread" (fread) t)

;;; (21) TPRINT
(load (bench-file "tprint"))
(bench "21" "Tprint"
       (let ((so (create-string-output-stream)))
            (format so "~s" test-pattern)
            (close so)
            t)
       t)

;;; (22) FRPOLY

;;; When implementation has no BIGNUMS, only tests for r and r3 are run.
#|
(load (bench-file "frpoly"))
(bench "22" "Frpoly" (mapc (lambda (n)
                                          (pexptsq r  n)
                             (if *bignum* (pexptsq r2 n))
                                          (pexptsq r3 n))
                          '(2 5 10 15))
                     '(2 5 10 15))
|#
(format (standard-output) "~%Total ~As.~%~%" (format-time *total-time*))

