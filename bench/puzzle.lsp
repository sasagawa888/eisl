;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     puzzle.lsp
;;;; Author:    Forest Baskett
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: puzzle.lsp,v 1.9 2013/06/18 05:21:53 jullien Exp $

;;; (17) PUZZLE
;;;  -- Forest Baskett's Puzzle benchmark, originally written in Pascal.

;;; call (puzzle-start)

(defconstant puzzle-size     511)
(defconstant puzzle-classmax 3)
(defconstant puzzle-typemax  12)
(defconstant puzzle-d        8)

(defglobal iii               0)
(defglobal kount             0)

(defglobal piececount        ())
(defglobal puzzle-class      ())
(defglobal piecemax          ())
(defglobal puzzle            ())
(defglobal puzzle-p          ())

(defmacro fit (x y)
   `(fit-aux ,x ,y (elt piecemax ,x)))

(defun fit-aux (i j end)
   (for ((k 0 (+ k 1)))
        ((or (> k end)
             (and (aref puzzle-p i k) (elt puzzle (+ j k))))
         (> k end))))

(defmacro place (i j)
   `(place-aux ,i ,j (elt piecemax ,i)))

(defun place-aux (i j end)
   (for ((k 0 (+ k 1)))
        ((> k end))
        (if (aref puzzle-p i k)
            (setf (elt puzzle (+ j k)) t)))
   (setf (elt piececount (elt puzzle-class i))
         (- (elt piececount (elt puzzle-class i)) 1))
   (for ((k j (+ k 1)))
        ((or (> k puzzle-size) (not (elt puzzle k)))
         (if (> k puzzle-size) 0 k))))

(defmacro puzzle-remove (i j)
   `(puzzle-remove-aux ,i ,j (elt piecemax ,i)))

(defun puzzle-remove-aux (i j end)
   (for ((k 0 (+ k 1)))
        ((> k end))
        (if (aref puzzle-p i k)
            (setf (elt puzzle (+ j k)) nil)))
   (setf (elt piececount (elt puzzle-class i))
         (+ (elt piececount (elt puzzle-class i)) 1)))

(defun trial (j k)
   (for ((i 0 (+ i 1)))
        ((or
             (> i puzzle-typemax)
             (if (not (= (elt piececount (elt puzzle-class i)) 0))
                 (cond ((fit i j)
                        (setq k (place i j))
                        (cond ((or (trial k 0) (= k 0))
                               (setq kount (+ kount 1))
                               t)
                              (t (puzzle-remove i j) ()))))))
         (if (> i puzzle-typemax)
             (progn
                    (setq kount (+ kount 1))
                    ())
             t))))

(defun definepiece (iclass ii jj kk)
   (let ((index 0))
        (for ((i 0 (+ i 1)))
             ((> i ii))
             (for ((j 0 (+ j 1)))
                  ((> j jj))
                  (for ((k 0 (+ k 1)))
                       ((> k kk))
                       (setq index (+ i (* puzzle-d (+ j (* puzzle-d k)))))
                       (setf (aref puzzle-p iii index) t))))
        (setf (elt puzzle-class iii) iclass)
        (setf (elt piecemax iii) index)
        (if (not (eq iii puzzle-typemax))
            (setq iii (+ iii 1)))))

(defun puzzle-start ()
   (setq piececount   (create-vector (+ puzzle-classmax 1) 0))
   (setq puzzle-class (create-vector (+ puzzle-typemax  1) 0))
   (setq piecemax     (create-vector (+ puzzle-typemax  1) 0))
   (setq puzzle       (create-vector (+ puzzle-size     1) 0))
   (setq puzzle-p     (create-array  (list
                                           (+ puzzle-typemax 1)
                                           (+ puzzle-size    1))
                                     0))
   (for ((m 0 (+ m 1)))
        ((> m puzzle-size))
        (setf (elt puzzle m) t))
   (for ((i 1 (+ i 1)))
        ((> i 5))
        (for ((j 1 (+ j 1)))
             ((> j 5))
             (for ((k 1 (+ k 1)))
                  ((> k 5))
                  (setf (elt puzzle (+ i (* puzzle-d (+ j (* puzzle-d k)))))
                        nil))))
   (for ((i 0 (+ i 1)))
        ((> i puzzle-typemax))
        (for ((m 0 (+ m 1)))
             ((> m puzzle-size))
             (setf (aref puzzle-p i m) nil)))

   (setq iii 0)
   (definePiece 0 3 1 0)
   (definePiece 0 1 0 3)
   (definePiece 0 0 3 1)
   (definePiece 0 1 3 0)
   (definePiece 0 3 0 1)
   (definePiece 0 0 1 3)
  
   (definePiece 1 2 0 0)
   (definePiece 1 0 2 0)
   (definePiece 1 0 0 2)
  
   (definePiece 2 1 1 0)
   (definePiece 2 1 0 1)
   (definePiece 2 0 1 1)
  
   (definePiece 3 1 1 1)
  
   (setf (elt pieceCount 0) 13)
   (setf (elt pieceCount 1)  3)
   (setf (elt pieceCount 2)  1)
   (setf (elt pieceCount 3)  1)

   (setq kount 0)

   (let ((m (+ (* puzzle-d (+ puzzle-d 1)) 1)) (n 0))
        (if (fit 0 m)
            (setq n (place 0 m))
            (format (standard-output) "Error.~%"))
        (if (trial n 0)
            kount
            (format (standard-output) "Failure.~%"))))
