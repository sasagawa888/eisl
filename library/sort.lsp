;;; written by M.Hiroi
;;; 

(defmodule sort
    (defpublic quick-sort (xs)
        (if (null xs)
            nil
            (let ((zs (partition (lambda (x) 
                                   (< x (car xs))) (cdr xs))))
               (append (quick-sort (car zs)) (cons (car xs) (quick-sort (cdr zs)))) )))
    (defun partition (pred xs)
        (for ((xs xs (cdr xs))
              (ys nil)
              (zs nil) )
             ((null xs)
              (cons (nreverse ys) (nreverse zs)) )
             (if (funcall pred (car xs))
                 (setq ys (cons (car xs) ys))
                 (setq zs (cons (car xs) zs)))))
    
    ;;; 要素を挿入する
    (defun insert-element (x xs)
        (cond ((null xs) (list x))
              ((<= x (car xs)) (cons x xs))
              (t (cons (car xs) (insert-element x (cdr xs))))))

    ;;; 挿入ソート
    (defpublic insert-sort (xs)
        (if (null xs)
            nil
            (insert-element (car xs) (insert-sort (cdr xs)))))

    ;;; 最小値を求める
    (defun minimum-sub (xs m)
        (if (null xs)
            m
            (minimum-sub (cdr xs) (if (< (car xs) m)
                                      (car xs)
                                      m))))

    (defun minimum (xs)
        (minimum-sub (cdr xs) (car xs)))
    ;;; 最初に見つけた要素をひとつ削除する
    (defun remove-element (x xs)
        (if (eql x (car xs))
            (cdr xs)
            (cons (car xs) (remove-element x (cdr xs)))))

    ;;; 選択ソート
    (defpublic select-sort (xs)
        (if (null xs)
            nil
            (let ((m (minimum xs)))
               (cons m (select-sort (remove-element m xs))))))
               
)
