;;; ramanujan's taxi-number
;;; 1729 = 9^3+10^3 = 1^3+12^3
(import "combination")
(import "list")

;; (permutation #'taxi-number 4 (iota 1 12))

(defun taxi-number (ls)
    (let ((a (elt ls 0))
          (b (elt ls 1))
          (c (elt ls 2))
          (d (elt ls 3)))
      (if (= (+ (expt a 3) (expt b 3))
             (+ (expt c 3) (expt d 3)))
          (format (standard-output) 
                "~D ~A ~%" 
                (+ (expt a 3)(expt b 3)) ls)))) 
          
