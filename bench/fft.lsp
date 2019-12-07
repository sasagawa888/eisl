;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     fft.lsp
;;;; Author:    Harry Barrow
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: fft.lsp,v 1.11 2013/06/18 05:21:53 jullien Exp $

;;; (16) FFT -- This is an FFT benchmark written by Harry Barrow.
;;; It tests a variety of floating point operations, including array references.

(defconstant pi    3.1415926535)
(defconstant +re+  (create-vector 1025 0.0))
(defconstant +im+  (create-vector 1025 0.0))

(defglobal nur   nil)
(defglobal nui   nil)
(defglobal verif nil)

(defun ipower (a b) 
   ;; b always > 0
   (if (= b 1)
       a
       (* (ipower a (- b 1)) a)))

(defun fft (ar ai)
   (let ((n (- (length ar) 1)))
     (let ((nv2 (div n 2)) ; (div x 2) = (floor x 2)
           (m 0)
           (i 1)
           (j nil))
       (while (< i n)
              (setq m (+ m 1))
              (setq i (+ i i)))
       (if (not (= n (ipower 2 m)))
           (progn
                  (format (standard-output)
                          "error ... array size not a power of two.~%")
                  (read)
                  (format-fresh-line (standard-output)))
           (progn
              ;; interchange elements in bit-reversed order
              (setq j 1)
              (setq i 1)
              (while (< i n)
                     (if (< i j)
                         (let ((tr (elt ar j))
                               (ti (elt ai j)))
                              (set-elt (elt ar i) ar j)
                              (set-elt (elt ai i) ai j)
                              (set-elt tr ar i)
                              (set-elt ti ai i)))
                     (let ((k nv2))
                          (while (< k j)
                                 (setq j (- j k))
                                 (setq k (div k 2)))
                          (setq j (+ j k))
                          (setq i (+ i 1))))
              (let ((l 1))
               (while (<= l m)
                (let ((l2 (ipower 2 l))
                      (ur 1.0)
                      (ui 0.0))
                  (let* ((le1 (div l2 2))
                         (wr (cos (quotient pi (float le1))))
                         (wi (sin (quotient pi (float le1)))))
                    (let ((k 1))
                      (while (<= k le1)
                        (let ((p k))
                          (while (<= p n)
                            (let ((ip (+ p le1)))
                              (let ((tr (- (* (elt ar ip) ur)
                                           (* (elt ai ip) ui)))
                                    (ti (+ (* (elt ar ip) ur)
                                           (* (elt ai ip) ui))))
                                (set-elt (- (elt ar p) tr) ar ip)
                                (set-elt (- (elt ai p) ti) ai ip)
                                (set-elt (+ (elt ar p) tr) ar p)
                                (set-elt (+ (elt ai p) ti) ai p) ))
                            (setq p (+ p l2)) ))
                        (setq k (+ k 1)) ))
                    (setq nur (- (* ur wr) (* ui wi)))
                    (setq nui (+ (* ur wi) (* ui wr)))
                    (setq ur  nur)
                    (setq ui  nui)
                    (if verif
                        (format (standard-output)
                                "End of DO: ur=~S, ui=~S~%" ur ui))))
                (setq l (+ l 1))) );do
        ))))
  t)

;;; the timer which does 10 calls on fft

(defun fft-bench ()
  (for ((i 0 (+ i 1)))
       ((= i 10))
       (fft +re+ +im+)))

(defun fft-test ()
   (setq verif t)
   (fft +re+ +im+)
   (format (standard-output) "Compare results with the following references:~%")
   (format (standard-output) "End of DO: ur=-1.0, ui=1.509958e-07~%")
   (format (standard-output) "End of DO: ur=7.549789e-08, ui=1.0~%")
   (format (standard-output) "End of DO: ur=0.7071068, ui=0.7071067~%")
   (format (standard-output) "End of DO: ur=0.9238795, ui=0.3826834~%")
   (format (standard-output) "End of DO: ur=0.9807853, ui=0.1950903~%")
   (format (standard-output) "End of DO: ur=0.9951847, ui=0.09801713~%")
   (format (standard-output) "End of DO: ur=0.9987954, ui=0.04906767~%")
   (format (standard-output) "End of DO: ur=0.9996988, ui=0.02454123~%")
   (format (standard-output) "End of DO: ur=0.9999247, ui=0.01227154~%")
   (format (standard-output) "End of DO: ur=0.9999812, ui=0.006135884~%")
   (setq verif nil))

;;; call:  (fft-bench)
;;; test:  (fft-test)
