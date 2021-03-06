;;;; -*-Mode:LISP; Package:LISP; Base:10; Syntax:ISLISP -*-
;;;; Title:     takr.lsp
;;;; Author:    Richard Gabriel
;;;; License:   New BSD license
;;;; ISLISP:    Yes
;;;; CVS:       $Id: takr.lsp,v 1.7 2013/06/18 05:21:53 jullien Exp $

;;; (6)  TAKR  --  100  versions  of  TAK  that tries to defeat cache
;;; memory  effects.  Results  should be the same as for TAK on stack
;;; machines. Distribution of calls is not completely flat.

;;; call (takr 18 12 6)

(defun takr (x y z)
   (cond ((>= y x) z)
         (t (tak1 (tak37 (- x 1) y z)
                  (tak11 (- y 1) z x)
                  (tak17 (- z 1) x y)))))
(defun tak1 (x y z)
   (cond ((>= y x) z)
         (t (tak2 (tak74 (- x 1) y z)
                  (tak22 (- y 1) z x)
                  (tak34 (- z 1) x y)))))
(defun tak2 (x y z)
   (cond ((>= y x) z)
         (t (tak3 (tak11 (- x 1) y z)
                  (tak33 (- y 1) z x)
                  (tak51 (- z 1) x y)))))
(defun tak3 (x y z)
   (cond ((>= y x) z)
         (t (tak4 (tak48 (- x 1) y z)
                  (tak44 (- y 1) z x)
                  (tak68 (- z 1) x y)))))
(defun tak4 (x y z)
   (cond ((>= y x) z)
         (t (tak5 (tak85 (- x 1) y z)
                  (tak55 (- y 1) z x)
                  (tak85 (- z 1) x y)))))
(defun tak5 (x y z)
   (cond ((>= y x) z)
         (t (tak6 (tak22 (- x 1) y z)
                  (tak66 (- y 1) z x)
                  (tak2 (- z 1) x y)))))
(defun tak6 (x y z)
   (cond ((>= y x) z)
         (t (tak7 (tak59 (- x 1) y z)
                  (tak77 (- y 1) z x)
                  (tak19 (- z 1) x y)))))
(defun tak7 (x y z)
   (cond ((>= y x) z)
         (t (tak8 (tak96 (- x 1) y z)
                  (tak88 (- y 1) z x)
                  (tak36 (- z 1) x y)))))
(defun tak8 (x y z)
   (cond ((>= y x) z)
         (t (tak9 (tak33 (- x 1) y z)
                  (tak99 (- y 1) z x)
                  (tak53 (- z 1) x y)))))
(defun tak9 (x y z)
   (cond ((>= y x) z)
         (t (tak10 (tak70 (- x 1) y z)
                   (tak10 (- y 1) z x)
                   (tak70 (- z 1) x y)))))
(defun tak10 (x y z)
   (cond ((>= y x) z)
         (t (tak11 (tak7 (- x 1) y z)
                   (tak21 (- y 1) z x)
                   (tak87 (- z 1) x y)))))
(defun tak11 (x y z)
   (cond ((>= y x) z)
         (t (tak12 (tak44 (- x 1) y z)
                   (tak32 (- y 1) z x)
                   (tak4 (- z 1) x y)))))
(defun tak12 (x y z)
   (cond ((>= y x) z)
         (t (tak13 (tak81 (- x 1) y z)
                   (tak43 (- y 1) z x)
                   (tak21 (- z 1) x y)))))
(defun tak13 (x y z)
   (cond ((>= y x) z)
         (t (tak14 (tak18 (- x 1) y z)
                   (tak54 (- y 1) z x)
                   (tak38 (- z 1) x y)))))
(defun tak14 (x y z)
   (cond ((>= y x) z)
         (t (tak15 (tak55 (- x 1) y z)
                   (tak65 (- y 1) z x)
                   (tak55 (- z 1) x y)))))
(defun tak15 (x y z)
   (cond ((>= y x) z)
         (t (tak16 (tak92 (- x 1) y z)
                   (tak76 (- y 1) z x)
                   (tak72 (- z 1) x y)))))
(defun tak16 (x y z)
   (cond ((>= y x) z)
         (t (tak17 (tak29 (- x 1) y z)
                   (tak87 (- y 1) z x)
                   (tak89 (- z 1) x y)))))
(defun tak17 (x y z)
   (cond ((>= y x) z)
         (t (tak18 (tak66 (- x 1) y z)
                   (tak98 (- y 1) z x)
                   (tak6 (- z 1) x y)))))
(defun tak18 (x y z)
   (cond ((>= y x) z)
         (t (tak19 (tak3 (- x 1) y z)
                   (tak9 (- y 1) z x)
                   (tak23 (- z 1) x y)))))
(defun tak19 (x y z)
   (cond ((>= y x) z)
         (t (tak20 (tak40 (- x 1) y z)
                   (tak20 (- y 1) z x)
                   (tak40 (- z 1) x y)))))
(defun tak20 (x y z)
   (cond ((>= y x) z)
         (t (tak21 (tak77 (- x 1) y z)
                   (tak31 (- y 1) z x)
                   (tak57 (- z 1) x y)))))
(defun tak21 (x y z)
   (cond ((>= y x) z)
         (t (tak22 (tak14 (- x 1) y z)
                   (tak42 (- y 1) z x)
                   (tak74 (- z 1) x y)))))
(defun tak22 (x y z)
   (cond ((>= y x) z)
         (t (tak23 (tak51 (- x 1) y z)
                   (tak53 (- y 1) z x)
                   (tak91 (- z 1) x y)))))
(defun tak23 (x y z)
   (cond ((>= y x) z)
         (t (tak24 (tak88 (- x 1) y z)
                   (tak64 (- y 1) z x)
                   (tak8 (- z 1) x y)))))
(defun tak24 (x y z)
   (cond ((>= y x) z)
         (t (tak25 (tak25 (- x 1) y z)
                   (tak75 (- y 1) z x)
                   (tak25 (- z 1) x y)))))
(defun tak25 (x y z)
   (cond ((>= y x) z)
         (t (tak26 (tak62 (- x 1) y z)
                   (tak86 (- y 1) z x)
                   (tak42 (- z 1) x y)))))
(defun tak26 (x y z)
   (cond ((>= y x) z)
         (t (tak27 (tak99 (- x 1) y z)
                   (tak97 (- y 1) z x)
                   (tak59 (- z 1) x y)))))
(defun tak27 (x y z)
   (cond ((>= y x) z)
         (t (tak28 (tak36 (- x 1) y z)
                   (tak8 (- y 1) z x)
                   (tak76 (- z 1) x y)))))
(defun tak28 (x y z)
   (cond ((>= y x) z)
         (t (tak29 (tak73 (- x 1) y z)
                   (tak19 (- y 1) z x)
                   (tak93 (- z 1) x y)))))
(defun tak29 (x y z)
   (cond ((>= y x) z)
         (t (tak30 (tak10 (- x 1) y z)
                   (tak30 (- y 1) z x)
                   (tak10 (- z 1) x y)))))
(defun tak30 (x y z)
   (cond ((>= y x) z)
         (t (tak31 (tak47 (- x 1) y z)
                   (tak41 (- y 1) z x)
                   (tak27 (- z 1) x y)))))
(defun tak31 (x y z)
   (cond ((>= y x) z)
         (t (tak32 (tak84 (- x 1) y z)
                   (tak52 (- y 1) z x)
                   (tak44 (- z 1) x y)))))
(defun tak32 (x y z)
   (cond ((>= y x) z)
         (t (tak33 (tak21 (- x 1) y z)
                   (tak63 (- y 1) z x)
                   (tak61 (- z 1) x y)))))
(defun tak33 (x y z)
   (cond ((>= y x) z)
         (t (tak34 (tak58 (- x 1) y z)
                   (tak74 (- y 1) z x)
                   (tak78 (- z 1) x y)))))
(defun tak34 (x y z)
   (cond ((>= y x) z)
         (t (tak35 (tak95 (- x 1) y z)
                   (tak85 (- y 1) z x)
                   (tak95 (- z 1) x y)))))
(defun tak35 (x y z)
   (cond ((>= y x) z)
         (t (tak36 (tak32 (- x 1) y z)
                   (tak96 (- y 1) z x)
                   (tak12 (- z 1) x y)))))
(defun tak36 (x y z)
   (cond ((>= y x) z)
         (t (tak37 (tak69 (- x 1) y z)
                   (tak7 (- y 1) z x)
                   (tak29 (- z 1) x y)))))
(defun tak37 (x y z)
   (cond ((>= y x) z)
         (t (tak38 (tak6 (- x 1) y z)
                   (tak18 (- y 1) z x)
                   (tak46 (- z 1) x y)))))
(defun tak38 (x y z)
   (cond ((>= y x) z)
         (t (tak39 (tak43 (- x 1) y z)
                   (tak29 (- y 1) z x)
                   (tak63 (- z 1) x y)))))
(defun tak39 (x y z)
   (cond ((>= y x) z)
         (t (tak40 (tak80 (- x 1) y z)
                   (tak40 (- y 1) z x)
                   (tak80 (- z 1) x y)))))
(defun tak40 (x y z)
   (cond ((>= y x) z)
         (t (tak41 (tak17 (- x 1) y z)
                   (tak51 (- y 1) z x)
                   (tak97 (- z 1) x y)))))
(defun tak41 (x y z)
   (cond ((>= y x) z)
         (t (tak42 (tak54 (- x 1) y z)
                   (tak62 (- y 1) z x)
                   (tak14 (- z 1) x y)))))
(defun tak42 (x y z)
   (cond ((>= y x) z)
         (t (tak43 (tak91 (- x 1) y z)
                   (tak73 (- y 1) z x)
                   (tak31 (- z 1) x y)))))
(defun tak43 (x y z)
   (cond ((>= y x) z)
         (t (tak44 (tak28 (- x 1) y z)
                   (tak84 (- y 1) z x)
                   (tak48 (- z 1) x y)))))
(defun tak44 (x y z)
   (cond ((>= y x) z)
         (t (tak45 (tak65 (- x 1) y z)
                   (tak95 (- y 1) z x)
                   (tak65 (- z 1) x y)))))
(defun tak45 (x y z)
   (cond ((>= y x) z)
         (t (tak46 (tak2 (- x 1) y z)
                   (tak6 (- y 1) z x)
                   (tak82 (- z 1) x y)))))
(defun tak46 (x y z)
   (cond ((>= y x) z)
         (t (tak47 (tak39 (- x 1) y z)
                   (tak17 (- y 1) z x)
                   (tak99 (- z 1) x y)))))
(defun tak47 (x y z)
   (cond ((>= y x) z)
         (t (tak48 (tak76 (- x 1) y z)
                   (tak28 (- y 1) z x)
                   (tak16 (- z 1) x y)))))
(defun tak48 (x y z)
   (cond ((>= y x) z)
         (t (tak49 (tak13 (- x 1) y z)
                   (tak39 (- y 1) z x)
                   (tak33 (- z 1) x y)))))
(defun tak49 (x y z)
   (cond ((>= y x) z)
         (t (tak50 (tak50 (- x 1) y z)
                   (tak50 (- y 1) z x)
                   (tak50 (- z 1) x y)))))
(defun tak50 (x y z)
   (cond ((>= y x) z)
         (t (tak51 (tak87 (- x 1) y z)
                   (tak61 (- y 1) z x)
                   (tak67 (- z 1) x y)))))
(defun tak51 (x y z)
   (cond ((>= y x) z)
         (t (tak52 (tak24 (- x 1) y z)
                   (tak72 (- y 1) z x)
                   (tak84 (- z 1) x y)))))
(defun tak52 (x y z)
   (cond ((>= y x) z)
         (t (tak53 (tak61 (- x 1) y z)
                   (tak83 (- y 1) z x)
                   (tak1 (- z 1) x y)))))
(defun tak53 (x y z)
   (cond ((>= y x) z)
         (t (tak54 (tak98 (- x 1) y z)
                   (tak94 (- y 1) z x)
                   (tak18 (- z 1) x y)))))
(defun tak54 (x y z)
   (cond ((>= y x) z)
         (t (tak55 (tak35 (- x 1) y z)
                   (tak5 (- y 1) z x)
                   (tak35 (- z 1) x y)))))
(defun tak55 (x y z)
   (cond ((>= y x) z)
         (t (tak56 (tak72 (- x 1) y z)
                   (tak16 (- y 1) z x)
                   (tak52 (- z 1) x y)))))
(defun tak56 (x y z)
   (cond ((>= y x) z)
         (t (tak57 (tak9 (- x 1) y z)
                   (tak27 (- y 1) z x)
                   (tak69 (- z 1) x y)))))
(defun tak57 (x y z)
   (cond ((>= y x) z)
         (t (tak58 (tak46 (- x 1) y z)
                   (tak38 (- y 1) z x)
                   (tak86 (- z 1) x y)))))
(defun tak58 (x y z)
   (cond ((>= y x) z)
         (t (tak59 (tak83 (- x 1) y z)
                   (tak49 (- y 1) z x)
                   (tak3 (- z 1) x y)))))
(defun tak59 (x y z)
   (cond ((>= y x) z)
         (t (tak60 (tak20 (- x 1) y z)
                   (tak60 (- y 1) z x)
                   (tak20 (- z 1) x y)))))
(defun tak60 (x y z)
   (cond ((>= y x) z)
         (t (tak61 (tak57 (- x 1) y z)
                   (tak71 (- y 1) z x)
                   (tak37 (- z 1) x y)))))
(defun tak61 (x y z)
   (cond ((>= y x) z)
         (t (tak62 (tak94 (- x 1) y z)
                   (tak82 (- y 1) z x)
                   (tak54 (- z 1) x y)))))
(defun tak62 (x y z)
   (cond ((>= y x) z)
         (t (tak63 (tak31 (- x 1) y z)
                   (tak93 (- y 1) z x)
                   (tak71 (- z 1) x y)))))
(defun tak63 (x y z)
   (cond ((>= y x) z)
         (t (tak64 (tak68 (- x 1) y z)
                   (tak4 (- y 1) z x)
                   (tak88 (- z 1) x y)))))
(defun tak64 (x y z)
   (cond ((>= y x) z)
         (t (tak65 (tak5 (- x 1) y z)
                   (tak15 (- y 1) z x)
                   (tak5 (- z 1) x y)))))
(defun tak65 (x y z)
   (cond ((>= y x) z)
         (t (tak66 (tak42 (- x 1) y z)
                   (tak26 (- y 1) z x)
                   (tak22 (- z 1) x y)))))
(defun tak66 (x y z)
   (cond ((>= y x) z)
         (t (tak67 (tak79 (- x 1) y z)
                   (tak37 (- y 1) z x)
                   (tak39 (- z 1) x y)))))
(defun tak67 (x y z)
   (cond ((>= y x) z)
         (t (tak68 (tak16 (- x 1) y z)
                   (tak48 (- y 1) z x)
                   (tak56 (- z 1) x y)))))
(defun tak68 (x y z)
   (cond ((>= y x) z)
         (t (tak69 (tak53 (- x 1) y z)
                   (tak59 (- y 1) z x)
                   (tak73 (- z 1) x y)))))
(defun tak69 (x y z)
   (cond ((>= y x) z)
         (t (tak70 (tak90 (- x 1) y z)
                   (tak70 (- y 1) z x)
                   (tak90 (- z 1) x y)))))
(defun tak70 (x y z)
   (cond ((>= y x) z)
         (t (tak71 (tak27 (- x 1) y z)
                   (tak81 (- y 1) z x)
                   (tak7 (- z 1) x y)))))
(defun tak71 (x y z)
   (cond ((>= y x) z)
         (t (tak72 (tak64 (- x 1) y z)
                   (tak92 (- y 1) z x)
                   (tak24 (- z 1) x y)))))
(defun tak72 (x y z)
   (cond ((>= y x) z)
         (t (tak73 (tak1 (- x 1) y z)
                   (tak3 (- y 1) z x)
                   (tak41 (- z 1) x y)))))
(defun tak73 (x y z)
   (cond ((>= y x) z)
         (t (tak74 (tak38 (- x 1) y z)
                   (tak14 (- y 1) z x)
                   (tak58 (- z 1) x y)))))
(defun tak74 (x y z)
   (cond ((>= y x) z)
         (t (tak75 (tak75 (- x 1) y z)
                   (tak25 (- y 1) z x)
                   (tak75 (- z 1) x y)))))
(defun tak75 (x y z)
   (cond ((>= y x) z)
         (t (tak76 (tak12 (- x 1) y z)
                   (tak36 (- y 1) z x)
                   (tak92 (- z 1) x y)))))
(defun tak76 (x y z)
   (cond ((>= y x) z)
         (t (tak77 (tak49 (- x 1) y z)
                   (tak47 (- y 1) z x)
                   (tak9 (- z 1) x y)))))
(defun tak77 (x y z)
   (cond ((>= y x) z)
         (t (tak78 (tak86 (- x 1) y z)
                   (tak58 (- y 1) z x)
                   (tak26 (- z 1) x y)))))
(defun tak78 (x y z)
   (cond ((>= y x) z)
         (t (tak79 (tak23 (- x 1) y z)
                   (tak69 (- y 1) z x)
                   (tak43 (- z 1) x y)))))
(defun tak79 (x y z)
   (cond ((>= y x) z)
         (t (tak80 (tak60 (- x 1) y z)
                   (tak80 (- y 1) z x)
                   (tak60 (- z 1) x y)))))
(defun tak80 (x y z)
   (cond ((>= y x) z)
         (t (tak81 (tak97 (- x 1) y z)
                   (tak91 (- y 1) z x)
                   (tak77 (- z 1) x y)))))
(defun tak81 (x y z)
   (cond ((>= y x) z)
         (t (tak82 (tak34 (- x 1) y z)
                   (tak2 (- y 1) z x)
                   (tak94 (- z 1) x y)))))
(defun tak82 (x y z)
   (cond ((>= y x) z)
         (t (tak83 (tak71 (- x 1) y z)
                   (tak13 (- y 1) z x)
                   (tak11 (- z 1) x y)))))
(defun tak83 (x y z)
   (cond ((>= y x) z)
         (t (tak84 (tak8 (- x 1) y z)
                   (tak24 (- y 1) z x)
                   (tak28 (- z 1) x y)))))
(defun tak84 (x y z)
   (cond ((>= y x) z)
         (t (tak85 (tak45 (- x 1) y z)
                   (tak35 (- y 1) z x)
                   (tak45 (- z 1) x y)))))
(defun tak85 (x y z)
   (cond ((>= y x) z)
         (t (tak86 (tak82 (- x 1) y z)
                   (tak46 (- y 1) z x)
                   (tak62 (- z 1) x y)))))
(defun tak86 (x y z)
   (cond ((>= y x) z)
         (t (tak87 (tak19 (- x 1) y z)
                   (tak57 (- y 1) z x)
                   (tak79 (- z 1) x y)))))
(defun tak87 (x y z)
   (cond ((>= y x) z)
         (t (tak88 (tak56 (- x 1) y z)
                   (tak68 (- y 1) z x)
                   (tak96 (- z 1) x y)))))
(defun tak88 (x y z)
   (cond ((>= y x) z)
         (t (tak89 (tak93 (- x 1) y z)
                   (tak79 (- y 1) z x)
                   (tak13 (- z 1) x y)))))
(defun tak89 (x y z)
   (cond ((>= y x) z)
         (t (tak90 (tak30 (- x 1) y z)
                   (tak90 (- y 1) z x)
                   (tak30 (- z 1) x y)))))
(defun tak90 (x y z)
   (cond ((>= y x) z)
         (t (tak91 (tak67 (- x 1) y z)
                   (tak1 (- y 1) z x)
                   (tak47 (- z 1) x y)))))
(defun tak91 (x y z)
   (cond ((>= y x) z)
         (t (tak92 (tak4 (- x 1) y z)
                   (tak12 (- y 1) z x)
                   (tak64 (- z 1) x y)))))
(defun tak92 (x y z)
   (cond ((>= y x) z)
         (t (tak93 (tak41 (- x 1) y z)
                   (tak23 (- y 1) z x)
                   (tak81 (- z 1) x y)))))
(defun tak93 (x y z)
   (cond ((>= y x) z)
         (t (tak94 (tak78 (- x 1) y z)
                   (tak34 (- y 1) z x)
                   (tak98 (- z 1) x y)))))
(defun tak94 (x y z)
   (cond ((>= y x) z)
         (t (tak95 (tak15 (- x 1) y z)
                   (tak45 (- y 1) z x)
                   (tak15 (- z 1) x y)))))
(defun tak95 (x y z)
   (cond ((>= y x) z)
         (t (tak96 (tak52 (- x 1) y z)
                   (tak56 (- y 1) z x)
                   (tak32 (- z 1) x y)))))
(defun tak96 (x y z)
   (cond ((>= y x) z)
         (t (tak97 (tak89 (- x 1) y z)
                   (tak67 (- y 1) z x)
                   (tak49 (- z 1) x y)))))
(defun tak97 (x y z)
   (cond ((>= y x) z)
         (t (tak98 (tak26 (- x 1) y z)
                   (tak78 (- y 1) z x)
                   (tak66 (- z 1) x y)))))
(defun tak98 (x y z)
   (cond ((>= y x) z)
        (t (tak99 (tak63 (- x 1) y z)
                  (tak89 (- y 1) z x)
                  (tak83 (- z 1) x y)))))
(defun tak99 (x y z)
   (cond ((>= y x) z)
         (t (takr (takr (- x 1) y z)
                  (takr (- y 1) z x)
                  (takr (- z 1) x y)))))
