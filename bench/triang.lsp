;;;; LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     triang.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: triang.lsp,v 1.10 2013/06/18 05:21:53 jullien Exp $

;;;; (18) TRIANG -- Board game benchmark.

;; call       (gogogo 22)

(defconstant triang-board    (create-vector 16 1))

(defconstant triang-sequence (create-vector 14 0))

(defconstant triang-a
  #( 1  2  4  3  5  6  1  3  6  2  5  4 11 12 13  7  8  4  4  7 11  8 12 13
     6 10 15  9 14 13 13 14 15  9 10  6  6))

(defconstant triang-b
  #( 2  4  7  5  8  9  3  6 10  5  9  8 12 13 14  8  9  5  2  4  7  5  8  9
     3  6 10  5  9  8 12 13 14  8  9  5  5))

(defconstant triang-c
  #( 4  7 11  8 12 13  6 10 15  9 14 13 13 14 15  9 10  6  1  2  4  3  5  6
     1  3  6  2  5  4 11 12 13  7  8  4  4))

(defdynamic triang-answer ())

(defdynamic triang-final ())

(setf (elt triang-board 5) 0)

(defun triang-last-position ()
   (for ((i 1 (+ i 1)))
        ((or (= i 16)
             (= (elt triang-board i) 1))
             (if (= i 16) 0 i))))

(defun triang-try (i depth)
   (cond
         ((= depth 14)
          (let ((lp (triang-last-position)))
               (if (not (member lp (dynamic triang-final)))
                   (setf (dynamic triang-final)
                         (cons lp (dynamic triang-final)))))
          (setf (dynamic triang-answer)
                (cons (dynamic triang-answer)
                      (cdr (convert triang-sequence <list>))))
          t)
         ((and (= 1 (elt triang-board (elt triang-a i)))
               (= 1 (elt triang-board (elt triang-b i)))
               (= 0 (elt triang-board (elt triang-c i))))
          (setf (elt triang-board (elt triang-a i)) 0)
          (setf (elt triang-board (elt triang-b i)) 0)
          (setf (elt triang-board (elt triang-c i)) 1)
          (setf (elt triang-sequence depth) i)
          (for ((j 0 (+ j 1))
                (d (+ depth 1)))
               ((or (= j 36)
                    (triang-try j d))))
          (setf (elt triang-board (elt triang-a i)) 1)
          (setf (elt triang-board (elt triang-b i)) 1)
          (setf (elt triang-board (elt triang-c i)) 0)
          ())))

(defun gogogo (i)
   (dynamic-let ((triang-answer ())
                 (triang-final  ()))
                (triang-try i 1)))

;;; call:  (gogogo 22)
