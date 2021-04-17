;;; pattern match
;;; under construction
;;; (match x
;;;      ((+ _a _b) (+ _a 2))
;;;      ((- _a _a) (- _a 3)))
;;;    expand
;;;  (let ((_a nil)
;;;        (_b nil))
;;;     (cond ((and (eq (car x) '+) (setq _a (car (cdr x))) (setq _b (car (cdr (cdr x))))
;;;            (+ _a _2))
;;;           ((and (eq (car x) '0) (setq _a (car (cdr x))) (equal _a (car (cdr (cdr x))))
;;;            (- _a 3)))))    

(defmacro match (x :rest body)
    (let ((vars (extract-variables body nil nil))
          (body1 (expand-body x body)))
        `(let ,vars ,body1)))


(defun expand-body (x body)
    (cons 'cond (expand-body1 x body)))

(defun expand-body1 (x body)
    (mapcar (lambda (y) (cons (cdr (expand-match x (car y) nil nil)) (cdr y)))
            body)) 

;; e.g. _a _x  return T
(defun variablep (x)
    (and (symbolp x)
         (char= (car (convert (convert x <string>) <list>)) #\_)))

;; (((+ _a 2)...) ((* _b 3)...)) return ((_a nil)(_b nil))
(defun extract-variables (body var ans)
    (cond ((and (null body) (null var)) (reverse ans))
          ((null var) (extract-variables (cdr body) (extract-variable (car (car body))) ans))
          ((not (member (car var) ans)) (extract-variables body (cdr var) (cons (car var) ans)))
          (t (extract-variables body (cdr var) ans))))

;; e.g. (+ _a 2 _b) return ((_a nil)(_b nil))
(defun extract-variable (x)
    (cond ((null x) nil)
          ((consp (car x)) (append (extract-variable (car x))
                                 (extract-variable (cdr x))))
          ((variablep (car x)) (cons (list (car x) nil) (extract-variable (cdr x))))
          (t (extract-variable (cdr x)))))


;; e.g. x and (+ _a _b)  ans = (and (eq (car x) '+) (setq _a (car (cdr x)) (setq _b (car (cdr (cdr x))))
;; env = (_a _b)
;; return (env . ans)
(defun expand-match (x y env ans)
    (cond ((null y) (cons env (cons 'and (reverse ans))))
          ((numberp y) (cons env (cons (list '= x y) ans)))
          ((characterp y) (cons env (cons (list 'char= x y) ans)))
          ((stringp y) (cons env (cons (list 'string= x y) ans)))
          ((and (variablep y) (not (member y env)))
           (cons (cons y env) (cons (list 'setq y x) ans)))
          ((and (variablep y) (member y env))
           (cons env (cons (list 'equal x y) ans)))
          ((symbolp y) (cons env (cons (list 'eq x (list 'quote y)) ans)))
          ((and (consp y) (eq (car y) ':rest))
            (cons env (cons 'and (reverse (cons (list 'setq (car (cdr y)) x) ans)))))
          ((consp y)
           (let ((res (expand-match (list 'car x) (car y) env ans)))
                    (expand-match (list 'cdr x) (cdr y) (car res) (cdr res))))))
