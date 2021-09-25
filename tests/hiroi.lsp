;;; 組み合わせの生成
(defun combination (fn n r :rest a)
    (if (null a)
        (setq a 0)
        (setq a (car a)) )
    (cond ((zerop r) (funcall fn a))
          ((zerop n) nil)
          (t (combination fn (1- n) r a) (combination fn (1- n) (1- r) (logior (ash 1 (1- n)) a)))))
