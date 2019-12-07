;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     browse.lsp
;;;; Author:    Unknown.
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: browse.lsp,v 1.8 2013/06/18 05:21:53 jullien Exp $

;;; (8) BROWSE -- Benchmark to create and browse through an AI-like
;;; data base of units.

;;; call (browse)

(defglobal browse-rand      21)
(defglobal *browse-counter* 1)

(defmacro browse-char1 (x)
   `(elt (convert ,x <string>) 0))

(defun gen-browse ()
   (setq *browse-counter* (+ *browse-counter* 1))
   (convert (string-append "g" (convert *browse-counter* <string>)) <symbol>))

(defun browse-init (nbs m npats ipats)
   ;; nbs   is # of symbols
   ;; m     is maximum amount of stuff on the plist
   ;; npats is the number of basic patterns on the unit
   ;; ipats is the instantiated copies of the patterns
   (setq browse-rand 21)
   (let ((ip (mapcar #'identity ipats))) ;; (copy-list ipats)
        (for ((p ip (cdr p)))
             ((null (cdr p)) (set-cdr ip p)))        
        (for ((n nbs (- n 1))
              (i m (if (= i 0) m (- i 1)))
              (name (gen-browse) (gen-browse))
              (a ()))
             ((= n 0) a)
             (setq a (cons name a))
             (for ((j i (- j 1)))
                  ((= j 0))
                  (set-property () name (gen-browse)))
             (set-property
                  (for ((j npats (- j 1))
                        (p ip (cdr p))
                        (x ()))
                       ((= j 0) x)
                       (setq x (cons (car p) x)))
                  name
                  'pattern)
             (for ((j (- m i) (- j 1)))
                  ((= j 0))
                  (set-property () name (gen-browse))))))

(defun browse-random ()
   (setq browse-rand (mod (* browse-rand 17) 251)))

(defun browse-randomize (l)
   (for ((a ()))
        ((null l) a)
        (let ((n (mod (browse-random) (length l))))
             (cond ((= n 0)
                    (setq a (cons (car l) a))
                    (setq l (cdr l)))
                   (t
                    (for ((i n (- i 1))
                          (x l (cdr x)))
                         ((eq i 1)
                          (setq x (cons (car (cdr x)) x))
                          (set-cdr (cdr (cdr x)) x))))))))

(defun match (pat dat alist)
   (cond ((null pat)
          (null dat))
         ((null dat) dat)
         ((or (eq (car pat) '?)
              (eq (car pat) (car dat)))
          (match (cdr pat) (cdr dat) alist))
         ((eq (car pat) '*)
          (or (match (cdr pat) dat alist)
              (match (cdr pat) (cdr dat) alist)
              (match pat (cdr dat) alist)))
         (t (if (not (consp (car pat)))
                (let ((val ()))
                     (case (browse-char1 (car pat))
                           ((#\?)
                            (setq val (assoc (car pat) alist))
                            (if val
                                (match (cons (cdr val) (cdr pat)) dat alist)
                                (match (cdr pat)
                                       (cdr dat)
                                       (cons (cons pat dat) alist))))
                           ((#\*)
                            (setq val (assoc (car pat) alist))
                            (if val
                                (match (append (cdr val) (cdr pat)) dat alist)
                                (for ((l () (append l
                                                    (cons (and d (car d)) ())))
                                      (e (cons () dat) (and e (cdr e)))
                                      (d dat (and d (cdr d))))
                                     ((or (null e)
                                          (match (cdr pat)
                                                 d
                                                 (cons (cons (car pat) l)
                                                       alist)))
                                      e))))
                           (t nil)))
                (if (consp (car dat))
                    (progn
                           (match (car pat) (car dat) alist)
                           (match (cdr pat) (cdr dat) alist)))))))

(defun browse ()
  (investigate
     (browse-randomize
        (browse-init 80 8 4 '((a a a b b b b a a a a a b b a a a)
                              (a a b b b b a a (a a) (b b))
                              (a a a b (b a) b a b a))))
     '((*a ?b *b ?b a *a a *b *a)
       (*a *b *b *a (*a) (*b))
       (? ? * (b a) * ? ?))))

(defun investigate (units patterns)
   (for ((u units (cdr u)))
        ((null u))
        (for ((pats patterns (cdr pats)))
             ((null pats))
             (for ((p (property (car u) 'pattern) (cdr p)))
                  ((null p))
                  (match (car pats) (car p) ())))))
