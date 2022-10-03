(import "test")

(defun elementp (x :rest y)
    (if (not (listp x)) (*error))
    (elementp1 x y))

(defun elementp1 (x y)
    (cond ((null y) t)
          ((and (symbolp (car y))(member (car y) x)) (elementp1 x (cdr y)))
          ((and (listp (car y))(membern (elt (car y) 0) (elt (car y) 1) x)) (elementp1 x (cdr y)))
          (t nil)))

(defun membern (n x ls)
    (cond ((= n 0) t)
          ((member x ls) (membern (- n 1) x (cdr (member x ls))))
          (t nil)))


(defun modify (x :rest y)
    (if (not (listp x)) (*error ))
    (modify1 x y))

(defun modify1 (x y)
    (cond ((null y) x)
          ((and (listp (car y))(eq (elt (car y) 0) '+)(symbolp (elt (car y) 1)))
           (modify1 (addn 1 x (elt (car y) 1)) (cdr y)))
          ((and (listp (car y))(eq (elt (car y) 0) '+)(listp (elt (car y) 1)))
           (modify1 (addn (elt (elt (car y) 1) 0) x (elt (elt (car y) 1) 1)) (cdr y)))
          ((and (listp (car y))(eq (elt (car y) 0) '-)(symbolp (elt (car y) 1)))
           (modify1 (removen 1 x (elt (car y) 1)) (cdr y)))
          ((and (listp (car y))(eq (elt (car y) 0) '-)(listp (elt (car y) 1)))
           (modify1 (removen (elt (elt (car y) 1) 0) x (elt (elt (car y) 1) 1)) (cdr y)))))

(defun addn (n x y)
    (cond ((= n 0) x)
          (t (addn (- n 1) (cons y x) y))))

(defun removen (n x y)
    (cond ((= n 0) x)
          (t (removen (- n 1) (remove1 x y) y))))

(defun remove1 (x y)
    (cond ((null x) nil)
          ((eq (car x) y) (remove1 (cdr x) y))
          (t (cons (car x) (remove1 (cdr x) y)))))


($test (elementp '(a b c) 'a) t)
($test (elementp '(a b c) 'c) t)
($test (elementp '(a b c) 'c 'a) t)
($test (elementp '(a b c) 'c '(2 a)) nil)
($test (elementp '(a b a c) 'c '(2 a)) t)
($test (elementp '(a b a c) 'c '(2 a) 'b) t)


($test (modify '(a b c) '(+ (3 d))) (d d d a b c))
($test (modify '(a b c) '(- (1 c))) (a b))
($test (modify '(a b c) '(- (1 d))) (a b c))
($test (modify '(a b c) '(-  b)) (a c))
($test (modify '(a b c) '(-  b) '(- a)) (c))