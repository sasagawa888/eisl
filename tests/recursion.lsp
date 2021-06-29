;; exercise from Recursion's video

(defun str-swap (str)
    (let* ((len (length str))
           (n (div len 2))
           (temp nil))
        (for ((i 0 (+ i 1)))
             ((> i n) str)
             (setq temp (elt str i))
             (setf (elt str i) (elt str (- len i 1)))
             (setf (elt str (- len i 1)) temp))))