

(defun pair-with (x lst)
  (if (null lst)
      nil
      (cons (list x (car lst))
            (pair-with x (my-cdr lst)))))

(defun combinations-2-rec (head tail)
  (if (null head)
      nil
      (append (pair-with (car head) tail)
              (combinations-2-rec (my-cdr head) (my-cdr tail)))))

(defun combinations-2 (lst)
  (combinations-2-rec lst (my-cdr lst)))

(defun my-cdr (x)
  (if (null x) nil (cdr x)))