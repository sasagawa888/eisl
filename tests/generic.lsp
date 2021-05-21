;;; 
;;; generic function compile test
;;; alpha convert variables of eash method


(defgeneric hash-func (k))

(defmethod hash-func ((s <string>))
  (for ((i 0 (+ i 1))
        (a 0))
       ((>= i (length s)) a)
       (setq a (+ (* a 8) (convert (elt s i) <integer>)))))
