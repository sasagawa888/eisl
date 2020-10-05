;; when n is kakrekar-number t else nil
(defun kaprekarp (n)
    (let* ((ls (number-to-list n))
            (a (list-to-number (sort ls #'>)))
            (b (list-to-number (sort ls #'<))))
        (= n (- a b))))

;; when digits of n is 4, stop at kaprekar number 
(defun kaprekar (n)
    (let* ((ls (number-to-list n))
            (a (list-to-number (sort ls #'>)))
            (b (list-to-number (sort ls #'<))))
        (cond ((= n (- a b)) t)
              (t (print (- a b)) (kaprekar (- a b))))))

;; insert sort
(defun sort (x fun)
    (sort1 x nil fun))

(defun sort1 (x y fun)
    (if (null x)
        y
        (sort1 (cdr x) (insert (car x) y fun) fun)))

(defun insert (x ls fun)
    (cond ((null ls) (cons x ls))
          ((not (funcall fun x (car ls))) (cons (car ls) (insert x (cdr ls) fun)))
          (t (cons x ls))))
;; e.g. [1,2,3] -> 123
(defun list-to-number(ls)
    (list-to-number1 ls 0))

(defun list-to-number1 (ls n)
    (if (null ls)
        n
        (list-to-number1 (cdr ls) (+ (car ls) (* n 10)))))

;; e.g. 123 -> [1,2,3]
(defun number-to-list (n)
    (if (< n 10)
        (list n)
        (append (number-to-list (div n 10)) (list (mod n 10)))))

