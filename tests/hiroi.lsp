;; test from M.Hiroi home page

;; 組み合わせをリストに格納して返す
(defun combinations (n xs)
    (labels ((comb (n xs ys zs)
               (cond ((= n 0) (cons (reverse ys) zs))
                     ((null xs) zs)
                     (t (comb (- n 1) (cdr xs) (cons (car xs) ys) (comb n (cdr xs) ys zs))) )))
        (comb n xs nil nil)))
