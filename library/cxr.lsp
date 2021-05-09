;;;
;;; cxr.lsp : car と cdr の組み合わせ
;;;
;;;           Copyright (C) 2021 Makoto Hiroi
;;;

;;; ISLisp には car と cdr しかない
(defun caar (xs) (car (car xs)))
(defun cadr (xs) (car (cdr xs)))
(defun cdar (xs) (cdr (car xs)))
(defun cddr (xs) (cdr (cdr xs)))

(defun caaar (xs) (car (car (car xs))))
(defun caadr (xs) (car (car (cdr xs))))
(defun cadar (xs) (car (cdr (car xs))))
(defun caddr (xs) (car (cdr (cdr xs))))
(defun cdaar (xs) (cdr (car (car xs))))
(defun cdadr (xs) (cdr (car (cdr xs))))
(defun cddar (xs) (cdr (cdr (car xs))))
(defun cdddr (xs) (cdr (cdr (cdr xs))))

(defun caaaar (xs) (car (car (car (car xs)))))
(defun caaadr (xs) (car (car (car (cdr xs)))))
(defun caadar (xs) (car (car (cdr (car xs)))))
(defun caaddr (xs) (car (car (cdr (cdr xs)))))
(defun cadaar (xs) (car (cdr (car (car xs)))))
(defun cadadr (xs) (car (cdr (car (cdr xs)))))
(defun caddar (xs) (car (cdr (cdr (car xs)))))
(defun cadddr (xs) (car (cdr (cdr (cdr xs)))))
(defun cdaaar (xs) (cdr (car (car (car xs)))))
(defun cdaadr (xs) (cdr (car (car (cdr xs)))))
(defun cdadar (xs) (cdr (car (cdr (car xs)))))
(defun cdaddr (xs) (cdr (car (cdr (cdr xs)))))
(defun cddaar (xs) (cdr (cdr (car (car xs)))))
(defun cddadr (xs) (cdr (cdr (car (cdr xs)))))
(defun cdddar (xs) (cdr (cdr (cdr (car xs)))))
(defun cddddr (xs) (cdr (cdr (cdr (cdr xs)))))

(defun first   (xs) (car xs))
(defun second  (xs) (elt xs 1))
(defun third   (xs) (elt xs 2))
(defun fourth  (xs) (elt xs 3))
(defun fifth   (xs) (elt xs 4))
(defun sixth   (xs) (elt xs 5))
(defun seventh (xs) (elt xs 6))
(defun eigthth (xs) (elt xs 7))
(defun ninth   (xs) (elt xs 8))
(defun tenth   (xs) (elt xs 9))

;;; end-of-file