;;;
;;; kakko.lsp : カッコ列の問題
;;;
;;;             Copyright (C) 2021 Makoto Hiroi
;;;
(import "cxr")
(import "seq")
(import "macro")
(import "combination")

;;; 表示
(defun display (x)
    (format (standard-output) "~S~%" x) )


;;; カッコ列の判定
(defun kakko-p (s)
    (let ((l 0)
          (r 0) )
       (dolist
        (x (string->list s) (= l r))
        (case x
           ((#\() (incf l))
           ((#\)) (incf r) (when (< l r) (return nil)))
           (t (error "illegal character")) ))))

;;; カッコ列の生成
(defun create-kakko (f n)
    (labels ((kakko-sub (l r a)
               (cond ((and (= l r) (= r n)) (funcall f (list->string (reverse a))))
                     (t
                      (when (< l n) (kakko-sub (+ l 1) r (cons #\( a)))
                      (when (< r l) (kakko-sub l (+ r 1) (cons #\) a)))))))
        (kakko-sub 0 0 '())))

;;; 最後尾のセルを取り除く
(defun butlast (xs)
    (if (null (cdr xs))
        nil
        (cons (car xs) (butlast (cdr xs))) ))


;;; 二分木をカッコ列に変換
(defun tree->kakko (ls)
    (labels ((tree-kakko-sub (ls)
               (cond ((consp ls)
                      (append (list #\() (tree-kakko-sub (cadr ls)) (tree-kakko-sub (caddr ls))))
                     (t (list #\))))))
        (list->string (butlast (tree-kakko-sub ls)))))

;;; カッコ列を二分木に変換
(defun kakko->tree (ks)
    (labels ((kakko-sub (ls)
               (cond ((null ls) (list 'L nil))
                     ((eql (car ls) #\)) (list 'L (cdr ls)))
                     (t
                      (let* ((xs (kakko-sub (cdr ls)))
                             (ys (kakko-sub (cadr xs))) )
                          (list (list 'N (car xs) (car ys)) (cadr ys)))))))
        (kakko-sub (string->list ks))))

;;; カタラン数
(defun catalan-number (n)
    (div (combination-number (* n 2) n) (+ n 1)) )

