;; test for distribute parallel

(defun ptarai(x y z)
  (dp-call tarai (tarai (- x 1) y z)
                 (tarai (- y 1) z x)
                 (tarai (- z 1) x y)))
                 
(defun tarai(x y z)
  (if (<= x y)
      y
      (tarai (tarai (- x 1) y z)
             (tarai (- y 1) z x)
             (tarai (- z 1) x y))))