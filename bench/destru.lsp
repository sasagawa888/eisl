;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     destru.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: destru.lsp,v 1.8 2013/06/18 05:21:53 jullien Exp $

;;; (9) DESTRU -- Destructive operation benchmark.
                        
(defun destructive (n m)
   (let ((l (for ((i 10 (- i 1))
                  (a () (cons () a)))
                 ((= i 0) a))))
        (for ((i n (- i 1)))
             ((= i 0))
             (if (null (car l))
                 (for ((p l (cdr p)))
                      ((null p))
                      (or (car p)
                          (set-car (cons () ()) p))
                      (append (car p)
                              (for ((j m (- j 1))
                                    (x () (cons () x)))
                                   ((= j 0) x))))
                 (for ((l1 l (cdr l1))
                       (l2 (cdr l) (cdr l2)))
                      ((null l2))
                      (set-cdr (let ((k (div (length (car l1)) 2))
                                     (x nil))
                                    (cond ((= k 0)
                                           (set-car () l1)
                                           (car l1))
                                          (t
                                             (for ((j k (- j 1))
                                                   (a (car l1) (cdr a)))
                                                  ((eq j 1)
                                                   (setq x (cdr a))
                                                   (set-cdr () a)
                                                   x)
                                                  (set-car i a)))))
                               (for ((j (div (length (car l2)) 2) (- j 1))
                                     (a (car l2) (cdr a)))
                                        ((= j 0) a)
                                        (set-car i a))))))))

;; call (destructive 600 50)
