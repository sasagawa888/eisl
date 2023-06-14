;;;
;;; list.lsp : ISLisp 用リスト操作関数
;;;
;;;            Copyright (C) 2016-2021 Makoto Hiroi
;;;
(import "macro")

;;; 末尾のセル
(defun last-pair (xs)
  (for ((xs xs (cdr xs)))
       ((null (cdr xs)) xs)))

;;; 末尾の要素
(defun last (xs) (car (last-pair xs)))

;;; 先頭から n 個の要素を取り出す
(defun take (xs n)
  (for ((xs xs (cdr xs))
	(n n (- n 1))
	(a nil (cons (car xs) a)))
       ((= n 0) (nreverse a))))

;;; 先頭から n 個の要素を取り除く
(defun drop (xs n)
  (for ((xs xs (cdr xs))
	(n n (- n 1)))
       ((= n 0) xs)))

;;;
;;; 連結 : ISLisp には append と nconc がある
;;;

;;; xs を反転して ys と連結する
(defun revappend (xs ys)
  (dolist (x xs ys) (push x ys)))

;;;
;;; コピーと置換
;;;
(defun copy-tree (tree)
  (cond
   ((consp tree)
    (cons (copy-tree (car tree))
	  (copy-tree (cdr tree))))
   (t tree)))

(defun copy-list (xs)
  (let ((zs nil))
    (dolist (x xs (nreverse zs))
      (push x zs))))

(defun copy-alist (xs)
  (let ((zs nil))
    (dolist (x xs (nreverse zs))
      (push (cons (car x) (cdr x)) zs))))

(defun subst-if (new pred tree)
  (cond
   ((funcall pred tree) new)
   ((consp tree)
    (cons (subst-if new pred (car tree))
	  (subst-if new pred (cdr tree))))
   (t tree)))

(defun subst (new old tree)
  (subst-if new (lambda (x) (eql x old)) tree))

(defun subst-if-not (new pred tree)
  (subst-if new (lambda (x) (not (funcall pred x))) tree))

;;;
;;; リストの生成: ISLisp には create-list がある
;;;
(defun iota (n m)
  (for ((m m (- m 1))
	(a nil))
       ((> n m) a)
       (push m a)))

(defun tabulate (f n m)
  (for ((m m (- m 1))
	(a nil))
       ((> n m) a)
       (push (funcall f m) a)))

;;; 解きほぐし (末尾再帰ではない)
(defun unfold (p f g seed)
  (if (funcall p seed)
      nil
    (cons (funcall f seed) (unfold p f g (funcall g seed)))))

;;;
;;; 畳み込み
;;;

;;; 先頭から
(defun fold-left-1 (f a xs)
  (dolist (x xs a) (setq a (funcall f a x))))

(defun fold-left (f a xs &rest args)
  (if (null args)
      (fold-left-1 f a xs)
    (for ((ys (cons xs args) (mapcar #'cdr ys))
	  (a a (apply f a (mapcar #'car ys))))
	 ((member nil ys) a))))

;;; 末尾から (末尾再帰ではない)
(defun fold-right-1 (f a xs)
  (if (null xs)
      a
    (funcall f (fold-right-1 f a (cdr xs)) (car xs))))

(defun fold-right-n (f a xss)
  (if (member nil xss)
      a
    (apply f (fold-right-n f a (mapcar #'cdr xss)) (mapcar #'car xss))))

(defun fold-right (f a xs &rest args)
  (if (null args)
      (fold-right-1 f a xs)
    (fold-right-n f a (cons xs args))))

;;;
;;; 巡回
;;;
(defun for-each (f xs &rest args)
  (if (null args)
      (dolist (x xs) (funcall f x))
    (for ((ys (cons xs args) (mapcar #'cdr ys)))
	 ((member nil ys))
	 (apply f (mapcar #'car ys)))))

#| 
(defmacro for-each (f xs &rest args)
  `(mapcan ,f ,xs ,@args))
;;; modified by sasagawa
;;; for compiled code
|#

;;;
;;; 分割
;;;
(defun partition (pred xs)
  (let ((ys nil) (zs nil))
    (dolist (x xs (list (nreverse ys) (nreverse zs)))
      (if (funcall pred x)
	  (push x ys)
	(push x zs)))))

;;;
;;; 述語 (リスト専用)
;;;
(defun any-1 (pred xs)
  (dolist (x xs)
    (if (funcall pred x) (return t))))

(defun any-n (pred xss)
  (block
      exit
    (for ((xss xss (mapcar #'cdr xss)))
	 ((member nil xss))
	 (when
	     (apply pred (mapcar #'car xss))
	   (return-from exit t)))))

(defun any (pred xs &rest args)
  (if (null args)
      (any-1 pred xs)
    (any-n pred (cons xs args))))

(defun all-1 (pred xs)
  (dolist (x xs t)
    (unless (funcall pred x) (return))))

(defun all-n (pred xss)
  (block
      exit
    (for ((xss xss (mapcar #'cdr xss)))
	 ((member nil xss) t)
	 (unless
	     (apply pred (mapcar #'car xss))
	   (return-from exit nil)))))

(defun all (pred xs &rest args)
  (if (null args)
      (all-1 pred xs)
    (all-n pred (cons xs args))))

;;;
;;; 集合演算
;;;

;;;
;;; 検査 : member は ISLisp にある
;;;
(defun member-if (pred xs)
  (block
      exit
    (for ((xs xs (cdr xs)))
	 ((null xs))
	 (when
	     (funcall pred (car xs))
	   (return-from exit xs)))))

(defun member-if-not (pred xs)
  (member-if (lambda (x) (not (funcall pred x))) xs))

;;; 重複要素を削除する
(defun remove-duplicates (xs)
  (let ((ys nil))
    (dolist (x xs (nreverse ys))
      (unless
	  (member x ys)
	(push x ys)))))

;;; 和集合
(defun union (xs ys)
  (let ((zs nil))
    (dolist (x xs (revappend zs ys))
      (unless
	  (member x ys)
	(push x zs)))))

;;; 積集合
(defun intersection (xs ys)
  (let ((zs nil))
    (dolist (x xs (nreverse zs))
      (when
	  (member x ys)
	(push x zs)))))

;;; 差集合
(defun difference (xs ys)
  (let ((zs nil))
    (dolist (x xs (nreverse zs))
      (unless
	  (member x ys)
	(push x zs)))))

;;; 部分集合
(defun subsetp (xs ys)
  (dolist (x xs t)
    (unless
	(member x ys)
      (return nil))))

;;;
;;; 連想リスト : ISLisp には assoc がある
;;;
(defun acons (k v alist)
  (cons (cons k v) alist))

(defun pairlis (ks vs alist)
  (fold-right (lambda (a k v) (acons k v a)) alist ks vs))

(defun assoc-if (pred xs)
  (dolist (x xs)
    (if (funcall pred (car x)) (return x))))

(defun assoc-if-not (pred xs)
  (assoc-if (lambda (x) (not (funcall pred x))) xs))

(defun rassoc-if (pred xs)
  (dolist (x xs)
    (if (funcall pred (cdr x)) (return x))))

(defun rassoc (v xs)
  (rassoc-if (lambda (x) (eql x v)) xs))

(defun rassoc-if-not (pred xs)
  (rassoc-if (lambda (x) (not (funcall pred x))) xs))

;;; end-of-file