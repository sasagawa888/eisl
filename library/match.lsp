;;; pattern match
;;; under construction

(defmacro match (x body)
    (let ((vars (extract-variables body))
          (body (expand-body x body)))
        `(let ,vars ,body)))


(defun expand-body (x body)
    (list 'cond (expand-body1 x body)))

(defun expand-body1 (x body)
    (mapcar (lambda (y) (cons (list 'pattern-match x (car y)) (cdr y)))
            body)) 

;; e.g. _a _x  return T
(defun variablep (x)
    (and (symbolp x)
         (char= (car (convert (convert x <string>) <list>)) #\_)))

;; (((+ _a 2)...) ((* _b 3)...)) return ((_a nil)(_b nil))
(defun extract-variables (body)
    (mapc (lambda (x) (extract-variable (car x))) body))

;; e.g. (+ _a 2 _b) return ((_a nil)(_b nil))
(defun extract-variable (x)
    (cond ((null x) nil)
          ((consp (car x)) (append (extract-variable (car x))
                                 (extract-variable (cdr x))))
          ((variablep (car x)) (cons (list (car x) nil) (extract-variable (cdr x))))
          (t (extract-variable (cdr x)))))

;; e.g. (+ 1 2) (+ _a _b) eval (setq _a 1)(setq _b 2) and return env
;; e.g. (* 1 2) (+ _a _b) return nil
(defun pattern-match (x y env)
    (cond ((and (null x) (null y)) env)
          ((and (null x) (consp y)) 'no)
          ((and (consp y) (null y)) 'no)
          ((and (numberp x) (numberp y) (= x y)) env)
          ((and (characterp x) (characterp y) (char= x y)) env)
          ((and (stringp x) (stringp y) (string= x y)) env)
          ((and (variablep y) (not (member y env)))
           (progn (eval `(setq ,y ,x)) env))
          ((and (symbolp x) (symbolp y) (eq x y)) env)
          ((and (consp x) (consp y))
           (let ((env1 (pattern-match (car x) (car y) env)))
                    (if (eq env1 'no)
                        'no
                        (pattern-match (cdr x) (cdr y) env1))))
          (t 'no)))
