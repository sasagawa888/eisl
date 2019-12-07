;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     traverse.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: traverse.lsp,v 1.10 2013/06/18 05:21:53 jullien Exp $

;;; (10-11) TRAVERSE --  Benchmark which creates and traverses a tree structure.

#|
(defstruct node
    (parents ())
    (sons    ())
    (sn      (snb))
    (entry1  ())
    (entry2  ())
    (entry3  ())
    (entry4  ())
    (entry5  ())
    (entry6  ())
    (mark    ()))
|#

(defmacro node-parents (x) `(elt ,x 0))
(defmacro node-sons    (x) `(elt ,x 1))
(defmacro node-sn      (x) `(elt ,x 2))
(defmacro node-entry1  (x) `(elt ,x 3))
(defmacro node-entry2  (x) `(elt ,x 4))
(defmacro node-entry3  (x) `(elt ,x 5))
(defmacro node-entry4  (x) `(elt ,x 6))
(defmacro node-entry5  (x) `(elt ,x 7))
(defmacro node-entry6  (x) `(elt ,x 8))
(defmacro node-mark    (x) `(elt ,x 9))

(defun make-node ()
   (let ((x (create-vector 10 nil)))
        (setf (node-sn x) (snb))
        x))

(defglobal traverse-sn     0)
(defglobal traverse-rand   21)
(defglobal traverse-marker nil)
(defglobal traverse-root   nil)

(defdynamic traverse-count  0)

(defun snb ()
   (setq traverse-sn (+ traverse-sn 1)))

(defun traverse-seed ()
   (setq traverse-rand 21))

(defun traverse-random ()
   (setq traverse-rand (mod (* traverse-rand 17) 251)))

(defun traverse-remove (n q)
   (let ((res nil))
        (cond ((eq (cdr (car q)) (car q))
               (setq res (car (car q)))
               (setf (car q) ())
               res)
              ((= n 0)
               (setf res (car (car q)))
               (for ((p (car q) (cdr p)))
                    ((eq (cdr p) (car q))
                     (setf (car q)
                           (setf (cdr p) (cdr (car q))))))
               res)
              (t (for ((i n (- i 1))
                       (x (car q) (cdr x))
                       (p (cdr (car q)) (cdr p)))
                      ((= i 0)
                       (progn
                              (setq res (car x))
                              (setf (cdr x) p)
                              res)))))))

(defun traverse-select (n q)
   (for ((i n (- i 1))
         (x (car q) (cdr x)))
        ((= i 0) (car x))))

(defun traverse-add (a q)
   (cond
         ((null q)
          `(,(let ((x `(,a)))
                  (setf (cdr x) x)
                  x)))
         ((null (car q))
          (let ((x `(,a)))
               (setf (cdr x) x)
               (setf (car q) x)))
         (t (setf (car q) (setf (cdr (car q)) `(,a .,(cdr (car q))))))))

(defun traverse-create-structure (n)
   (let ((a `(,(make-node))))
        (for ((m (- n 1) (- m 1))
              (p a))
             ((eq m 0)
              (setq a `(,(setf (cdr p) a)))
              (for ((unused a)
                    (used (traverse-add (traverse-remove 0 a) ()))
                    (x nil)
                    (y nil))
                   ((null (car unused))
                    (find-root (traverse-select 0 used) n))
                   (setq x (traverse-remove (mod (traverse-random) n) unused))
                   (setq y (traverse-select (mod (traverse-random) n) used))
                   (traverse-add x used)
                   (setf (node-sons y) `(,x .,(node-sons y)))
                   (setf (node-parents x) `(,y .,(node-parents x))) ))
             (setq a (cons (make-node) a)))))

(defun find-root (node size)
   (for ((n size (- n 1)))
        ((or (= n 0) (null (node-parents node))) node)
        (setq node (car (node-parents node)))))

(defun travers (node mark)
;; (the <general-vector> node)
   (cond
         ((eq (node-mark node) mark) ())
         (t (setf (node-mark node) mark)
            (setf (dynamic traverse-count) (+ (dynamic traverse-count) 1))
            (setf (node-entry1 node) (not (node-entry1 node)))
            (setf (node-entry2 node) (not (node-entry2 node)))
            (setf (node-entry3 node) (not (node-entry3 node)))
            (setf (node-entry4 node) (not (node-entry4 node)))
            (setf (node-entry5 node) (not (node-entry5 node)))
            (setf (node-entry6 node) (not (node-entry6 node)))
            (for ((sons (node-sons node) (cdr sons)))
                 ((null sons) ())
                 (travers (car sons) mark)))))

(defun traverse (root)
   (dynamic-let ((traverse-count 0))
                (travers root
                         (setq traverse-marker (not traverse-marker)))
                (dynamic traverse-count)))

(defun init-traverse ()
   (setq traverse-root (traverse-create-structure 100))
   nil)

(defun run-traverse ()
   (for ((i 50 (- i 1)))
        ((= i 0))
        (traverse traverse-root)
        (traverse traverse-root)
        (traverse traverse-root)
        (traverse traverse-root)
        (traverse traverse-root)))

;;; to initialize, call:  (init-traverse)
;;; to run traverse, call:  (run-traverse)
