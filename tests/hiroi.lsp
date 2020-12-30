;　クイックソート
; written by M.hiroi

(defun find-if (pred xs)
  (block exit
    (for ((xs xs (cdr xs)))
         ((null xs))
         (if (funcall pred (car xs))
             (return-from exit (car xs))))))

(defglobal a #\0)

(defun quick-sort (xs)
  (if (null xs)
      nil
    (let ((zs (partition (lambda (x) (> x (car xs))) (cdr xs))))
      (append (quick-sort (car zs))
              (cons (car xs) (quick-sort (cdr zs)))))))

(defun partition (pred xs)
  (for ((xs xs (cdr xs))
        (ys nil)
        (zs nil))
       ((null xs) (cons (nreverse ys) (nreverse zs)))
       (if (funcall pred (car xs))
           (setq ys (cons (car xs) ys))
         (setq zs (cons (car xs) zs)))))

;; nreverse  and reverse