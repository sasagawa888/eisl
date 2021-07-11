;; exercise from Recursion's video

(defun str-swap (str)
    (let* ((len (length str))
           (n (div len 2))
           (temp nil))
        (for ((i 0 (+ i 1)))
             ((>= i n) str)
             (setq temp (elt str i))
             (setf (elt str i) (elt str (- len i 1)))
             (setf (elt str (- len i 1)) temp))))


(defun str-recur (str)
    (let* ((len (length str))
           (n (div len 2)))
        (str-recur1 str 0 n len)))

(defun str-recur1 (str i n len)
    (cond ((>= i n) str)
          (t (let ((temp nil))
                (setq temp (elt str i))
                (setf (elt str i) (elt str (- len i 1)))
                (setf (elt str (- len i 1)) temp)
                (str-recur1 str (+ i 1) n len)))))


(defun twocomplement (str)
    (list-to-string (complement1 (convert str <list>))))

(defun twocomplement1 (ls)
    (cond ((null ls) nil)
          ((char= (car ls) #\0)
           (cons #\1 (twocomplement1 (cdr ls))))
          ((char= (car ls) #\1)
           (cons #\0 (twocomplement1 (cdr ls))))))

(defun list-to-string (ls)
    (if (null ls)
        ""
        (string-append (convert (car ls) <string>) 
                       (list-to-string (cdr ls)))))
        