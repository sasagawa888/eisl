;;;
;;; combination.lsp : ISLisp 用順列と組み合わせ (改訂 2021/05/18)
;;;
;;;                   Copyright (C) 2016-2021 Makoto Hiroi
;;;

;;;
;;; 要素の選択 : 選んだ要素は CAR に、残りの要素は CDR に格納される
;;;
(defun selects (xs)
  (if (null (cdr xs))
      (list (list (car xs)))
    (cons (cons (car xs) (cdr xs))
	  (mapcar (lambda (ys) (cons (car ys) (cons (car xs) (cdr ys))))
		  (selects (cdr xs))))))

;;;
;;; 順列
;;;

;;; 高階関数版
(defun permutation (fn n xs)
  (labels ((perm (n xs a)
	     (if (= n 0)
		 (funcall fn (reverse a))
	       (mapc (lambda (ys)
		       (perm (- n 1) (cdr ys) (cons (car ys) a)))
		     (selects xs)))))
    (perm n xs nil)
    nil))

;;; リストに格納して返す
(defun permutations (n xs)
  (if (= n 0)
      '(())
    (mapcan (lambda (ys)
	      (mapcar (lambda (zs) (cons (car ys) zs))
		      (permutations (- n 1) (cdr ys))))
	    (selects xs))))

;;; 重複順列 (高階関数版)
(defun permutation-with-repetition (fn n xs)
  (labels ((perm (n xs a)
	     (if (= n 0)
		 (funcall fn (reverse a))
	       (mapc (lambda (y)
		       (perm (- n 1) xs (cons y a)))
		     xs))))
    (perm n xs nil)
    nil))

;;; 重複順列 (リストに格納して返す)
(defun permutations-with-repetition (n xs)
  (if (= n 0)
      '(())
    (mapcan (lambda (x)
	      (mapcar (lambda (ys) (cons x ys))
		      (permutations-with-repetition (- n 1) xs)))
	    xs)))

;;;
;;; 組み合わせ
;;;

;;; 組み合わせの数
(defun combination-number (n r)
  (if (or (= n r) (= r 0))
      1
    (div (* (combination-number n (- r 1)) (+ (- n r) 1)) r)))

;;; 高階関数版
(defun combination (fn n xs)
  (labels ((comb (n xs ys)
	     (cond
	      ((= n 0)
	       (funcall fn (reverse ys)))
	      ((null xs) nil)
	      (t
	       (comb (- n 1) (cdr xs) (cons (car xs) ys))
	       (comb n (cdr xs) ys)))))
    (comb n xs nil)))

;;; リストに格納して返す
(defun combinations (n xs)
  (cond
   ((= n 0) '(()))
   ((null xs) nil)
   (t
    (append
     (mapcar (lambda (ys) (cons (car xs) ys))
	     (combinations (- n 1) (cdr xs)))
     (combinations n (cdr xs))))))

;;; 重複組み合わせ (高階関数版)
(defun combination-with-repetition (fn n xs)
  (labels ((comb (n xs ys)
	     (cond
	      ((= n 0)
	       (funcall fn (reverse ys)))
	      ((null xs) nil)
	      (t
	       (comb (- n 1) xs (cons (car xs) ys))
	       (comb n (cdr xs) ys)))))
    (comb n xs nil)))

;;; 重複組み合わせ (リストに格納して返す)
(defun combinations-with-repetition (n xs)
  (cond
   ((= n 0) '(()))
   ((null xs) nil)
   (t
    (append
     (mapcar (lambda (ys) (cons (car xs) ys))
	     (combinations-with-repetition (- n 1) xs))
     (combinations-with-repetition n (cdr xs))))))
