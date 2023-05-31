;;; ramanujan's taxi-number

(import "combination")
(import "list")

;; (permutation #'taxi-number 4 (iota 1 12))

(defun taxi-number (ls)
    (if (taxi-number-p ls)
        (print ls)))

(defun taxi-number-p (ls)
    (let ((a (elt ls 0))
          (b (elt ls 1))
          (c (elt ls 2))
          (d (elt ls 3)))
      (= (+ (expt a 3) (expt b 3))
         (+ (expt c 3) (expt d 3)))))



